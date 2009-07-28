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
 *      B - accumulator     EBX
 *      D - data stack      EDI
 *      R - address stack   ESI
 *
 *      ECX, EDX - scratch (as EDX is only used by DIVx primitives this 
 *                          register is not saved in PROLOG, ECX don't need
 *                          to be saved)
 ******************************************************************************/

#define COMP_REGISTER register int comp_acc asm("eax"); \
                      register int comp_opn asm("ebx");

#define COMP_PROLOG asm volatile ("push %ebx");              \
                    asm volatile ("push %edi");              \
                    asm volatile ("push %esi");              \
                    asm volatile ("mov  comp_dstack, %edi"); \
                    asm volatile ("mov  comp_rstack, %esi");

#define COMP_EPILOG asm volatile ("pop %esi"); \
                    asm volatile ("pop %edi"); \
                    asm volatile ("pop %ebx"); \

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

/* primitives which accesses accumulator A */

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
  /* mov [esi], eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0x06;

  /* add esi, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xC6;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  
}

#define PLDA comp_plda ();
#define plda comp_plda ();

void comp_plda (void)
{
  /* sub edi, 4 */
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
  /* sub esi, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xEE;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /* mov eax, [esi] */
  comp_tbuffer[comp_tptr++] = 0x8B;      
  comp_tbuffer[comp_tptr++] = 0x06;
}

#define TDA comp_tda ();
#define tda comp_tda ();

void comp_tda (void)
{
  /* mov eax, edi */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xF8;
}

#define TRA comp_tra ();
#define tra comp_tra ();

void comp_tra (void)
{
  /* mov eax, esi */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xF0;
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
  /* mov esi, eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xC6;
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

#define ADDA comp_adda ();
#define adda comp_adda ();

void comp_adda (void)
{
  /* add eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x01;      
  comp_tbuffer[comp_tptr++] = 0xD8;
}

#define SUBA comp_suba ();
#define suba comp_suba ();

void comp_suba (void)
{
  /* sub eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x29;      
  comp_tbuffer[comp_tptr++] = 0xD8;

}

#define DIVA comp_diva ();
#define diva comp_diva ();

void comp_diva (void)
{
  /* push edx */
  comp_tbuffer[comp_tptr++] = 0x52;      

  /* xor edx, edx */
  comp_tbuffer[comp_tptr++] = 0x31;      
  comp_tbuffer[comp_tptr++] = 0xD2;  

  /* idiv ebx */
  comp_tbuffer[comp_tptr++] = 0xF7;      
  comp_tbuffer[comp_tptr++] = 0xFB;

  /* pop edx */
  comp_tbuffer[comp_tptr++] = 0x5A;
}

#define MULA comp_mula ();
#define mula comp_mula ();

void comp_mula (void)
{
  /* imul ebx */
  comp_tbuffer[comp_tptr++] = 0xF7;      
  comp_tbuffer[comp_tptr++] = 0xEB;
}

#define INCA comp_inca ();
#define inca comp_inca ();

void comp_inca (void)
{
  /* inc eax */
  comp_tbuffer[comp_tptr++] = 0x40;      
}

#define DECA comp_deca ();
#define deca comp_deca ();

void comp_deca (void)
{
  /* dec eax */
  comp_tbuffer[comp_tptr++] = 0x48;      
}

#define ANDA comp_anda ();
#define anda comp_anda ();

void comp_anda (void)
{
  /* and eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x21;      
  comp_tbuffer[comp_tptr++] = 0xD8;      
}

#define GORA comp_gora ();
#define gora comp_gora ();

void comp_gora (void)
{
  /* or eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x09;      
  comp_tbuffer[comp_tptr++] = 0xD8;      
}

#define XORA comp_xora ();
#define xora comp_xora ();

void comp_xora (void)
{
  /* xor eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x31;      
  comp_tbuffer[comp_tptr++] = 0xD8;      
}

#define SHLA comp_shla ();
#define shla comp_shla ();

void comp_shla (void)
{
  /*  mov cl, bl */
  comp_tbuffer[comp_tptr++] = 0x88;      
  comp_tbuffer[comp_tptr++] = 0xD9;     

  /*  shl eax, cl */
  comp_tbuffer[comp_tptr++] = 0xD3;      
  comp_tbuffer[comp_tptr++] = 0xE0;     
}

