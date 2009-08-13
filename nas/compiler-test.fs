( Test des Assemblers und aller Ngaro Instruktionen )

: ln cr cr ;

: lits-test ins [ lits , 100 , lits , 28 , adds , rts , ] ; 
  lits-test constant lits-trace

: cas-taken ins [ lits , 1 , rts , ] ;
  cas-taken constant cas-taken-trace

: cas-test ins [ lits , 0 , cas , cas-taken-trace , rts , ] ;
  cas-test constant cas-trace

: compiler-test
        ln ." Testing trace-compiler:" ln

        ." LITS    result: " 0 lits-trace aot . cr ."      should be: 128" cr
        ." CAS     result: " 0  cas-trace aot . cr ."      should be: 1"   cr
;

