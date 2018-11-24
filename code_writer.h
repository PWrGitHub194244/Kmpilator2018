/**************
Code Writer
**************/
bool first_variables=0;
//a = num;
void make_number(unsigned long long int num){
	//if(!first_variables){
	  
	//gen_code(INC, -1);
	//gen_code(STORE, 888);
	//first_variables=1;
	//}
	
	  
	int n = 0;
gen_code2(SUB, 1, 1);
	for(int i=0 ;i < num; i++)
gen_code(INC, 1);
	//n--;
	gen_code(STORE, 1);
			
		
		
}

//a = sym
void get_identifier(slist* sym){
	if(sym == NULL){}
	else{
	
		//gen_code(LOAD,sym->offset);
}
}

//PUT sym
void write_identifier(slist* sym){
	if(sym == NULL);
	else{
		//gen_code(LOAD,sym->offset);
		gen_code(WRITE,sym->offset);
	}
	
}

//a = sym1 + sym2
void add(slist* sym1, slist* sym2){
	if(sym1 == NULL || sym2 == NULL)
	return;
	else {
		//gen_code(LOAD,sym1->offset);
		gen_code2(ADD, sym1->offset,sym2->offset);
        gen_code(STORE, sym1->offset);
	}
}
//a = sym1 + exp
void addexp2(slist* sym1 ){
	if(sym1 == NULL )
	return;
	else {
		//gen_code(LOAD,sym1->offset);
		gen_code2(ADD,1,sym1->offset);
gen_code(STORE, sym1->offset);
	}
}

//a = exp1 + ex2
void addexp3(){
	
	
		//gen_code(LOAD,8889);
		gen_code2(ADD,2,1);
	gen_code(STORE, 2);
}

//a = sym1 - sym2
void sub(slist* sym1, slist* sym2){
if(sym1 == NULL || sym2 == NULL) return;
	else{
		//gen_code(LOAD,sym1->offset);
		gen_code2(SUB, sym1->offset,sym2->offset);
gen_code(STORE, sym1->offset);	
}
}

//a = sym1 - exp
void sub2(slist* sym1){
if(sym1 == NULL ) return;
	else{
		//gen_code(LOAD,sym1->offset);
		gen_code2(SUB,sym1->offset,1);
gen_code(STORE, sym1->offset);	
}
}

//a = exp1 - exp2
void sub3(){
		gen_code2(SUB,2,1);
	gen_code(STORE, 2);
	}

//a = sym1 * sym2
void multiply(slist* sym1, slist* sym2){
	
	if(sym1 == NULL || sym2 == NULL) return;
	
	gen_code(STORE,sym1->offset);
	int while_label = get_label();
	gen_code2(JZERO,sym1->offset,while_label + 4);		//0
    gen_code(DEC,sym1->offset);	 //1
   gen_code2(ADD,sym2->offset,sym1->offset);					//2
	gen_code(JUMP,while_label);			//3
    gen_code(STORE,sym2->offset);					//4
	}


//a = sym1 * exp
void multiply2(slist* sym1){
	
	if(sym1 == NULL ) return;
	
		gen_code(LOAD,sym1->offset);
	
	gen_code(STORE,1);
	 
	gen_code(STORE,0);
	
		gen_code(LOAD,8888);
	
	int while_label = get_label();
	gen_code(JZERO,while_label + 13);		//0
	gen_code(STORE,2);					//1
	gen_code(JODD,while_label + 4);		//2
	gen_code(JUMP,while_label + 7);		//3
	gen_code(LOAD,0);					//4
	gen_code(ADD, 1);					//5
	gen_code(STORE,0);					//6
	gen_code(LOAD,1);					//7
	gen_code(SHL,888);					//8
	gen_code(STORE,1);					//9
	gen_code(LOAD,2);					//10
	gen_code(SHR,888);					//11
	gen_code(JUMP,while_label);			//12
	gen_code(LOAD, 0);					
}

