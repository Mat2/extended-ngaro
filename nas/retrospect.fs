( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Retrospect by Charles Childers                              )
( This code is gifted to the public domain. Share freely.     )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( This contains a set of words I find useful while debugging  )
( code.                                                       )
(                                                             )
( Stack comments are provided for words which are intended    )
( to be used directly. Internal factors do not have the stack )
( comments provided.                                          )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ) 
( Mat: - Exchange opcodes with new mnemonic system from the   )
(        extended-instruction set for unification purposes.   )
(      - Added some new instructions for compilation and      )
(        execution of native-code traces                      )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ) 

{{
  variable *addr

  : nextOp    1 *addr +! 
  ;
  
  : @addr     *addr @ 
              @ 
  ;

  : .contents @addr . 
  ;

  : .addr     *addr @ 
              . 
  ;

  : .ascii dup 32 >if 
             dup 128 <if 
               39 emit emit 39 emit 0 
             then 
           then 
           drop 
  ;

  : render type cr drop ;

  : s: 32 accept 
       tib keepString literal, 
       ['] render compile 
       ` ;; 
  ;

  compiler: a: ` over 
               ` =if 
               s: 
               ` then 
  ;

  : .name d->name type cr ;
  
  : resolve -1 
            last @ 
            repeat 
              dup 
              d->xt @ @addr =if 
                .name drop 0 
              ;then 
              0; 
              @ 
            again 
  ;

  : render type 32 emit drop nextOp resolve 0; drop .contents cr ;
  
  : x: 32 accept tib keepString literal, ['] render compile ` ;; ;
  
  compiler: b: ` over 
               ` =if x: 
               ` then 
  ;

  : decompile
    32 emit
    @addr
     0 a: nop      1 b: lits      2 a: dups      3 a: drps
     4 a: swps     5 a: pshs      6 a: pops      7 b: cas
     8 b: bras     9 a: rts      10 b: bgrs     11 b: bles  
    12 b: bnes    13 b: beqs     14 a: ldsr     15 a: strs
    16 a: adds    17 a: subs     18 a: muls     19 a: divs
    20 a: ands    21 a: gors     22 a: xors     23 a: shls
    24 a: shrs    25 a: reqs     26 a: incs     27 a: decs
    28 a: ldps    29 a: stps     30 a: wait     31 a: ins
    32 a: aot     33 a: cofs     34 a: lia      35 a: psad
    36 a: psar    37 a: plda     38 a: plra     39 a: tda
    40 a: tra     41 a: tad      42 a: tar      43 a: tab
    44 a: tba     45 a: adda     46 a: suba     47 a: diva
    48 a: mula    49 a: inca     50 a: deca     51 a: anda
    52 a: gora    53 a: xora     54 a: shla     55 a: slia
    56 a: shra    57 a: sria     58 a: cmpa     59 a: ldra
    60 a: stra    61 a: lib      62 a: psbd     63 a: psbr
    64 a: pldb    65 a: plrb     66 a: tdb      67 a: trb
    68 a: addb    69 a: subb     70 a: divb     71 a: mulb
    72 a: incb    73 a: decb     74 a: andb     75 a: gorb
    76 a: xorb    77 a: cmpb     78 a: shlb     79 a: slib
    80 a: shrb    81 a: srib     82 a: ldrb     83 a: strb
    84 a: ci      85 a: cieq     86 a: cigr     87 a: cile
    88 a: cnza    89 a: ciza     90 a: cnzb     91 a: cizb
    92 a: cra     93 a: crb      94 a: bra      95 a: brb
    96 a: bi      97 a: bieq     98 a: bigr     99 a: bile
   100 a: bnza   101 a: biza    102 a: bnzb    103 a: bizb
   104 a: lid    105 a: incd    106 a: decd    107 a: bnzd
   108 a: bizd

    s" unknown: " type dup . .ascii cr 
  ;

  : header? @addr 9 =if 
              *addr @ 
              1+ @ 30 >if 
                .addr decompile pop pop 2drop 
              then 
            then 
  ;

  : vector? @addr 0 =if 
              *addr @ 
              1+ @ 0 =if 
                pop pop 2drop 
              then 
            then 
  ;

  : more? header? vector? ;

  : getWord ' drop which @ d->xt @ *addr ! ;

---reveal---
  : dump ( an- )  cr 
                  for 
                    @+ over 1- . . cr 
                  next 
                  drop 
  ;

  : show ( an- ) swap *addr ! cr 
                 for 
                   .addr decompile nextOp 
                 next 
  ;

  : see  ( "- ) getWord cr 
                repeat 
                  .addr decompile nextOp more? 
                again 
  ;
}} 
