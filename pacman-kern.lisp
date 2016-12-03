(in-package :astar)

(defun between (x y)
  (lambda (u)
    (and (>= u x) (<= u y))))

(defparameter *board*
  '((* * * * * * * * *)
    (* * $ * * * * * *)
    (* * * * $ * * * *)
    (* * * $ $ * * * *)
    (* * $ * * * $ * *)
    (* $ * * * * * * *)
    (* * * * * $ * * *)
    (* * * * * * * * *)
    (* * * * * * * * *)))




(defparameter *board-size* '(9  9))


(defparameter *goal* '(8  8))



(defun eu-dist (cur goal)
  (flet ((sqr (x) (* x x)))
    (sqrt
     (+ (sqr (- (car cur) (car goal)))
        (sqr (- (cadr cur) (cadr goal)))))))

(defun distance (goal)
  (lambda (cur)
    (eu-dist cur goal)))

(defun next-yx (this-yx)
  (let* ((y (first this-yx))
         (x (second this-yx))
         (next-pos-list
          (list
           `(,y ,(1+ x))
           `(,y ,(1- x))
           `(,(1+ y) ,x)
           `(,(1- y) ,x)))
         (restrict-fn-y (between 0 (1- (car *board-size*))))
         (restrict-fn-x (between 0 (1- (cadr *board-size*)))))
    (remove-if-not (lambda (cell)
                     (and (funcall restrict-fn-y (first cell))
                          (funcall restrict-fn-x (second cell))
                          (eql '* (nth (cadr cell)
                                       (nth (car cell)
                                            *board*)))))
                   next-pos-list)))

(defun arrive (goal)
  (lambda (x)
    (equal x goal)))


(defun printpaths (paths)
  (print (reverse paths))
  (let ((origin (copy-tree *board*)))
    (loop for (y x) in paths do
         (setf (nth y (nth x *board*)) '^))
    (print *board*)
    (setf *board* origin)))



(defun search! (initial goal)
  (printpaths
    (path-traverse
     (a*-search (list (make-path :state initial))
                (arrive goal)
                #'next-yx
                #'(lambda (&rest rst) 1)
                (distance goal)
                #'equal))))

;;test
(search! '(0 0) *goal*)


