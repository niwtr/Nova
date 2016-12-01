(eval-when (:compile-toplevel :load-toplevel :execute)
  (ql:quickload :excalibur))


(defpackage :astar
  (:use :excalibur :cl-user :common-lisp))
(in-package :astar)

(defun print-path (path &optional (stream t) depth)
  (declare (ignore depth))
  (format stream "#<Path to ~a cost ~,1f>"
          (path-state path) (path-total-cost path)))


(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar achievement
    '((1 2 3) (8 -1 4) (7 6 5)))
  (defstruct (path (:print-function print-path))
    state (previous nil) (cost-so-far 0) (total-cost 0))
)

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


(defun between (x y)
  (lambda (u)
    (and (>= u x) (<= u y))))


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


(defun find-path (state paths state=)
  (find state paths :key #'path-state :test state=))

(defun better-path-p (path1 path2)
  (< (path-total-cost path1) (path-total-cost path2)))

(defun insert-path (path paths)
  (merge 'list (list path) paths #'< :key #'path-total-cost))

(defun path-states (path)
  (if (null path)
      nil
      (cons (path-state path)
            (path-states (path-previous path)))))


(defun a*-search (paths goal-p succ cost-fn cost-left-fn
                  &optional (state= #'eql) old-paths)
  (cond ((null paths) nil)
        ((funcall goal-p (path-state (first paths)))
         (values (first paths) paths))
        (t (let* ((path (pop paths))
                  (state (path-state path)))
             (setf old-paths (insert-path path old-paths))
             (dolist (state2 (funcall succ state))
               (let* ((cost (+ (path-cost-so-far path)
                               (funcall cost-fn state state2)))
                      (cost2 (funcall cost-left-fn state2))
                      (path2 (make-path
                              :state state2 :previous path
                              :cost-so-far cost
                              :total-cost (+ cost cost2)))
                      (old nil))
                 (cond
                   ((setf old (find-path state2 paths state=))
                    (when (better-path-p path2 old)
                      (setf paths (insert-path path2
                                               (delete old paths)))))

                   ((setf old (find-path state2 old-paths state=))
                    (when (better-path-p path2 old)
                      (setf paths (insert-path path2 paths))
                      (setf old-paths (delete old old-paths))))
                   (t (setf paths (insert-path path2 paths))))))
             (a*-search paths goal-p succ cost-fn cost-left-fn
                        state= old-paths)))))



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
    (path-states
     (a*-search (list (make-path :state initial))
                (achieve achievement)
                #'next-grids
                #'(lambda (&rest rst) 1)
                (matrix-diff achievement)
                #'equal))))

(search! '((2 8 3) (1 6 4) (7 -1 5)) achievement)
(search! '((-1 1 3) (4 2 5) (7 8 6)) '((1 2 3) (4 5 6) (7 8 -1)))
(search! '((8 6 7) (2 5 4) (3 1 -1)) achievement)
