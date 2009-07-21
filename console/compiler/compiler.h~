/*******************************************************************************
 *|F|
 *|F| FILE: compiler.h
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

/* private data and address stacks for traces (comp_rstack holds offsets
   with base comp_cbuffer (so trace addresses are comp_cbuffer + ofs) !! */

int *comp_dstack;
int *comp_rstack;

/* pointer into actual stack frame */

int comp_sptr;

/* union for representation of immediate values */

typedef union
{
  int   w;     /* whole word */
  uint8 b[3];  /* bytes of word */

} imm;