void multiply3(){
	
	
		gen_code(LOAD,8888);
	
	gen_code(STORE,1);
	 
	gen_code(STORE,0);
	
		gen_code(LOAD,8889);
	
	int while_label = get_label();
	gen_code(JZERO,while_label + 13);		//0
	gen_code(STORE,2);					//1
	gen_code(JODD,while_label + 4);		//2
	gen_code(JUMP,while_label + 7);		//3
	gen_code(LOAD,0);					//4
	gen_code(ADD, 1);					//5
	gen_code(STORE,0);					//6
	gen_code(LOAD,1);					//7
	gen_code(SHL,888);					//8
	gen_code(STORE,1);					//9
	gen_code(LOAD,2);					//10
	gen_code(SHR,888);					//11
	gen_code(JUMP,while_label);			//12
	gen_code(LOAD, 0);					
}

//a = sym1 / sym2
void divide(slist* sym1, slist* sym2){
	
	if(sym1 == NULL || sym2 == NULL) return;
	
	
		gen_code(LOAD, sym2->offset);
	
	int bp_return_a_1 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor == 0: return 0
	gen_code(STORE, 0);					//0: divisor
				//1: dividend
		gen_code(LOAD, sym1->offset);	//2: remainder
	
	gen_code(STORE, 1);
	gen_code(INC, -1);
	gen_code(SUB, 0);
	int bp_return_a_2 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor > divident: return 0
	gen_code(SUB, 888);
	int bp_return_a_plus_1 = get_label();	//---back_patch
	gen_code(JZERO, 9999);					//if divisor == divident: return 1
	//reverse (dividend << 1 | 1)
	  
	gen_code(STORE, 3);					//quotient = 0
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	int reverse_label = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//jz to end of reverse_loop
	int bp_reverse_if_odd = get_label();	//---back_patch
	gen_code(JODD, 9999);		
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(bp_reverse_if_odd, JODD, get_label());
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(reverse_label, JZERO, get_label());
	gen_code(LOAD, 2);					//1:dividend_reversed
	gen_code(SHL, 888);
	//while remainder < divisor
	gen_code(STORE, 1);
	  
	gen_code(STORE, 2);
	int rem_div_label = get_label();
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	int bp_end_while_1 = get_label();			//---back_patch
	gen_code(JZERO, 9999);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	int bp_while_if_odd = get_label();			//---back_patch
	gen_code(JODD, 9999);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_while_if_odd, JODD, get_label());
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_end_while_1, JZERO, get_label());
	//end while
	gen_code(LOAD, 2);
	gen_code(SHR, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	//while div_inv != 1		//needs div_inv in a
	int div_inv_label = get_label();
	gen_code(SUB, 888);
	int bp_return_3 = get_label();		//---back_patch
	gen_code(JZERO, 9999);
	gen_code(INC, -1);
	gen_code(JODD, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	//if remainder >= divisor
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	gen_code(JZERO, get_label() + 2);		//---relative jump
	int bp_rem_gt_div_true = get_label();	//---back_patch
	gen_code(JUMP, 9999);
	gen_code(LOAD, 3);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 3);
	gen_code(LOAD, 2);
	gen_code(SUB, 0);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 4);	//---relative jump
	back_patch(bp_rem_gt_div_true, JUMP, get_label());
	gen_code(LOAD, 3);
	gen_code(SHL, 888);
	gen_code(STORE, 3);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(JUMP, div_inv_label);
	//return 3
	back_patch(bp_return_3, JZERO, get_label());
	gen_code(LOAD, 3);
	gen_code(JUMP, get_label() + 2);	//---relative jump
	//*****end_while *****/
	back_patch(bp_return_a_plus_1, JZERO, get_label());
	gen_code(INC, -1);					//only used in line 9 - returns 1
	back_patch(bp_return_a_1, JZERO, get_label());
	back_patch(bp_return_a_2, JZERO, get_label());
}

