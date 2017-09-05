(define (f x)
 (define (even? m)
  (if (= m 0)
   true
   (odd? (- m 1))))
 (define (odd? n)
  (if (= n 0)
   false
   (even? (- n 1))))
 (even? x))

(f 1)
(f 2)
(f 3)
(f 4)
