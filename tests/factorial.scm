(define (factorials n)
  (cond ((= n 1) 1)
        (else (* n
               (factorials (- n 1))))))

(factorials 6)
