#lang racket
(define (equ? x y)
  (apply-generic 'equ? x y))
(define (=zero? x)
  (apply-generic '=zero? x))

(define (install-scheme-number-package)
  (define (tag x)
    (attach-tag 'scheme-number x))
  (put 'make 'scheme-number
       (lambda (x)
         (tag x)))
  (put 'equ? '(scheme-number scheme-number)
       (lambda (x y)
         (= x y)))
  (put '=zero? 'scheme-number
       (lambda (value)
         (= value 0)))
  'done)
(define (make-scheme-number n)
  ((get 'make 'scheme-number) n))

(define (install-rational-package)
  (define (numer x) (car x))
  (define (denom x) (cdr x))
  (define (make-rat n d) (cons n d))
  (define (tag x)
    (attach-tag 'rational x))
  (put 'make 'rational
       (lambda (n d)
         (tag (make-rat n d))))
  (put 'equ? '(rational rational)
       (lambda (x y)
         (and (= (numer x) (numer y))
              (= (denom x) (denom y)))))
  (put '=zero? 'rational
       (lambda (value)
         (= (numer r) 0)))
  'done)
(define (make-rational n d)
  ((get 'make 'rational) n d))