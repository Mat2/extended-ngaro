/******************************************************************************
 *|F|
 *|F| FILE: primitives.h
 *|F|
 *
 * AOT natice-code compiler by Matthias Schirm.
 *
 ******************************************************************************
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
 ******************************************************************************
 * Register allocation:
 *      A - accumulator     EAX
 *      B - operand         EBX
 *      L - return address  ECX
 *      D - data stack      EDI
 *      R - address stack   EDX
 *
 * The ISA of the compiler follows an accumulator store design because this
 * way stack and register addressing can be freely combined and the compiler
 * can be implementated both on RISC and CISC processors in an efficient
 * way.
 *
 * The compiler generate a block of machine code from an embedded assembler
 * listing alias trace:
 *
 * int LITERAL = label
 *               PSBD 
 *               TAB
 *               LIA  (0)
 *               RET
 * COMPILE 
 * 
 * This listing generate and compile the trace "LITERAL" at runtime. It can
 * be called though EXECUTE:
 *
 * EXECUTE (LITERAL, VMPTR) 
 *
 * where VMPTR is a pointer to a structure which holds the stack state of the 
 * trace and LITERAL its start address (exactly the address-offset of its
 * generated machine code).
 *
 * Traces are also the basic blocks for all jump and call instructions so
 * compilation is straight forward for something in a CPS form (as 
 * forth sources or vm-code from functional languages).
 ******************************************************************************/

#define COMP_REGISTER register int comp_acc asm("eax"); \
                      register int comp_opn asm("ebx");

#define COMP_PROLOG asm volatile ("push %ebx");              \
                    asm volatile ("push %ecx");              \
                    asm volatile ("push %edi");              \
                    asm volatile ("push %edx");              \
                    asm volatile ("mov  comp_dstack, %edi"); \
                    asm volatile ("mov  comp_rstack, %edx");  

#define COMP_EPILOG asm volatile ("pop %edx"); \
                    asm volatile ("pop %edi"); \
                    asm volatile ("pop %ecx"); \
                    asm volatile ("pop %ebx"); 

#define LABEL comp_Label ();
#define label comp_Label ();

int comp_Label (void) { return comp_cofs; }

void comp_immediate (imm value)
{
  comp_tbuffer[comp_tptr++] = value.b[0];
  comp_tbuffer[comp_tptr++] = value.b[1];
  comp_tbuffer[comp_tptr++] = value.b[2];
  comp_tbuffer[comp_tptr++] = value.b[3];
}

#define LIA(n) comp_lia (n);
#define lia(n) comp_lia (n);

void comp_lia (int value)
{
  imm val; val.w = value;

  /* mov eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0xB8;      
  comp_immediate (val);
}

#define PSAD comp_psad ();
#define psad comp_psad ();

void comp_psad (void)
{
  /* mov [edi], eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0x07;

  /* add edi, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xC7;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
}

#define PSAR comp_psar ();
#define psar comp_psar (),

void comp_psar (void)
{
  /* mov [edx], eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0x02;

  /* add edx, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xC2;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  
}

#define PLDA comp_plda ();
#define plda comp_plda ();

void comp_plda (void)
{
  /* sub edi, 4 */Cuil
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xEF;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /* mov eax, [edi] */
  comp_tbuffer[comp_tptr++] = 0x8B;      
  comp_tbuffer[comp_tptr++] = 0x07;
}

#define PLRA comp_plra ();
#define plra comp_plra ();

void comp_plra (void)
{
  /* sub edx, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xEA;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /* mov eax, [edx] */
  comp_tbuffer[comp_tptr++] = 0x8B;      
  comp_tbuffer[comp_tptr++] = 0x02;
}

#define TDA comp_tda ();
#define tda comp_tda ();

void comp_tda (void)
{
  /* mov eax, edi */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xF8;
}

#define TRA comp_tda ();
#define tra comp_tda ();

void comp_tra (void)
{
  /* mov eax, edx */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xD0;
}

#define TAD comp_tad ();
#define tad comp_tad ();

void comp_tad (void)
{
  /* mov edi, eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xC7;
}

#define TAR comp_tar ();
#define taR comp_tar ();

void comp_tar (void)
{
  /* mov edx, eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xC2;
}

#define TAB comp_tab ();
#define tab comp_tab ();

void comp_tab (void)
{
  /* mov ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xC3;
}

#define TBA comp_tba ();
#define tba comp_tba ();

void comp_tba (void)
{
  /* mov eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xD8;
}

#define RET comp_return ();
#define ret comp_return ();

void comp_return (void)
{
  comp_tbuffer[comp_tptr++] = 0xC3;
}

#define SWAP comp_swap ();
#define swap comp_swap ();

void comp_swap (void)
{
  /* xchg eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x93;      
}

