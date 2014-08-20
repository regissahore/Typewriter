(define (mul a b)
  (define (double n) (+ n n))
  (define (halve n) (/ n 2))
  (if (= b 0)
      0
      (if (even? b)
          (double (mul a (halve b)))
          (+ a (mul a (- b 1))))))
(mul 9 11)