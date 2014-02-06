(define (reverse sequence)
    (fold-right (lambda (x y) (append y (list x))) (list) sequence))
(define (reverse sequence)
    (fold-left (lambda (x y) (append (list y) x)) (list) sequence))