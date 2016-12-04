(in-package :cl-user)
(defpackage astar-asd
  (:use :cl :asdf)
  (:export #:*astar-version*))

(in-package :astar-asd)
(defparameter *astar-version* "0.1")

(defsystem #:astar
  :serial t
  :version #.*astar-version*
  :author "NiwTR"
  :license "MIT"
  :depends-on (#:usocket
               #:excalibur)
  :components ((:file "package")
               (:file "astar")
               (:file "8-puzzle")
               (:file "pacman-kern")))

;;EOF