//a = sym1 / exp
void divide2(slist* sym1){
	
	if(sym1 == NULL ) return;
	
	
		gen_code(LOAD, 8888);
	
	int bp_return_a_1 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor == 0: return 0
	gen_code(STORE, 0);					//0: divisor
				//1: dividend
		gen_code(LOAD, sym1->offset);	//2: remainder
	
	gen_code(STORE, 1);
	gen_code(INC, -1);
	gen_code(SUB, 0);
	int bp_return_a_2 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor > divident: return 0
	gen_code(SUB, 888);
	int bp_return_a_plus_1 = get_label();	//---back_patch
	gen_code(JZERO, 9999);					//if divisor == divident: return 1
	//reverse (dividend << 1 | 1)
	  
	gen_code(STORE, 3);					//quotient = 0
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	int reverse_label = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//jz to end of reverse_loop
	int bp_reverse_if_odd = get_label();	//---back_patch
	gen_code(JODD, 9999);		
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(bp_reverse_if_odd, JODD, get_label());
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(reverse_label, JZERO, get_label());
	gen_code(LOAD, 2);					//1:dividend_reversed
	gen_code(SHL, 888);
	//while remainder < divisor
	gen_code(STORE, 1);
	  
	gen_code(STORE, 2);
	int rem_div_label = get_label();
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	int bp_end_while_1 = get_label();			//---back_patch
	gen_code(JZERO, 9999);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	int bp_while_if_odd = get_label();			//---back_patch
	gen_code(JODD, 9999);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_while_if_odd, JODD, get_label());
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_end_while_1, JZERO, get_label());
	//end while
	gen_code(LOAD, 2);
	gen_code(SHR, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	//while div_inv != 1		//needs div_inv in a
	int div_inv_label = get_label();
	gen_code(SUB, 888);
	int bp_return_3 = get_label();		//---back_patch
	gen_code(JZERO, 9999);
	gen_code(INC, -1);
	gen_code(JODD, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	//if remainder >= divisor
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	gen_code(JZERO, get_label() + 2);		//---relative jump
	int bp_rem_gt_div_true = get_label();	//---back_patch
	gen_code(JUMP, 9999);
	gen_code(LOAD, 3);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 3);
	gen_code(LOAD, 2);
	gen_code(SUB, 0);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 4);	//---relative jump
	back_patch(bp_rem_gt_div_true, JUMP, get_label());
	gen_code(LOAD, 3);
	gen_code(SHL, 888);
	gen_code(STORE, 3);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(JUMP, div_inv_label);
	//return 3
	back_patch(bp_return_3, JZERO, get_label());
	gen_code(LOAD, 3);
	gen_code(JUMP, get_label() + 2);	//---relative jump
	//*****end_while *****/
	back_patch(bp_return_a_plus_1, JZERO, get_label());
	gen_code(INC, -1);					//only used in line 9 - returns 1
	back_patch(bp_return_a_1, JZERO, get_label());
	back_patch(bp_return_a_2, JZERO, get_label());
}


