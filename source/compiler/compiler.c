/*******************************************************************************
 *|F|
 *|F| FILE: compiler.c
 *|F|
 *
 * AOT natice-code compiler by Matthias Schirm.
 *
 * Copyright (c) Matthias Schirm
 *
 * LICENCE:
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright 
 *     notice, and this list of conditions in the documentation and/or other 
 *     materials provided with the distribution.
 *  3. Neither the name of Matthias Schirm nor the names of its contributors 
 *     may be used to endorse or promote products derived from this software 
 *     without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTOR “AS IS” AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 ******************************************************************************/

/*
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
*/

#include <sys/mman.h>
#include <string.h>
#include "compiler.h"
#include "primitives.h"


/* compiler initialisation */

void comp_init (int tracemem)
{
  /* allocate memory for trace and execution buffers */

  comp_tbuffer = (uint8*) malloc (tracemem);
  if (comp_tbuffer == NULL) { printf ("comp_init: E1\n"); exit (-1); }

  comp_cbuffer = (function) malloc (tracemem);
  if (comp_cbuffer == NULL) { printf ("comp_init: E2\n"); exit (-1); }

  /* and for the private stacks */

  comp_dstack = (int*) valloc (CSTACK_DEPTH);
  comp_rstack = (int*) valloc (CSTACK_DEPTH);
 
  /* save buffer lenghts */

  comp_clen = tracemem;

  /* correct page flags to make memory managers happy */

  mprotect ((void*) comp_dstack,  CSTACK_DEPTH, PROT_READ | PROT_WRITE);
  mprotect ((void*) comp_rstack,  CSTACK_DEPTH, PROT_READ | PROT_WRITE);
  mprotect ((void*) comp_cbuffer, tracemem,     PROT_READ | PROT_WRITE | PROT_EXEC);
}

/* update binary buffer */

#define COMPILE comp_flush ();
#define compile comp_flush ();

int comp_flush (void)
{
  if (comp_cofs > comp_clen) { printf ("comp_flush: E3\n"); exit (-1); }

  memcpy ((uint8*) (comp_cbuffer + comp_cofs),(uint8*) comp_tbuffer, comp_tptr);
  comp_cofs = comp_cofs + comp_tptr;
  comp_tptr = 0;
}

/* call trace */

#define EXECUTE(t,a,b) comp_execute (t,a,b);
#define execute(t,a,b) comp_execute (t,a,b);

int comp_a;
int comp_b;

function comp_adr;

int comp_execute (int trace, int a, int b)
{
  comp_a   = a; 
  comp_b   = b;
  comp_adr = comp_cbuffer + trace;

  /* init execution state, save C register allocation and call function */

  COMP_PROLOG

  /* restore C specific register allocation */

  COMP_EPILOG
}

/* compile return and flush stream buffer */

#define RETC comp_returnc ();
#define retc comp_returnc ();

void comp_returnc (void)
{
  RET COMPILE
}

