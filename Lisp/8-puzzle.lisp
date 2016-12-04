(in-package :astar)

(defparameter achievement
  '((1 2 3) (8 -1 4) (7 6 5)))


(defun between (x y)
  (lambda (u)
    (and (>= u x) (<= u y))))

(defun locate-n (num)
  "locate num in a matrix"
  (lambda (mat)
    (loop named exit
       for line in mat
       for i from 0 do
         (loop for x in line
            for j from 0 do
              (if (= num x)
                  (return-from exit
                    (values i j)))))))


(defun next-grids (grid)
  (let* ((fn (locate-n -1))
         (rst nil))
    (multiple-value-bind (i j)
        (funcall fn grid)
      (let ((next-pos-list
             (list
              `(,(1- i) ,j)
              `(,(1+ i) ,j)
              `(,i ,(1- j))
              `(,i ,(1+ j))))
            (restrict-fn (between 0 2)))
        (mapcar (lambda (ok-pos)
                  (let ((next (copy-tree grid)))
                    (rotatef (nth j (nth i next))
                             (nth (second ok-pos)
                                  (nth (first ok-pos) next)))
                    next))
                (remove-if-not (lambda (pos)
                                 (and
                                  (funcall restrict-fn (first pos))
                                  (funcall restrict-fn (second pos))))
                               next-pos-list))))))

(defun matrix-diff (ideal-matrix)
  (lambda (matrix)
    (reduce #'+
            (mapcar (lambda (x y)
                      (if (= x y) 0 1))
                    (flatten matrix) (flatten ideal-matrix)))))

(defun achieve (ideal-matrix)
  (lambda (x)
    (= 0 (funcall (matrix-diff ideal-matrix)
                  x))))


(defun is-solvable (mat)
  "judge wether a matrix is solvable."
  (lett (fmat (remove -1 (flatten mat)))
    (zerop (mod
            (loop
               for i in (butlast fmat)
               for j in (cdr fmat)
               if (> i j)
               sum 1 into count
               finally (return count))
            2))))



(defun search! (initial achievement)
  (when (is-solvable initial)
    (path-traverse
     (a*-search (list (make-path :state initial))
                (achieve achievement)
                #'next-grids
                #'(lambda (&rest rst) 1)
                (matrix-diff achievement)
                #'equal))))

;;test.
(search! '((2 8 3) (1 6 4) (7 -1 5)) achievement)
(search! '((-1 1 3) (4 2 5) (7 8 6)) '((1 2 3) (4 5 6) (7 8 -1)))
(search! '((8 6 7) (2 5 4) (3 1 -1)) achievement)


(defun start-server (port)
  (usocket:socket-server "127.0.0.1" port #'(lambda (stream) (format stream "~a~%" "hello usocket"))))

(defun start-client (ip port)
  (let ((sock (usocket:socket-connect ip port)))
    (progn
      (force-output (usocket:socket-stream sock))
      (do ((line
            (read-line (usocket:socket-stream sock) nil)
            (read-line (usocket:socket-stream sock) nil)))
          ((not line))
        (format t "~A" line)))))


(defun start-echo-server (port)
  "Listening on a port for a message, and print the received message."
  (usocket:with-socket-listener (socket "127.0.0.1" port)
    (usocket:wait-for-input socket)
    (loop
       (usocket:with-connected-socket (connection (usocket:socket-accept socket))
         (format t "~a~%" (read-line (usocket:socket-stream connection)))
         (princ (search! '((2 8 3) (1 6 4) (7 -1 5)) achievement)
                     (usocket:socket-stream connection))

         ))))

(defun echo-serv ()
  (start-echo-server 9990))

(defun start-echo-client (port)
  "Connect to a server and send a message."
  (usocket:with-client-socket (socket stream "127.0.0.1" port)
    (format stream "Hello world!~%")
    (force-output stream)
    (print (read-line stream))))