//a = exp / exp
void divide3(){
	
	
	
		gen_code(LOAD, 8888);
	
	int bp_return_a_1 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor == 0: return 0
	gen_code(STORE, 0);					//0: divisor
				//1: dividend
		gen_code(LOAD,8889);	//2: remainder
	
	gen_code(STORE, 1);
	gen_code(INC, -1);
	gen_code(SUB, 0);
	int bp_return_a_2 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor > divident: return 0
	gen_code(SUB, 888);
	int bp_return_a_plus_1 = get_label();	//---back_patch
	gen_code(JZERO, 9999);					//if divisor == divident: return 1
	//reverse (dividend << 1 | 1)
	  
	gen_code(STORE, 3);					//quotient = 0
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	int reverse_label = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//jz to end of reverse_loop
	int bp_reverse_if_odd = get_label();	//---back_patch
	gen_code(JODD, 9999);		
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(bp_reverse_if_odd, JODD, get_label());
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(reverse_label, JZERO, get_label());
	gen_code(LOAD, 2);					//1:dividend_reversed
	gen_code(SHL, 888);
	//while remainder < divisor
	gen_code(STORE, 1);
	  
	gen_code(STORE, 2);
	int rem_div_label = get_label();
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	int bp_end_while_1 = get_label();			//---back_patch
	gen_code(JZERO, 9999);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	int bp_while_if_odd = get_label();			//---back_patch
	gen_code(JODD, 9999);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_while_if_odd, JODD, get_label());
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_end_while_1, JZERO, get_label());
	//end while
	gen_code(LOAD, 2);
	gen_code(SHR, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	//while div_inv != 1		//needs div_inv in a
	int div_inv_label = get_label();
	gen_code(SUB, 888);
	int bp_return_3 = get_label();		//---back_patch
	gen_code(JZERO, 9999);
	gen_code(INC, -1);
	gen_code(JODD, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	//if remainder >= divisor
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	gen_code(JZERO, get_label() + 2);		//---relative jump
	int bp_rem_gt_div_true = get_label();	//---back_patch
	gen_code(JUMP, 9999);
	gen_code(LOAD, 3);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 3);
	gen_code(LOAD, 2);
	gen_code(SUB, 0);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 4);	//---relative jump
	back_patch(bp_rem_gt_div_true, JUMP, get_label());
	gen_code(LOAD, 3);
	gen_code(SHL, 888);
	gen_code(STORE, 3);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(JUMP, div_inv_label);
	//return 3
	back_patch(bp_return_3, JZERO, get_label());
	gen_code(LOAD, 3);
	gen_code(JUMP, get_label() + 2);	//---relative jump
	//*****end_while *****/
	back_patch(bp_return_a_plus_1, JZERO, get_label());
	gen_code(INC, -1);					//only used in line 9 - returns 1
	back_patch(bp_return_a_1, JZERO, get_label());
	back_patch(bp_return_a_2, JZERO, get_label());
}




