assembler vocabulary

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

  : nextOp    1 *addr +! ;
  
  : @addr     *addr @ 
              @ 
  ;

  : .contents @addr . ;

  : .addr     *addr @ . ;

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
               ` =if s: ` then 
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
    32 a: aot     33 a: cofs     34 b: lia      35 a: psad
    36 a: psar    37 a: plda     38 a: plra     39 a: tda
    40 a: tra     41 a: tad      42 a: tar      43 a: tab
    44 a: tba     45 a: adda     46 a: suba     47 a: diva
    48 a: mula    49 a: inca     50 a: deca     51 a: anda
    52 a: gora    53 a: xora     54 a: shla     55 b: slia
    56 a: shra    57 b: sria     58 a: cmpa     59 a: ldra
    60 a: stra    61 b: lib      62 a: psbd     63 a: psbr
    64 a: pldb    65 a: plrb     66 a: tdb      67 a: trb
    68 a: addb    69 a: subb     70 a: divb     71 a: mulb
    72 a: incb    73 a: decb     74 a: andb     75 a: gorb
    76 a: xorb    77 a: cmpb     78 a: shlb     79 b: slib
    80 a: shrb    81 b: srib     82 a: ldrb     83 a: strb
    84 b: ci      85 b: cieq     86 b: cigr     87 b: cile
    88 b: cnza    89 b: ciza     90 b: cnzb     91 b: cizb
    92 a: cra     93 a: crb      94 b: bra      95 b: brb
    96 b: bi      97 b: bieq     98 b: bigr     99 b: bile
   100 b: bnza   101 b: biza    102 b: bnzb    103 b: bizb
   104 b: lid    105 a: incd    106 a: decd    107 b: bnzd
   108 b: bizd   109 b: adia    110 b: sbia    111 b: ania
   112 b: oria   113 b: xoia    114 b: cpia    115 b: adib
   116 b: sbib   117 b: anib    118 b: orib    129 b: xoib
   120 b: cpib   121 b: lisa    122 b: sisa    123 b: lisb
   124 b: sisb   125 b: inis    126 b: deis

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

current vocabulary: disassembler
