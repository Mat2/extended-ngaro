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

typedef unsigned char byte;
typedef signed int    word;
typedef int           (*function) ();

/* comp_clen: Lenght of trace buffer 
   comp_cptr: pointer to first free byte in trace buffer */

int comp_clen;
int comp_cptr;

/* trace and execution buffer */

function comp_cbuffer;
byte     comp_tbuffer;

/* private data and address stacks for traces */

int comp_dstack [CSTACK_DEPTH];
int comp_rstack [CSTACK_DEPTH];

/* pointer into actual stack frame */

int comp_sptr;
