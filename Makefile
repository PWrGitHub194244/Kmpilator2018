all: compiler.y compiler.l error_handler.o label.o
	bison -d compiler.y
	gcc -std=c99 -c compiler.tab.c
	flex compiler.l
	gcc -c lex.yy.c
	gcc -o compiler compiler.tab.o lex.yy.o error_handler.o label.o -lm
	
error_handler.o: error_handler.c
	gcc -c error_handler.c
	
label.o: label.c
	gcc -c label.c

clean:
	rm -rf *.o
	rm -rf lex.yy.c
	rm -rf compiler.tab.h
	rm -rf compiler.tab.c
	

