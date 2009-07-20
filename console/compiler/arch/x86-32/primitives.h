/******************************************************
 * Ngaro
 *
 *|F|
 *|F| FILE: primitives.h
 *|F|
 *
 * AOT natice-code compiler by Matthias Schirm.
 * Released into the public domain
 ******************************************************/

#define COMP_REGISTER register int comp_acc asm("eax"); \
                      register int comp_opn asm("ebx");

#define COMP_PROLOG asm volatile ("push %eax");               \
                    asm volatile ("push %ebx");               \
                    asm volatile ("push %ecx");               \
                    asm volatile ("push %edx");               \
                    asm volatile ("push %edi");               \
                    asm volatile ("mov $comp_dstack, %ecx");  \
                    asm volatile ("mov $comp_rstack, %edx");  \
                    asm volatile ("xor %edi, %edi");

#define COMP_EPILOG asm volatile ("pop %edi"); \
                    asm volatile ("pop %edx"); \
                    asm volatile ("pop %ecx"); \
                    asm volatile ("pop %ebx"); \
                    asm volatile ("pop %eax");

void comp_return (void)
{
  comp_tbuffer[comp_tptr++] = 0xC3;      /* ret */
}

void comp_lit (imm value)
{ 
  comp_tbuffer[comp_tptr++] = 0x89;      /* mov [ecx], ebx */
  comp_tbuffer[comp_tptr++] = 0x19;

  comp_tbuffer[comp_tptr++] = 0x89;      /* mov ebx, eax */
  comp_tbuffer[comp_tptr++] = 0xC3;

  comp_tbuffer[comp_tptr++] = 0xB8;      /* mov eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = value.b[3];
  comp_tbuffer[comp_tptr++] = value.b[2];
  comp_tbuffer[comp_tptr++] = value.b[1];
  comp_tbuffer[comp_tptr++] = value.b[0];

  comp_tbuffer[comp_tptr++] = 0x83;      /* add ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xC1;
  comp_tbuffer[comp_tptr++] = 0x04;
}

void comp_dup (void)
{
  comp_tbuffer[comp_tptr++] = 0x89;      /* mov [ecx], ebx */
  comp_tbuffer[comp_tptr++] = 0x19;

  comp_tbuffer[comp_tptr++] = 0x89;      /* mov ebx, eax */
  comp_tbuffer[comp_tptr++] = 0xC3;

  comp_tbuffer[comp_tptr++] = 0x83;      /* add ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xC1;
  comp_tbuffer[comp_tptr++] = 0x04;
}

void comp_drop (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;      /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x89;      /* mov eax, ebx */
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_swap (void)
{
  comp_tbuffer[comp_tptr++] = 0x93;      /* xchg eax, ebx */
}

void comp_push (void)
{
  comp_tbuffer[comp_tptr++] = 0x89;      /* mov [edx], eax */
  comp_tbuffer[comp_tptr++] = 0x02;

  comp_tbuffer[comp_tptr++] = 0x83;      /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x89;      /* mov eax, ebx */
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;

  comp_tbuffer[comp_tptr++] = 0x83;      /* add edx, 4 */
  comp_tbuffer[comp_tptr++] = 0xC2;
  comp_tbuffer[comp_tptr++] = 0x04;
}

void comp_pop (void)
{
  comp_tbuffer[comp_tptr++] = 0x89;      /* mov [ecx], ebx */
  comp_tbuffer[comp_tptr++] = 0x19;

  comp_tbuffer[comp_tptr++] = 0x83;      /* sub edx, 4 */
  comp_tbuffer[comp_tptr++] = 0xEA;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x89;      /* mov ebx, eax */
  comp_tbuffer[comp_tptr++] = 0xC3;

  comp_tbuffer[comp_tptr++] = 0x83;      /* add ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xC1;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov eax, [edx] */
  comp_tbuffer[comp_tptr++] = 0x02;
}

void comp_call (function trace)
{
  imm loc; loc.w = (int) trace;

  comp_tbuffer[comp_tptr++] = 0xBF;      /* mov edi,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = loc.b[3];
  comp_tbuffer[comp_tptr++] = loc.b[2];
  comp_tbuffer[comp_tptr++] = loc.b[1];
  comp_tbuffer[comp_tptr++] = loc.b[0];

  comp_tbuffer[comp_tptr++] = 0xFF;      /* call edi */
  comp_tbuffer[comp_tptr++] = 0xD7;
}

void comp_jump (function trace)
{
  imm loc; loc.w = (int) trace;

  comp_tbuffer[comp_tptr++] = 0xBF;      /* mov edi,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = loc.b[3];
  comp_tbuffer[comp_tptr++] = loc.b[2];
  comp_tbuffer[comp_tptr++] = loc.b[1];
  comp_tbuffer[comp_tptr++] = loc.b[0];

  comp_tbuffer[comp_tptr++] = 0xFF;      /* jmp edi */
  comp_tbuffer[comp_tptr++] = 0xE7;
}

void comp_gt_jump (function trace)
{
  imm loc; loc.w = (int) trace;

  comp_tbuffer[comp_tptr++] = 0x83;       /* sub ecx, 16 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x10;

  comp_tbuffer[comp_tptr++] = 0xBF;       /* mov edi,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = loc.b[3];
  comp_tbuffer[comp_tptr++] = loc.b[2];
  comp_tbuffer[comp_tptr++] = loc.b[1];
  comp_tbuffer[comp_tptr++] = loc.b[0];

  comp_tbuffer[comp_tptr++] = 0x39;      /* cmp ebx, eax*/
  comp_tbuffer[comp_tptr++] = 0xC3;

  comp_tbuffer[comp_tptr++] = 0x7E;      /* jng ntaken */
  comp_tbuffer[comp_tptr++] = 0x08;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov eax, [ecx-8] */
  comp_tbuffer[comp_tptr++] = 0x41;
  comp_tbuffer[comp_tptr++] = 0xF8;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov ebx, [ecx-4] */
  comp_tbuffer[comp_tptr++] = 0x59;
  comp_tbuffer[comp_tptr++] = 0xFC;

  comp_tbuffer[comp_tptr++] = 0xFF;      /* jmp edi */
  comp_tbuffer[comp_tptr++] = 0xE7;

  /* ntaken: */

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov eax, [ecx-8] */
  comp_tbuffer[comp_tptr++] = 0x41;
  comp_tbuffer[comp_tptr++] = 0xF8;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov ebx, [ecx-4] */
  comp_tbuffer[comp_tptr++] = 0x59;
  comp_tbuffer[comp_tptr++] = 0xFC;
}

void comp_lt_jump (function trace)
{
  imm loc; loc.w = (int) trace;

  comp_tbuffer[comp_tptr++] = 0x83;       /* sub ecx, 16 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x10;

  comp_tbuffer[comp_tptr++] = 0xBF;       /* mov edi,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = loc.b[3];
  comp_tbuffer[comp_tptr++] = loc.b[2];
  comp_tbuffer[comp_tptr++] = loc.b[1];
  comp_tbuffer[comp_tptr++] = loc.b[0];

  comp_tbuffer[comp_tptr++] = 0x39;      /* cmp ebx, eax*/
  comp_tbuffer[comp_tptr++] = 0xC3;

  comp_tbuffer[comp_tptr++] = 0x7D;      /* jnl ntaken */
  comp_tbuffer[comp_tptr++] = 0x08;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov eax, [ecx-8] */
  comp_tbuffer[comp_tptr++] = 0x41;
  comp_tbuffer[comp_tptr++] = 0xF8;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov ebx, [ecx-4] */
  comp_tbuffer[comp_tptr++] = 0x59;
  comp_tbuffer[comp_tptr++] = 0xFC;

  comp_tbuffer[comp_tptr++] = 0xFF;      /* jmp edi */
  comp_tbuffer[comp_tptr++] = 0xE7;

  /* ntaken: */

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov eax, [ecx-8] */
  comp_tbuffer[comp_tptr++] = 0x41;
  comp_tbuffer[comp_tptr++] = 0xF8;

  comp_tbuffer[comp_tptr++] = 0x8B;      /* mov ebx, [ecx-4] */
  comp_tbuffer[comp_tptr++] = 0x59;
  comp_tbuffer[comp_tptr++] = 0xFC;
}

void comp_ne_jump (function trace)
{
  imm loc; loc.w = (int) trace;

  comp_tbuffer[comp_tptr++] = 0x83;       /* sub ecx, 16 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x10;

  comp_tbuffer[comp_tptr++] = 0xBF;       /* mov edi,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = loc.b[3];
  comp_tbuffer[comp_tptr++] = loc.b[2];
  comp_tbuffer[comp_tptr++] = loc.b[1];
  comp_tbuffer[comp_tptr++] = loc.b[0];

  comp_tbuffer[comp_tptr++] = 0x39;     /* cmp eax, ebx*/
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x75;     /* jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x08;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov eax, [ecx-8] */
  comp_tbuffer[comp_tptr++] = 0x41;
  comp_tbuffer[comp_tptr++] = 0xF8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx-4] */
  comp_tbuffer[comp_tptr++] = 0x59;
  comp_tbuffer[comp_tptr++] = 0xFC;

  comp_tbuffer[comp_tptr++] = 0xFF;     /* jmp edi */
  comp_tbuffer[comp_tptr++] = 0xE7;

  /* ntaken: */

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov eax, [ecx-8] */
  comp_tbuffer[comp_tptr++] = 0x41;
  comp_tbuffer[comp_tptr++] = 0xF8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx-4] */
  comp_tbuffer[comp_tptr++] = 0x59;
  comp_tbuffer[comp_tptr++] = 0xFC;
}

