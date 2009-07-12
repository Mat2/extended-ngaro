/******************************************************
 * Ngaro
 *
 *|F|
 *|F| FILE: compiler.c
 *|F|
 *
 * AOT natice-code compiler by Matthias Schirm.
 * Released into the public domain
 ******************************************************/

#ifdef X86_64
  #include "arch/x86-64/primitives.h"
#elsif X86_32
  #include "arch/x86-32/primitives.h"
#elsif MIPS
  #include "arch/MIPS/primitives.h"
#elsif POWERPC
  #include "arch/POWERPC/primitives.h"
#elsif ARM
  #include "arch/arm-7/primitives.h"
#endif

#include <sys/mman.h>
#include "compiler.h"

/* compiler initialisation */

void comp_init (int tracemem)
{
  /* allocate memory for trace and execution buffers */

  byte *tmem = (byte) valloc (tracemem);
  if (tmem == NULL) { printf ("NGARO: E1\n"); exit (-1); }

  function cmem = (function) valloc (tracemem);
  if (cmem == NULL) { printf ("NGARO: E2\n"); exit (-1); }

  /* init buffer pointers */

  comp_tbuffer = tmem;
  comp_cbuffer = cmem;

  /* save buffer lenghts */

  comp_clen = tracemem;

  /* clear local stack areas */

  int i;
  for (i = 0; i < CSTACK_DEPTH; i++) comp_dstack[i] = 0;
  for (i = 0; i < CSTACK_DEPTH; i++) comp_rstack[i] = 0;

  /* correct page flags to make memory managers happy */

  mprotect ((void*) comp_dstack,  CSTACK_DEPTH, PROT_READ | PROT_WRITE);
  mprotect ((void*) comp_rstack,  CSTACK_DEPTH, PROT_READ | PROT_WRITE);
  mprotect ((void*) comp_cbuffer, tracemem,     PROT_READ | PROT_WRITE | PROT_EXEC);
}

/* update binary buffer */

int comp_flush (void);
{
  int clen = comp_cofs - comp_cptr;
  int cbuf = comp_cbuffer + comp_cptr;
  int tbuf  = comp_tbuffer + comp_tptr;

  if (cbuf > comp_clen) { printf ("NGARO: E3\n"); exit (-1); }

  memcpy ((void*) cbuf, (int) clen, (void*) tbuf);

  comp_tptr = 0;
  comp_cptr = cbuf + clen;
}

/* call trace */

int comp_execute (int trace, VM *vm)
{
  /* define accumulator and operand register */

  COMP_REGISTER

  /* copy the first two stack elements into registers */

  comp_acc = vm->data[vm->sp-1];
  comp_opn = vm->data[vm->sp];

  /* init execution state and save C register allocation */

  COMP_PROLOG

  /* call function (trace) */

  vm->data[vm->sp] = (comp_cbuffer + trace) ();

  /* restore C specific register allocation */

  COMP_EPILOG
}

