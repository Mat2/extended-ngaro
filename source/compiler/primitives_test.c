#include <stdio.h>
#include <stdlib.h>

#include "compiler.c"

int main (int argc, char **argv)
{
    comp_init (0xFFFF);

    printf ("\nTrace-compiler test:\n\n");

    /* streams */

    int TAB_test = label
                   lia      (20) tab
                   lia      (0)
                   tba
                   retc

    int LIA_test = label	
                   lia     (1024) 
                   retc

    int PSAD_test = label
                    lia     (200) psad
                    lia     (64)  plda
                    retc

    int PSAR_test = label
                    lia     (100) psar
                    lia     (32)  plra
                    retc

    int TDA_test = label
                   lia      (400) tda
                   retc

    int TRA_test = label
                   lia      (500) tra
                   retc

    int ADDA_test = label
                    lia     (-4096) tab
                    adda
                    retc

    int SUBA_test = label
                    lia     (-40) tab
                    suba
                    retc

    int DIVA_test = label
                    lia     (10)
                    lib     (2)  diva
                    retc

    int MULA_test = label
                    lia     (4) tab
                    mula
                    retc

    int ANDA_test = label
                    lia     (128) tab
                    anda
                    retc

    int GORA_test = label
                    lia      (128) tab
                    gora
                    retc

    int XORA_test = label
                    lia      (128) tab
                    xora
                    retc

    int SHLA_test = label
                    lia      (2) tab
                    lia      (4)
                    shla
                    retc

    int SLIA_test = label
                    lia      (4) slia (2)
                    retc

    int SHRA_test = label
                    lia      (2) tab
                    lia      (4)
                    shra
                    retc

    int SRIA_test = label
                    lia      (4) sria (2)
                    retc

    int INCA_test = label
                    lia      (45) inca
                    retc

    int DECA_test = label
                    lia      (45) deca
                    retc

    int STCK_test = label
                    lia     (20) psad
                    plra
                    retc

    int LIB_test = label
                   lib      (1024) tba
                   retc

    int PSBD_test = label
                    lib     (130) psbd 
                    lib     (20)  pldb
                    tba
                    retc

    int PSBR_test = label
                    lib     (365) psbr
                    lib     (30)  plrb
                    tba
                    retc

   int TDB_test = label
                  tdb
                  tba
                  retc

   int TRB_test = label
                  trb
                  tba
                  retc

   int ADDB_test = label
                   lia      (10)
                   lib      (92) addb
                   tba
                   retc

   int SUBB_test = label
                   lia      (-20)
                   lib      (30)  subb
                   tba
                   retc

   int DIVB_test = label
                   lia      (2)
                   lib      (10) divb
                   tba
                   retc

   int MULB_test = label
                   lia      (-20)
                   lib      (-30) mulb
                   tba
                   retc

   int INCB_test = label
                   lib      (45) incb
                   tba
                   retc

   int DECB_test = label
                   lib      (45) decb
                   tba
                   retc

   int ANDB_test = label
                   lia      (128) tab
                   andb
                   tba
                   retc

   int GORB_test = label
                   lia      (128) tab
                   gorb
                   tba
                   retc

   int XORB_test = label
                   lia      (128) tab
                   xorb
                   tba
                   retc

   int SHLB_test = label
                   lia      (2)
                   lib      (4)
                   shlb
                   tba
                   retc

   int SLIB_test = label
                   lib      (4) slib (2)
                   tba
                   retc

   int SHRB_test = label
                   lia      (2)
                   lib      (4)
                   shrb
                   tba
                   retc

   int SRIB_test = label
                   lib      (4) srib (2)
                   tba
                   retc

   int STRA_test = label
                   tdb
                   lia      (40)  psad
                   lia      (128) stra
                   lia      (0)
                   plda
                   retc

   int STRB_test = label
                   tda
                   lib      (40)  psbd
                   lib      (256) strb
                   lia      (0)
                   plda
                   retc

   int LDRA_test = label
                   tdb
                   lia      (42) psad
                   lia      (90) psad
                   ldra
                   pldb
                   pldb
                   retc

   int LDRB_test = label 
                   tda
                   lib       (10)  psbd
                   lib       (0)
                   ldrb
                   tba
                   retc

    int SWAP_test = label
                    lia      (20)
                    lib      (100)
                    swap
                    retc

    int CI_test = label
                  ci         (TAB_test)
                  retc

    int CRA_test = label
                   lia       (LDRB_test)
                   cra
                   retc

    int CRB_test = label
                   lib       (LDRB_test)
                   crb
                   retc

    int CIEQ_test = label
                    lia      (3)
                    lib      (3) 
                    cmpa     cieq (LIB_test)
                    retc

    int CIGR_test = label
                    lia      (10)
                    lib      (5) 
                    cmpa     cigr (LIB_test)
                    retc

    int CILE_test = label
                    lia      (5)
                    lib      (10) 
                    cmpa     cile (LIB_test)
                    retc

    int CNZA_test = label
                    lia      (5) 
                    cnza     (LIB_test)
                    retc

    int CIZA_test = label
                    lia      (0) 
                    ciza     (LIB_test)
                    retc

    int CNZB_test = label
                    lib      (5) 
                    cnzb     (LIB_test)
                    retc

    int CIZB_test = label
                    lib      (0) 
                    cizb     (LIB_test)
                    retc

    int BI_test = label
                  bi         (TAB_test)
                  retc

    int BRA_test = label
                   lia       (LDRB_test)
                   bra
                   retc

    int BRB_test = label
                   lib       (LDRB_test)
                   brb
                   retc

    int BIEQ_test = label
                    lia      (3)
                    lib      (3) 
                    cmpa     bieq (LIB_test)
                    retc

    int BIGR_test = label
                    lia      (10)
                    lib      (5) 
                    cmpa     bigr (LIB_test)
                    retc

    int BILE_test = label
                    lia      (5)
                    lib      (10) 
                    cmpa     bile (LIB_test)
                    retc

    int BNZA_test = label
                    lia      (5) 
                    bnza     (LIB_test)
                    retc

    int BIZA_test = label
                    lia      (0) 
                    biza     (LIB_test)
                    retc

    int BNZB_test = label
                    lib      (5) 
                    bnzb     (LIB_test)
                    retc

    int BIZB_test = label
                    lib      (0) 
                    bizb     (LIB_test)
                    retc

    int TAIB_test = label
                    inca
                    cmpa     bile (tail)
                    retc

    int TAIA_test = label
                    lia      (0)
                    lib      (100)
                    ci       (TAIB_test)
                    retc

    /* generated-traces test */

    int erg = 0;

    printf ("    - Arithmetic and logic operations:\n\n");
    printf ("      result	| should be\n");
    
    erg = execute (LIA_test,0, 0);  
          printf ("LIA:  %i	| ", erg); 
          printf ("1024\n");
    erg = execute (PSAD_test,0, 0); 
          printf ("PSAD: %i	| ", erg); 
          printf ("200\n");
    erg = execute (PSAR_test,0, 0); 
          printf ("PSAR: %i	| ", erg); 
          printf ("100\n");
    erg = execute (TRA_test,0, 0);  
          printf ("TRA:  %x	| ", (unsigned int) erg); 
          printf ("%x\n", (unsigned int) comp_rstack);
    erg = execute (TDA_test,0, 0);  
          printf ("TDA:  %x	| ", (unsigned int) erg); 
          printf ("%x\n", (unsigned int) comp_dstack);
    erg = execute (TAB_test,0, 0);  
          printf ("TAB:  %i	| ", erg); 
          printf ("20\n");
    erg = execute (ADDA_test,0, 0); 
          printf ("ADDA: %i	| ", erg); 
          printf ("-8192\n");
    erg = execute (SUBA_test,0, 0); 
          printf ("SUBA: %i		| ", erg); 
          printf ("0\n");
    erg = execute (DIVA_test,0, 0); 
          printf ("DIVA: %i		| ", erg); 
          printf ("5\n");
    erg = execute (MULA_test,0, 0); 
          printf ("MULA: %i	| ", erg); 
          printf ("16\n");
    erg = execute (INCA_test,0, 0); 
          printf ("INCA: %i	| ", erg); 
          printf ("46\n");
    erg = execute (DECA_test,0, 0); 
          printf ("DECA: %i	| ", erg); 
          printf ("44\n");
    erg = execute (ANDA_test,0, 0); 
          printf ("ANDA: %i	| ", erg); 
          printf ("128\n");
    erg = execute (GORA_test,0, 0); 
          printf ("GORA: %i	| ", erg); 
          printf ("128\n");
    erg = execute (XORA_test,0, 0); 
          printf ("XORA: %i		| ", erg); 
          printf ("0\n");
    erg = execute (SHLA_test,0, 0); 
          printf ("SHLA: %i	| ", erg); 
          printf ("16\n");
    erg = execute (SHRA_test,0, 0); 
          printf ("SHRA: %i		| ", erg); 
          printf ("1\n");
    erg = execute (SLIA_test,0, 0); 
          printf ("SLIA: %i	| ", erg); 
          printf ("16\n");
    erg = execute (SRIA_test,0, 0); 
          printf ("SRIA: %i		| ", erg); 
          printf ("1\n");
    erg = execute (LIB_test,0, 0); 
          printf ("LIB:  %i	| ", erg); 
          printf ("1024\n");
    erg = execute (PSBD_test,0, 0); 
          printf ("PSBD: %i	| ", erg); 
          printf ("130\n");
    erg = execute (PSBR_test,0, 0); 
          printf ("PSBR: %i	| ", erg); 
          printf ("365\n");
    erg = execute (TRB_test,0, 0);  
          printf ("TRB:  %x	| ", (unsigned int) erg); 
          printf ("%x\n", (unsigned int) comp_rstack);
    erg = execute (TDB_test,0, 0);  
          printf ("TDB:  %x	| ", (unsigned int) erg); 
          printf ("%x\n", (unsigned int) comp_dstack);
    erg = execute (ADDB_test,0, 0); 
          printf ("ADDB: %i	| ", erg); 
          printf ("102\n");
    erg = execute (SUBB_test,0, 0); 
          printf ("SUBB: %i	| ", erg); 
          printf ("50\n");
    erg = execute (DIVB_test,0, 0); 
          printf ("DIVB: %i		| ", erg); 
          printf ("5\n");
    erg = execute (MULB_test,0, 0); 
          printf ("MULB: %i	| ", erg); 
          printf ("600\n");
    erg = execute (INCB_test,0, 0); 
          printf ("INCB: %i	| ", erg); 
          printf ("46\n");
    erg = execute (DECB_test,0, 0); 
          printf ("DECB: %i	| ", erg); 
          printf ("44\n");
    erg = execute (ANDB_test,0, 0); 
          printf ("ANDB: %i	| ", erg); 
          printf ("128\n");
    erg = execute (GORB_test,0, 0); 
          printf ("GORB: %i	| ", erg); 
          printf ("128\n");
    erg = execute (XORB_test,0, 0); 
          printf ("XORB: %i		| ", erg); 
          printf ("0\n");
    erg = execute (SHLB_test,0, 0); 
          printf ("SHLB: %i	| ", erg); 
          printf ("16\n");
    erg = execute (SHRB_test,0, 0); 
          printf ("SHRB: %i		| ", erg); 
          printf ("1\n");
    erg = execute (SLIB_test,0, 0); 
          printf ("SLIB: %i	| ", erg); 
          printf ("16\n");
    erg = execute (SRIB_test,0, 0); 
          printf ("SRIB: %i		| ", erg); 
          printf ("1\n");
    erg = execute (SWAP_test,0, 0); 
          printf ("SWAP: %i	| ", erg); 
          printf ("100\n");

    /* load and store primitives */

    printf ("\n    - Load and store instructions:\n\n");
    printf ("      result	| should be\n");

    erg = execute (STRA_test,0, 0); 
          printf ("STRA: %i	| ", erg); 
          printf ("128\n");
    erg = execute (STRB_test,0, 0); 
          printf ("STRB: %i	| ", erg); 
          printf ("256\n");
    erg = execute (LDRA_test,0, 0); 
          printf ("LDRA: %i	| ", erg); 
          printf ("42\n");
    erg = execute (LDRB_test,0, 0); 
          printf ("LDRB: %i	| ", erg); 
          printf ("10\n");

    /* branch and call isntructions */

    printf ("\n    - branch and call instructions:\n\n");
    printf ("      result	| should be\n");

    erg = execute (CI_test,0, 0); 
          printf ("CI:   %i	| ", erg); 
          printf ("20\n");
    erg = execute (CRA_test,0, 0); 
          printf ("CRA:  %i	| ", erg); 
          printf ("10\n");
    erg = execute (CRB_test,0, 0); 
          printf ("CRB:  %i	| ", erg); 
          printf ("10\n");
    erg = execute (CIEQ_test,0, 0); 
          printf ("CIEQ: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (CIGR_test,0, 0); 
          printf ("CIGR: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (CILE_test,0, 0); 
          printf ("CILE: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (CNZA_test,0, 0); 
          printf ("CNZA: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (CIZA_test,0, 0); 
          printf ("CIZA: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (CNZB_test,0, 0); 
          printf ("CNZB: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (CIZB_test,0, 0); 
          printf ("CIZB: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (BI_test,0, 0); 
          printf ("BI:   %i	| ", erg); 
          printf ("20\n");
    erg = execute (BRA_test,0, 0); 
          printf ("BRA:  %i	| ", erg); 
          printf ("10\n");
    erg = execute (BRB_test,0, 0); 
          printf ("BRB:  %i	| ", erg); 
          printf ("10\n");
    erg = execute (BIEQ_test,0, 0); 
          printf ("BIEQ: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (BIGR_test,0, 0); 
          printf ("BIGR: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (BILE_test,0, 0); 
          printf ("BILE: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (BNZA_test,0, 0); 
          printf ("BNZA: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (BIZA_test,0, 0); 
          printf ("BIZA: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (BNZB_test,0, 0); 
          printf ("BNZB: %i	| ", erg); 
          printf ("1024\n");
    erg = execute (BIZB_test,0, 0); 
          printf ("BIZB: %i	| ", erg); 
          printf ("1024\n");

    /* are PROLOG and EPILOG correct ? */

    printf ("\n    - Correct compiler call-frame implementation:\n\n");
    printf ("      result	| should be\n");

    erg = execute (TAIB_test,0, 100);  
    printf ("TAIL: %i	| ", erg);
    printf ("100\n");
    erg = execute (STCK_test,0, 0);  
    printf ("STCK: %i 	| ", erg);
    printf ("!= 20\n");
    printf ("\n");

    /* enviroment status */

    printf ("\n    - Frame status:\n\n");

    printf ("D: %x | ", (unsigned int) comp_dstack);
    printf ("R: %x | ",  (unsigned int) comp_rstack);

    printf ("comp_cofs: %i | ", comp_cofs); 
    printf ("comp_tptr: %i\n\n",comp_tptr);
}
