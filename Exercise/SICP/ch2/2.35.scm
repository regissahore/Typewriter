(load "2.33.scm")
(define (count-leaves t)
    (accumulate + 0 (map (lambda (sub)
                             (if (pair? sub)
                                 (count-leaves sub)
                                 1)) t)))