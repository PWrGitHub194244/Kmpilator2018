%{
	#include <stdlib.h>		//malloc, NULL, in ST
	#include <string.h>		//strcmp, strlen, in ST
	#include <stdio.h>		//errors, debug
	#include <stdbool.h>
	#include "label.h"				//label structure
	#include "machine_language.h"		//machine language
	#include "error_handler.h"			//error handler
	#include "code_manager.h"			//code manager
	#include "symbol_list.h"			//symbol table
	#include "code_writer.h"			//code writer
	#define YYDEBUG 1		//debugging on
	
	int yyerror(char*);
	
	//declare variable
	void declare(char *sym_name){
		slist *s = get_symbol(sym_name);
		if(s == NULL)
			s = put_sym(sym_name);
		else
			raise_error(IDEN_DEC,sym_name);
	}
	
	
	
	//checks variable and assigns a value
	void context_check_variable( enum assm_ops operation, char* sym_name){
		slist* identifier = get_symbol(sym_name);
		if(identifier == NULL){
			raise_error(IDEN_UNDEC,sym_name);
		}
		else{
			gen_code2(operation, identifier->offset, 1);
			identifier->is_defined = 1;
		}
	}
	
	//returns 1 if sym_name is declared and defined, 0 othw
	slist* context_check_get( char* sym_name){
		slist* identifier = get_symbol(sym_name);
		if(identifier == NULL){
			raise_error(IDEN_UNDEC,sym_name);
			return NULL;
		} else if(!identifier->is_defined){
			raise_error(VAR_UNDEF,sym_name);
			return NULL;
		} else
			return identifier;
	}	
	
	int yylex();
%}

%union semrec{
	int intval;
	char *id;
	label lbval;
}

%start program
%token <intval> NUMBER
%token <id> IDENTIFIER TAB
%token <lbval> IF WHILE FOR
%token  DECLARE _IN
%token ASSGNOP THEN ELSE ENDIF TO END ENDFOR ENDDO ENDWHILE DO GET PUT PLUS MINUS TIMES DIV MOD LE GE LEQ GEQ EQ DIFF FROM DOWNTO

%left '-' '+'
%left '*' '/' '%'
%left "==" "!=" "<" ">" "<=" ">="

%%
program:
	DECLARE vdeclarations
	_IN
	commands
	END { gen_code(HALT, -1); YYACCEPT; }
;

vdeclarations: //empty
	| IDENTIFIER ';' vdeclarations { declare($1); }
    | IDENTIFIER '('exp ':' exp ')'';' {declare($1);}
;
commands: //empty
	| commands command
;


command: IDENTIFIER DIV NUMBER ';' {context_check_get($1);}
	| IDENTIFIER TIMES NUMBER ';' {context_check_get($1);}
	| IDENTIFIER MOD NUMBER ';' {context_check_get($1);}
	| IDENTIFIER PLUS NUMBER ';' {context_check_get($1);}
	| IDENTIFIER MINUS NUMBER ';' {context_check_get($1);}  
	
	|IDENTIFIER DIV IDENTIFIER ';' {context_check_get($1);context_check_get($3);}
	| IDENTIFIER TIMES IDENTIFIER ';' {context_check_get($1);context_check_get($3);}
	| IDENTIFIER MOD IDENTIFIER ';' {context_check_get($1);context_check_get($3);}
	| IDENTIFIER PLUS IDENTIFIER ';' {context_check_get($1);context_check_get($3);}
	| IDENTIFIER MINUS IDENTIFIER ';' {context_check_get($1);context_check_get($3);} 
	
	
	|NUMBER DIV IDENTIFIER ';' {context_check_get($3);}
	| NUMBER TIMES IDENTIFIER ';' {context_check_get($3);}
	| NUMBER MOD IDENTIFIER ';' {context_check_get($3);}
	| NUMBER PLUS IDENTIFIER ';' {context_check_get($3);}
	| NUMBER MINUS IDENTIFIER ';' {context_check_get($3);}
	
	|NUMBER DIV NUMBER ';' {}
	| NUMBER TIMES NUMBER ';' {}
	| NUMBER MOD NUMBER ';' {}
	| NUMBER PLUS NUMBER ';' {}
	| NUMBER MINUS NUMBER ';' {};
	
	
	
	

