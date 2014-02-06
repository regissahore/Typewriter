(load "3.05.scm")
(define rand
  (let ((x 7))
    (lambda (op)
        (cond ((eq? op 'generate) 
               (begin
                 (set! x (remainder (+ (* x 177)
                                       1777) 
                                    10009))
                 x))
              ((eq? op 'reset) (set! x 7))
              (else (error "Unknow operation -- RAND" op))))))