(load "3.01.scm")
(define (make-monitored f)
  (let ((count 0))
    (define (mf val)
      (cond ((eq? val 'how-many-calls?) count)
            (else (begin
                    (set! count (+ count 1))
                    (f val)))))
    mf))