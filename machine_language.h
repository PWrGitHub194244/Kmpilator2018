/**************
Machine Language
**************/

enum assm_ops {READ, WRITE , LOAD, STORE, COPY, DEC,
	ADD, SUB, SHR, SHL, INC, 
 	JUMP, JZERO,  JODD, HALT,HALF};

char *op_name[] = {"GET", "PUT", "LOAD", "STORE", "COPY","DEC"
	"ADD", "SUB", "SHR", "SHL", "INC",
	"JUMP", "JZERO",  "JODD", "HALT", "HALF"};

struct instruction{
	enum assm_ops op;
	int arg;
int arg2;
};

struct instruction code[9997];
