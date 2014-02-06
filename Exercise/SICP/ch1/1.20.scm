(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))
; Applicative-order
; (gcd 206 40)
; (gcd 40 6)
; (gcd 6 4)
; (gcd 4 2)
; (gcd 2 0)
; 2
; Normal-order
; (gcd 206 40)
; (gcd 40 (remainder 206 40))
; (if (= (remainder 206 40) 0) (remainder 206 40) (gcd 40 (remainder (remainder 206 40) 40)))
; ...