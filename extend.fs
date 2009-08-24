( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Extensions to RETRO by Charles Childers                     )
( This code is gifted to the public domain. Share freely.     )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( This file contains a set of words I find to be very useful, )
( but not ones that are essential to the actual low-level     )
( core.                                                       )
(                                                             )
( Stack comments are provided for words which are intended    )
( to be used directly. Internal factors do not have the stack )
( comments provided.                                          )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( These words provide a limited degree of control over the    )
( visibility of words.                                        )
(                                                             )
( In older versions of Retro, these were called loc: and ;loc )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( ... global scope ....                                       )
(                                                             )
( { ... start local scope, level 1                            )
(                                                             )
(   { ... start local scope, level 2                          )
(   } ... words in scope level 2 are no longer                )
(     ... visible                                             )
(                                                             )
( } ... words in scope level 1 are no longer                  )
(   ... visible                                               )
(                                                             )
( ... back to global scope ...                                )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
create <list>  ( -a )
       0 , 0 , 0 , 0 , 0 ,
: { ( - ) last @ <list> @ 1+ <list> + ! 1 <list> +! ;
: } ( - ) 1 <list> -! <list> @ 1+ <list> + @ last ! ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( A somewhat more powerful scoping system                     )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( ... global scope ...                                        )
( {{                                                          )
(    ... local scope ...                                      )
( ---reveal---                                                )
(    ... global scope, with local scope still visible ...     )
( }}                                                          )
( ... global scope, local words not visible ...               )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
: find-last-visible last repeat @ dup @ <list> 1+ @ =if ;; then again ;
: {{ ( - )  last @ <list> ! ;
: ---reveal---  ( - ) last @ <list> 1+ ! ;
: }} ( - )  <list> @ find-last-visible ! ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( A simple word to allocate memory in a linear fashion. It's  )
( useful for arrays and similar things.                       )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
: allot  ( n- )  heap +! ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( These allow a more readable way to create variables and     )
( constants. It also makes constants more efficient.          )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
: variable:  ( n"- )  create , ;
: variable   ( "-  )  0 variable: ;
: constant   ( n"- )  create last @ d->xt ! ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Shortcuts for incrementing and decrementing variables       )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
: ++  ( a- )  1 swap +! ;
: --  ( a- )  1 swap -! ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Copy memory from one location to another.                   )
( Takes source, dest, and a count.                            )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
{{
  variable src
  variable dst
  : (copy) for src @ @ dst @ ! src ++ dst ++ next ;
  ---reveal---
  : copy ( aan- ) push dst ! src ! pop (copy) ;
}}


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Fill a memory range with a specific value.                  )
( Takes an address, a value, and a count.                     )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
{{
  variable dst
  variable val
  : (fill) for val @ dst @ ! dst ++ next ;
---reveal---
  : fill ( ann- ) push val ! dst ! pop (fill) ;
}}


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Some shortcuts that save some typing and keep the code a    )
( bit cleaner in macros.                                      )
(   ` wordname  =  ['] wordname compile                      )
(   ` wordname  =  ['] wordname execute                      )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
compiler: `  ( "- )  ' literal, which @ d->class @ compile ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( This is a rather common word that can be used to easily     )
( display a string.                                           )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
macro: ." ( "- )
   compiler @ 0 =if " type ;; then ` s" ` type ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Retro has some simple conditional forms, which tie the      )
( comparisons to the flow control. It's often useful to have  )
( separate functions for the comparisons, so I define them    )
( here.                                                       )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
-1 constant TRUE   ( -f )
 0 constant FALSE  ( -f )

compiler: if    ( f- )
       compiler @ 0; drop TRUE literal, ` =if ;

compiler: ;then ( - )
       compiler @ 0; drop ` ;; ` then ;

: =  ( xy-f )  =if TRUE ;then FALSE ;
: <> ( xy-f )  !if TRUE ;then FALSE ;
: >  ( xy-f )  >if TRUE ;then FALSE ;
: <  ( xy-f )  <if TRUE ;then FALSE ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Allows Retro to "forget" a word, and anything defined after )
( it.                                                         )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
: forget ( "- ) ' drop which @ dup heap ! @ last ! ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Allow changing the class of a word                          )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
: reclass ( a"- ) ' drop which @ d->class ! ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Numeric Bases                                               )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
: decimal ( - ) 10 base ! ;
: hex     ( - ) 16 base ! ;
: octal   ( - )  8 base ! ;
: binary  ( - )  2 base ! ;
