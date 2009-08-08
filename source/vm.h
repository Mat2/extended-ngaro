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
#define COMP_BUFFER  0xFFFFF

typedef struct 
{
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
                VM_WAIT, VM_STREAM, VM_AOT,
                
                /* extended-instruction set */

                VM_AOTC, VM_JITC, VM_XOP, VM_LIA, VM_PSAD, VM_PSAR, VM_PLDA,
                VM_PLRA, VM_TDA, VM_TRA, VM_TAD, VM_TAR, VM_TAB, VM_TBA,
                VM_ADDA, VM_SUBA, VM_DIVA, VM_MULA, VM_INCA, VM_DECA,
                VM_ANDA, VM_GORA, VM_XORA, VM_SHLA, VM_SLIA, VM_SHRA,
                VM_SRIA, VM_CMPA, VM_LDRA, VM_STRA, VM_LIB, VM_PSBD,
                VM_PSBR, VM_PLDB, VM_PLRB, VM_TDB, VM_TRB, VM_ADDB,
                VM_SUBB, VM_DIVB, VM_MULB, VM_INCB, VM_DECB, VM_ANDB,
                VM_GORB, VM_XORB, VM_CMPB, VM_SHLB, VM_SLIB, VM_SHRB,
                VM_SRIB, VM_LDRB, VM_STRB, VM_CI, VM_CIEQ, VM_CIGR,
                VM_CILE, VM_CNZA, VM_CIZA, VM_CNZB, VM_CIZB, VM_CRA,
                VM_CRB, VM_BRA, VM_BRB, VM_BI, VM_BIEQ, VM_BIGR, VM_BILE,
                VM_BNZA, VM_BIZA, VM_BNZB, VM_BIZB};

/* interpreter */

#define NEXT  	switch(vm->image[vm->ip])                     \
  			    {                                             \
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
                                case VM_STREAM:    goto fVM_STREAM;       \
                                case VM_AOT:       goto fVM_AOT;          \
    				default:           goto fVM_DEFAULT;      \
  			    }

/* compiler */

