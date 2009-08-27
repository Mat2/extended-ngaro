assembler vocabulary

: fib-loop  ins adda
                swps
                decd
                bnzd [ tail ], tba
                rts
; fib-loop  
  constant fib-loop-trace

: fib-start ins psad
                lia  [ 1 ], lib  [ 2 ], bi [ fib-loop-trace ], rts
; fib-start 
  constant fib-start-trace

: fib ( n - fib.n ) fib-start-trace aot ;

37 fib . bye 