void comp_eq_jump (function trace)
{
  imm loc; loc.w = (int) trace;

  comp_tbuffer[comp_tptr++] = 0x83;       /* sub ecx, 16 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x10;

  comp_tbuffer[comp_tptr++] = 0xBF;       /* mov edi,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = loc.b[3];
  comp_tbuffer[comp_tptr++] = loc.b[2];
  comp_tbuffer[comp_tptr++] = loc.b[1];
  comp_tbuffer[comp_tptr++] = loc.b[0];

  comp_tbuffer[comp_tptr++] = 0x39;     /* cmp eax, ebx*/
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x74;     /* je taken */
  comp_tbuffer[comp_tptr++] = 0x02;

  comp_tbuffer[comp_tptr++] = 0x75;     /* jne ntaken */
  comp_tbuffer[comp_tptr++] = 0x08;

  /* taken */

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov eax, [ecx-8] */
  comp_tbuffer[comp_tptr++] = 0x41;
  comp_tbuffer[comp_tptr++] = 0xF8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx-4] */
  comp_tbuffer[comp_tptr++] = 0x59;
  comp_tbuffer[comp_tptr++] = 0xFC;

  comp_tbuffer[comp_tptr++] = 0xFF;     /* jmp edi */
  comp_tbuffer[comp_tptr++] = 0xE7;

  /* ntaken: */

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov eax, [ecx-8] */
  comp_tbuffer[comp_tptr++] = 0x41;
  comp_tbuffer[comp_tptr++] = 0xF8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx-4] */
  comp_tbuffer[comp_tptr++] = 0x59;
  comp_tbuffer[comp_tptr++] = 0xFC;
}

