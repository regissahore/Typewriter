(load "2.40.scm")
(define (unique-trible n)
    (accumulate append
                (list)
                (map (lambda (i)
                         (map (lambda (j) (append (list i) j))
                              (unique-pairs (- i 1))))
                     (enumerate-interval 1 n))))