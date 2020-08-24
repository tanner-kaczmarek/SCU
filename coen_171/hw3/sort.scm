; vi:ai:lisp:sm
;

(define (filter f lst)
  (cond
    ((null? lst) lst)
    ((f (car lst))
     (cons (car lst) (filter f (cdr lst))))
    (else (filter f (cdr lst)))))


;(define (append l1 l2)
  ;(cond
    ;((null? l1) l2)
    ;(else (cons (car 1) (append (cdr l1) l2)))))

(define (quicksort lst)
     (if(null? lst) lst
     	(let*
          ((h (car lst))
	   (t (cdr lst))
	   (below (lambda (x) (< x h)))
	   (above (lambda (x) (>= x h)))
	   )
	  (append (quicksort (filter below t)) (cons h (quicksort(filter above t)))))))
