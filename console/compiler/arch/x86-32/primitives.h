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

#define COMP_REGISTER register int comp_acc; asm("eax"); \
                      register int comp_opn; asm("ebx");

#define COMP_PROLOG asm("pushad");                \
                    asm("mov $comp_dstack, %ecx"; \
                    asm("mov $comp_rstack, %edx"; \
                    asm("xor edi, edi");

#define COMP_EPILOG asm("popad");

void comp_return (void)
{
  comp_tbuffer[comp_tptr++] = 0xC3; /* ret */
}

void comp_lit (imm value)
{ 
  comp_tbuffer[comp_tptr++] = 0x89;      /* mov [ecx], ebx */
  comp_tbuffer[comp_tptr++] = 0x19;

  comp_tbuffer[comp_tptr++] = 0x89;      /* mov ebx, eax */
  comp_tbuffer[comp_tptr++] = 0xC3;

  comp_tbuffer[comp_tptr++] = 0xB8;      /* mov eax,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = imm.b[3];
  comp_tbuffer[comp_tptr++] = imm.b[2];
  comp_tbuffer[comp_tptr++] = imm.b[1];
  comp_tbuffer[comp_tptr++] = imm.b[0];

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
  imm location; location.v = (imm) trace;

  comp_tbuffer[comp_tptr++] = 0xBF;      /* mov edi,nnnnnnnn */
  comp_tbuffer[comp_tptr++] = imm.b[3];
  comp_tbuffer[comp_tptr++] = imm.b[2];
  comp_tbuffer[comp_tptr++] = imm.b[1];
  comp_tbuffer[comp_tptr++] = imm.b[0];

  comp_tbuffer[comp_tptr++] = 0xFF;     /* call [edi] */
  comp_tbuffer[comp_tptr++] = 0x17;
}

