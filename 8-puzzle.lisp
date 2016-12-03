(in-package :astar)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar achievement
    '((1 2 3) (8 -1 4) (7 6 5))))


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
