(define (pascal-triangle row col)
  (cond ((> col row) 0)
        ((or (= col 1) (= row 1)) 1)
        (else (+ (pascal-triangle (- row 1) col) 
                 (pascal-triangle (- row 1) (- col 1))))))
(pascal-triangle 5 4)