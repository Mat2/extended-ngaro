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
                    asm("mov $comp_rstack, %edx";

#define COMP_EPILOG asm("popad");

void comp_lit (int value)
{
}

