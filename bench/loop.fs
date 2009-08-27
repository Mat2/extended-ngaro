assembler vocabulary

: loop-test ins inca 
                decb
                bnzb [ tail ], rts
; loop-test 
  constant loop-test-trace

: start ins lib [ 1000000000 ], lia [ 0 ], bi  [ loop-test-trace ],
            rts
; start 
  constant start-trace

: test start-trace aot . ; test bye 

