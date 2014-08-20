(load "3.02.scm")
(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (dispatch pwd m)
    (if (not (eq? pwd password))
        (begin
          (newline)
          (display "Incorrect password"))
        (cond ((eq? m 'withdraw) withdraw)
              ((eq? m 'deposit) deposit)
              (else (error "Unknown request -- MAKE_ACCOUNT"
                           m)))))
  dispatch)