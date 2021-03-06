(define (make-table same-key?)
  (let ((local-table (list '*table*)))
    (define (assoc key records)
      (cond ((null? records) false)
            ((same-key? key (caar records)) (car records))
            (else (assoc key (cdr records)))))
    (define (lookup key-list)
      (define (iter key-list table)
        (let ((subtable (assoc (car key-list) (cdr table))))
          (if subtable
              (if (null? (cdr key-list))
                  (cdr subtable)
                  (iter (cdr key-list) subtable))
              false)))
      (if (list? key-list)
          (iter key-list local-table)
          (iter (list key-list) local-table)))
    (define (insert! key-list value)
      (define (iter key-list value table)
        (let ((subtable (assoc (car key-list) (cdr table))))
          (if subtable
              (if (null? (cdr key-list))
                  (set-cdr! subtable value)
                  (iter (cdr key-list) value subtable))
              (if (null? (cdr key-list))
                  (set-cdr! table
                            (cons (cons (car key-list) value)
                                  (cdr table)))
                  (let ((newtable (list (car key-list))))
                    (set-cdr! table
                              (cons newtable
                                    (cdr table)))
                    (iter (cdr key-list) value newtable)))))
        'ok)
      (if (list? key-list)
          (iter key-list value local-table)
          (iter (list key-list) value local-table)))
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc!) insert!)
            (else (error "Unkown operation -- TABLE" m))))
    dispatch))