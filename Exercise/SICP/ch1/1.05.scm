(define (p) (p))
(define (test x y)
  (if (= x 0)
      0
      y))
(test 0 (p))
; Applicative-order: infinity loops.
; Normal-order: 0