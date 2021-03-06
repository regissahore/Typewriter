(define (cube x) (* x x x))
(define (sum term a next b)
    (if (> a b)
        0
        (+ (term a)
           (sum term (next a) next b))))
(define (integral f a b dx)
    (define (add-dx x) (+ x dx))
    (* (sum f (+ a (/ dx 2.0)) add-dx b)
       dx))
(define (simpson f a b n)
    (define h (/ (- b a) n))
    (define dx (/ 1.0 n))
    (define (add-dx x) (+ x (* dx 2.0)))
    (define (simpson-sum x) (+ (f x) 
                               (* 4 (f (+ x dx)))
                               (f (+ x dx dx))))
    (* (sum simpson-sum a add-dx b) (/ h 3.0)))
(newline)
(display (integral cube 0 1 (/ 1.0 100)))
(newline)
(display (simpson cube 0 1 100))
(newline)
(newline)
(display (integral cube 0 1 (/ 1.0 1000)))
(newline)
(display (simpson cube 0 1 1000))