#define SLIA(n) comp_slia (n);
#define slia(n) comp_slia (n);

void comp_slia (int value)
{
  imm val; val.w = value;

  if (value > 0xFF) 
  { 
    printf ("comp_slia: E4\n");
    exit (-1);
  }

  /* shl eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0xC1;      
  comp_tbuffer[comp_tptr++] = 0xE0;      
  comp_tbuffer[comp_tptr++] = val.b[0];
}

#define SHRA comp_shra ();
#define shra comp_shra ();

void comp_shra (void)
{
  /*  mov cl, bl */
  comp_tbuffer[comp_tptr++] = 0x88;      
  comp_tbuffer[comp_tptr++] = 0xD9;     

  /*  shr eax, cl */
  comp_tbuffer[comp_tptr++] = 0xD3;      
  comp_tbuffer[comp_tptr++] = 0xE8;     
}

#define SRIA(n) comp_sria (n);
#define sria(n) comp_sria (n);

void comp_sria (int value)
{
  imm val; val.w = value;

  if (value > 0xFF) 
  { 
    printf ("comp_sria: E4\n");
    exit (-1);
  }

  /* shr eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0xC1;      
  comp_tbuffer[comp_tptr++] = 0xE8;      
  comp_tbuffer[comp_tptr++] = val.b[0];
}

#define CMPA comp_cmpa ();
#define cmpa comp_cmpa ();

void comp_cmpa (void)
{
  /*  cmp eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x39;      
  comp_tbuffer[comp_tptr++] = 0xD8;      
}

#define LDRA comp_ldra ();
#define ldra comp_ldra ();

void comp_ldra (void)
{
  /*  mov eax, [ebx] */
  comp_tbuffer[comp_tptr++] = 0x8B;      
  comp_tbuffer[comp_tptr++] = 0x03;      
}

#define STRA comp_stra ();
#define stra comp_stra ();

