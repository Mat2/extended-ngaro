( ------------------------------------------------------ )
( NAS:                  Ngaro Assembler                  )
( Forth:                Retro Forth 10                   )
( Version:              0.1                              )
( File:                 nas.fs                           )
( Description:	        Basic word set for the compiler  )
( Licence:              See LICENCE                      )
( Needs:                Retro image with extend.ngaro    )
( ------------------------------------------------------ )

: state compiler @ ;
: self  last     @ ;

: set-class d->class ! ;
: set-value d->xt    ! ;

 0 constant imode
-1 constant cmode


( word classes for ngaro-opcodes and compiler-uops )

: .opc state imode =if , ;; then , ;

( assembler words )

: opcode: ( n : opcode - )
          create 
          ['] .opc self set-class
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
30 opcode: wait
31 opcode: ins
32 opcode: aot
33 opcode: cofs

( extended instruction-set [only within trace compiler avariable] )

34  opcode: lia
35  opcode: psad
36  opcode: psar
37  opcode: plda
38  opcode: plra
39  opcode: tda
40  opcode: tra
41  opcode: tad
42  opcode: tar
43  opcode: tab
44  opcode: tba
45  opcode: adda
46  opcode: suba
47  opcode: diva
48  opcode: mula
49  opcode: inca
50  opcode: deca
51  opcode: anda
52  opcode: gora
53  opcode: xora
54  opcode: shla
55  opcode: slia
56  opcode: shra
57  opcode: sria
58  opcode: cmpa
59  opcode: ldra
60  opcode: stra
61  opcode: lib
62  opcode: psbd
63  opcode: psbr
64  opcode: pldb
65  opcode: plrb
66  opcode: tdb
67  opcode: trb
68  opcode: addb
69  opcode: subb
70  opcode: divb
71  opcode: mulb
72  opcode: incb
73  opcode: decb
74  opcode: andb
75  opcode: gorb
76  opcode: xorb
77  opcode: cmpb
78  opcode: shlb
79  opcode: slib
80  opcode: shrb
81  opcode: srib
82  opcode: ldrb
83  opcode: strb
84  opcode: ci
85  opcode: cieq
86  opcode: cigr
87  opcode: cile
88  opcode: cnza
89  opcode: ciza
90  opcode: cnzb
91  opcode: cizb
92  opcode: cra
93  opcode: crb
94  opcode: bra
95  opcode: brb
96  opcode: bi
97  opcode: bieq
98  opcode: bigr
99  opcode: bile
100 opcode: bnza
101 opcode: biza
102 opcode: bnzb
103 opcode: bizb
104 opcode: lid
105 opcode: incd
106 opcode: decd
107 opcode: bnzd
108 opcode: bizd
109 opcode: adia
110 opcode: sbia
111 opcode: ania
112 opcode: oria
113 opcode: xoia
114 opcode: cpia
115 opcode: adib
116 opcode: sbib
117 opcode: anib
118 opcode: orib
119 opcode: xoib
120 opcode: cpib
121 opcode: lisa
122 opcode: lisb
123 opcode: sisa
124 opcode: sisb
125 opcode: inis
126 opcode: deis

( syntax sugar )

: tail cofs ;

: ], , cmode compiler ! ;

