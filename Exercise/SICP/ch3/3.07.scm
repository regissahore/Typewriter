(load "3.06.scm")
(define (make-joint origin-dispatch origin-password new-password)
  (lambda (password op)
    (if (eq? password new-password)
        (origin-dispatch origin-password op)
        (begin
          (newline)
          (display "Wrong password")))))