void comp_store (void)
{
  comp_tbuffer[comp_tptr++] = 0x89;     /* mov [edx], eax */
  comp_tbuffer[comp_tptr++] = 0x02;

  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x89;     /* mov eax, ebx */
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x83;     /* add edx, 4 */
  comp_tbuffer[comp_tptr++] = 0xC2;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_fetch (void)
{
  comp_tbuffer[comp_tptr++] = 0x89;     /* mov [ecx], ebx */
  comp_tbuffer[comp_tptr++] = 0x19;

  comp_tbuffer[comp_tptr++] = 0x83;     /* sub edx, 4 */
  comp_tbuffer[comp_tptr++] = 0xEA;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x89;     /* mov ebx, eax */
  comp_tbuffer[comp_tptr++] = 0xC3;

  comp_tbuffer[comp_tptr++] = 0x83;     /* add ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xC1;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov eax, [edx] */
  comp_tbuffer[comp_tptr++] = 0x02;
}

void comp_add (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x01;     /* add eax, ebx */ 
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_sub (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x29;     /* sub eax, ebx */ 
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_mul (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0xF7;     /* mul ebx */ 
  comp_tbuffer[comp_tptr++] = 0xE3;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_div (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0xF7;     /* div ebx */ 
  comp_tbuffer[comp_tptr++] = 0xF3;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_and (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x21;     /* and eax, ebx */ 
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_or (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x09;     /* or  eax, ebx */ 
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_xor (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x31;     /* add eax, ebx */ 
  comp_tbuffer[comp_tptr++] = 0xD8;

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_shl (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x51;     /* push ecx */ 

  comp_tbuffer[comp_tptr++] = 0x88;     /* mov cl, dl */
  comp_tbuffer[comp_tptr++] = 0xD9;

  comp_tbuffer[comp_tptr++] = 0xD3;     /* shl eax, cl */
  comp_tbuffer[comp_tptr++] = 0xE0;

  comp_tbuffer[comp_tptr++] = 0x59;     /* pop ecx */

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}

void comp_shr (void)
{
  comp_tbuffer[comp_tptr++] = 0x83;     /* sub ecx, 4 */
  comp_tbuffer[comp_tptr++] = 0xE9;
  comp_tbuffer[comp_tptr++] = 0x04;

  comp_tbuffer[comp_tptr++] = 0x51;     /* push ecx */ 

  comp_tbuffer[comp_tptr++] = 0x88;     /* mov cl, dl */
  comp_tbuffer[comp_tptr++] = 0xD9;

  comp_tbuffer[comp_tptr++] = 0xD3;     /* shr eax, cl */
  comp_tbuffer[comp_tptr++] = 0xE8;

  comp_tbuffer[comp_tptr++] = 0x59;     /* pop ecx */

  comp_tbuffer[comp_tptr++] = 0x8B;     /* mov ebx, [ecx] */
  comp_tbuffer[comp_tptr++] = 0x19;
}
