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

enum vm_opcode {VM_NOP,       /* 0   */ 
                VM_LIT,       /* 1   */
                VM_DUP,       /* 2   */
                VM_DROP,      /* 3   */
                VM_SWAP,      /* 4   */
                VM_PUSH,      /* 5   */
                VM_POP,       /* 6   */
                VM_CALL,      /* 7   */
                VM_JUMP,      /* 8   */
                VM_RETURN,    /* 9   */
                VM_GT_JUMP,   /* 10  */
                VM_LT_JUMP,   /* 11  */
                VM_NE_JUMP,   /* 12  */
                VM_EQ_JUMP,   /* 13  */
                VM_FETCH,     /* 14  */
                VM_STORE,     /* 15  */
                VM_ADD,       /* 16  */
                VM_SUB,       /* 17  */
                VM_MUL,       /* 18  */
                VM_DIVMOD,    /* 19  */
                VM_AND,       /* 20  */
                VM_OR,        /* 21  */
                VM_XOR,       /* 22  */
                VM_SHL,       /* 23  */
                VM_SHR,       /* 24  */
                VM_ZERO_EXIT, /* 25  */
                VM_INC,       /* 26  */
                VM_DEC,       /* 27  */
                VM_IN,        /* 28  */
                VM_OUT,       /* 29  */
                VM_WAIT,      /* 30  */
                VM_STREAM,    /* 31  */
                VM_AOT,       /* 32  */
                VM_TAIL,      /* 33  */
                
                /* extended-instruction set */

                VM_LIA,       /* 34  */ 
                VM_PSAD,      /* 35  */
                VM_PSAR,      /* 36  */
                VM_PLDA,      /* 37  */
                VM_PLRA,      /* 38  */ 
                VM_TDA,       /* 39  */
                VM_TRA,       /* 40  */
                VM_TAD,       /* 41  */
                VM_TAR,       /* 42  */
                VM_TAB,       /* 43  */
                VM_TBA,       /* 44  */
                VM_ADDA,      /* 45  */ 
                VM_SUBA,      /* 46  */
                VM_DIVA,      /* 47  */
                VM_MULA,      /* 48  */
                VM_INCA,      /* 49  */
                VM_DECA,      /* 50  */
                VM_ANDA,      /* 51  */
                VM_GORA,      /* 52  */
                VM_XORA,      /* 53  */
                VM_SHLA,      /* 54  */
                VM_SLIA,      /* 55  */
                VM_SHRA,      /* 56  */
                VM_SRIA,      /* 57  */ 
                VM_CMPA,      /* 58  */
                VM_LDRA,      /* 59  */
                VM_STRA,      /* 60  */
                VM_LIB,       /* 61  */
                VM_PSBD,      /* 62  */
                VM_PSBR,      /* 63  */ 
                VM_PLDB,      /* 64  */
                VM_PLRB,      /* 65  */
                VM_TDB,       /* 66  */
                VM_TRB,       /* 67  */
                VM_ADDB,      /* 68  */
                VM_SUBB,      /* 69  */ 
                VM_DIVB,      /* 70  */
                VM_MULB,      /* 71  */
                VM_INCB,      /* 72  */
                VM_DECB,      /* 73  */
                VM_ANDB,      /* 74  */
                VM_GORB,      /* 75  */
                VM_XORB,      /* 76  */
                VM_CMPB,      /* 77  */
                VM_SHLB,      /* 78  */
                VM_SLIB,      /* 79  */
                VM_SHRB,      /* 80  */
                VM_SRIB,      /* 81  */ 
                VM_LDRB,      /* 82  */
                VM_STRB,      /* 83  */
                VM_CI,        /* 84  */
                VM_CIEQ,      /* 85  */
                VM_CIGR,      /* 86  */
                VM_CILE,      /* 87  */
                VM_CNZA,      /* 88  */
                VM_CIZA,      /* 89  */
                VM_CNZB,      /* 90  */
                VM_CIZB,      /* 91  */
                VM_CRA,       /* 92  */
                VM_CRB,       /* 93  */ 
                VM_BRA,       /* 94  */
                VM_BRB,       /* 95  */
                VM_BI,        /* 96  */
                VM_BIEQ,      /* 97  */
                VM_BIGR,      /* 98  */
                VM_BILE,      /* 99  */
                VM_BNZA,      /* 100 */ 
                VM_BIZA,      /* 101 */
                VM_BNZB,      /* 102 */
                VM_BIZB,      /* 103 */
                VM_LID,       /* 104 */
                VM_INCD,      /* 105 */
                VM_DECD,      /* 106 */ 
                VM_BNZD,      /* 107 */
                VM_BIZD,      /* 108 */ 
                VM_ADIA,      /* 109 */
                VM_SBIA,      /* 110 */
                VM_ANIA,      /* 111 */
                VM_ORIA,      /* 112 */
                VM_XOIA,      /* 113 */
                VM_CPIA,      /* 114 */
                VM_ADIB,      /* 115 */
                VM_SBIB,      /* 116 */
                VM_ANIB,      /* 117 */
                VM_ORIB,      /* 118 */
                VM_XOIB,      /* 119 */
                VM_CPIB,      /* 120 */
                VM_LISA,      /* 121 */
                VM_LISB,      /* 122 */
                VM_SISA,      /* 123 */
                VM_SISB,      /* 124 */
                VM_INIS,      /* 125 */
                VM_DEIS       /* 126 */
              };

/* interpreter */

#define NEXT  	switch(vm->image[vm->ip])                                 \
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
                                case VM_TAIL:      goto fVM_TAIL;         \
    				default:           goto fVM_DEFAULT;      \
  			    }

/* compiler */

#define INEXT  	switch(vm->image[vm->ip])                                 \
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
                                case VM_LID:       goto cVM_LID;          \
                                case VM_INCD:      goto cVM_INCD;         \
                                case VM_DECD:      goto cVM_DECD;         \
                                case VM_BNZD:      goto cVM_BNZD;         \
                                case VM_BIZD:      goto cVM_BIZD;         \
                                case VM_ADIA:      goto cVM_ADIA;         \
                                case VM_SBIA:      goto cVM_SBIA;         \
                                case VM_ANIA:      goto cVM_ANIA;         \
                                case VM_ORIA:      goto cVM_ORIA;         \
                                case VM_XOIA:      goto cVM_XOIA;         \
                                case VM_CPIA:      goto cVM_CPIA;         \
                                case VM_ADIB:      goto cVM_ADIB;         \
                                case VM_SBIB:      goto cVM_SBIB;         \
                                case VM_ANIB:      goto cVM_ANIB;         \
                                case VM_ORIB:      goto cVM_ORIB;         \
                                case VM_XOIB:      goto cVM_XOIB;         \
                                case VM_CPIB:      goto cVM_CPIB;         \
                                case VM_LISA:      goto cVM_LISA;         \
                                case VM_LISB:      goto cVM_LISB;         \
                                case VM_SISA:      goto cVM_SISA;         \
                                case VM_SISB:      goto cVM_SISB;         \
                                case VM_INIS:      goto cVM_INIS;         \
                                case VM_DEIS:      goto cVM_DEIS;         \
    				default:           goto cVM_DEFAULT;      \
  			    }
#define CNEXT   vm->ip++; INEXT

#define NUM_OPS VM_DEIS
#endif
