(define (type-tag num)
  (cond ((number? num) 'scheme-number)
        ((pair? num) (car num))
        (else (error "TYPE-TAG" num))))
(define (contents num)
  (cond ((number? num) num)
        ((pair? num) (cdr num))
        (else (error "CONTENT" num))))
(define (attach-tag tag content)
  (if (number? content)
      content
      (cons tag content)))