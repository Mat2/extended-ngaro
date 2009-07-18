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
}


/******************************************************
 * Process the current opcode
 ******************************************************/
void vm_process(VM *vm)
{
  register int a, b;
  register int acc;

  NEXT;

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

   DEFAULT:  vm->ip = IMAGE_SIZE;
}