//a = sym1 % sym2
void mod(slist* sym1, slist* sym2){

	
	if(sym1 == NULL || sym2 == NULL) return;
	
		gen_code(LOAD, sym2->offset);
	
	int bp_return_a_1 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor == 0: return 0
	gen_code(STORE, 0);					//0: divisor
	
		gen_code(LOAD, sym1->offset);	//2: remainder
	
	gen_code(STORE, 1);
	gen_code(INC, -1);
	gen_code(SUB, 0);
	int bp_return_r0 = get_label();			//---back_patch
	gen_code(JZERO, 9999);					//if divisor > divident: return r0
	gen_code(SUB, 888);
	int bp_return_a_2 = get_label();	//---back_patch
	gen_code(JZERO, 9999);					//if divisor == divident: return 0
	//reverse (dividend << 1 | 1)
	  
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	int reverse_label = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//jz to end of reverse_loop
	int bp_reverse_if_odd = get_label();	//---back_patch
	gen_code(JODD, 9999);		
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(bp_reverse_if_odd, JODD, get_label());
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(reverse_label, JZERO, get_label());
	gen_code(LOAD, 2);					//1:dividend_reversed
	gen_code(SHL, 888);
	//while remainder < divisor
	gen_code(STORE, 1);
	  
	gen_code(STORE, 2);
	int rem_div_label = get_label();
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	int bp_end_while_1 = get_label();			//---back_patch
	gen_code(JZERO, 9999);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	int bp_while_if_odd = get_label();			//---back_patch
	gen_code(JODD, 9999);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_while_if_odd, JODD, get_label());
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_end_while_1, JZERO, get_label());
	//end while
	gen_code(LOAD, 2);
	gen_code(SHR, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	//while div_inv != 1		//needs div_inv in a
	int div_inv_label = get_label();
	gen_code(SUB, 888);
	int bp_return_3 = get_label();		//---back_patch
	gen_code(JZERO, 9999);
	gen_code(INC, -1);
	gen_code(JODD, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	//if remainder >= divisor
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	gen_code(JZERO, get_label() + 2);		//---relative jump
	int bp_rem_gt_div_true = get_label();	//---back_patch
	gen_code(JUMP, 9999);
	gen_code(LOAD, 2);
	gen_code(SUB, 0);
	gen_code(STORE, 2);
	back_patch(bp_rem_gt_div_true, JUMP, get_label());
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(JUMP, div_inv_label);
	//return 3
	back_patch(bp_return_3, JZERO, get_label());
	gen_code(LOAD, 2);
	gen_code(JUMP, get_label() + 2);	//---relative jump
	//*****end_while *****/
	back_patch(bp_return_r0, JZERO, get_label());
	gen_code(LOAD, 0);					//only used in line 9 - returns 1
	back_patch(bp_return_a_1, JZERO, get_label());
	back_patch(bp_return_a_2, JZERO, get_label());
}


//a = sym1 % exp
void mod2(slist* sym1){

	
	if(sym1 == NULL ) return;
	
		gen_code(LOAD, 8888);
	
	int bp_return_a_1 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor == 0: return 0
	gen_code(STORE, 0);					//0: divisor
	
		gen_code(LOAD, sym1->offset);	//2: remainder
	
	gen_code(STORE, 1);
	gen_code(INC, -1);
	gen_code(SUB, 0);
	int bp_return_r0 = get_label();			//---back_patch
	gen_code(JZERO, 9999);					//if divisor > divident: return r0
	gen_code(SUB, 888);
	int bp_return_a_2 = get_label();	//---back_patch
	gen_code(JZERO, 9999);					//if divisor == divident: return 0
	//reverse (dividend << 1 | 1)
	  
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	int reverse_label = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//jz to end of reverse_loop
	int bp_reverse_if_odd = get_label();	//---back_patch
	gen_code(JODD, 9999);		
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(bp_reverse_if_odd, JODD, get_label());
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(reverse_label, JZERO, get_label());
	gen_code(LOAD, 2);					//1:dividend_reversed
	gen_code(SHL, 888);
	//while remainder < divisor
	gen_code(STORE, 1);
	  
	gen_code(STORE, 2);
	int rem_div_label = get_label();
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	int bp_end_while_1 = get_label();			//---back_patch
	gen_code(JZERO, 9999);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	int bp_while_if_odd = get_label();			//---back_patch
	gen_code(JODD, 9999);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_while_if_odd, JODD, get_label());
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_end_while_1, JZERO, get_label());
	//end while
	gen_code(LOAD, 2);
	gen_code(SHR, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	//while div_inv != 1		//needs div_inv in a
	int div_inv_label = get_label();
	gen_code(SUB, 888);
	int bp_return_3 = get_label();		//---back_patch
	gen_code(JZERO, 9999);
	gen_code(INC, -1);
	gen_code(JODD, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	//if remainder >= divisor
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	gen_code(JZERO, get_label() + 2);		//---relative jump
	int bp_rem_gt_div_true = get_label();	//---back_patch
	gen_code(JUMP, 9999);
	gen_code(LOAD, 2);
	gen_code(SUB, 0);
	gen_code(STORE, 2);
	back_patch(bp_rem_gt_div_true, JUMP, get_label());
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(JUMP, div_inv_label);
	//return 3
	back_patch(bp_return_3, JZERO, get_label());
	gen_code(LOAD, 2);
	gen_code(JUMP, get_label() + 2);	//---relative jump
	//*****end_while *****/
	back_patch(bp_return_r0, JZERO, get_label());
	gen_code(LOAD, 0);					//only used in line 9 - returns 1
	back_patch(bp_return_a_1, JZERO, get_label());
	back_patch(bp_return_a_2, JZERO, get_label());
}

//a = exp % exp
void mod3(){

	

	
		gen_code(LOAD, 8888);
	
	int bp_return_a_1 = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//if divisor == 0: return 0
	gen_code(STORE, 0);					//0: divisor
	
		gen_code(LOAD, 8889);	//2: remainder
	
	gen_code(STORE, 1);
	gen_code(INC, -1);
	gen_code(SUB, 0);
	int bp_return_r0 = get_label();			//---back_patch
	gen_code(JZERO, 9999);					//if divisor > divident: return r0
	gen_code(SUB, 888);
	int bp_return_a_2 = get_label();	//---back_patch
	gen_code(JZERO, 9999);					//if divisor == divident: return 0
	//reverse (dividend << 1 | 1)
	  
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	int reverse_label = get_label();		//---back_patch
	gen_code(JZERO, 9999);					//jz to end of reverse_loop
	int bp_reverse_if_odd = get_label();	//---back_patch
	gen_code(JODD, 9999);		
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(bp_reverse_if_odd, JODD, get_label());
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	gen_code(JUMP, reverse_label);
	back_patch(reverse_label, JZERO, get_label());
	gen_code(LOAD, 2);					//1:dividend_reversed
	gen_code(SHL, 888);
	//while remainder < divisor
	gen_code(STORE, 1);
	  
	gen_code(STORE, 2);
	int rem_div_label = get_label();
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	int bp_end_while_1 = get_label();			//---back_patch
	gen_code(JZERO, 9999);
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	int bp_while_if_odd = get_label();			//---back_patch
	gen_code(JODD, 9999);
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_while_if_odd, JODD, get_label());
	gen_code(STORE, 1);
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	gen_code(JUMP, rem_div_label);
	back_patch(bp_end_while_1, JZERO, get_label());
	//end while
	gen_code(LOAD, 2);
	gen_code(SHR, 888);
	gen_code(STORE, 2);
	gen_code(LOAD, 1);
	//while div_inv != 1		//needs div_inv in a
	int div_inv_label = get_label();
	gen_code(SUB, 888);
	int bp_return_3 = get_label();		//---back_patch
	gen_code(JZERO, 9999);
	gen_code(INC, -1);
	gen_code(JODD, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(STORE, 2);
	gen_code(JUMP, get_label() + 5);	//---relative jump
	gen_code(LOAD, 2);
	gen_code(SHL, 888);
	gen_code(INC, -1);
	gen_code(STORE, 2);
	//if remainder >= divisor
	gen_code(LOAD, 0);
	gen_code(SUB, 2);
	gen_code(JZERO, get_label() + 2);		//---relative jump
	int bp_rem_gt_div_true = get_label();	//---back_patch
	gen_code(JUMP, 9999);
	gen_code(LOAD, 2);
	gen_code(SUB, 0);
	gen_code(STORE, 2);
	back_patch(bp_rem_gt_div_true, JUMP, get_label());
	gen_code(LOAD, 1);
	gen_code(SHR, 888);
	gen_code(STORE, 1);
	gen_code(JUMP, div_inv_label);
	//return 3
	back_patch(bp_return_3, JZERO, get_label());
	gen_code(LOAD, 2);
	gen_code(JUMP, get_label() + 2);	//---relative jump
	//*****end_while *****/
	back_patch(bp_return_r0, JZERO, get_label());
	gen_code(LOAD, 0);					//only used in line 9 - returns 1
	back_patch(bp_return_a_1, JZERO, get_label());
	back_patch(bp_return_a_2, JZERO, get_label());
}

/*=========CONDITIONS===========*/
//a = 0 if codition is false, anything else if otherwise

// sym1 == sym2
void con_eq(slist* sym1, slist* sym2){
	if(sym1 == NULL || sym2 == NULL) return;
	
		gen_code(LOAD,sym1->offset);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,sym2->offset);
	
	gen_code(STORE, 1);
	gen_code(SUB, 0);
	gen_code(JZERO, get_label() + 2);
	gen_code(JUMP, get_label() + 4);
	gen_code(LOAD, 0);
	gen_code(SUB, 1);
	gen_code(JZERO, get_label() + 3);
	  
	gen_code(JUMP, get_label() + 2);
	gen_code(INC, -1);
}

