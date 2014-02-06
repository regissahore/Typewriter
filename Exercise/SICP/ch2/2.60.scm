(load "2.59.scm")
(define (adjoin-set x set)
    (if (element-of-set? x set)
        set
        (cons x set)))