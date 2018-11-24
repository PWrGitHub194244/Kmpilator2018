/***********
* Label.c
************/

#include "label.h"
#include <stdlib.h>



label new_label(){
	return malloc(sizeof(struct lbl));
}