// sym1 == exp
void con_eq2(slist* sym1){
	if(sym1 == NULL) return;
	
		gen_code(LOAD,sym1->offset);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,8888);
	
	gen_code(STORE, 1);
	gen_code(SUB, 0);
	gen_code(JZERO, get_label() + 2);
	gen_code(JUMP, get_label() + 4);
	gen_code(LOAD, 0);
	gen_code(SUB, 1);
	gen_code(JZERO, get_label() + 3);
	  
	gen_code(JUMP, get_label() + 2);
	gen_code(INC, -1);
}

// exp == exp
void con_eq3(){
	
	
		gen_code(LOAD,8888);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,8889);
	
	gen_code(STORE, 1);
	gen_code(SUB, 0);
	gen_code(JZERO, get_label() + 2);
	gen_code(JUMP, get_label() + 4);
	gen_code(LOAD, 0);
	gen_code(SUB, 1);
	gen_code(JZERO, get_label() + 3);
	  
	gen_code(JUMP, get_label() + 2);
	gen_code(INC, -1);
}

// sym1 != sym2
void con_ne(slist* sym1, slist* sym2){
	if(sym1 == NULL || sym2 == NULL) return;
	
		gen_code(LOAD,sym1->offset);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,sym2->offset);
	
	gen_code(STORE, 1);
	gen_code(SUB, 0);
	gen_code(JZERO, get_label() + 2);
	gen_code(JUMP, get_label() + 4);
	gen_code(LOAD, 0);
	gen_code(SUB, 1);
	gen_code(JZERO, get_label() + 3);
	gen_code(INC, -1);
	gen_code(JUMP, get_label() + 2);
	  
}