command: IDENTIFIER ASSGNOP exp ';' {		gen_code(LOAD,1); context_check_variable(COPY, $1); }
|IDENTIFIER '('exp')' ASSGNOP exp ';'

	| IF condition { $1 = (label)new_label(); $1->for_jump_false = code_allocate(); }
		THEN commands {$1->for_jump = code_allocate(); }
		ELSE { back_patch( $1->for_jump_false, JZERO, get_label()); }
		commands 
		ENDIF {back_patch( $1->for_jump, JUMP, get_label()); free($1); }
	| IF condition { $1 = (label)new_label(); $1->for_jump_false = code_allocate(); }
		THEN /*empty*/ {$1->for_jump = code_allocate(); }
		ELSE { back_patch( $1->for_jump_false, JZERO, get_label()); }
		commands 
		ENDIF {back_patch( $1->for_jump, JUMP, get_label()); free($1); }
	| WHILE { $1 = new_label(); $1->for_jump = get_label(); }
		condition { $1->for_jump_false = code_allocate(); }
		DO commands
		ENDWHILE { gen_code(JUMP, $1->for_jump);
			back_patch($1->for_jump_false, JZERO, get_label()); free($1); }
    | FOR IDENTIFIER { declare($2); $1 = new_label(); $1->for_jump = get_label(); }
        FROM condition { $1->for_jump_false = code_allocate(); }
        DO commands 
        ENDFOR { gen_code(JUMP, $1->for_jump);
			back_patch($1->for_jump_false, JZERO, get_label()); free($1); }
    | DO 
commands 
    WHILE condition
 ENDDO 

	| GET IDENTIFIER ';'{ gen_code(READ,$2);  }
	| PUT IDENTIFIER ';'{ write_identifier(context_check_get($2)); }
| GET IDENTIFIER'('exp')' ';'{ gen_code(READ,$2); }
	| PUT IDENTIFIER'('exp')' ';'{ write_identifier(context_check_get($2)); }
	//| WRITE exp { $2; gen_code(STORE, 0); gen_code(WRITE, 0); }
;
exp: NUMBER	{   make_number($1); }
	| IDENTIFIER { get_identifier(context_check_get($1)); }
	| IDENTIFIER PLUS IDENTIFIER { add(context_check_get($1),
									  context_check_get($3)); }  //ok
    | IDENTIFIER PLUS NUMBER {make_number($3), 
									  addexp2(context_check_get($1)); } //ok
	| NUMBER PLUS IDENTIFIER {make_number($1) , 
									  addexp2(context_check_get($3)); } //ok
	| NUMBER PLUS NUMBER {make_number($1), gen_code2(COPY,2,1), make_number($3), 
									  addexp3(); }//ok
   
   
    | IDENTIFIER MINUS NUMBER {make_number($3), 
									  sub2(context_check_get($1)); } //ok
	| NUMBER MINUS IDENTIFIER {make_number($1) , 
									  sub2(context_check_get($3)); }//ok
	| NUMBER MINUS NUMBER {make_number($1),gen_code2(COPY,2,1) , make_number($3),
									  sub3(); } //ok
	| IDENTIFIER MINUS IDENTIFIER { sub(context_check_get($1),
									  context_check_get($3)); } //ok
									  
									  
	
	 | IDENTIFIER TIMES NUMBER {make_number($3),gen_code(STORE,8888) , 
									  multiply2(context_check_get($1)); }
	| NUMBER TIMES IDENTIFIER {make_number($1),gen_code(STORE,8888) , 
									  multiply2(context_check_get($3)); }
	| NUMBER TIMES NUMBER {make_number($1),gen_code(STORE,8888) , make_number($3),gen_code(STORE,8889) , 
									  multiply3(); }
	
	| IDENTIFIER TIMES IDENTIFIER { multiply(context_check_get($1),
										   context_check_get($3)); }
	
	| IDENTIFIER DIV NUMBER {make_number($3),gen_code(STORE,8888) , 
									  divide2(context_check_get($1)); }
	| NUMBER DIV IDENTIFIER {make_number($1),gen_code(STORE,8888) , 
									  divide2(context_check_get($3)); }
	| NUMBER DIV NUMBER {make_number($1),gen_code(STORE,8888) , make_number($3),gen_code(STORE,8889) , 
									  divide3(); }
	| IDENTIFIER DIV IDENTIFIER { divide(context_check_get($1),
										 context_check_get($3)); }
	
	
	
	| IDENTIFIER MOD NUMBER {make_number($3),gen_code(STORE,8888) , 
									  mod2(context_check_get($1)); }
	| NUMBER MOD IDENTIFIER {make_number($1),gen_code(STORE,8888) , 
									  mod2(context_check_get($3)); }
	| NUMBER MOD NUMBER {make_number($1),gen_code(STORE,8888) , make_number($3),gen_code(STORE,8889) , 
									  mod3(); }
	
	| IDENTIFIER MOD IDENTIFIER { mod(context_check_get($1),
									  context_check_get($3)); }
