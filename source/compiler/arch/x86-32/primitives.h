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
 * Non accessible registers:
 *
 *      S - scratch         ECX
 *      F - flags           EFL
 ******************************************************************************/

#ifdef __linux__
#define COMP_PROLOG asm volatile ("push %ebx");               \
                    asm volatile ("push %edi");               \
                    asm volatile ("push %esi");               \
                    asm volatile ("mov  comp_dstack,  %edi"); \
                    asm volatile ("mov  comp_rstack,  %esi"); \
                    asm volatile ("mov  comp_a,       %eax"); \
                    asm volatile ("mov  comp_b,       %ebx"); \
                    asm volatile ("mov  comp_adr,     %ecx"); \
                    asm volatile ("call *%ecx");

#define COMP_EPILOG asm volatile ("pop %esi"); \
                    asm volatile ("pop %edi"); \
                    asm volatile ("pop %ebx");
#else
#define COMP_PROLOG asm volatile ("push %ebx");               \
                    asm volatile ("push %edi");               \
                    asm volatile ("push %esi");               \
                    asm volatile ("mov  _comp_dstack,  %edi"); \
                    asm volatile ("mov  _comp_rstack,  %esi"); \
                    asm volatile ("mov  _comp_a,       %eax"); \
                    asm volatile ("mov  _comp_b,       %ebx"); \
                    asm volatile ("mov  _comp_adr,     %ecx"); \
                    asm volatile ("call *%ecx");

#define COMP_EPILOG asm volatile ("pop %esi"); \
                    asm volatile ("pop %edi"); \
                    asm volatile ("pop %ebx");
#endif


#define LABEL comp_Label ();
#define label comp_Label ();

#define TAIL comp_cofs
#define tail comp_cofs


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
#define tar comp_tar ();

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

#define ADIA(n) comp_adia (n);
#define adia(n) comp_adia (n);

void comp_adia (int value)
{
  imm val; val.w = value;

  /* add eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x05;      
  comp_immediate (val);
}

#define SUBA comp_suba ();
#define suba comp_suba ();

void comp_suba (void)
{
  /* sub eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x29;      
  comp_tbuffer[comp_tptr++] = 0xD8;

}

#define SBIA(n) comp_sbia (n);
#define sbia(n) comp_sbia (n);

void comp_sbia (int value)
{
  imm val; val.w = value;

  /* sub eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x2D;      
  comp_immediate (val);
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

#define ANIA(n) comp_ania (n);
#define ania(n) comp_ania (n);

void comp_ania (int value)
{
  imm val; val.w = value;

  /* and eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x25;      
  comp_immediate (val);
}

#define GORA comp_gora ();
#define gora comp_gora ();

void comp_gora (void)
{
  /* or eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x09;      
  comp_tbuffer[comp_tptr++] = 0xD8;      
}

#define ORIA(n) comp_oria (n);
#define oria(n) comp_oria (n);

void comp_oria (int value)
{
  imm val; val.w = value;

  /* or eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x0D;      
  comp_immediate (val);
}

#define XORA comp_xora ();
#define xora comp_xora ();

void comp_xora (void)
{
  /* xor eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x31;      
  comp_tbuffer[comp_tptr++] = 0xD8;      
}

#define XOIA(n) comp_xoia (n);
#define xoia(n) comp_xoia (n);

void comp_xoia (int value)
{
  imm val; val.w = value;

  /* xor eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x35;      
  comp_immediate (val);
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

#define CPIA(n) comp_cpia (n);
#define cpia(n) comp_cpia (n);

void comp_cpia (int value)
{
  imm val; val.w = value;

  /* cmp eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x3D;      
  comp_immediate (val);
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

#define ADIB(n) comp_adib (n);
#define adib(n) comp_adib (n);

void comp_adib (int value)
{
  imm val; val.w = value;

  /* add ebx,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xC3;      
  comp_immediate (val);
}

#define SUBB comp_subb ();
#define subb comp_subb ();

void comp_subb (void)
{
  /* sub ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x29;      
  comp_tbuffer[comp_tptr++] = 0xC3;

}

#define SBIB(n) comp_sbib (n);
#define sbib(n) comp_sbib (n);

void comp_sbib (int value)
{
  imm val; val.w = value;

  /* sub ebx,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xEB;      
  comp_immediate (val);
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

#define ANIB(n) comp_anib (n);
#define anib(n) comp_anib (n);

void comp_anib (int value)
{
  imm val; val.w = value;

  /* and ebx,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xE3;      
  comp_immediate (val);
}

#define GORB comp_gorb ();
#define gorb comp_gorb ();

void comp_gorb (void)
{
  /* or ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x09;      
  comp_tbuffer[comp_tptr++] = 0xC3;      
}

#define ORIB(n) comp_orib (n);
#define orib(n) comp_orib (n);

void comp_orib (int value)
{
  imm val; val.w = value;

  /* or ebx,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xCB;      
  comp_immediate (val);
}

#define XORB comp_xorb ();
#define xorb comp_xorb ();

void comp_xorb (void)
{
  /* xor ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x31;      
  comp_tbuffer[comp_tptr++] = 0xC3;      
}

#define XOIB(n) comp_xoib (n);
#define xoib(n) comp_xoib (n);

void comp_xoib (int value)
{
  imm val; val.w = value;

  /* xor ebx,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xF3;      
  comp_immediate (val);
}

#define CMPB comp_cmpb ();
#define cmpb comp_cmpb ();

void comp_cmpb (void)
{
  /* cmp ebx, eax */
  comp_tbuffer[comp_tptr++] = 0x39;      
  comp_tbuffer[comp_tptr++] = 0xC3;      
}

