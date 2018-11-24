/**************
Error handler.c
**************/

#include <stdio.h>
#include "error_handler.h"


char *error_messages[] = {
	"identifier already defined:",
	"undeclared identifier:",
	"can't read undefined variable:",
	
	"in std04, newline is not acceptable in comment:",
	"matching error:"
};

void raise_error(enum error_args err, char* ident){
	errors++;
	fprintf(stderr,"Line %d: ", lines);
	fprintf(stderr,"%s %s\n",error_messages[err], ident);
}
