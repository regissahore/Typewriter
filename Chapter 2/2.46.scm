(define (make-vect x y) 
    (cons x y))
(define (xcor-vect vect) 
    (car vect))
(define (ycor-vect vect) 
    (cdr vect))
(define (add-vect x y)
    (make-vect (+ (xcor-vect x) (xcor-vect y))
               (+ (ycor-rect x) (ycor-vect y))))
(define (sub-vect x y)
    (make-vect (- (xcor-vect x) (xcor-vect y))
               (- (ycor-rect x) (ycor-vect y))))
(define (scale-vect scale vect)
    (make-vect (* scale (xcor-vect vect))
               (* scale (ycor-rect vect))))