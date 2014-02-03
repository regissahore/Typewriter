#lang planet neil/sicp
(define (make-accumulator sum)
  (lambda (x)
    (set! sum (+ sum x))
    sum))