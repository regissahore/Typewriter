(load "3.04.scm")
(define (monte-carlo trials experiment)
  (define (iter trials-remaining trials-passed)
    (cond ((= trials-remaining 0)
           (/ trials-passed trials))
          ((experiment)
           (iter (- trials-remaining 1) (+ trials-passed 1)))
          (else
           (iter (- trials-remaining 1) trials-passed))))
  (iter trials 0))
(define (random-in-range low high)
  (let ((range (- high low)))
    (+ low (random range))))
(define (estimate-integral trials experiment x1 x2 y1 y2)
  (monte-carlo trials (lambda ()
                        (experiment (random-in-range x1 x2)
                                    (random-in-range y1 y2)))))
(define (estimate-pi trials)
  (* 4
     (exact->inexact (estimate-integral 
                      trials
                      (lambda (x y)
                        (< (+ (square x)
                              (square y))
                           1.0))
                        -1.0 1.0 -1.0 1.0))))