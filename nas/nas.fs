( ------------------------------------------------------ )
( NAS:			Ngaro Assembler                  )
( Forth:		Retro Forth 10                   )
( Version:		0.1                              )
( File:			base.fs                          )
( Description:	        Basic word set for the compiler  )
( Licence:		See LICENCE                      )
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

33  uopcode: lia
34  uopcode: psad
35  uopcode: psar
36  uopcode: plda
37  uopcode: plra
38  uopcode: tda
39  uopcode: tra
40  uopcode: tad
41  uopcode: tar
42  uopcode: tab
43  uopcode: tba
44  uopcode: adda
45  uopcode: suba
46  uopcode: diva
47  uopcode: mula
48  uopcode: inca
49  uopcode: deca
50  uopcode: anda
51  uopcode: gora
52  uopcode: xora
53  uopcode: shla
54  uopcode: slia
55  uopcode: shra
56  uopcode: sria
57  uopcode: cmpa
58  uopcode: ldra
59  uopcode: stra
60  uopcode: lib
61  uopcode: psbd
62  uopcode: psbr
63  uopcode: pldb
64  uopcode: plrb
65  uopcode: tdb
66  uopcode: trb
67  uopcode: addb
68  uopcode: subb
69  uopcode: divb
70  uopcode: mulb
71  uopcode: incb
72  uopcode: decb
73  uopcode: andb
74  uopcode: gorb
75  uopcode: xorb
76  uopcode: cmpb
77  uopcode: shlb
78  uopcode: slib
79  uopcode: shrb
80  uopcode: srib
81  uopcode: ldrb
82  uopcode: strb
83  uopcode: ci
84  uopcode: cieq
85  uopcode: cigr
86  uopcode: cile
87  uopcode: cnza
88  uopcode: ciza
89  uopcode: cnzb
90  uopcode: cizb
91  uopcode: cra
92  uopcode: crb
93  uopcode: bra
94  uopcode: brb
95  uopcode: bi
96  uopcode: bieq
97  uopcode: bigr
98  uopcode: bile
99  uopcode: bnza
100 uopcode: biza
101 uopcode: bnzb
102 uopcode: bizb