#define INEXT  	switch(vm->image[vm->ip])                     \
  			    {                                             \
    				case VM_NOP: 	   goto cVM_NOP;          \
    				case VM_LIT: 	   goto cVM_LIT;          \
                                case VM_DUP: 	   goto cVM_DUP;          \
    				case VM_DROP: 	   goto cVM_DROP;         \
    				case VM_SWAP: 	   goto cVM_SWAP;         \
    				case VM_PUSH: 	   goto cVM_PUSH;         \
    				case VM_POP: 	   goto cVM_POP;          \
    				case VM_CALL: 	   goto cVM_CALL;         \
    				case VM_JUMP: 	   goto cVM_JUMP;         \
    				case VM_RETURN:    goto cVM_RETURN;       \
    				case VM_GT_JUMP:   goto cVM_GT_JUMP;      \
                                case VM_LT_JUMP:   goto cVM_LT_JUMP;      \
    				case VM_NE_JUMP:   goto cVM_NE_JUMP;      \
    				case VM_EQ_JUMP:   goto cVM_EQ_JUMP;      \
    				case VM_FETCH: 	   goto cVM_FETCH;        \
    				case VM_STORE: 	   goto cVM_STORE;        \
    				case VM_ADD: 	   goto cVM_ADD;          \
    				case VM_SUB: 	   goto cVM_SUB;          \
    				case VM_MUL: 	   goto cVM_MUL;          \
    				case VM_DIVMOD:    goto cVM_DIVMOD;       \
    				case VM_AND: 	   goto cVM_AND;          \
    				case VM_OR: 	   goto cVM_OR;           \
    				case VM_XOR: 	   goto cVM_XOR;          \
    				case VM_SHL: 	   goto cVM_SHL;          \
    				case VM_SHR: 	   goto cVM_SHR;          \
    				case VM_ZERO_EXIT: goto cVM_ZERO_EXIT;    \
    				case VM_INC: 	   goto cVM_INC;          \
    				case VM_DEC: 	   goto cVM_DEC;          \
    				case VM_IN: 	   goto cVM_IN;           \
    				case VM_OUT:	   goto cVM_OUT;          \
    				case VM_WAIT: 	   goto cVM_WAIT;         \
				case VM_LIA:       goto cVM_LIA;          \
				case VM_PSAD:      goto cVM_PSAD;         \
				case VM_PSAR:      goto cVM_PSAR;         \
				case VM_PLDA:      goto cVM_PLDA;         \
			        case VM_PLRA:      goto cVM_PLRA;         \
                                case VM_TDA:       goto cVM_TDA;          \
				case VM_TRA:       goto cVM_TRA;          \
				case VM_TAD:       goto cVM_TAD;          \
				case VM_TAR:       goto cVM_TAR;          \
				case VM_TAB:       goto cVM_TAB;          \
		                case VM_TBA:       goto cVM_TBA;          \
			 	case VM_ADDA:      goto cVM_ADDA;         \
			        case VM_SUBA:      goto cVM_SUBA;         \
				case VM_DIVA:      goto cVM_DIVA;         \
				case VM_MULA:      goto cVM_MULA;         \
				case VM_INCA:      goto cVM_INCA;         \
				case VM_DECA:      goto cVM_DECA;         \
				case VM_ANDA:      goto cVM_ANDA;         \
				case VM_GORA:      goto cVM_GORA;         \
				case VM_XORA:      goto cVM_XORA;         \
				case VM_SHLA:      goto cVM_SHLA;         \
				case VM_SLIA:      goto cVM_SLIA;         \
				case VM_SHRA:      goto cVM_SHRA;         \
				case VM_SRIA:      goto cVM_SRIA;         \
				case VM_CMPA:      goto cVM_CMPA;         \
				case VM_LDRA:      goto cVM_LDRA;         \
				case VM_STRA:      goto cVM_STRA;         \
				case VM_LIB:       goto cVM_LIB;          \
				case VM_PSBD:      goto cVM_PSBD;         \
				case VM_PSBR:      goto cVM_PSBR;         \
				case VM_PLDB:      goto cVM_PLDB;         \
				case VM_PLRB:      goto cVM_PLRB;         \
				case VM_TDB:       goto cVM_TDB;          \
				case VM_TRB:       goto cVM_TRB;          \
				case VM_ADDB:      goto cVM_ADDB;         \
				case VM_SUBB:      goto cVM_SUBB;         \
				case VM_DIVB:      goto cVM_DIVB;         \
				case VM_MULB:      goto cVM_MULB;         \
				case VM_INCB:      goto cVM_INCB;         \
				case VM_DECB:      goto cVM_DECB;         \
				case VM_ANDB:      goto cVM_ANDB;         \
				case VM_GORB:      goto cVM_GORB;         \
				case VM_XORB:      goto cVM_XORB;         \
				case VM_CMPB:      goto cVM_CMPB;         \
				case VM_SHLB:      goto cVM_SHLB;         \
				case VM_SLIB:      goto cVM_SLIB;         \
				case VM_SHRB:      goto cVM_SHRB;         \
				case VM_SRIB:      goto cVM_SRIB;         \
				case VM_LDRB:      goto cVM_LDRB;         \
				case VM_STRB:      goto cVM_STRB;         \
				case VM_CI:        goto cVM_CI;           \
				case VM_CIEQ:      goto cVM_CIEQ;         \
				case VM_CIGR:      goto cVM_CIGR;         \
				case VM_CILE:      goto cVM_CILE;         \
				case VM_CNZA:      goto cVM_CNZA;         \
				case VM_CIZA:      goto cVM_CIZA;         \
				case VM_CNZB:      goto cVM_CNZB;         \
				case VM_CIZB:      goto cVM_CIZB;         \
				case VM_CRA:       goto cVM_CRA;          \
				case VM_CRB:       goto cVM_CRB;          \
				case VM_BRA:       goto cVM_BRA;          \
				case VM_BRB:       goto cVM_BRB;          \
				case VM_BI:        goto cVM_BI;           \
				case VM_BIEQ:      goto cVM_BIEQ;         \
				case VM_BIGR:      goto cVM_BIGR;         \
				case VM_BILE:      goto cVM_BILE;         \
				case VM_BNZA:      goto cVM_BNZA;         \
				case VM_BIZA:      goto cVM_BIZA;         \
				case VM_BNZB:      goto cVM_BNZB;         \
				case VM_BIZB:      goto cVM_BIZB;         \
    				default:           goto cVM_DEFAULT;      \
  			    }
#define CNEXT   vm->ip++; INEXT

#define NUM_OPS VM_BIZB#endif