;
condition:	//a = 0 if condition false, if true - anything else is ok
	  IDENTIFIER EQ IDENTIFIER {con_eq(context_check_get($1),
										 context_check_get($3)); }
	 | IDENTIFIER EQ NUMBER {make_number($3),gen_code(STORE,8888) ,  con_eq2(context_check_get($1)); }									 
		 | NUMBER EQ IDENTIFIER {make_number($1),gen_code(STORE,8888) ,  con_eq2(context_check_get($3)); }	
| NUMBER EQ NUMBER {make_number($1),gen_code(STORE,8888) ,make_number($3),gen_code(STORE,8889) ,  con_eq3(); }			 									 
										 
										 
	| IDENTIFIER DIFF IDENTIFIER {con_ne(context_check_get($1),
										 context_check_get($3)); }
	
	
		 | IDENTIFIER DIFF NUMBER {make_number($3),gen_code(STORE,8888) ,  con_ne2(context_check_get($1)); }
									 
		 | NUMBER DIFF IDENTIFIER {make_number($1),gen_code(STORE,8888) ,  con_ne2(context_check_get($3)); }	
| NUMBER DIFF NUMBER {make_number($3),gen_code(STORE,8888) ,make_number($1),gen_code(STORE,8889) ,  con_ne3(); }	
	
| IDENTIFIER TO IDENTIFIER {con_ne(context_check_get($1),
										 context_check_get($3)); }
		
	| IDENTIFIER LE IDENTIFIER {con_lt(context_check_get($1),context_check_get($3)); }
	
		 | IDENTIFIER LE NUMBER {make_number($3),gen_code(STORE,8888) ,  con_lt2(context_check_get($1)); }									 
		 | NUMBER LE IDENTIFIER {make_number($1),gen_code(STORE,8888) ,  con_lt2(context_check_get($3)); }	
| NUMBER LE NUMBER {make_number($3),gen_code(STORE,8888) ,make_number($1),gen_code(STORE,8889) ,  con_lt3(); }	


										
		| IDENTIFIER LEQ IDENTIFIER {con_lteq(context_check_get($1),context_check_get($3)); }
	
		 | IDENTIFIER LEQ NUMBER {make_number($3),gen_code(STORE,8888) ,  con_lteq2(context_check_get($1)); }									 
		 | NUMBER LEQ IDENTIFIER {make_number($1),gen_code(STORE,8888) ,  con_lteq2(context_check_get($3)); }	
| NUMBER LEQ NUMBER {make_number($3),gen_code(STORE,8888) ,make_number($1),gen_code(STORE,8889) ,  con_lteq3(); }	
										
		
		| IDENTIFIER GEQ IDENTIFIER {con_gteq(context_check_get($1),context_check_get($3)); }
	
		 | IDENTIFIER GEQ NUMBER {make_number($3),gen_code(STORE,8888) ,  con_gteq2(context_check_get($1)); }									 
		 | NUMBER GEQ IDENTIFIER {make_number($1),gen_code(STORE,8888) ,  con_gteq2(context_check_get($3)); }	
| NUMBER GEQ NUMBER {make_number($3),gen_code(STORE,8888) ,make_number($1),gen_code(STORE,8889) ,  con_gteq3(); }	
										
										
	
	
	
	| IDENTIFIER GE IDENTIFIER {con_gt(context_check_get($1),
										context_check_get($3)); }
										
										
		| IDENTIFIER GE NUMBER {make_number($3),gen_code(STORE,8888) ,  con_gt2(context_check_get($1)); }									 
		 | NUMBER GE IDENTIFIER {make_number($1),gen_code(STORE,8888) ,  con_gt2(context_check_get($3)); }	
| NUMBER GE NUMBER {make_number($3),gen_code(STORE,8888) ,make_number($1),gen_code(STORE,8889) ,  con_gt3(); }	
										
	| NUMBER TO NUMBER {}
| NUMBER DOWNTO NUMBER {}
	
									   
;

%%

int main(int argc, char *argv[]){
	extern FILE* yyin;
	yyin = fopen( argv[1], "r");
	FILE* out = fopen( argv[2], "w");
	yydebug = 0;
	errors = 0;
	lines = 0;
	yyparse();
	if(!errors){
		print_code(out);
		printf("Compilation successful.\n");
	} else
		printf("Compilation failed with %d errors.\n", errors);
	del_symbols();
}
int yyerror (char *s){
	raise_error(WRONG_MATCHING, s);
}
