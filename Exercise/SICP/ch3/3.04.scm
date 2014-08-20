(load "3.03.scm")
(define (make-account balance password)
  (let ((error-count 0))
    (define (withdraw amount)
      (if (>= balance amount)
          (begin (set! balance (- balance amount))
                 balance)
          "Insufficient funds"))
    (define (deposit amount)
      (set! balance (+ balance amount))
      balance)
    (define (call-the-cops)
      (newline)
      (display "Call the cops."))
    (define (dispatch pwd m)
      (if (not (eq? pwd password))
          (if (= error-count 6)
              (call-the-cops)
              (begin
                (newline)
                (display "Incorrect password")
                (set! error-count (+ error-count 1))))
          (begin 
            (set! error-count 0)
            (cond ((eq? m 'withdraw) withdraw)
                  ((eq? m 'deposit) deposit)
                  (else (error "Unknown request -- MAKE_ACCOUNT"
                               m)))))
    dispatch)))