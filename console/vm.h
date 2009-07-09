#ifndef NGARO_HEADER
#define NGARO_HEADER

#define INPUT  1
#define OUTPUT 2

#define CELL int
#define DROP vm->data[vm->sp] = 0; vm->sp--; if (vm->sp < 0) vm->ip = IMAGE_SIZE;
#define TOS  vm->data[vm->sp]
#define NOS  vm->data[vm->sp-1]

#define TORS vm->address[vm->rsp]
#define NORS vm->address[vm->rsp-1]

#define VMOP vm->image[vm->ip]

#define IMAGE_SIZE   5000000
#define STACK_DEPTH      100
#define ADDRESSES       1024

typedef struct {
  int sp;
  int rsp;
  int ip;
  int data[STACK_DEPTH];
  int address[ADDRESSES];
  int ports[1024];
  int image[IMAGE_SIZE];
  int padding;
  char filename[2048];
} VM;

enum vm_opcode {VM_NOP, VM_LIT, VM_DUP, VM_DROP, VM_SWAP, VM_PUSH, VM_POP,
                VM_CALL, VM_JUMP, VM_RETURN, VM_GT_JUMP, VM_LT_JUMP,
                VM_NE_JUMP,VM_EQ_JUMP, VM_FETCH, VM_STORE, VM_ADD,
                VM_SUB, VM_MUL, VM_DIVMOD, VM_AND, VM_OR, VM_XOR, VM_SHL,
                VM_SHR, VM_ZERO_EXIT, VM_INC, VM_DEC, VM_IN, VM_OUT,
                VM_WAIT };

#define NEXT  	switch(vm->image[vm->ip])                               \
  			{                                                 \
    				case VM_NOP: 	   goto fVM_NOP;          \
    				case VM_LIT: 	   goto fVM_LIT;          \
   				case VM_DUP: 	   goto fVM_DUP;          \
    				case VM_DROP: 	   goto fVM_DROP;         \
    				case VM_SWAP: 	   goto fVM_SWAP;         \
    				case VM_PUSH: 	   goto fVM_PUSH;         \
    				case VM_POP: 	   goto fVM_POP;          \
    				case VM_CALL: 	   goto fVM_CALL;         \
    				case VM_JUMP: 	   goto fVM_JUMP;         \
    				case VM_RETURN:    goto fVM_RETURN;       \
    				case VM_GT_JUMP:   goto fVM_GT_JUMP;      \
				case VM_LT_JUMP:   goto fVM_LT_JUMP;      \
    				case VM_NE_JUMP:   goto fVM_NE_JUMP;      \
    				case VM_EQ_JUMP:   goto fVM_EQ_JUMP;      \
    				case VM_FETCH: 	   goto fVM_FETCH;        \
    				case VM_STORE: 	   goto fVM_STORE;        \
    				case VM_ADD: 	   goto fVM_ADD;          \
    				case VM_SUB: 	   goto fVM_SUB;          \
    				case VM_MUL: 	   goto fVM_MUL;          \
    				case VM_DIVMOD:    goto fVM_DIVMOD;       \
    				case VM_AND: 	   goto fVM_AND;          \
    				case VM_OR: 	   goto fVM_OR;           \
    				case VM_XOR: 	   goto fVM_XOR;          \
    				case VM_SHL: 	   goto fVM_SHL;          \
    				case VM_SHR: 	   goto fVM_SHR;          \
    				case VM_ZERO_EXIT: goto fVM_ZERO_EXIT;    \
    				case VM_INC: 	   goto fVM_INC;          \
    				case VM_DEC: 	   goto fVM_DEC;          \
    				case VM_IN: 	   goto fVM_IN;           \
    				case VM_OUT:	   goto fVM_OUT;          \
    				case VM_WAIT: 	   goto fVM_WAIT;         \
    				default:           goto DEFAULT;          \
  			}

#define NUM_OPS VM_WAIT
#endif
