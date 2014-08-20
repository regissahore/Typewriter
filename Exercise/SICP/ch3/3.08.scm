(load "3.07.scm")
(define f
  (lambda (x)
      (set! f (lambda (y) 0))
      x))