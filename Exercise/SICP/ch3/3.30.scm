(define (ripple-carry-adder A B C S)
  (define (iter a b c s)
    (if (null? a)
        'ok
        (let ((nextc (make-wire))
              (full-adder (car a) (car b) c (car s) nextc)
              (iter (cdr a) (cdr b) (get-signal nextc) (cdr s))))))
  (iter A B (get-signal C) S))