(load "1.37.scm")
(define (tan-cf x k)
    (cont-frac (lambda (i) (if (= i 1)
                               x
                               (- (square x))))
               (lambda (i) (- (* i 2) 1.0))
               k))