// sym1 != exp
void con_ne2(slist* sym1){
	if(sym1 == NULL ) return;
	
		gen_code(LOAD,sym1->offset);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,8888);
	
	gen_code(STORE, 1);
	gen_code(SUB, 0);
	gen_code(JZERO, get_label() + 2);
	gen_code(JUMP, get_label() + 4);
	gen_code(LOAD, 0);
	gen_code(SUB, 1);
	gen_code(JZERO, get_label() + 3);
	gen_code(INC, -1);
	gen_code(JUMP, get_label() + 2);
	  
}

// exp != exp
void con_ne3(){
	
	
		gen_code(LOAD,8888);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,8889);
	
	gen_code(STORE, 1);
	gen_code(SUB, 0);
	gen_code(JZERO, get_label() + 2);
	gen_code(JUMP, get_label() + 4);
	gen_code(LOAD, 0);
	gen_code(SUB, 1);
	gen_code(JZERO, get_label() + 3);
	gen_code(INC, -1);
	gen_code(JUMP, get_label() + 2);
	  
}

// sym1 < sym2
void con_lt(slist* sym1, slist* sym2){
	if(sym1 == NULL || sym2 == NULL) return;
	
		gen_code(LOAD,sym1->offset);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,sym2->offset);
	
	gen_code(SUB, 0);
}

// sym1 < exp
void con_lt2(slist* sym1){
	if(sym1 == NULL ) return;
	
		gen_code(LOAD,sym1->offset);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,8888);
	
	gen_code(SUB, 0);
}
void con_lt3(){
	
	
		gen_code(LOAD,8888);
	
	gen_code(STORE, 0);
	
		gen_code(LOAD,8889);
	
	gen_code(SUB, 0);
}


// sym1 <= sym2
void con_lteq(slist* sym1, slist* sym2){
	if(sym1 == NULL || sym2 == NULL) return;
	
		gen_code(LOAD,sym1->offset);
	
	//gen_code(STORE, 0);
		gen_code(LOAD,sym2->offset);
	
	//gen_code(INC, -1);
	gen_code(SUB, 0);
}


// sym1 <= exp
void con_lteq2(slist* sym1){
	if(sym1 == NULL ) return;
	
		gen_code(LOAD,sym1->offset);
	
	gen_code(STORE, 0);
		gen_code(LOAD,8888);
	
	gen_code(INC, -1);
	gen_code(SUB, 0);
}

// exp <= exp
void con_lteq3(){
	
	
		gen_code(LOAD,8888);
	
	gen_code(STORE, 0);
		gen_code(LOAD,8889);
	
	gen_code(INC, -1);
	gen_code(SUB, 0);
}



// sym1 > sym2
void con_gt(slist* sym1, slist* sym2){
	con_lt(sym2, sym1);
}
// sym1 > exp
void con_gt2(slist* sym1){
	con_lt2(sym1);
}
// exp > exp
void con_gt3(){
	con_lt3();
}

// sym1 >= sym2
void con_gteq(slist* sym1, slist* sym2){
	con_lteq(sym2, sym1);
}

// sym1 >= exp
void con_gteq2(slist* sym1){
	con_lteq2(sym1);
}
// exp >= exp
void con_gteq3(){
	con_lteq3();
}
