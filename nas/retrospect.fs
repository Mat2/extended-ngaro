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
(      - Added two new instructions for compilation and       )
(        execution of native-code traces                      )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ) 

{{
  variable *addr

  : nextOp 1 *addr +! ;
  : @addr *addr @ @ ;
  : .contents @addr . ;
  : .addr *addr @ . ;

  : .ascii dup 32 >if dup 128 <if 39 emit emit 39 emit 0 then then drop ;

  : render type cr drop ;
  : s: 32 accept tib keepString literal, ['] render compile ` ;; ;
  compiler: a: ` over ` =if s: ` then ;

  : .name d->name type cr ;
  : resolve -1 last @ repeat dup d->xt @ @addr =if .name drop 0 ;then 0; @ again ;
  : render type 32 emit drop nextOp resolve 0; drop .contents cr ;
  : x: 32 accept tib keepString literal, ['] render compile ` ;; ;
  compiler: b: ` over ` =if x: ` then ;

  : decompile
    32 emit
    @addr
     0 a: nop      1 b: lits      2 a: dups      3 a: drps
     4 a: swps     5 a: pshs      6 a: pops      7 b: call
     8 b: bra      9 a: ret      10 b: bgr      11 b: ble  
    12 b: bne     13 b: beq      14 a: ldsr     15 a: strs
    16 a: adds    17 a: subs     18 a: muls     19 a: divs
    20 a: ands    21 a: gors     22 a: xors     23 a: shls
    24 a: shrs    25 a: req      26 a: incs     27 a: decs
    28 a: ldp     29 a: stp      30 a: wait     31 a: ins
    32 a: aot
    s" unknown: " type dup . .ascii cr ;

  : header? @addr 9 =if *addr @ 1+ @ 30 >if .addr decompile pop pop 2drop then then ;
  : vector? @addr 0 =if *addr @ 1+ @ 0 =if pop pop 2drop then then ;
  : more? header? vector? ;
  : getWord ' drop which @ d->xt @ *addr ! ;

---reveal---
  : dump ( an- )  cr for @+ over 1- . . cr next drop ;
  : show ( an- ) swap *addr ! cr for .addr decompile nextOp next ;
  : see  ( "- ) getWord cr repeat .addr decompile nextOp more? again ;
}}