#define CPIB(n) comp_cpib (n);
#define cpib(n) comp_cpib (n);

void comp_cpib (int value)
{
  imm val; val.w = value;

  /* cmp ebx,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xFB;      
  comp_immediate (val);
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


/* branch primitives */

#define CI(t) comp_ci (t);
#define ci(t) comp_ci (t);

void comp_ci (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_ci: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* tail-call optimation */

       /* mov ecx, trace */
       comp_tbuffer[comp_tptr++] = 0xB9;
       comp_immediate (val);      

  if (trace == tail)
  {
       /* jmp ecx */
       comp_tbuffer[comp_tptr++] = 0xFF;
       comp_tbuffer[comp_tptr++] = 0xE1;
  }
  else
  {
       /* call ecx */
       comp_tbuffer[comp_tptr++] = 0xFF;
       comp_tbuffer[comp_tptr++] = 0xD1;
  }
}

#define CIEQ(t) comp_cieq (t);
#define cieq(t) comp_cieq (t);

void comp_cieq (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_cieq: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x75;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        call ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD1;

  /* ntaken: */
}

#define CIGR(t) comp_cigr (t);
#define cigr(t) comp_cigr (t);

void comp_cigr (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_cigr: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: jng ntaken */
  comp_tbuffer[comp_tptr++] = 0x7E;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        call ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD1;

  /* ntaken: */
}

#define CILE(t) comp_cile (t);
#define cile(t) comp_cile (t);

void comp_cile (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_cile: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: jnl ntaken */
  comp_tbuffer[comp_tptr++] = 0x7D;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        call ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD1;

  /* ntaken: */
}

#define CNZA(t) comp_cnza (t);
#define cnza(t) comp_cnza (t);

void comp_cnza (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_cnza: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp eax, 0 */
  comp_tbuffer[comp_tptr++] = 0x3D;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        je ntaken */
  comp_tbuffer[comp_tptr++] = 0x74;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        call ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD1;

  /* ntaken: */
}

#define CIZA(t) comp_ciza (t);
#define ciza(t) comp_ciza (t);

void comp_ciza (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_ciza: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp eax, 0 */
  comp_tbuffer[comp_tptr++] = 0x3D;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x75;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        call ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD1;

  /* ntaken: */
}

#define CNZB(t) comp_cnzb (t);
#define cnzb(t) comp_cnzb (t);

void comp_cnzb (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_cnzb: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp ebx, 0 */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xFB;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        je ntaken */
  comp_tbuffer[comp_tptr++] = 0x74;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        call ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD1;

  /* ntaken: */
}

#define CIZB(t) comp_cizb (t);
#define cizb(t) comp_cizb (t);

void comp_cizb (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_cizb: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp ebx, 0 */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xFB;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x75;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        call ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD1;

  /* ntaken: */
}

#define CRA comp_cra ();
#define cra comp_cra ();

void comp_cra (void)
{
  imm val; val.w = (int) comp_cbuffer;

  /* add eax, comp_cbuffer */
  comp_tbuffer[comp_tptr++] = 0x05;
  comp_immediate (val);

  /* call eax */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD0;
}

#define CRB comp_crb ();
#define crb comp_crb ();

void comp_crb (void)
{
  imm val; val.w = (int) comp_cbuffer;

  /* add ebx, comp_cbuffer */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xC3;
  comp_immediate (val);

  /* call ebx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xD3;
}

#define BRA comp_bra ();
#define bra comp_bra ();

void comp_bra (void)
{
  imm val; val.w = (int) comp_cbuffer;

  /* add eax, comp_cbuffer */
  comp_tbuffer[comp_tptr++] = 0x05;
  comp_immediate (val);

  /* jmp eax */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE0;
}

#define BRB comp_brb ();
#define brb comp_brb ();

void comp_brb (void)
{
  imm val; val.w = (int) comp_cbuffer;

  /* add ebx, comp_cbuffer */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xC3;
  comp_immediate (val);

  /* jmp ebx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE3;
}

#define BI(t) comp_bi (t);
#define bi(t) comp_bi (t);

void comp_bi (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bi: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /* jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;
}

#define BIEQ(t) comp_bieq (t);
#define bieq(t) comp_bieq (t);

void comp_bieq (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bieq: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x75;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

#define BIGR(t) comp_bigr (t);
#define bigr(t) comp_bigr (t);

void comp_bigr (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bigr: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: jng ntaken */
  comp_tbuffer[comp_tptr++] = 0x7E;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

#define BILE(t) comp_bile (t);
#define bile(t) comp_bile (t);

void comp_bile (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bile: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: jnl ntaken */
  comp_tbuffer[comp_tptr++] = 0x7D;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

#define BNZA(t) comp_bnza (t);
#define bnza(t) comp_bnza (t);

void comp_bnza (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bnza: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp eax, 0 */
  comp_tbuffer[comp_tptr++] = 0x3D;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        je ntaken */
  comp_tbuffer[comp_tptr++] = 0x74;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

#define BIZA(t) comp_biza (t);
#define biza(t) comp_biza (t);

void comp_biza (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_biza: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp eax, 0 */
  comp_tbuffer[comp_tptr++] = 0x3D;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x75;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

#define BNZB(t) comp_bnzb (t);
#define bnzb(t) comp_bnzb (t);

void comp_bnzb (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bnzb: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp ebx, 0 */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xFB;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        je ntaken */
  comp_tbuffer[comp_tptr++] = 0x74;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

#define BIZB(t) comp_bizb (t);
#define bizb(t) comp_bizb (t);

void comp_bizb (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bizb: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp ebx, 0 */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0xFB;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x75;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

#define RET comp_return ();
#define ret comp_return ();

void comp_return (void)
{
  comp_tbuffer[comp_tptr++] = 0xC3;
}

/* primitives whic directly access TOS in data stack */

#define LID(n) comp_lid (n);
#define lid(n) comp_lid (n);

void comp_lid (int value)
{
  imm val; val.w = value;

  /* mov dword [edi-4],nnnnnnnn */
  comp_tbuffer[comp_tptr++] = 0xC7;      
  comp_tbuffer[comp_tptr++] = 0x47;      
  comp_tbuffer[comp_tptr++] = 0xFC;      
  comp_immediate (val);
}

#define INCD comp_incd ();
#define incd comp_incd ();

void comp_incd (void)
{
  /* inc dword [edi-4] */
  comp_tbuffer[comp_tptr++] = 0xFF;      
  comp_tbuffer[comp_tptr++] = 0x47;
  comp_tbuffer[comp_tptr++] = 0xFC;      
}

#define DECD comp_decd ();
#define decd comp_decd ();

void comp_decd (void)
{
  /* dec dword [edi-4] */
  comp_tbuffer[comp_tptr++] = 0xFF;      
  comp_tbuffer[comp_tptr++] = 0x4F;
  comp_tbuffer[comp_tptr++] = 0xFC;        
}

#define BNZD(n) comp_bnzd (n);
#define bnzd(n) comp_bnzd (n);

void comp_bnzd (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bnzd: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp dword [edi-4], 0 */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0x7F;
  comp_tbuffer[comp_tptr++] = 0xFC;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        je ntaken */
  comp_tbuffer[comp_tptr++] = 0x74;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

#define BIZD(t) comp_bizd (t);
#define bizd(t) comp_bizd (t);

void comp_bizd (int trace)
{
  imm val;

  if ((trace > comp_clen) || (trace < 0)) 
  { 
    printf ("comp_bizd: E5\n"); 
    exit (-1); 
  }

  int address = (int) comp_cbuffer + trace;
      val.w   = address;

  /* taken: cmp dword [edi], 0 */
  comp_tbuffer[comp_tptr++] = 0x81;
  comp_tbuffer[comp_tptr++] = 0x7F;
  comp_tbuffer[comp_tptr++] = 0xFC;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;
  comp_tbuffer[comp_tptr++] = 0x00;

  /*        jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x75;
  comp_tbuffer[comp_tptr++] = 0x07;

  /*        mov ecx, trace */
  comp_tbuffer[comp_tptr++] = 0xB9;
  comp_immediate (val);      

  /*        jmp ecx */
  comp_tbuffer[comp_tptr++] = 0xFF;
  comp_tbuffer[comp_tptr++] = 0xE1;

  /* ntaken: */
}

/* common primitives */

#define SWAP comp_swap ();
#define swap comp_swap ();

void comp_swap (void)
{
  /* xchg eax, ebx */
  comp_tbuffer[comp_tptr++] = 0x93;      
}

#define LISA(n) comp_lisa (n);
#define lisa(n) comp_lisa (n);

void comp_lisa (int value)
{
  switch (value)
  {
    case 0:  /* mov eax, [edi-4] */
             comp_tbuffer[comp_tptr++] = 0x8B;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xFC;
             break;
    case 1:  /* mov eax, [edi-8] */
             comp_tbuffer[comp_tptr++] = 0x8B;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF8;
             break;
    case 2:  /* mov eax, [edi-12] */
             comp_tbuffer[comp_tptr++] = 0x8B;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF4;
             break;
    case 3:  /* mov eax, [edi-16] */
             comp_tbuffer[comp_tptr++] = 0x8B;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF0;
             break;
    default: printf ("comp_lisa: E5\n"); 
             exit (-1); 
  }
}

#define LISB(n) comp_lisb (n);
#define lisb(n) comp_lisb (n);

void comp_lisb (int value)
{
  switch (value)
  {
    case 0:  /* mov ebx, [edi-4] */
             comp_tbuffer[comp_tptr++] = 0x8B;
             comp_tbuffer[comp_tptr++] = 0x5F;
             comp_tbuffer[comp_tptr++] = 0xFC;
             break;
    case 1:  /* mov ebx, [edi-8] */
             comp_tbuffer[comp_tptr++] = 0x8B;
             comp_tbuffer[comp_tptr++] = 0x5F;
             comp_tbuffer[comp_tptr++] = 0xF8;
             break;
    case 2:  /* mov ebx, [edi-12] */
             comp_tbuffer[comp_tptr++] = 0x8B;
             comp_tbuffer[comp_tptr++] = 0x5F;
             comp_tbuffer[comp_tptr++] = 0xF4;
             break;
    case 3:  /* mov ebx, [edi-16] */
             comp_tbuffer[comp_tptr++] = 0x8B;
             comp_tbuffer[comp_tptr++] = 0x5F;
             comp_tbuffer[comp_tptr++] = 0xF0;
             break;
    default: printf ("comp_lisb: E5\n"); 
             exit (-1); 
  }
}



#define SISA(n) comp_sisa (n);
#define sisa(n) comp_sisa (n);

void comp_sisa (int value)
{
  switch (value)
  {
    case 0:  /* mov [edi-4], eax */
             comp_tbuffer[comp_tptr++] = 0x89;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xFC;
             break;
    case 1:  /* mov [edi-8], eax */
             comp_tbuffer[comp_tptr++] = 0x89;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF8;
             break;
    case 2:  /* mov [edi-12], eax */
             comp_tbuffer[comp_tptr++] = 0x89;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF4;
             break;
    case 3:  /* mov [edi-16], eax */
             comp_tbuffer[comp_tptr++] = 0x89;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF0;
             break;
    default: printf ("comp_sisa: E5\n"); 
             exit (-1); 
  }
}

#define SISB(n) comp_sisb (n);
#define sisb(n) comp_sisb (n);

void comp_sisb (int value)
{
  switch (value)
  {
    case 0:  /* mov [edi-4], ebx */
             comp_tbuffer[comp_tptr++] = 0x89;
             comp_tbuffer[comp_tptr++] = 0x5F;
             comp_tbuffer[comp_tptr++] = 0xFC;
             break;
    case 1:  /* mov [edi-8], ebx */
             comp_tbuffer[comp_tptr++] = 0x89;
             comp_tbuffer[comp_tptr++] = 0x5F;
             comp_tbuffer[comp_tptr++] = 0xF8;
             break;
    case 2:  /* mov [edi-12], ebx */
             comp_tbuffer[comp_tptr++] = 0x89;
             comp_tbuffer[comp_tptr++] = 0x5F;
             comp_tbuffer[comp_tptr++] = 0xF4;
             break;
    case 3:  /* mov [edi-16], ebx */
             comp_tbuffer[comp_tptr++] = 0x89;
             comp_tbuffer[comp_tptr++] = 0x5F;
             comp_tbuffer[comp_tptr++] = 0xF0;
             break;
    default: printf ("comp_sisb: E5\n"); 
             exit (-1); 
  }
}

#define INIS(n) comp_inis (n);
#define inis(n) comp_inis (n);

void comp_inis (int value)
{
  switch (value)
  {
    case 0:  /* inc dword [edi-4] */
             comp_tbuffer[comp_tptr++] = 0xFF;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xFC;
             break;
    case 1:  /* inc dword [edi-8] */
             comp_tbuffer[comp_tptr++] = 0xFF;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF8;
             break;
    case 2:  /* inc dword [edi-12] */
             comp_tbuffer[comp_tptr++] = 0xFF;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF4;
             break;
    case 3:  /* inc dword [edi-16] */
             comp_tbuffer[comp_tptr++] = 0xFF;
             comp_tbuffer[comp_tptr++] = 0x47;
             comp_tbuffer[comp_tptr++] = 0xF0;
             break;
    default: printf ("comp_incs: E5\n"); 
             exit (-1); 
  }
}

#define DEIS(n) comp_deis (n);
#define deis(n) comp_deis (n);

void comp_deis (int value)
{
  switch (value)
  {
    case 0:  /* dec dword [edi-4] */
             comp_tbuffer[comp_tptr++] = 0xFF;
             comp_tbuffer[comp_tptr++] = 0x4F;
             comp_tbuffer[comp_tptr++] = 0xFC;
             break;
    case 1:  /* dec dword [edi-8] */
             comp_tbuffer[comp_tptr++] = 0xFF;
             comp_tbuffer[comp_tptr++] = 0x4F;
             comp_tbuffer[comp_tptr++] = 0xF8;
             break;
    case 2:  /* dec dword [edi-12] */
             comp_tbuffer[comp_tptr++] = 0xFF;
             comp_tbuffer[comp_tptr++] = 0x4F;
             comp_tbuffer[comp_tptr++] = 0xF4;
             break;
    case 3:  /* dec dword [edi-16] */
             comp_tbuffer[comp_tptr++] = 0xFF;
             comp_tbuffer[comp_tptr++] = 0x4F;
             comp_tbuffer[comp_tptr++] = 0xF0;
             break;
    default: printf ("comp_decs: E5\n"); 
             exit (-1); 
  }
}

