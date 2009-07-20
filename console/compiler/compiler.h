/******************************************************
 * Ngaro
 *
 *|F|
 *|F| FILE: compiler.h
 *|F|
 *
 * AOT natice-code compiler by Matthias Schirm.
 * Released into the public domain
 ******************************************************/

/* constants for determination of maximal number
   of processes */

#define CSTACK_DEPTH 0xFFFF
#define CSTACK_FRAME 128
#define MAX_PROCESS  CSTACK_DEPTH / CSTACK_FRAME

/* some useful type declarations */

typedef unsigned char uint8;
typedef signed int    int32;
typedef int           (*function) ();

/* comp_clen: Lenght of trace and binary buffer 
   comp_cptr: offset to first free uint8 in binary buffer 
   comp_tptr: offset to first free uint8 in trace buffer */

int comp_clen;
int comp_cptr;
int comp_tptr;

/* offset into actual trace */

int comp_cofs;

/* trace and execution buffer (base address) */

function  comp_cbuffer;
uint8    *comp_tbuffer;

/* private data and address stacks for traces */

int comp_dstack [CSTACK_DEPTH];
int comp_rstack [CSTACK_DEPTH];

/* pointer into actual stack frame */

int comp_sptr;

/* union for representation of immediate values */

typedef union
{
  int   w;     /* whole word */
  uint8 b[3];  /* bytes of word */

} imm;
