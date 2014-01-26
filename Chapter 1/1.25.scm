(load "1.16.scm")
(define (expmod base exp m)
  (remainder (fast-expt base exp) m))
; The multiplication of big integer is slow.