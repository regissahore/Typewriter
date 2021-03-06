(load "2.40.scm")
(define (flatmap proc seq)
    (accumulate append (list) (map proc seq)))
(define (queens board-size)
    (define (queen-cols k)
        (if (= k 0)
            (list empty-board)
            (filter
                (lambda (positions)
                    (safe? k positions))
                (flatmap
                    (lambda (rest-of-queens)
                        (map (lambda (new-row)
                                 (adjoin-position new-row k rest-of-queens))
                             (enumerate-interval 1 board-size)))
                    (queen-cols (- k 1))))))
    (define empty-board (list))
    (define (adjoin-position new-row k rest-of-queens)
        (append (list new-row) rest-of-queens))
    (define (safe? k position)
        (define (check new old index)
            (if (null? old)
                #t
                (if (or (= new (car old))
                        (= new (+ (car old) index))
                        (= new (- (car old) index)))
                    #f
                    (check new (cdr old) (+ index 1)))))
        (check (car position) (cdr position) 1))
    (queen-cols board-size))
(queens 8)