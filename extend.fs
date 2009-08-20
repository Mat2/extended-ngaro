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
( This is a block editor that I've been using for many years. )
( It's simple, and doesn't have a lot of features, but it is  )
( more than enough for most of my prototyping work.           )
(                                                             )
( Actually, it's proven more popular than I ever expected. It )
( has been used by many of Retro's users, and implementations )
( now exist for several other Forth systems.                  )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Line and column numbers start at 0.                         )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Quick Reference:                                            )
(      # s        Select a new block                          )
(        p        Previous block                              )
(        n        Next block                                  )
(      # i ..     Insert .. into line                         )
(   # #2 ia ..    Insert .. into line [#2] starting at        )
(                 column [#]                                  )
(        x        Erase the current block                     )
(      # d        Erase the specified line                    )
(        v        Display the current block                   )
(        e        Evaluate Block                              )
(        new      Erase all blocks                            )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( The memory layout and basic configuration.                  )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
1024 constant #-blocks
 512 constant #-block-size
#mem @ #-block-size #-blocks * - constant offset

13 variable: line-ending

variable blk
: block     512 * offset + ;
: (block)   blk @ block ;
: (line)    64 * (block) + ;

: (v) ;
: (e) ;
: v   ( -  ) (v) ;
: s   ( n- ) blk ! v ;
: d   ( n- ) (line) 32 64 fill v ;
: x   ( -  ) (block) 32 512 fill v ;
: p   ( -  ) -1 blk +! v ;
: n   ( -  ) 1 blk +! v ;
: ia  ( nn"- )
  (line) + push line-ending @ accept tib pop
  tib getLength copy v ;
: i   ( n"- ) 0 swap ia v ;
: new ( -  ) offset 32 #-block-size #-blocks * fill ;
: e   ( -  ) (e) ;


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Default Block Viewer                                        )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
{
  : (type)  for dup @ emit 1+ next ;
  : type    (type) drop ;
  : space   32 emit ;

  : row     . dup 64 type 64 + cr ;
  : .rows   0 row 1 row 2 row 3 row
            4 row 5 row 6 row 7 row ;
  : .block  ." Block: " blk @ . ." of " #-blocks . ;
  : x       ." +---:---+---:---" ;
  : bar     space space x x x x cr ;
  : vb      bar blk @ block .rows drop bar ;
  : status  .block ;
  here is (v) ] clear vb status ;
}


( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( Default Block Evaluator                                     )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
{
  variable count
  variable buffer
  : setup  ( -- )    512 count ! (block) buffer ! ;
  : -remap ( -- )    ['] key :devector ;
  : get    ( -- c )  buffer @ @ ;
  : next   ( -- c )
    count @ 0 =if 32 -remap ;then
    count -- get buffer ++ ;
  : remap  ( -- )    ['] next ['] key :is ;
  here is (e) ] setup remap ;
}
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( A simple implementation of does>                            )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
: reclass last @ d->class ! ;
: .does compiler @ -1 =if swap literal, compile pop drop ;; then drop ;

macro: does>
        1 , here 0 ,            ( compile address of code after does> [will be patched] )
        ['] reclass compile     ( compile a call to reclass, which assigns the code )
                                ( after does> as the class handler for the word. )
        ['] ;; execute          ( compile an exit, so no code following does> will be )
                                ( executed when the create/does> sequence is run. )
        here swap !             ( Patch the address from the 1 , here 0 , line to the )
                                ( actual start of the code for the does> action. )
        here literal,           ( Compile the address following does> as a literal so )
                                ( it can be used by the .does class. )
        ['] .does compile       ( And finally, compile a call to the .does class, which )
                                ( will take care of compile-time and interpret-time bits)
;
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
( All done! Fill the blocks with spaces, and we're good to go )
( ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ )
new
