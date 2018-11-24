/***********
* Label.h
************/
#ifndef COMPILER_H
#define COMPILER_H

struct lbl{
	int for_jump;
	int for_jump_false;
};

typedef struct lbl* label;

label new_label();

#endif