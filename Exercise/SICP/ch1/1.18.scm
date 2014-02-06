(define (mul a b)
  (define (mul-iter a b c)
    (if (= b 0)
        c
        (if (even? b)
            (mul-iter (+ a a) (/ b 2) c)
            (mul-iter a (- b 1) (+ a c)))))
  (mul-iter a b 0))
(mul 9 11)