(define (length2 lst)
  (cond ((null? lst) 0)
        (else (+ 1 (length2 (cdr lst))))))

(define (map2 f lst)
  (cond ((null? lst) lst)
        (else (cons (f (car lst)) (map2 f (cdr lst))))))

(define (filter2 p lst)
  (cond ((null? lst) lst)
        ((p (car lst)) (cons (car lst) (filter2 p (cdr lst))))
        ((not (p (car lst))) (filter2 p (cdr lst)))))

(define (foldl op nv lst)
  (cond ((null? lst) nv)
        (else (foldl op (op (car lst) nv) (cdr lst)))))

(define (foldr op nv lst)
  (cond ((null? lst) nv)
        (else (op (car lst) (foldr op nv (cdr lst))))))
