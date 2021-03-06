(define (or-gate a1 a2 output)
  (let ((invert1 (make-wire))
        (invert2 (make-wire))
        (and-invert (make-wire)))
    (inverter a1 invert1)
    (inverter a2 invert2)
    (and-gate invert1 invert2 and-invert)
    (inverter and-invert output))
  'ok)