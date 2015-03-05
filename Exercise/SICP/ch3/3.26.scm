(define (make-tree key value left right)
  (list key value left right))
(define (key-tree tree)
  (car tree))
(define (value-tree tree)
  (cadr tree))
(define (left-tree tree)
  (caddr tree))
(define (right-tree tree)
  (cadddr tree))
(define (empty-tree? tree)
  (null? tree))
(define (set-key-tree! tree value)
  (set-car! tree value))
(define (set-value-tree! tree value)
  (set-car! (cdr tree) value))
(define (set-left-tree! tree value)
  (set-car! (cddr tree) value))
(define (set-right-tree! tree value)
  (set-car! (cdddr tree) value))
(define (insert! tree key value compare)
  (if (empty-tree? tree)
      (make-tree key value '() '())
      (let ((result (compare key (key-tree tree))))
        (cond ((= 0 result)
               (set-value-tree! tree value)
               tree)
              ((= -1 result)
               (set-left-tree! (insert! (left-tree tree) key value compare))
               tree)
              ((= 1 result)
               (set-right-tree! (insert! (right-tree tree) key value compare))
               tree)))))
(define (find tree key compare)
  (if (empty-tree? tree)
      false
      (let ((result (compare key (key-tree tree))))
        (cond ((= 0 result) (value-tree tree))
              ((= -1 result) (find (left-tree tree) key compare))
              ((= 1 result) (find (right-tree tree) key compare))))))
(define (compare-number a b)
  (cond ((= a b) 0)
        ((< a b) -1)
        ((> a b) 1)))