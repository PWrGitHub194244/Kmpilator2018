/**************
Error handler.h
**************/

#ifndef EH_H
#define EH_H

int errors;	//number of errors
int lines;	//current line

enum error_args {
	IDEN_DEC,			//identifier already defined
	IDEN_UNDEC,			//identifier not defined in this scope
	VAR_UNDEF,			//variable declared but not defined

	NEWLINE_COMMENT,	//newline in comment
	WRONG_MATCHING		//probably unmatched character
};

void raise_error(enum error_args err, char* ident);

#endif
