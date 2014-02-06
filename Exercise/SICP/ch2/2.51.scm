(load "2.50.scm")
(define (below painter1 painter2)
    (let ((split-point (make-vect 0.0 0.5)))
        (let ((paint-top
                   (transform-painter painter1
                                      split-point
                                      (make-vect 1.0 0.5)
                                      (make-vect 0.0 1.0)))
              (paint-down
                   (transform-painter painter2
                                      (make-vect 0.0 0.0)
                                      (make-vect 1.0 0.0)
                                      split-point)))
              (lambda (frame)
                  (paint-top frame)
                  (paint-bottom frame)))))
(define (below painter1 painter)
    (rotate90 (beside (rotate270 painter1) 
                      (rotate270 painter2))))