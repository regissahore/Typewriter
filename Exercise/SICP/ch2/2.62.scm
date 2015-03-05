(load "2.61.scm")
(define (union-set set1 set2)
  (cond ((null? set1) set2)
        ((null? set2) set1)
        ((< (car set1) (car set2)) (append (list (car set1)) (union-set (cdr set1) set2)))
        ((> (car set1) (car set2)) (append (list (car set2)) (union-set (cdr set2) set1)))
        (else (append (list (car set1)) (union-set (cdr set1) (cdr set2))))))