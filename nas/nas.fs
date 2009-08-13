( ------------------------------------------------------ )
( NAS:                  Ngaro Assembler                  )
( Forth:                Retro Forth 10                   )
( Version:              0.1                              )
( File:                 base.fs                          )
( Description:          Basic word set for the compiler  )
( Licence:              See LICENCE                      )
( Needs:                Retro image with extend.ngaro    )
( ------------------------------------------------------ )

: interpret-only-error
        ." <-- only usable in interpreter mode !"
;

: state compiler @ ;
: self  last     @ ;

: set-class d->class ! ;
: set-value d->xt    ! ;

 0 constant imode
-1 constant cmode


( word classes for ngaro-opcodes and compiler-uops )

: .opc state imode =if ;; then , ;
: .uop state imode =if ;; then interpret-only-error drop ;


( assembler words )

: opcode: ( n : opcode - )
          create 
          ['] .opc self set-class
             ( n ) self set-value
;

: uopcode: ( n : uop - )
           create
           ['] .uop self set-class
              ( n ) self set-value
;


( ngaro mnemonics )

1  opcode: lits
7  opcode: cas
8  opcode: bras
10 opcode: bgrs
11 opcode: bles
12 opcode: bnes
13 opcode: beqs

0  opcode: nop
2  opcode: dups
3  opcode: drps
4  opcode: swps
5  opcode: pshs
6  opcode: pops
9  opcode: rts
14 opcode: ldsr
15 opcode: strs
16 opcode: adds
17 opcode: subs
18 opcode: muls 
19 opcode: divs
20 opcode: ands
21 opcode: gors
22 opcode: xors
23 opcode: shls
24 opcode: shrs
25 opcode: reqs
26 opcode: incs
27 opcode: decs
28 opcode: ldps          
29 opcode: stps
30 opcode: wais
31 opcode: ins
32 opcode: aot

( extended instruction-set [only within trace compiler avariable] )

31  uopcode: lia
32  uopcode: psad
33  uopcode: psar
34  uopcode: plda
35  uopcode: plra
36  uopcode: tda
37  uopcode: tra
38  uopcode: tad
39  uopcode: tar
40  uopcode: tab
41  uopcode: tba
42  uopcode: adda
43  uopcode: suba
44  uopcode: diva
45  uopcode: mula
46  uopcode: inca
47  uopcode: deca
48  uopcode: anda
49  uopcode: gora
50  uopcode: xora
51  uopcode: shla
52  uopcode: slia
53  uopcode: shra
54  uopcode: sria
55  uopcode: cmpa
56  uopcode: ldra
57  uopcode: stra
58  uopcode: lib
59  uopcode: psbd
60  uopcode: psbr
61  uopcode: pldb
62  uopcode: plrb
63  uopcode: tdb
64  uopcode: trb
65  uopcode: addb
66  uopcode: subb
67  uopcode: divb
68  uopcode: mulb
69  uopcode: incb
70  uopcode: decb
71  uopcode: andb
72  uopcode: gorb
73  uopcode: xorb
74  uopcode: cmpb
75  uopcode: shlb
76  uopcode: slib
77  uopcode: shrb
78  uopcode: srib
79  uopcode: ldrb
80  uopcode: strb
81  uopcode: ci
82  uopcode: cieq
83  uopcode: cigr
84  uopcode: cile
85  uopcode: cnza
86  uopcode: ciza
87  uopcode: cnzb
88  uopcode: cizb
89  uopcode: cra
90  uopcode: crb
91  uopcode: bra
92  uopcode: brb
93  uopcode: bi
94  uopcode: bieq
95  uopcode: bigr
96  uopcode: bile
97  uopcode: bnza
98  uopcode: biza
99  uopcode: bnzb
100 uopcode: bizb

