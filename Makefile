make: opt_compiler.y opt_compiler.l
	bison -d opt_compiler.y
	flex opt_compiler.l
	g++ -std=c++11 -o compiler lex.yy.c opt_compiler.tab.c 
clean:
	rm -rf *.o
	rm -rf lex.yy.c
	rm -rf compiler.tab.h
	rm -rf compiler.tab.c
