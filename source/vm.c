/******************************************************
 * Ngaro
 *
 *|F|
 *|F| FILE: vm.c
 *|F|
 *
 * Threading interpreter by Matthias Schirm.
 * Released into the public domain
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "vm.h"
#include "compiler.c"

/******************************************************
 * Initialize the VM
 * This will clear the memory and stacks, and set the
 * registers to zero.
 ******************************************************/
void init_vm(VM *vm)
{
   int a;
   vm->ip = 0;
   vm->sp = 0;
   vm->rsp = 0;
   for (a = 0; a < STACK_DEPTH; a++)
      vm->data[a] = 0;
   for (a = 0; a < ADDRESSES; a++)
      vm->address[a] = 0;
   for (a = 0; a < IMAGE_SIZE; a++)
      vm->image[a] = 0;
   for (a = 0; a < 1024; a++)
      vm->ports[a] = 0;

   comp_init (COMP_BUFFER);
}


/******************************************************
 * Process the entire vm-code image
 ******************************************************/

void vm_process(VM *vm)
{
  /* register cache */

  register int a, b;
  register int acc;

  /* this is a common stream for compiling trace returns on a = 0
     (see compilation of opcode: 25) */

  int cVM_ZERO_TAKEN = label
                       tba
                       pldb                                     
                       retc
 
  /* start interpreter loop */

  NEXT;

  /* interpreter primitives */

     				/***************************************************/
    				/* NOP    Does Nothing. Used for padding           */
    				/* Opcode: 0        Stack:  -       Address: -     */
     				/***************************************************/

  fVM_NOP: vm->ip++; NEXT;

    				/***************************************************/
    				/* LIT    Push the value in the following cell to  */
    				/*        the stack                                */
    				/* Opcode: 1 n      Stack: -n       Address: -     */
     				/***************************************************/

  fVM_LIT: vm->sp++;
           vm->ip++;
           TOS = acc;
           acc = VMOP;
	       vm->ip++;
           NEXT;

			    	/***************************************************/
    				/* DUP    Duplicate the value on the top of the    */
    				/*        stack                                    */
    				/* Opcode: 2        Stack: n-nn     Address: -     */
			    	/***************************************************/ 

  fVM_DUP: vm->sp++;
           vm->data[vm->sp] = acc;
	       vm->ip++;
           NEXT;

    				/***************************************************/
    				/* DROP   Drop the value on the top of the stack   */
    				/* Opcode: 3        Stack: n-       Address: -     */
    				/***************************************************/

  fVM_DROP: acc = vm->data[vm->sp];
            vm->sp--;
            vm->ip++; 
            NEXT;

    				/***************************************************/
    				/* SWAP   Exchange the top two values on the stack */
    				/* Opcode: 4        Stack: xy-yx    Address: -     */
    				/***************************************************/

  fVM_SWAP: a = TOS;
            TOS = acc;
            acc = a;
	        vm->ip++; 
            NEXT;
 
    				/***************************************************/
    				/* PUSH   Move the top value on the stack to the   */
    				/*        address stack. Remove it from the data   */
    				/*        stack.                                   */
    				/* Opcode: 5        Stack: n-       Address: -n    */
    				/***************************************************/

  fVM_PUSH: vm->rsp++;
            TORS = acc;
            acc = vm->data[vm->sp];
            vm->sp--;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* POP    Move the top value from the address      */
    				/*        stack to the data stack. Remove it from  */
    				/*        the address stack.                       */
    				/* Opcode: 6        Stack: -n       Address: n-    */
   				    /***************************************************/

  fVM_POP: vm->sp++;
           TOS = acc;
           acc = TORS;
           vm->rsp--;
	       vm->ip++;
           NEXT;

    				/***************************************************/
    				/* CALL   Call a subroutine whose address is given */
    				/*        in the following cell. Push the address  */
    				/*        following this instruction to the address*/
    				/*         stack.                                  */
    				/* Opcode: 7 a       Stack: -      Address: -a     */
    				/***************************************************/

  fVM_CALL: vm->ip++;
            vm->rsp++;
            TORS = (vm->ip);
            vm->ip = vm->image[vm->ip];
            NEXT;

    				/***************************************************/
    				/* JUMP   Unconditional jump to the address given  */
    				/*        in the following cell.                   */
    				/* Opcode: 8 a       Stack: -       Address: -     */
    				/***************************************************/

  fVM_JUMP: vm->ip++;
            vm->ip = VMOP;
            NEXT;

    				/***************************************************/
    				/* ;      Return from a subroutine. Control is     */
    				/*        passed to the address on the top of the  */
    				/*        address stack.                           */
    				/* Opcode: 9         Stack: -       Address: a-    */
    				/***************************************************/

  fVM_RETURN: vm->ip = (TORS+1);
              vm->rsp--;
              NEXT;

    				/***************************************************/
    				/* >JUMP  Jump to the address in the following     */
    				/*        cell if NOS > TOS.                       */
    				/* Opcode: 10 a      Stack: xy-     Address: -     */
    				/***************************************************/

  fVM_GT_JUMP: vm->ip++;
               if(TOS > acc)
                 vm->ip = VMOP;
               else vm->ip++;
               vm->sp--;
               acc = vm->data[vm->sp];
               vm->sp--;
               NEXT;

    				/***************************************************/
    				/* <JUMP  Jump to the address in the following     */
    				/*        cell if NOS < TOS.                       */
    				/* Opcode: 11 a      Stack: xy-     Address: -     */
    				/***************************************************/

   fVM_LT_JUMP: vm->ip++;
         	    if(TOS < acc)
                  vm->ip = VMOP;
                else vm->ip++;
                vm->sp--;
                acc = vm->data[vm->sp];
                vm->sp--;
                NEXT;

    				/***************************************************/
    				/* !JUMP  Jump to the address in the following     */
    				/*        cell if NOS <> TOS.                      */
    				/* Opcode: 12 a      Stack: xy-     Address: -     */
    				/***************************************************/

   fVM_NE_JUMP: vm->ip++;
         	    if(acc != TOS)
                  vm->ip = VMOP;
                else vm->ip++;
                vm->sp--;
                acc = vm->data[vm->sp];
                vm->sp--;
                NEXT;

    				/***************************************************/
    				/* =JUMP  Jump to the address in the following     */
    				/*        cell if NOS = TOS.                       */
    				/* Opcode: 13 a      Stack: xy-     Address: -     */
    				/***************************************************/

   fVM_EQ_JUMP: vm->ip++;
         	    if(acc == TOS)
                  vm->ip = VMOP;
                else vm->ip++;
                vm->sp--;
                acc = vm->data[vm->sp];
                vm->sp--;
                NEXT;

    				/***************************************************/
    				/* @      Fetch a value from a memory location     */
    				/* Opcode: 14        Stack: a-n     Address: -     */
    				/***************************************************/

   fVM_FETCH: acc = vm->image[acc];
	          vm->ip++;
              NEXT;

    				/***************************************************/
    				/* !      Store a value to a memory location       */
    				/* Opcode: 15        Stack: na-     Address: -     */
    				/***************************************************/

   fVM_STORE: vm->image[acc] = TOS;
              vm->sp--;
              acc = vm->data[vm->sp];
              vm->sp--;
	          vm->ip++;
              NEXT;

    				/***************************************************/
    				/* +      Add TOS and NOS, leaving the result      */
    				/* Opcode: 16        Stack: xy-z    Address: -     */
    				/***************************************************/

   fVM_ADD: TOS += acc;
            acc = vm->data[vm->sp];
            vm->sp--;
            vm->ip++;
            NEXT;

    				/***************************************************/
   			 	    /* -      Subtract TOS from NOS, leaving the result*/
    				/* Opcode: 17        Stack: xy-z    Address: -     */
    				/***************************************************/

   fVM_SUB: TOS -= acc;
            acc = vm->data[vm->sp];
            vm->sp--;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* *      Multiply TOS by NOS, leaving the result  */
    				/* Opcode: 18        Stack: xy-z    Address: -     */
    				/***************************************************/

   fVM_MUL: TOS *= acc;
            acc = vm->data[vm->sp];
            vm->sp--;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* /MOD   Divide NOS by TOS, leaving the quotient  */
    				/*        and remainder.                           */
    				/* Opcode: 19        Stack: xy-qr   Address: -     */
    				/***************************************************/

   fVM_DIVMOD: a = acc;
               b = TOS;
               acc = b / a;
               TOS = b % a;
	           vm->ip++;
               NEXT;

    				/***************************************************/
    				/* AND    Perform a bitwise and operation on TOS   */
    				/*        and NOS.                                 */
    				/* Opcode: 20        Stack: xy-z    Address: -     */
    				/***************************************************/

   fVM_AND: a = acc;
            b = TOS;
            acc = vm->data[vm->sp];
            vm->sp--;
            acc = a & b;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* OR     Perform a bitwise or operation on TOS    */
    				/*        and NOS.                                 */
    				/* Opcode: 21        Stack: xy-z    Address: -     */
    				/***************************************************/

   fVM_OR: a = acc;
           b = TOS;
           acc = vm->data[vm->sp];
           vm->sp--;
           acc = a | b;
	       vm->ip++;
           NEXT;

    				/***************************************************/
    				/* XOR    Perform a bitwise xor operation on TOS   */
    				/*        and NOS.                                 */
    				/* Opcode: 22        Stack: xy-z    Address: -     */
   			 	    /***************************************************/

   fVM_XOR: a = acc;
            b = TOS;
            acc = vm->data[vm->sp];
            vm->sp--;
            acc = a ^ b;
	        vm->ip++;
            NEXT;


    				/***************************************************/
    				/* <<    Shift NOS left by TOS bits.               */
    				/* Opcode: 23        Stack: xy-z    Address: -     */
    				/***************************************************/

   fVM_SHL: a = acc;
            b = TOS;
            acc = vm->data[vm->sp];
            vm->sp--;
            acc = b << a;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* >>    Shift NOS right by TOS bits.              */
    				/* Opcode: 24        Stack: xy-z    Address: -     */
    				/***************************************************/

   fVM_SHR: a = acc;
            b = TOS;
            acc = vm->data[vm->sp];
            vm->sp--;
            acc = b >>= a;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* 0;    Return from a subroutine if TOS = 0.      */
    				/*       If TOS = 0, DROP TOS.                     */
    				/*       If TOS <> 0, do nothing                   */
    				/* Opcode: 25         Stack: n-     Address: a-    */
    				/*                    Stack: n-n    Address: -     */
    				/***************************************************/

   fVM_ZERO_EXIT: if (acc == 0)
         	      {
                    acc = vm->data[vm->sp];
                    vm->sp--;
           	        vm->ip = (TORS+1);
           	        vm->rsp--;
                  }
	              else vm->ip++;
         	      NEXT;

    				/***************************************************/
    				/* 1+    Increase TOS by 1                         */
    				/* Opcode: 26        Stack: x-y     Address: -     */
    				/***************************************************/

   fVM_INC: acc += 1;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* 1-    Decrease TOS by 1                         */
   				    /* Opcode: 27        Stack: x-y     Address: -     */
    				/***************************************************/

   fVM_DEC: acc -= 1;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* IN    Read a value from an I/O port             */
    				/* Opcode: 28        Stack: p-n     Address: -     */
    				/***************************************************/

   fVM_IN: a = acc;
           acc = vm->ports[a];
           vm->ports[a] = 0;
	       vm->ip++;
           NEXT;

    				/***************************************************/
    				/* OUT   Send a value to an I/O port               */
    				/* Opcode: 29        Stack: np-     Address: -     */
    				/***************************************************/

   fVM_OUT: vm->ports[0] = 0;
            vm->ports[acc] = TOS;
            acc = vm->data[vm->sp];
            vm->sp--;
            acc = vm->data[vm->sp];
            vm->sp--;
	        vm->ip++;
            NEXT;

    				/***************************************************/
    				/* WAIT  Wait for an I/O event to occur.           */
    				/* Opcode: 30        Stack: -       Address: -     */
    				/***************************************************/

   fVM_WAIT: if (vm->ports[0] == 1)
             {
               vm->ip++;
               NEXT;
             }

             /* Input */
             if (vm->ports[0] == 0 && vm->ports[1] == 1)
             {
               vm->ports[1] = dev_getch();
               vm->ports[0] = 1;
               dev_refresh ();
             }

             /* Output (character generator) */
             if (vm->ports[2] == 1)
             {
               dev_putch(acc);
               acc = vm->data[vm->sp];
               vm->sp--;
               vm->ports[2] = 0;
               vm->ports[0] = 1;
               dev_refresh ();
             }

             /* Save Image */
             if (vm->ports[4] == 1)
             {
               vm_save_image(vm, vm->filename);
               vm->ports[4] = 0;
               vm->ports[0] = 1;
             }

             /* Capabilities */
             if (vm->ports[5] == -1)
             {
               vm->ports[5] = IMAGE_SIZE;
               vm->ports[0] = 1;
             }

             /* The framebuffer related bits aren't supported, so return 0 for them. */
             if (vm->ports[5] == -2 || vm->ports[5] == -3 || vm->ports[5] == -4)
             {
               vm->ports[5] = 0;
               vm->ports[0] = 1;
             }

             /* Data & Return Stack Depth */
             if (vm->ports[5] == -5)
             {
               vm->ports[5] = vm->sp;
               vm->ports[0] = 1;
             }
             if (vm->ports[5] == -6)
             {
               vm->ports[5] = vm->rsp;
               vm->ports[0] = 1;
             }
	         vm->ip++;
             NEXT;

    				/***************************************************/
    				/* STREAM  Compile stream to trace.                */
    				/* Opcode: 31        Stack: - a     Address: -     */
    				/***************************************************/

   fVM_STREAM: vm->sp++;
               TOS = acc;
               acc = comp_cofs;
               CNEXT;

    				/***************************************************/
    				/* AOT  execute trace                              */
    				/* Opcode: 32     Stack: a tos sos - i  Address: - */
    				/***************************************************/

   fVM_AOT: vm->ip++;
            a = vm->data[vm->sp];
            b = vm->data[vm->sp-1];
            vm->sp = vm->sp-1;
            acc = execute (acc, a, b)
            NEXT;

   /* compiler routines */

                    /***************************************************
                     * compiler routines:                              *
                     *                                                 *
                     *         a : first accululator,                  *
                     *         b : second accumulator,                 *
                     *         d : current data-stack pointer          *
                     *         r : current return-stack pointer        *
                     *                                                 *
                     *         p : internal program counter            *
                     *         s : internal return-address stack       *
                     *         f : internal flag register              *
                     *                                                 *
                     * (s+), (r+), (d+) : store register onto TOS and  *
                     *                    post increment pointer       *
                     * (-s), (-r), (-d) : decrement pointer and load   *
                     *                    TOS into register            *
                     *                                                 *
                     *          <, >, = : conditional execution        *
                     *                c : test condition               *
                     *                m : memory access                *
                     *                                                 *
                     *             VMOP : immediate parameter          *
                     ***************************************************/

   cVM_NOP:     CNEXT;

   cVM_LIT:     vm->ip++;
                psbd                                   /* (d+) = b    */ 
                tab                                    /*    b = a    */
                lia  (VMOP)                            /*    a = VMOP */
                CNEXT;

   cVM_DUP:     psbd                                   /* (d+) = b    */  
                tab                                    /*    b = a    */
                CNEXT;

   cVM_DROP:    tba                                    /*    a = b    */
                pldb                                   /*    b = (-d) */
                CNEXT;

   cVM_SWAP:    swap                                   /*    a <-> b */
                CNEXT;


   cVM_PUSH:    psar                                   /* (r+) = a    */ 
                tba                                    /*    a = b    */
                pldb                                   /*    b = (-d) */
                CNEXT;

   cVM_POP:     psbd                                   /* (d+) = b    */ 
                tab                                    /*    b = a    */
                plra                                   /*    a = (-r) */
                CNEXT;

   cVM_CALL:    vm->ip++;
                ci   (VMOP)                            /* (s+) = p    */
                CNEXT;                                 /*    p = VMOP */

   cVM_JUMP:    vm->ip++;
                bi   (VMOP)                            /*    p = VMOP */
                CNEXT;

   cVM_RETURN:  vm->ip++;
                retc                                   /*    p = (-s) */
                NEXT;

   cVM_GT_JUMP: vm->ip++;
                cmpa                                   /*       f = c.a  */
                plda                                   /*       a = (-d) */
                pldb                                   /*       b = (-d) */ 
                bigr (VMOP)                            /* f.> : p = VMOP */
                CNEXT;                                    

   cVM_LT_JUMP: vm->ip++;
                cmpa                                   /*       f = c.a  */
                plda                                   /*       a = (-d) */
                pldb                                   /*       b = (-d) */ 
                bile (VMOP)                            /* f.< : p = VMOP */
                CNEXT;                                    

   cVM_NE_JUMP: vm->ip++;
                cmpa                                   /*       f = c.a  */
                plda                                   /*       a = (-d) */
                pldb                                   /*       b = (-d) */ 
                bigr (VMOP)                            /* f.> : p = VMOP */
                bile (VMOP)                            /* f.< : p = VMOP */
                CNEXT;                                    

   cVM_EQ_JUMP: vm->ip++;
                cmpa                                   /*       f = c.a  */
                plda                                   /*       a = (-d) */
                pldb                                   /*       b = (-d) */ 
                bieq (VMOP)                            /* f.= : p = VMOP */
                CNEXT;                                    

   cVM_FETCH:   psbd                                   /* (d+) = b    */  
                tab                                    /*    b = a    */
                ldra                                   /*    a = m.b  */
                pldb                                   /*    b = (-d) */
                CNEXT;

   cVM_STORE:   stra                                   /*  m.b = a    */
                plda                                   /*    a = (-d) */
                pldb                                   /*    b = (-d) */
                CNEXT;

   cVM_ADD:     adda                                   /*    a = a + b */
                pldb                                   /*    b = (-d)  */
                CNEXT;

   cVM_SUB:     suba                                   /*    a = a - b */
                pldb                                   /*    b = (-d)  */
                CNEXT;

   cVM_MUL:     mula                                   /*    a = a * b */
                pldb                                   /*    b = (-d)  */
                CNEXT;

   cVM_DIVMOD:  diva                                   /*    a = a / b */
                lib  (0)                               /*    b = 0     */
                CNEXT;

   cVM_AND:     anda                                   /*    a = a & b */
                pldb                                   /*    b = (-d)  */
                CNEXT;

   cVM_OR:      gora                                   /*    a = a | b */
                pldb                                   /*    b = (-d)  */
                CNEXT;

   cVM_XOR:     xora                                   /*    a = a ^ b */
                pldb                                   /*    b = (-d)  */
                CNEXT;

   cVM_SHL:     shla                                   /*    a = a << b */
                pldb                                   /*    b = (-d)   */
                CNEXT;
 
   cVM_SHR:     shra                                   /*    a = a >> b */
                pldb                                   /*    b = (-d)   */
                CNEXT;

   cVM_INC:     inca                                   /*    a = a + 1 */
                CNEXT;

   cVM_DEC:     deca                                   /*    a = a - 1 */
                CNEXT;

   cVM_ZERO_EXIT: biza (cVM_ZERO_TAKEN)                /*  a=0 : p = cVM.. */                 
                  CNEXT;

   cVM_IN:      printf ("cVM_IN: illegal stream opcode !\n");
                exit (-1);

   cVM_OUT:     printf ("cVM_OUT: illegal stream opcode !\n");
                exit (-1);

   cVM_WAIT:    printf ("cVM_WAIT: illegal stream opcode !\n");
                exit (-1);

   /* compiler routines for the extended-instruction set */

   cVM_LIA:     vm->ip++;
                lia (VMOP)                             /*    a = VMOP */
                CNEXT;

   cVM_PSAD:    psad                                   /* (d+) = a    */
                CNEXT;

   cVM_PSAR:    psar                                   /* (r+) = a    */
                CNEXT;

   cVM_PLDA:    plda                                   /*    a = (-d) */
                CNEXT;

   cVM_PLRA:    plra                                   /*    a = (-r) */
                CNEXT;

   cVM_TDA:     tda                                    /*    a = d    */
                CNEXT;

   cVM_TRA:     tra                                    /*    a = r    */
                CNEXT;

   cVM_TAD:     tad                                    /*    d = a    */
                CNEXT;

   cVM_TAR:     tar                                    /*    r = a    */
                CNEXT;

   cVM_TAB:     tab                                    /*    b = a    */
                CNEXT;

   cVM_TBA:     tba                                    /*    a = b    */
                CNEXT;

   cVM_ADDA:    adda                                   /*    a = a + b */
                CNEXT;

   cVM_SUBA:    suba                                   /*    a = a - b */
                CNEXT;

   cVM_DIVA:    diva                                   /*    a = a / b */
                CNEXT;

   cVM_MULA:    mula                                   /*    a = a * b */
                CNEXT;

   cVM_INCA:    inca                                   /*    a = a + 1 */
                CNEXT;

   cVM_DECA:    deca                                   /*    a = a - 1 */
                CNEXT;

   cVM_ANDA:    anda                                   /*    a = a & b */
                CNEXT;

   cVM_GORA:    gora                                   /*    a = a | b */
                CNEXT;

   cVM_XORA:    xora                                   /*    a = a ^ b */
                CNEXT;

   cVM_SHLA:    shla                                   /*    a = a << b */
                CNEXT;

   cVM_SHRA:    shra                                   /*    a = a >> b */
                CNEXT;

   cVM_SLIA:    vm->ip++;
                slia (VMOP)                            /*    a = a << VMOP */
                CNEXT;

   cVM_SRIA:    vm->ip++;
                sria (VMOP)                            /*    a = a >> VMOP */
                CNEXT;

   cVM_CMPA:    cmpa                                   /*    f = c.a    */
                CNEXT;

   cVM_LDRA:    ldra                                   /*    a = m.b    */
                CNEXT;

   cVM_STRA:    stra                                   /*  m.b = a      */
                CNEXT;

   cVM_LIB:     vm->ip++;
                lib  (VMOP)                            /*    b = VMOP   */
                CNEXT;

   cVM_PSBD:    psbd                                   /* (d+) = b      */
                CNEXT;

   cVM_PSBR:    psbr                                   /* (r+) = b      */
                CNEXT;

   cVM_PLDB:    pldb                                   /*    b = (-d)   */
                CNEXT;

   cVM_PLRB:    plrb                                   /*    b = (-r)   */
                CNEXT;

   cVM_TDB:     tdb                                    /*    b = d      */
                CNEXT;

   cVM_TRB:     trb                                    /*    b = r      */
                CNEXT;

   cVM_ADDB:    addb                                   /*    b = b + a  */
                CNEXT;

   cVM_SUBB:    subb                                   /*    b = b - a  */
                CNEXT;

   cVM_DIVB:    divb                                   /*    b = b / a  */
                CNEXT;

   cVM_MULB:    mulb                                   /*    b = b / a  */
                CNEXT;

   cVM_INCB:    incb                                   /*    b = b + 1  */
                CNEXT;

   cVM_DECB:    decb                                   /*    b = b - 1  */
                CNEXT;

   cVM_ANDB:    andb                                   /*    b = b & a  */
                CNEXT;

   cVM_GORB:    gorb                                   /*    b = b | a  */
                CNEXT;

   cVM_XORB:    xorb                                   /*    b = b ^ a  */
                CNEXT;

   cVM_CMPB:    cmpb                                   /*    f = c.b    */
                CNEXT;

   cVM_SHLB:    shlb                                   /*    b = b << a */
                CNEXT;

   cVM_SLIB:    vm->ip++;
                slib (VMOP)                            /*    b = b << VMOP */
                CNEXT;

   cVM_SHRB:    shrb                                   /*    b = b >> a */
                CNEXT;

   cVM_SRIB:    vm->ip++;
                srib (VMOP)                            /*    b = b >> VMOP */
                CNEXT;

   cVM_LDRB:    ldrb                                   /*    b = m.a   */
                CNEXT;

   cVM_STRB:    strb                                   /*  m.a = b     */
                CNEXT;

   cVM_CI:      vm->ip++;
                ci   (VMOP)                            /* (s+) = p     */
                CNEXT;                                 /*    p = VMOP  */

   cVM_CIEQ:    vm->ip++;                              
                cieq (VMOP)                            /*  f.= : (s+) = p    */
                CNEXT;                                 /*           p = VMOP */

   cVM_CIGR:    vm->ip++;                              
                cigr (VMOP)                            /*  f.> : (s+) = p    */
                CNEXT;                                 /*           p = VMOP */

   cVM_CILE:    vm->ip++;                              
                cile (VMOP)                            /*  f.< : (s+) = p    */
                CNEXT;                                 /*           p = VMOP */

   cVM_CNZA:    vm->ip++;                              /*           f = c.a  */
                cnza (VMOP)                            /*  f.! : (s+) = p    */
                CNEXT;                                 /*           p = VMOP */

   cVM_CIZA:    vm->ip++;                              /*           f = c.a  */
                ciza (VMOP)                            /*  f.0 : (s+) = p    */
                CNEXT;                                 /*           p = VMOP */

   cVM_CNZB:    vm->ip++;                              /*           f = c.b  */
                cnzb (VMOP)                            /*  f.! : (s+) = p    */
                CNEXT;                                 /*           p = VMOP */

   cVM_CIZB:    vm->ip++;                              /*           f = c.b  */
                cizb (VMOP)                            /*  f.0 : (s+) = p    */
                CNEXT;                                 /*           p = VMOP */

   cVM_CRA:     cra                                    /* (s+) = p     */
                CNEXT;                                 /*    p = a     */

   cVM_CRB:     crb                                    /* (s+) = p     */
                CNEXT;                                 /*    p = b     */

   cVM_BRA:     bra                                    /*    p = a     */
                CNEXT;

   cVM_BRB:     brb                                    /*    p = b     */
                CNEXT;

   cVM_BI:      vm->ip++;                              
                bi   (VMOP)                            /*    p = VMOP  */
                CNEXT;

   cVM_BIEQ:    vm->ip++;                              /*        f = c.a   */
                bieq (VMOP)                            /*  f.= : p = VMOP  */
                CNEXT;

   cVM_BIGR:    vm->ip++;                              /*        f = c.a   */
                bigr (VMOP)                            /*  f.> : p = VMOP  */
                CNEXT;

   cVM_BILE:    vm->ip++;                              /*        f = c.a   */
                bile (VMOP)                            /*  f.< : p = VMOP  */
                CNEXT;

   cVM_BNZA:    vm->ip++;                              /*        f = c.a   */
                bnza (VMOP)                            /*  f.! : p = VMOP  */
                CNEXT;

   cVM_BIZA:    vm->ip++;                              /*        f = c.a   */
                biza (VMOP)                            /*  f.= : p = VMOP  */
                CNEXT;

   cVM_BNZB:    vm->ip++;                              /*        f = c.b   */
                bnzb (VMOP)                            /*  f.! : p = VMOP  */
                CNEXT;

   cVM_BIZB:    vm->ip++;                              /*        f = c.b   */
                bizb (VMOP)                            /*  f.= : p = VMOP  */
                CNEXT;

   cVM_DEFAULT: printf ("Instruction: %i : ",vm->image[vm->ip]);
				printf ("Illegal opcode in stream detected !\n");
   
   fVM_DEFAULT: vm->ip = IMAGE_SIZE;
                printf ("ACC: %i | ",acc);
                printf ("TOS: %i | ",vm->data[vm->sp-1]);
                printf ("SND: %i \n",vm->data[vm->sp-2]);
}