void comp_stra (void)
{
  /*  mov [ebx], eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0x03;      
}

/* primitives which accesses accumulator B */

#define LIB(n) comp_lib (n);
#define lib(n) comp_lib (n);

void comp_lib (int value)
{
  imm val; val.w = value;

  /* mov ebx,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0xBB;      
  comp_immediate (val);
}

#define PSBD comp_psbd ();
#define psbd comp_psbd ();

void comp_psbd (void)
{
  /* mov [edi], ebx */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0x1F;

  /* add edi, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xC7;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
}

#define PSBR comp_psbr ();
#define psbr comp_psbr (),

void comp_psbr (void)
{
  /* mov [esi], ebx */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0x1E;

  /* add esi, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xC6;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  
}

#define PLDB comp_pldb ();
#define pldb comp_pldb ();

void comp_pldb (void)
{
  /* sub edi, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xEF;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /* mov ebx, [edi] */
  comp_tbuffer[comp_tptr++] = 0x8B;      
  comp_tbuffer[comp_tptr++] = 0x1F;
}

#define PLRB comp_plrb ();
#define plrb comp_plrb ();

void comp_plrb (void)
{
  /* sub esi, 4 */
  comp_tbuffer[comp_tptr++] = 0x81;      
  comp_tbuffer[comp_tptr++] = 0xEE;
  comp_tbuffer[comp_tptr++] = 0x04;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /* mov ebx, [esi] */
  comp_tbuffer[comp_tptr++] = 0x8B;      
  comp_tbuffer[comp_tptr++] = 0x1E;
}

#define TDB comp_tdb ();
#define tdb comp_tdb ();

void comp_tdb (void)
{
  /* mov ebx, edi */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xFB;
}

#define TRB comp_trb ();
#define trb comp_trb ();

void comp_trb (void)
{
  /* mov ebx, esi */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xF3;
}

#define ADDB comp_addb ();
#define addb comp_addb ();

void comp_addb (void)
{
  /* add ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x01;      
  comp_tbuffer[comp_tptr++] = 0xC3;
}

#define SUBB comp_subb ();
#define subb comp_subb ();

void comp_subb (void)
{
  /* sub ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x29;      
  comp_tbuffer[comp_tptr++] = 0xC3;

}

#define DIVB comp_divb ();
#define divb comp_divb ();

void comp_divb (void)
{
  /* push edx */
  comp_tbuffer[comp_tptr++] = 0x52;      

  /* xor edx, edx */
  comp_tbuffer[comp_tptr++] = 0x31;      
  comp_tbuffer[comp_tptr++] = 0xD2;  

  /* mov ecx, eax */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xC1;

  /* xchg eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x93;      

  /* idiv ebx */
  comp_tbuffer[comp_tptr++] = 0xF7;      
  comp_tbuffer[comp_tptr++] = 0xFB;      

  /* mov ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x89;
  comp_tbuffer[comp_tptr++] = 0xC3;

  /* mov eax, ecx */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0xC8;

  /* pop edx */
  comp_tbuffer[comp_tptr++] = 0x5A;        
}

#define MULB comp_mulb ();
#define mulb comp_mulb ();

void comp_mulb (void)
{
  /* xchg eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x93;      

  /* imul ebx */
  comp_tbuffer[comp_tptr++] = 0xF7;      
  comp_tbuffer[comp_tptr++] = 0xEB;

  /* xchg eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x93;      
}

#define INCB comp_incb ();
#define incb comp_incb ();

void comp_incb (void)
{
  /* inc ebx */
  comp_tbuffer[comp_tptr++] = 0x43;      
}

#define DECB comp_decb ();
#define decb comp_decb ();

void comp_decb (void)
{
  /* dec ebx */
  comp_tbuffer[comp_tptr++] = 0x4B;      
}

#define ANDB comp_andb ();
#define andb comp_andb ();

void comp_andb (void)
{
  /* and ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x21;      
  comp_tbuffer[comp_tptr++] = 0xC3;      
}

#define GORB comp_gorb ();
#define gorb comp_gorb ();

void comp_gorb (void)
{
  /* or ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x09;      
  comp_tbuffer[comp_tptr++] = 0xC3;      
}

#define XORB comp_xorb ();
#define xorb comp_xorb ();

void comp_xorb (void)
{
  /* xor ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x31;      
  comp_tbuffer[comp_tptr++] = 0xC3;      
}

#define SHLB comp_shlb ();
#define shlb comp_shlb ();

void comp_shlb (void)
{
  /*  mov cl, al */
  comp_tbuffer[comp_tptr++] = 0x88;      
  comp_tbuffer[comp_tptr++] = 0xC1;     

  /*  shl ebx, cl */
  comp_tbuffer[comp_tptr++] = 0xD3;      
  comp_tbuffer[comp_tptr++] = 0xE3;     
}

#define SLIB(n) comp_slib (n);
#define slib(n) comp_slib (n);

void comp_slib (int value)
{
  imm val; val.w = value;

  if (value > 0xFF) 
  { 
    printf ("comp_slib: E4\n");
    exit (-1);
  }

  /* shl ebx,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0xC1;      
  comp_tbuffer[comp_tptr++] = 0xE3;      
  comp_tbuffer[comp_tptr++] = val.b[0];
}

#define SHRB comp_shrb ();
#define shrb comp_shrb ();

void comp_shrb (void)
{
  /*  mov cl, al */
  comp_tbuffer[comp_tptr++] = 0x88;      
  comp_tbuffer[comp_tptr++] = 0xC1;     

  /*  shr ebx, cl */
  comp_tbuffer[comp_tptr++] = 0xD3;      
  comp_tbuffer[comp_tptr++] = 0xEB;     
}

#define SRIB(n) comp_srib (n);
#define srib(n) comp_srib (n);

void comp_srib (int value)
{
  imm val; val.w = value;

  if (value > 0xFF) 
  { 
    printf ("comp_srib: E4\n");
    exit (-1);
  }

  /* shr eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0xC1;      
  comp_tbuffer[comp_tptr++] = 0xEB;      
  comp_tbuffer[comp_tptr++] = val.b[0];
}

#define LDRB comp_ldrb ();
#define ldrb comp_ldrb ();

void comp_ldrb (void)
{
  /*  mov ebx, [eax] */
  comp_tbuffer[comp_tptr++] = 0x8B;      
  comp_tbuffer[comp_tptr++] = 0x18;      
}

#define STRB comp_strb ();
#define strb comp_strb ();

void comp_strb (void)
{
  /*  mov [eax], ebx */
  comp_tbuffer[comp_tptr++] = 0x89;      
  comp_tbuffer[comp_tptr++] = 0x18;      
}

/* common primitives */

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

