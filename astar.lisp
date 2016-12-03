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
  (defstruct (path (:print-function print-path))
    state (previous nil) (cost-so-far 0) (total-cost 0)))


(defun find-path (state paths state=)
  (find state paths :key #'path-state :test state=))

(defun better-path-p (path1 path2)
  (< (path-total-cost path1) (path-total-cost path2)))

(defun insert-path (path paths)
  (merge 'list (list path) paths #'< :key #'path-total-cost))

(defun path-traverse (path)
  (if (null path)
      nil
      (cons (path-state path)
            (path-traverse (path-previous path)))))


(defun a*-search (paths goal-p succ cost-fn cost-left-fn
                  &optional (state= #'eql) old-paths)
  (cond ((null paths) nil)
        ((funcall goal-p (path-state (first paths)))
         (values (first paths) paths))
        (t (let* ((path (pop paths))
                  (state (path-state path)))
             ;;put current path into old-paths
             (setf old-paths (insert-path path old-paths))
             (dolist (state2 (funcall succ state)) ;;state2: next state of cur state.
               (let* ((cost (+ (path-cost-so-far path)
                               (funcall cost-fn state state2)));;cost1
                      (cost2 (funcall cost-left-fn state2));;cost2
                      (path2 (make-path
                              :state state2 :previous path
                              :cost-so-far cost
                              :total-cost (+ cost cost2)));;path towards next state
                      (old nil))
                 (cond
                   ((setf old (find-path state2 paths state=));;the next state is alreadly in paths. get it's old val.
                    (when (better-path-p path2 old) ;; the new one is a better path.
                      (setf paths (insert-path path2
                                               (delete old paths)))));; ? renew the old path.

                   ((setf old (find-path state2 old-paths state=)) ;; the next state is already in old-paths. ?? what list?
                    (when (better-path-p path2 old);;get its old val.
                      (setf paths (insert-path path2 paths))
                      (setf old-paths (delete old old-paths))))
                   (t (setf paths (insert-path path2 paths))))))  ;;this is a brand new path.
             (a*-search paths goal-p succ cost-fn cost-left-fn
                        state= old-paths)))))






