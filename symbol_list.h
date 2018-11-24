/**************
Symbol List
**************/

typedef struct slist{
	bool is_defined;
	char *name;		//symbol name
	int offset;		//offset in data memory for variables, value for constans
	struct slist *next;		//ptr to next
} slist;

//slist* identifier;

slist* dict = NULL;

//declares a symbol
//and returns it's node
slist* put_sym(char* sym_name){
	slist* fresh = malloc(sizeof(slist));
	fresh->name = malloc(strlen(sym_name)+1);
	strcpy(fresh->name,sym_name);
	fresh->offset = data_locate();
	fresh->next = dict;
	fresh->is_defined = 0;
	dict = fresh;
	return fresh;
}

//declares a constant
//and returns it's node


//returns node with given symbol
//if it's not declared, returns NULL
slist* get_symbol(char* sym_name){
	for(slist* ptr = dict; ptr != NULL; ptr = ptr->next)
		if(strcmp(ptr->name, sym_name) == 0)
			return ptr;
	return NULL;
}

//deletes Symbol Table
void del_symbols(){
	slist* ptr = dict;
	slist* tmp;
	while(ptr != NULL){
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
};
