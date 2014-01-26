(define (fr n)
  (if (< n 3)
      n
      (+ (fr (- n 1)) (* 2 (fr (- n 2))) (* 3 (fr (- n 3))))))
(define (fi n)
  (define (fi-iter a b c i)
    (if (= i n)
        c
        (fi-iter b c (+ (* 3 a) (* 2 b) c) (+ i 1))))
  (if (< n 3)
      n
      (fi-iter 0 1 2 2)))
(= (fr 10) (fi 10))