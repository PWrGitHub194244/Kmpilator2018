%{
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	string name;
    string type; //NUM, IDE, ARR
    int initialized;
    int counter;
	long long int mem;
	long long int local;
  	long long int tableSize;
} Identifier;

typedef struct {
    long long int placeInStack;
    long long int depth;
} Jump;

map<string, Identifier> identifierStack;
vector<string> codeStack;
vector<Jump> jumpStack;
vector<Identifier> forStack;
/*vector<long long int> initializedMem;*/

int yylex();
extern int yylineno;
int yyerror(const string str);

void pushCommand(string str);
void pushCommandOneArg(string str, long long int num);
void createIdentifier(Identifier *s, string name, long long int isLocal,
    long long int isArray, string type);
void insertIdentifier(string key, Identifier i);
void removeIdentifier(string key);
void createJump(Jump *j, long long int stack, long long int depth);
void registerToMem(long long int mem);
void setRegister(string number);
void setRegister2(string number);
void zeroRegister();
void memToRegister(long long int mem);
void memToRegister2(long long int mem);
void registerToMem();
void add(Identifier a, Identifier b);
void addTab(Identifier a, Identifier b, Identifier aIndex, Identifier bIndex);
void sub(Identifier a, Identifier b, int isINC, int isRemoval);
void subTab(Identifier a, Identifier b, Identifier aIndex, Identifier bIndex, int isINC, int isRemoval);
void addInt(long long int command, long long int val);
long long int setToTempMem(Identifier a, Identifier aI, long long int tempMem, int isJZERO, int isRemoval);
string decToBin(long long int dec);

long long int memCounter;
/*long long int registerValue;*/
long long int depth;
int assignFlag;
int writeFlag;
Identifier assignTarget;
string tabAssignTargetIndex = "-1";
string expressionArguments[2] = {"-1", "-1"};
string argumentsTabIndex[2] = {"-1", "-1"};

%}

%define parse.error verbose
%define parse.lac full
%union {
    char* str;
    long long int num;
}
%token <str> NUM
%token <str> VAR BEG END IF THEN ELSE ENDIF
%token <str> DO WHILE  ENDWHILE FOR FROM ENDFOR ENDDO
%token <str> WRITE READ IDE SEM TO DOWNTO
%token <str> LB RB ASG EQ LT GT LE GE NE ADD SUB MUL DIV MOD COLON

%type <str> value
%type <str> identifier


%%
program:
    VAR vdeclarations BEG commands END {
        pushCommand("HALT");
    }
;

vdeclarations:
    vdeclarations IDE SEM {
        if(identifierStack.find($2)!=identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno \
            << "]: Kolejna deklaracja zmiennej " << $<str>2 << "." << endl;
            exit(1);
        }
        else {
            Identifier s;
            createIdentifier(&s, $2, 0, 0, "IDE");
            insertIdentifier($2, s);
        }
    }
|   vdeclarations IDE LB NUM COLON NUM RB SEM{
        if(identifierStack.find($2)!=identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno \
            << "]: Kolejna deklaracja zmiennej " << $<str>2 << "." << endl;
            exit(1);
        }
        else if (atoll($6)-atoll($4) <= 0) {
            cout << "Błąd [okolice linii " << yylineno \
            << "]: Deklarowanie tablicy " << $<str>2 << " o rozmiarze zero." << endl;
            exit(1);
        }
        else {
            long long int size = $6- $4;
            Identifier s;
            createIdentifier(&s, $2, 0, size, "ARR");
            insertIdentifier($2, s);
            memCounter += size;
            setRegister(to_string(s.mem+1));
            registerToMem(s.mem);
        }
    }
|
;

commands:
    commands command
|   command
;

command:
    identifier ASG {
        assignFlag = 0;
    } expression SEM {
        if(assignTarget.type == "ARR") {
            Identifier index = identifierStack.at(tabAssignTargetIndex);
            if(index.type == "NUM") {
                long long int tabElMem = assignTarget.mem + stoll(index.name) + 1;
                registerToMem(tabElMem);
                removeIdentifier(index.name);
            }
            else {
                memToRegister2(assignTarget.mem);
                vector<string> opcodes;
                long long int startsFrom = index.mem;
                long long  int endsAt = 0;
                long long   int current = startsFrom;
                long long  int cost = 0;

                pushCommand("SUB A A");

                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                      current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                            current--;
                            cost++;
                            opcodes.push_back("INC A");
                        }
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD A A");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
	                pushCommand(opcodes.at(i));
                }
                pushCommand("LOAD A ");
                pushCommand("ADD A C ");
                pushCommand("STORE B");
            }
        }
        else if(assignTarget.local == 0) {
            registerToMem(assignTarget.mem);
        }
      	else {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Próba modyfikacji iteratora pętli." << endl;
      		exit(1);
      	}
        identifierStack.at(assignTarget.name).initialized = 1;
        /*if(initializedMem.empty() ||
            find(initializedMem.begin(), initializedMem.end(), assignTarget.name) == initializedMem.end())) {
            initializedMem.push_back(assignTarget.mem);
        }*/
      	assignFlag = 1;
    }
|   IF {assignFlag = 0;
        depth++;
    } condition {
        assignFlag = 1;
    } THEN commands ifbody
 | DO {
        assignFlag = 0;
        depth++;
        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
    } commands WHILE { assignFlag = 0;} condition {  long long int stack;
codeStack.at(codeStack.size()-1)="JZERO B "+to_string(codeStack.size()+1);
        long long int jumpCount = jumpStack.size()-1; stack = jumpStack.at(jumpCount-1).placeInStack;   stack = jumpStack.at(jumpCount-1).placeInStack;
           pushCommandOneArg("JUMP",stack);  depth--;} ENDDO
|   WHILE {
        assignFlag = 0;
        depth++;
        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
    } condition {
        assignFlag = 1;
    } DO commands ENDWHILE {
        long long int stack;
        long long int jumpCount = jumpStack.size()-1;
        if(jumpCount > 2 && jumpStack.at(jumpCount-2).depth == depth) {
            stack = jumpStack.at(jumpCount-2).placeInStack;
            pushCommandOneArg("JUMP", stack);
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
            addInt(jumpStack.at(jumpCount-1).placeInStack, codeStack.size());
            jumpStack.pop_back();
        }
        else {
            stack = jumpStack.at(jumpCount-1).placeInStack;
            pushCommandOneArg("JUMP", stack);
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
        }
        jumpStack.pop_back();
        jumpStack.pop_back();

        /*registerValue = -1;*/
        depth--;
        assignFlag = 1;
    }
 
|   FOR IDE {
        if(identifierStack.find($2)!=identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno \
            << "]: Kolejna deklaracja zmiennej " << $<str>2 << "." << endl;
            exit(1);
        }
        else {
            Identifier s;
            createIdentifier(&s, $2, 1, 0, "IDE");
            insertIdentifier($2, s);
        }
        assignFlag = 0;
        assignTarget = identifierStack.at($2);
        depth++;
    } FROM value{pushCommand("INC B");} forbody
|   READ identifier {
        assignFlag = 1;
    } SEM {
        /*registerValue = -1;*/
        if(assignTarget.type == "ARR") {
            Identifier index = identifierStack.at(tabAssignTargetIndex);
            if(index.type == "NUM") {
                pushCommand("GET B");
                long long int tabElMem = assignTarget.mem + stoll(index.name) + 1;
                registerToMem(tabElMem);
                removeIdentifier(index.name);
            }
            else {
                memToRegister(assignTarget.mem);
                pushCommandOneArg("ADD", index.mem);
                registerToMem(2);
                pushCommand("GET B");
                pushCommandOneArg("STOREI", 2);
            }
        }
        else if(assignTarget.local == 0) {
            pushCommand("GET B");
            registerToMem(assignTarget.mem);
        }
        else {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Próba modyfikacji iteratora pętli." << endl;
            exit(1);
        }
        identifierStack.at(assignTarget.name).initialized = 1;
        assignFlag = 1;
    }
|   WRITE {
        assignFlag = 0;
        writeFlag = 1;
    } value SEM {
        Identifier ide = identifierStack.at(expressionArguments[0]);

        if(ide.type == "NUM") {
            setRegister(ide.name);
            removeIdentifier(ide.name);
        }
        else if (ide.type == "IDE") {
            memToRegister(ide.mem);
        }
        else {
            Identifier index = identifierStack.at(argumentsTabIndex[0]);
            if(index.type == "NUM") {
                long long int tabElMem = ide.mem + stoll(index.name) + 1;
                memToRegister(tabElMem);
                removeIdentifier(index.name);
            }
            else {
                memToRegister2(ide.mem);
                vector<string> opcodes;
                long long int startsFrom = index.mem;
                long long  int endsAt = 0;
                long long   int current = startsFrom;
                long long  int cost = 0;
                pushCommand("SUB A A");
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                            current--;
                            cost++;
                            opcodes.push_back("INC A");
                        }
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD A A");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
	                pushCommand(opcodes.at(i));
                }
                pushCommand("LOAD A");
                pushCommand("ADD A C");
                pushCommand("LOAD B");     
            }
        }
        pushCommand("PUT B");
        assignFlag = 1;
        writeFlag = 0;
        expressionArguments[0] = "-1";
        argumentsTabIndex[0] = "-1";
    }
;



ifbody:
    ELSE {
        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
        pushCommand("JUMP");
        long long int jumpCount = jumpStack.size()-2;
        Jump jump = jumpStack.at(jumpCount);
        addInt(jump.placeInStack, codeStack.size());

        jumpCount--;
        if(jumpCount >= 0 && jumpStack.at(jumpCount).depth == depth) {
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
        }
        /*registerValue = -1;*/
        assignFlag = 1;
    } commands ENDIF {
        addInt(jumpStack.at(jumpStack.size()-1).placeInStack, codeStack.size());
        jumpStack.pop_back();
        jumpStack.pop_back();
        if(jumpStack.size() >= 1 && jumpStack.at(jumpStack.size()-1).depth == depth) {
            jumpStack.pop_back();
        }
        depth--;
        assignFlag = 1;
    }
|   ENDIF {
        long long int jumpCount = jumpStack.size()-1;
        addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
        jumpCount--;
        if(jumpCount >= 0 && jumpStack.at(jumpCount).depth == depth) {
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
            jumpStack.pop_back();
        }
        jumpStack.pop_back();
        /*registerValue = -1;*/
        depth--;
        assignFlag = 1;
    }
;

forbody:
    DOWNTO value DO {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUM") {
            setRegister(a.name);
            /*removeIdentifier(a.name);*/
        }
        else if(a.type == "IDE") {
            memToRegister(a.mem);
        }
        else {
            Identifier index = identifierStack.at(argumentsTabIndex[0]);
            if(index.type == "NUM") {
                long long int tabElMem = a.mem + stoll(index.name) + 1;
                memToRegister(tabElMem);
                removeIdentifier(index.name);
            }
            else {
                memToRegister(a.mem);
                memToRegister2(index.mem);
                pushCommand("ADD B C");
                pushCommand("COPY A B ");
                pushCommand(" LOAD B ");
            }
        }
        registerToMem(assignTarget.mem);
        identifierStack.at(assignTarget.name).initialized = 1;
        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";

        Identifier s;
        string name = "C" + to_string(depth);
        createIdentifier(&s, name, 1, 0, "IDE");
        insertIdentifier(name, s);
        registerToMem(identifierStack.at(name).mem);
        forStack.push_back(identifierStack.at(assignTarget.name));

        if(b.type == "NUM") {
            setRegister2(b.name);
            forStack.push_back(identifierStack.at(b.name));
        }
        else if(b.type == "IDE") {
            memToRegister2(b.mem);
            forStack.push_back(identifierStack.at(b.name));
        }
        else {
            Identifier index = identifierStack.at(argumentsTabIndex[1]);
            forStack.push_back(identifierStack.at(b.name));
            if(index.type == "NUM") {
                forStack.push_back(identifierStack.at(index.name));
                long long int tabElMem = b.mem + stoll(index.name) + 1;
                memToRegister2(tabElMem);
                forStack.push_back(identifierStack.at(index.name));
                forStack.push_back(identifierStack.at(b.name));
                removeIdentifier(index.name);
            }
            else {
                memToRegister2(b.mem);
                pushCommand("COPY H C ");
                memToRegister2(index.mem);
                pushCommand("ADD H C");
                pushCommand("COPY A H ");
                pushCommand(" LOAD C ");
                forStack.push_back(identifierStack.at(index.name));
                forStack.push_back(identifierStack.at(index.name));
                forStack.push_back(identifierStack.at(b.name));
            }
        }
        pushCommand("COPY E C");
        pushCommand("SUB B E");
        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
        pushCommand("JZERO B");
        assignFlag = 1;
    } commands ENDFOR {
        Identifier iterator2 = forStack.at(forStack.size()-1);

        if(iterator2.type=="IDE"){
            Identifier iterator = forStack.at(forStack.size()-2);
            memToRegister(iterator.mem);
            pushCommand("DEC B");
            registerToMem(iterator.mem);
            memToRegister2(iterator2.mem);


            long long int jumpCount = jumpStack.size()-1;
            long long int stack = jumpStack.at(jumpCount).placeInStack-1;
            pushCommandOneArg("JUMP", stack-1);
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
            jumpStack.pop_back();

            string name = "C" + to_string(depth);
            removeIdentifier(name);
            removeIdentifier(iterator.name);

            forStack.pop_back();
            forStack.pop_back();
        }
        else if(iterator2.type=="NUM"){
            Identifier iterator = forStack.at(forStack.size()-2);
            memToRegister(iterator.mem);
            pushCommand("DEC B");
            registerToMem(iterator.mem);
            pushCommand("SUB C C");           
            vector<string> opcodes;
            long long int startsFrom = stoll(iterator2.name);
            long long  int endsAt = 0;
            long long   int current = startsFrom;
            long long  int cost = 0;
            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC C");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD C C");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC C");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
	            pushCommand(opcodes.at(i));
            }
            long long int jumpCount = jumpStack.size()-1;
            long long int stack = jumpStack.at(jumpCount).placeInStack-1;
            pushCommandOneArg("JUMP", stack-1);
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
            jumpStack.pop_back();
            string name = "C" + to_string(depth);
            removeIdentifier(name);
            removeIdentifier(iterator.name);
            forStack.pop_back();
            forStack.pop_back();
        }
        else if(iterator2.type=="ARR"){
            Identifier iteratorindex2 = forStack.at(forStack.size()-5);
            Identifier iteratorindex = forStack.at(forStack.size()-2);

            if(iteratorindex.type=="NUM"){
            memToRegister2(iterator2.mem);
            pushCommand("SUB H H");           
            vector<string> opcodes;
            long long int startsFrom = stoll(iteratorindex.name);
            long long  int endsAt = 0;
            long long   int current = startsFrom;
            long long  int cost = 0;
            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC H");
                    }
                    else
                    {
                         current /= 2;
                         cost += 5;
                         opcodes.push_back("ADD H H");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC H");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
	            pushCommand(opcodes.at(i));
            }

            pushCommand("ADD C H");
            pushCommand("COPY A C");
            pushCommand("LOAD C");
            memToRegister(iteratorindex2.mem);
            pushCommand("DEC B");
            registerToMem(iteratorindex2.mem);
            long long int jumpCount = jumpStack.size()-1;
            long long int stack = jumpStack.at(jumpCount).placeInStack-1;
            pushCommandOneArg("JUMP", stack-1);
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
            jumpStack.pop_back();

            string name = "C" + to_string(depth);
            removeIdentifier(name);
            forStack.pop_back();
            forStack.pop_back();
        } 
        else if(iteratorindex.type=="IDE"){
            memToRegister(iterator2.mem);
            memToRegister2(iteratorindex.mem);    
            pushCommand("ADD B C");
            pushCommand("COPY A B");
            pushCommand("LOAD C");
            memToRegister(iteratorindex2.mem);
            pushCommand("DEC B");
            registerToMem(iteratorindex2.mem);
            long long int jumpCount = jumpStack.size()-1;
            long long int stack = jumpStack.at(jumpCount).placeInStack-1;
            pushCommandOneArg("JUMP", stack-1);
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
            jumpStack.pop_back();

            string name = "C" + to_string(depth);
            removeIdentifier(name);
            forStack.pop_back();
            forStack.pop_back();
        }
    }
    depth--;
    assignFlag = 1;

}
|   TO value DO {

        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUM") {
            setRegister(a.name);
            /*removeIdentifier(a.name);*/
        }
        else if(a.type == "IDE") {
            memToRegister(a.mem);
        }
        else {
            Identifier index = identifierStack.at(argumentsTabIndex[0]);
            if(index.type == "NUM") {
                long long int tabElMem = a.mem + stoll(index.name) + 1;
                memToRegister(tabElMem);
                removeIdentifier(index.name);
            }
            else {
                memToRegister(a.mem);
                memToRegister2(index.mem);
                pushCommand("ADD B C");
                pushCommand("COPY A B ");
                pushCommand(" LOAD B ");
            }
        }
        registerToMem(assignTarget.mem);
        identifierStack.at(assignTarget.name).initialized = 1;
 
       
        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";

        Identifier s;
        string name = "C" + to_string(depth);
        createIdentifier(&s, name, 1, 0, "IDE");
        insertIdentifier(name, s);

        forStack.push_back(identifierStack.at(assignTarget.name));

        if(b.type == "NUM") {
            setRegister2(b.name);
            forStack.push_back(identifierStack.at(b.name));
        }
        else if(b.type == "IDE") {
            memToRegister2(b.mem);
            forStack.push_back(identifierStack.at(b.name));
        }
        else {
            Identifier index = identifierStack.at(argumentsTabIndex[1]);
            forStack.push_back(identifierStack.at(b.name));
            if(index.type == "NUM") {
                forStack.push_back(identifierStack.at(index.name));

                long long int tabElMem = b.mem + stoll(index.name) + 1;
                memToRegister2(tabElMem);
                forStack.push_back(identifierStack.at(index.name));
                forStack.push_back(identifierStack.at(b.name));

                removeIdentifier(index.name);
            }
            else {
                memToRegister2(b.mem);
                pushCommand("COPY H C ");
                memToRegister2(index.mem);
                pushCommand("ADD C H ");
                pushCommand("COPY A C ");
                pushCommand(" LOAD C ");
                forStack.push_back(identifierStack.at(index.name));
                forStack.push_back(identifierStack.at(index.name));
                forStack.push_back(identifierStack.at(b.name));
            }
        }

        pushCommand("COPY E C");
        pushCommand("SUB E B");
        Jump j;
        
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
        pushCommand("JZERO E");
        assignFlag = 1;

    } 
    commands ENDFOR 
    {
        Identifier iterator2 = forStack.at(forStack.size()-1);

        if(iterator2.type=="IDE")
        {
        Identifier iterator = forStack.at(forStack.size()-2);

        memToRegister(iterator.mem);
        pushCommand("INC B");
        registerToMem(iterator.mem);
        memToRegister2(iterator2.mem);
        long long int jumpCount = jumpStack.size()-1;
        long long int stack = jumpStack.at(jumpCount).placeInStack-1;
        pushCommandOneArg("JUMP", stack-1);
        addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
        jumpStack.pop_back();

        string name = "C" + to_string(depth);
        removeIdentifier(name);
        removeIdentifier(iterator.name);
        forStack.pop_back();
        forStack.pop_back();
    }
    else if(iterator2.type=="NUM")
    {
        Identifier iterator = forStack.at(forStack.size()-2);
        memToRegister(iterator.mem);
        pushCommand("INC B");
        registerToMem(iterator.mem);
        pushCommand("SUB C C");           
        vector<string> opcodes;
        long long int startsFrom = stoll(iterator2.name);
        long long  int endsAt = 0;
        long long   int current = startsFrom;
        long long  int cost = 0;
        while (current > endsAt)
        {
            if (current % 2 == 0 &&
                current * 2 >= endsAt)
            {
                if (current - current / 2 < 5)
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC C");
                }
                else
                {
                    current /= 2;
                    cost += 5;
                    opcodes.push_back("ADD C C");
                }
            }
            else
            {
                current--;
                cost++;
                opcodes.push_back("INC C");
            }
        }
        std::reverse(opcodes.begin(),opcodes.end());
        for (long long int i=0; i<opcodes.size();i++)
        {
	        pushCommand(opcodes.at(i));
        }
        long long int jumpCount = jumpStack.size()-1;
        long long int stack = jumpStack.at(jumpCount).placeInStack-1;
        pushCommandOneArg("JUMP", stack-1);
        addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
        jumpStack.pop_back();

        string name = "C" + to_string(depth);
        removeIdentifier(name);
        removeIdentifier(iterator.name);
        forStack.pop_back();
        forStack.pop_back();
    }
    else if(iterator2.type=="ARR")
    {
        Identifier iteratorindex2 = forStack.at(forStack.size()-5);
        Identifier iteratorindex = forStack.at(forStack.size()-2);

        if(iteratorindex.type=="NUM"){

            memToRegister2(iterator2.mem);

            pushCommand("SUB H H");           
            vector<string> opcodes;
            long long int startsFrom = stoll(iteratorindex.name);
            long long  int endsAt = 0;
            long long   int current = startsFrom;
            long long  int cost = 0;
            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC H");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD H H");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC H");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
	            pushCommand(opcodes.at(i));
            }

            pushCommand("ADD C H");
            pushCommand("COPY A C");
            pushCommand("LOAD C");
            memToRegister(iteratorindex2.mem);
            pushCommand("INC B");
            registerToMem(iteratorindex2.mem);


            long long int jumpCount = jumpStack.size()-1;
            long long int stack = jumpStack.at(jumpCount).placeInStack-1;
            pushCommandOneArg("JUMP", stack-1);
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
            jumpStack.pop_back();

            string name = "C" + to_string(depth);
            removeIdentifier(name);

            forStack.pop_back();
            forStack.pop_back();
        }
        else if(iteratorindex.type=="IDE")
        {
            memToRegister(iterator2.mem);

            memToRegister2(iteratorindex.mem);    

            pushCommand("ADD B C");
            pushCommand("COPY A B");
            pushCommand("LOAD C");
            memToRegister(iteratorindex2.mem);
            pushCommand("INC B");
            registerToMem(iteratorindex2.mem);


            long long int jumpCount = jumpStack.size()-1;
            long long int stack = jumpStack.at(jumpCount).placeInStack-1;
            pushCommandOneArg("JUMP", stack-1);
            addInt(jumpStack.at(jumpCount).placeInStack, codeStack.size());
            jumpStack.pop_back();

            string name = "C" + to_string(depth);
            removeIdentifier(name);
            forStack.pop_back();
            forStack.pop_back();
        }
    }

    depth--;
    assignFlag = 1;
}
;

expression:
    value {
        Identifier ide = identifierStack.at(expressionArguments[0]);
        if(ide.type == "NUM") {
            setRegister(ide.name);
            removeIdentifier(ide.name);
        }
        else if(ide.type == "IDE") {
            memToRegister(ide.mem);
        }
        else {
            Identifier index = identifierStack.at(argumentsTabIndex[0]);
            if(index.type == "NUM") {
                long long int tabElMem = ide.mem + stoll(index.name) + 1;
                memToRegister(tabElMem);
                removeIdentifier(index.name);
            }
            else {
                memToRegister(ide.mem);
                memToRegister2(index.mem);
                pushCommand("ADD B C"); 
                pushCommand("COPY A B"); 
                pushCommand("LOAD B"); 
            }
        }
      	if (!writeFlag) {
            expressionArguments[0] = "-1";
            argumentsTabIndex[0] = "-1";
        }
    }
|   value ADD value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);
        if(a.type != "ARR" && b.type != "ARR")
            add(a, b);
        else {
            Identifier aI, bI;
            if(identifierStack.count(argumentsTabIndex[0]) > 0)
                aI = identifierStack.at(argumentsTabIndex[0]);
            if(identifierStack.count(argumentsTabIndex[1]) > 0)
                bI = identifierStack.at(argumentsTabIndex[1]);
            addTab(a, b, aI, bI);
            argumentsTabIndex[0] = "-1";
            argumentsTabIndex[1] = "-1";
        }
        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
    }
|   value SUB value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);
        if(a.type != "ARR" && b.type != "ARR")
            sub(a, b, 0, 1);
        else {
            Identifier aI, bI;
            if(identifierStack.count(argumentsTabIndex[0]) > 0)
                aI = identifierStack.at(argumentsTabIndex[0]);
            if(identifierStack.count(argumentsTabIndex[1]) > 0)
                bI = identifierStack.at(argumentsTabIndex[1]);
            subTab(a, b, aI, bI, 0, 1);
            argumentsTabIndex[0] = "-1";
            argumentsTabIndex[1] = "-1";
        }
        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
    }
|   value MUL value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);
        Identifier aI, bI;
        if(identifierStack.count(argumentsTabIndex[0]) > 0)
            aI = identifierStack.at(argumentsTabIndex[0]);
        if(identifierStack.count(argumentsTabIndex[1]) > 0)
            bI = identifierStack.at(argumentsTabIndex[1]);

        //TODO czy liczba razy liczba się zmieści w long long int?
    
        else if(a.type == "NUM" && b.type == "NUM") {
            long long int val = stoll(a.name) * stoll(b.name);
            pushCommand("SUB B B");           
            vector<string> opcodes;
            long long int startsFrom = val;
            long long  int endsAt = 0;
            long long   int current = startsFrom;
            long long  int cost = 0;
            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
	            pushCommand(opcodes.at(i));
            }
        }
        if(a.name == "2") {
            if(b.type == "IDE")
                memToRegister(b.mem);
            else if(b.type == "ARR" && bI.type == "NUM") {
                long long int addr = b.mem + stoll(bI.name) + 1;
                memToRegister(addr);
                removeIdentifier(bI.name);
            }else if(b.type == "ARR" && bI.type == "IDE") {
                memToRegister(b.mem);
                memToRegister2(bI.mem);
                pushCommand("ADD B C");
                pushCommand("COPY A B");
                pushCommand("LOAD B");
            }
          
            pushCommand("ADD B B");
            removeIdentifier(a.name);
        }
        else if(b.name == "2") {
            if(a.type == "IDE")
                memToRegister(a.mem);
            else if(a.type == "ARR" && aI.type == "NUM") {
                long long int addr = a.mem + stoll(aI.name) + 1;
                memToRegister(addr);
                removeIdentifier(aI.name);
            }
           else if(a.type == "ARR" && aI.type == "IDE") {
                memToRegister(a.mem);
                memToRegister2(aI.mem);
                pushCommand("ADD B C");
                pushCommand("COPY A B");
                pushCommand("LOAD B");
            }
            pushCommand("ADD B B");
            removeIdentifier(b.name);
        }
        else if(a.type == "IDE" && b.type == "IDE") {
            pushCommand("SUB B B");
            memToRegister2(a.mem);
            pushCommand("COPY D C");
            memToRegister2(b.mem);
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO D ",codeStack.size()+4);
            pushCommand("DEC D");
            pushCommand("ADD B C");
            pushCommandOneArg("JUMP ",jumpVal);
        }
        else if(a.type == "NUM" && b.type == "IDE") {
            pushCommand("SUB B B");
            memToRegister2(b.mem);
            for ( int i=0; i < stoll(a.name) ; i++)
            {
                pushCommand("ADD B C");
                
            }
        }
        else if(a.type == "ARR" && b.type == "NUM") {
            if(aI.type == "NUM"){
                long long int addr = a.mem + stoll(aI.name) + 1;
                memToRegister(addr);
                pushCommand("SUB C C");
                for ( int i=0; i < stoll(b.name) ; i++)
                {
                    pushCommand("ADD C B");
                }
            }
            else if(aI.type == "IDE"){
                memToRegister(a.mem);
                memToRegister2(aI.mem);
                pushCommand("ADD B C");
                pushCommand("COPY A B");
                pushCommand("LOAD B");
                pushCommand("SUB C C");
                for ( int i=0; i < stoll(b.name) ; i++)
                {
                    pushCommand("ADD C B");
                }
            }
            pushCommand("COPY B C");
        }
        else if(a.type == "NUM" && b.type == "ARR") {
            if(aI.type == "NUM"){
                long long int addr = b.mem + stoll(aI.name) + 1;
                memToRegister(addr);
                pushCommand("SUB C C");
                for ( int i=0; i < stoll(b.name) ; i++)
                {
                    pushCommand("ADD C B");
                }
            }else if(aI.type == "IDE"){
                memToRegister(b.mem);
                memToRegister2(bI.mem);
                pushCommand("ADD B C");
                pushCommand("COPY A B");
                pushCommand("LOAD B");
                pushCommand("SUB C C");
                for ( int i=0; i < stoll(a.name) ; i++)
                {
                    pushCommand("ADD C B");
                }
            }
            pushCommand("COPY B C");
        }
        else if(a.type == "ARR" && b.type == "ARR") {
            if(aI.type == "NUM" && bI.type == "NUM"){
                long long int addr = b.mem + stoll(bI.name) + 1;
                memToRegister(addr);
                pushCommand("COPY D B");
                addr = a.mem + stoll(aI.name) + 1;
                memToRegister2(addr);       
                pushCommand("SUB B B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO D ",codeStack.size()+4);
                pushCommand("DEC D");
                pushCommand("ADD B C");
                pushCommandOneArg("JUMP ",jumpVal);
            }
            else if(aI.type == "IDE" && bI.type == "NUM"){
                long long int addr = b.mem + stoll(bI.name) + 1;
                memToRegister(addr);
                pushCommand("COPY D B");
                memToRegister(a.mem);
                memToRegister2(aI.mem);
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD C");

                pushCommand("SUB B B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO D ",codeStack.size()+4);
                pushCommand("DEC D");
                pushCommand("ADD B C");
                pushCommandOneArg("JUMP ",jumpVal);
            }else if(aI.type == "NUM" && bI.type == "IDE"){
                long long int addr = a.mem + stoll(aI.name) + 1;
               
                memToRegister(b.mem);
                memToRegister2(bI.mem);
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD D");
                memToRegister(addr);
                pushCommand("COPY C B");
                pushCommand("SUB B B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO D ",codeStack.size()+4);
                pushCommand("DEC D");
                pushCommand("ADD B C");
                pushCommandOneArg("JUMP ",jumpVal);
            }else if(aI.type == "IDE" && bI.type == "IDE"){
                memToRegister(b.mem);
                memToRegister2(bI.mem);
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD D");
                memToRegister(a.mem);
                memToRegister2(aI.mem);
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD C");
                pushCommand("SUB B B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO D ",codeStack.size()+4);
                pushCommand("DEC D");
                pushCommand("ADD B C");
                pushCommandOneArg("JUMP ",jumpVal);
            }           
        }
        else if(a.type == "ARR" && b.type == "IDE") {
            if(aI.type == "NUM" ){
                memToRegister(b.mem);          
                pushCommand("COPY D B");
                long long int addr = a.mem + stoll(aI.name) + 1;
                memToRegister2(addr);    
                pushCommand("SUB B B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO D ",codeStack.size()+4);
                pushCommand("DEC D");
                pushCommand("ADD B C");
                pushCommandOneArg("JUMP ",jumpVal);
            }
            else if(aI.type == "IDE" ){
                memToRegister(b.mem);          
                pushCommand("COPY D B");
                memToRegister(a.mem);
                memToRegister2(aI.mem);
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD C");  
                pushCommand("SUB B B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO D ",codeStack.size()+4);
                pushCommand("DEC D");
                pushCommand("ADD B C");
                pushCommandOneArg("JUMP ",jumpVal);
            }   
        }
        else if(a.type == "IDE" && b.type == "ARR") {  
            if(bI.type == "NUM" ){ 
                memToRegister(a.mem);   
                pushCommand("COPY D B");
                long long int addr = b.mem + stoll(bI.name) + 1;
                memToRegister2(addr);
                pushCommand("SUB B B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO D ",codeStack.size()+4);
                pushCommand("DEC D");
                pushCommand("ADD B C");
                pushCommandOneArg("JUMP ",jumpVal);
            }
            else if(bI.type == "IDE" ){ 
                memToRegister(a.mem);          
                pushCommand("COPY D B");
                memToRegister(b.mem);
                memToRegister2(bI.mem);
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD C");  
                pushCommand("SUB B B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO D ",codeStack.size()+4);
                pushCommand("DEC D");
                pushCommand("ADD B C");
                pushCommandOneArg("JUMP ",jumpVal);
            }
        }
        else if(a.type == "IDE" && b.type == "NUM") {
            pushCommand("SUB B B");
            memToRegister2(a.mem);
            for ( int i=0; i < stoll(b.name) ; i++)
            {
                pushCommand("ADD B C");   
            }
        }
        argumentsTabIndex[0] = "-1";
        argumentsTabIndex[1] = "-1";
        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
    }
|   value DIV value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);
        Identifier aI, bI;
        if(identifierStack.count(argumentsTabIndex[0]) > 0)
            aI = identifierStack.at(argumentsTabIndex[0]);
        if(identifierStack.count(argumentsTabIndex[1]) > 0)
            bI = identifierStack.at(argumentsTabIndex[1]);

        if(b.type == "NUM" && stoll(b.name) == 0) {
            pushCommand("SUB B B");
        }
        else if(a.type == "NUM" && stoll(a.name) == 0) {
            pushCommand("SUB B B");
        }
        
        else if(a.type == "NUM" && b.type == "NUM") {
            long long int val = stoll(a.name) / stoll(b.name);
            pushCommand("SUB B B");
            vector<string> opcodes;
            long long int startsFrom = val;
            long long  int endsAt = 0;
            long long   int current = startsFrom;
            long long  int cost = 0;
            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
                pushCommand(opcodes.at(i));
            }
        }
        else if(b.name == "2") {
            if(a.type == "IDE")
            {            
                memToRegister(a.mem);
                pushCommand("HALF B");
            }            
            else if(a.type == "ARR" && aI.type == "NUM") {
                long long int addr = a.mem + stoll(aI.name) + 1;
                memToRegister(addr);
                pushCommand("HALF B");
                removeIdentifier(aI.name);
            }
            else if(a.type == "ARR" && aI.type == "IDE") {
                memToRegister(a.mem);
                memToRegister2(aI.mem);
                pushCommand("ADD B C");
                pushCommand("COPY A B");
                pushCommand("LOAD B");
                pushCommand("HALF B");
            }
            
            removeIdentifier(b.name);
        }
        else if(a.type == "NUM" && b.type == "IDE"){
            pushCommand("SUB B B");      
            pushCommand("SUB D D");  
            vector<string> opcodes;
            long long int startsFrom = stoll(a.name);
            long long int endsAt = 0;
            long long int current = startsFrom;
            long long int cost = 0;

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
	            pushCommand(opcodes.at(i));
            }
            memToRegister2(b.mem);              
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B C");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D");
        }
        else if(a.type == "NUM" && b.type == "ARR"){
            if(bI.type == "NUM"){
                pushCommand("SUB B B");      
                pushCommand("SUB D D");  
                vector<string> opcodes;
                long long int startsFrom =stoll( a.name);
                long long  int endsAt = 0;
                long long   int current = startsFrom;
                long long  int cost = 0;
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                            current--;
                            cost++;
                            opcodes.push_back("INC B");
                        }
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD B B");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
	                pushCommand(opcodes.at(i));
                }
                long long int addr = b.mem + stoll(bI.name) + 1;
                memToRegister2(addr);
                pushCommandOneArg("JZERO C ",codeStack.size()+7); 
                pushCommand("INC B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO B ",codeStack.size()+4);
                pushCommand("SUB B C");
                pushCommand("INC D");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("COPY B D");
            }
            else if(bI.type == "IDE"){
                long long int addr = b.mem;
                memToRegister2(addr);
                memToRegister(bI.mem);
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD C");
                pushCommand("SUB B B");      
                pushCommand("SUB D D");  
                vector<string> opcodes;
                long long int startsFrom =stoll( a.name);
                long long  int endsAt = 0;
                long long   int current = startsFrom;
                long long  int cost = 0;
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                            current--;
                            cost++;
                            opcodes.push_back("INC B");
                        }
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD B B");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
	                pushCommand(opcodes.at(i));
                }
                
                pushCommandOneArg("JZERO C ",codeStack.size()+7); 
                pushCommand("INC B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO B ",codeStack.size()+4);
                pushCommand("SUB B C");
                pushCommand("INC D");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("COPY B D");
            }
        }
        else if(a.type == "ARR" && b.type == "NUM"){
            if(aI.type == "NUM"){
                pushCommand("SUB B B");      
                pushCommand("SUB D D");  
                vector<string> opcodes;
                long long int startsFrom = stoll(b.name);
                long long  int endsAt = 0;
                long long   int current = startsFrom;
                long long  int cost = 0;
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                            current--;
                            cost++;
                        opcodes.push_back("INC B");
                        }   
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD B B");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
	                pushCommand(opcodes.at(i));
                }
                long long int addr = a.mem + stoll(aI.name) + 1;
                memToRegister2(addr);                
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+4);
                pushCommand("SUB C B");
                pushCommand("INC D");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("COPY B D");
        }
        else if(aI.type == "IDE"){
                long long int addr = a.mem;
                memToRegister2(addr);
                memToRegister(aI.mem);
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD C");
                pushCommand("SUB B B");      
                pushCommand("SUB D D");  
                vector<string> opcodes;
                long long int startsFrom = stoll(b.name);
                long long  int endsAt = 0;
                long long   int current = startsFrom;
                long long  int cost = 0;
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                            current--;
                            cost++;
                        opcodes.push_back("INC B");
                        }   
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD B B");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
	                pushCommand(opcodes.at(i));
                }
                               
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+4);
                pushCommand("SUB C B");
                pushCommand("INC D");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("COPY B D");
        }
    }
    else if(a.type == "IDE" && b.type == "NUM"){
        pushCommand("SUB B B");      
        pushCommand("SUB D D");  
        vector<string> opcodes;
        long long int startsFrom = stoll(b.name);
        long long  int endsAt = 0;
        long long   int current = startsFrom;
        long long  int cost = 0;
        while (current > endsAt)
        {
            if (current % 2 == 0 &&
                current * 2 >= endsAt)
            {
                if (current - current / 2 < 5)
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
                else
                {
                    current /= 2;
                    cost += 5;
                    opcodes.push_back("ADD B B");
                }
            }
            else
            {
                current--;
                cost++;
                opcodes.push_back("INC B");
            }
        }
        std::reverse(opcodes.begin(),opcodes.end());
        for (long long int i=0; i<opcodes.size();i++)
        {
	        pushCommand(opcodes.at(i));
        }
        memToRegister2(a.mem);                  
        pushCommand("INC C");
        long long int jumpVal = codeStack.size();
        pushCommandOneArg("JZERO C ",codeStack.size()+4);
        pushCommand("SUB C B");
        pushCommand("INC D");
        pushCommandOneArg("JUMP ",jumpVal);
        pushCommand("DEC D");
        pushCommand("COPY B D");              
    }
    else if(a.type == "IDE" && b.type == "IDE"){
        pushCommand("SUB D D");  
        memToRegister(a.mem);
        memToRegister2(b.mem);
        pushCommandOneArg("JZERO C ",codeStack.size()+7);    
        pushCommand("INC B");
        long long int jumpVal = codeStack.size();
        pushCommandOneArg("JZERO B ",codeStack.size()+4);
        pushCommand("SUB B C");
        pushCommand("INC D");
        pushCommandOneArg("JUMP ",jumpVal);
        pushCommand("DEC D");
        pushCommand("COPY B D");
    }
    else if(a.type == "IDE" && b.type == "ARR"){
        if(bI.type == "NUM"){
            pushCommand("SUB D D");  
            memToRegister(a.mem);
            long long int addr = b.mem + stoll(bI.name) + 1;
            memToRegister2(addr);
            pushCommandOneArg("JZERO C ",codeStack.size()+7);     
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B C");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D"); 
        }else if(bI.type == "IDE"){
            pushCommand("SUB D D");  
            memToRegister2(b.mem);
            memToRegister(bI.mem);
            pushCommand("ADD B C");
            pushCommand("COPY A B");
            pushCommand("LOAD C");
            memToRegister(a.mem);
            pushCommandOneArg("JZERO C ",codeStack.size()+7);     
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B C");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D"); 
        }
    }
    else if(a.type == "ARR" && b.type == "IDE"){
        if(aI.type == "NUM"){
            pushCommand("SUB D D");  
            memToRegister2(b.mem);
            long long int addr = a.mem + stoll(aI.name) + 1;
            memToRegister(addr);
            pushCommandOneArg("JZERO C ",codeStack.size()+7);   
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B C");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D");
        } 
        else if(aI.type == "IDE"){ 
            pushCommand("SUB D D"); 
            memToRegister2(a.mem);
            memToRegister(aI.mem);
            pushCommand("ADD B C");
            pushCommand("COPY A B");
            pushCommand("LOAD B"); 
            memToRegister2(b.mem);
           
            pushCommandOneArg("JZERO C ",codeStack.size()+7);   
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B C");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D");
        }
    }
    else if(a.type == "ARR" && b.type == "ARR"){
        if(aI.type == "NUM" && bI.type == "NUM"){ 
            pushCommand("SUB D D");  
            long long int addr = b.mem + stoll(bI.name) + 1;
            memToRegister2(addr);
            addr = a.mem + stoll(aI.name) + 1;
            memToRegister(addr);
            pushCommandOneArg("JZERO C ",codeStack.size()+7);        
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B C");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D");  
        }  
        else if(aI.type == "IDE" && bI.type == "NUM"){ 
            pushCommand("SUB D D");  
            memToRegister(a.mem);
            memToRegister2(aI.mem);
            pushCommand("ADD B C");
            pushCommand("COPY A B");
            pushCommand("LOAD B");
            long long int addr = b.mem + stoll(bI.name) + 1;
            memToRegister2(addr);
            
           
            pushCommandOneArg("JZERO C ",codeStack.size()+7);        
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B C");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D");  
        }
        else if(aI.type == "NUM" && bI.type == "IDE"){ 
            pushCommand("SUB D D");  
            memToRegister(b.mem);
            memToRegister2(bI.mem);
            pushCommand("ADD B C");
            pushCommand("COPY A B");
            pushCommand("LOAD C");
            long long int  addr = a.mem + stoll(aI.name) + 1;
            memToRegister(addr);
            pushCommandOneArg("JZERO C ",codeStack.size()+7);        
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B C");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D");  
        } 
        else if(aI.type == "IDE" && bI.type == "IDE"){
            pushCommand("SUB D D");  
            memToRegister(b.mem);
            memToRegister2(bI.mem);
            pushCommand("ADD B C");
            pushCommand("COPY A B");
            pushCommand("LOAD E");
            memToRegister(a.mem);
            memToRegister2(aI.mem);
            pushCommand("ADD B C");
            pushCommand("COPY A B");
            pushCommand("LOAD B");
            pushCommandOneArg("JZERO E ",codeStack.size()+7);        
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+4);
            pushCommand("SUB B E");
            pushCommand("INC D");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("COPY B D");  
        }
    }
    argumentsTabIndex[0] = "-1";
    argumentsTabIndex[1] = "-1";
    expressionArguments[0] = "-1";
    expressionArguments[1] = "-1";
    }
|   value MOD value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);
        Identifier aI, bI;
        if(identifierStack.count(argumentsTabIndex[0]) > 0)
            aI = identifierStack.at(argumentsTabIndex[0]);
        if(identifierStack.count(argumentsTabIndex[1]) > 0)
            bI = identifierStack.at(argumentsTabIndex[1]);

        if(b.type == "NUM" && (stoll(b.name) == 0 || stoll(b.name) == 1)) {
            pushCommand("SUB B B");
        }
        else if(a.type == "NUM" && stoll(a.name) == 0) {
            pushCommand("SUB B B");
        }
        else if(a.type == "NUM" && b.type == "NUM") {
            long long int val = stoll(a.name) % stoll(b.name);
            pushCommand("SUB B B");            
            vector<string> opcodes;
            long long int startsFrom = val;
            long long  int endsAt = 0;
            long long   int current = startsFrom;
            long long  int cost = 0;
            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
                pushCommand(opcodes.at(i));
            }
        }
        else if(b.name == "2") {
            if(a.type == "IDE")
            {
                pushCommand("SUB B B");
                memToRegister2(a.mem);
                pushCommandOneArg("JODD C", codeStack.size()+2); 
                pushCommandOneArg("JUMP ", codeStack.size()+2); 
                pushCommand("INC B");
            }            
            else if(a.type == "ARR" && aI.type == "NUM") {
                long long int addr = a.mem + stoll(aI.name) + 1;
                pushCommand("SUB B B");
                memToRegister2(addr);
                pushCommandOneArg("JODD C", codeStack.size()+2);
                pushCommandOneArg("JUMP ", codeStack.size()+2); 
                pushCommand("INC B");
                removeIdentifier(aI.name);
            }
            else if(a.type == "ARR" && aI.type == "IDE") {
                memToRegister(a.mem);
                memToRegister2(aI.mem);
                pushCommand("ADD B C");
                pushCommand("COPY A B");
                pushCommand("LOAD C");
                pushCommand("SUB B B");
                pushCommandOneArg("JODD C", codeStack.size()+2);
                pushCommandOneArg("JUMP ", codeStack.size()+2); 
                pushCommand("INC B");
            }
        }
        else if(a.type == "NUM" && b.type == "IDE"){
            pushCommand("SUB B B");      
            pushCommand("SUB D D");  
            vector<string> opcodes;
            long long int startsFrom = stoll(a.name);
            long long  int endsAt = 0;
            long long   int current = startsFrom;
            long long  int cost = 0;
            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
	            pushCommand(opcodes.at(i));
            }
            memToRegister2(b.mem);           
            pushCommand("INC B");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO B ",codeStack.size()+5);
            pushCommand("COPY D B");
            pushCommand("SUB B C");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("DEC D");
            pushCommand("COPY B D");         
        }
        else if(a.type == "IDE" && b.type == "NUM"){
            pushCommand("SUB B B");      
            pushCommand("SUB D D");  
            vector<string> opcodes;
            long long int startsFrom = stoll(b.name);
            long long  int endsAt = 0;
            long long   int current = startsFrom;
            long long  int cost = 0;
            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
	            pushCommand(opcodes.at(i));
            }
            memToRegister2(a.mem);
            pushCommand("INC C");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO C ",codeStack.size()+5);
            pushCommand("COPY D C");
            pushCommand("SUB C B");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("DEC D");
            pushCommand("COPY B D");
        }
        else if(a.type == "ARR" && b.type == "NUM"){
            if(aI.type == "NUM"){
                pushCommand("SUB B B");      
                pushCommand("SUB D D");  
                vector<string> opcodes;
                long long int startsFrom = stoll(b.name);
                long long  int endsAt = 0;
                long long   int current = startsFrom;
                long long  int cost = 0;
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                            current--;
                            cost++;
                            opcodes.push_back("INC B");
                        }
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD B B");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
                    pushCommand(opcodes.at(i));
                }
                long long int addr = a.mem + stoll(aI.name) + 1;
                memToRegister2(addr);             
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+5);
                pushCommand("COPY D C");
                pushCommand("SUB C B");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D");
            }
            if(aI.type == "IDE"){
                memToRegister(a.mem);
                memToRegister2(aI.mem); 
                pushCommand("ADD C B");
                pushCommand("COPY A C");
                pushCommand("LOAD C");  
                pushCommand("SUB B B");      
                pushCommand("SUB D D");  
                vector<string> opcodes;
                long long int startsFrom = stoll(b.name);
                long long  int endsAt = 0;
                long long   int current = startsFrom;
                long long  int cost = 0;
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                            current--;
                            cost++;
                            opcodes.push_back("INC B");
                        }
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD B B");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
                    pushCommand(opcodes.at(i));
                }
                
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+5);
                pushCommand("COPY D C");
                pushCommand("SUB C B");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D");
            }
        }
        else if(a.type == "NUM" && b.type == "ARR"){
            if(bI.type == "NUM"){
                pushCommand("SUB B B");      
                pushCommand("SUB D D");  
                vector<string> opcodes;
                long long int startsFrom = stoll(a.name);
                long long  int endsAt = 0;
                long long  int cost = 0;
                long long   int current = startsFrom;
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                           current--;
                           cost++;
                           opcodes.push_back("INC B");
                        }
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD B B");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
	                pushCommand(opcodes.at(i));
                }
                long long int addr = b.mem + stoll(bI.name) + 1;
                memToRegister2(addr);             
                pushCommand("INC B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO B ",codeStack.size()+5);
                pushCommand("COPY D B");
                pushCommand("SUB B C");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D");
            }  
            else if(bI.type == "IDE"){ 
                memToRegister2(b.mem); 
                memToRegister(bI.mem); 
                pushCommand("ADD B C");
                pushCommand("COPY A B");  
                pushCommand("LOAD C");   
                pushCommand("SUB B B");      
                pushCommand("SUB D D");  
                vector<string> opcodes;
                long long int startsFrom = stoll(a.name);
                long long  int endsAt = 0;
                long long  int cost = 0;
                long long   int current = startsFrom;
                while (current > endsAt)
                {
                    if (current % 2 == 0 &&
                        current * 2 >= endsAt)
                    {
                        if (current - current / 2 < 5)
                        {
                           current--;
                           cost++;
                           opcodes.push_back("INC B");
                        }
                        else
                        {
                            current /= 2;
                            cost += 5;
                            opcodes.push_back("ADD B B");
                        }
                    }
                    else
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                }
                std::reverse(opcodes.begin(),opcodes.end());
                for (long long int i=0; i<opcodes.size();i++)
                {
	                pushCommand(opcodes.at(i));
                }
               
            
                pushCommand("INC B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO B ",codeStack.size()+5);
                pushCommand("COPY D B");
                pushCommand("SUB B C");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D");   
            }   
        }
        else if(a.type == "IDE" && b.type == "ARR"){
            if(bI.type == "NUM"){ 
                long long int addr = b.mem + stoll(bI.name) + 1;
            memToRegister(addr);
            memToRegister2(a.mem);            
            pushCommand("INC C");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO C ",codeStack.size()+5);
            pushCommand("COPY D C");
            pushCommand("SUB C B");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("DEC D");
            pushCommand("COPY B D"); 
            } 
            else if(bI.type == "IDE"){  
               
                memToRegister2(b.mem); 
                memToRegister(bI.mem); 
                pushCommand("ADD B C");
                pushCommand("COPY A B"); 
                pushCommand("LOAD B"); 
                memToRegister2(a.mem);
                           
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+5);
                pushCommand("COPY D C");
                pushCommand("SUB C B");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D");
            }     
        }
            else if(a.type == "ARR" && b.type == "IDE"){
            if(aI.type == "NUM"){
                memToRegister(b.mem);
                long long int addr = a.mem + stoll(aI.name) + 1;
                memToRegister2(addr);           
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+5);
                pushCommand("COPY D C");
                pushCommand("SUB C B");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D"); 
            } 
            else if(aI.type == "IDE"){ 
                memToRegister2(a.mem); 
                memToRegister(aI.mem); 
                pushCommand("ADD B C");
                pushCommand("COPY A B"); 
                pushCommand("LOAD C");  
                memToRegister(b.mem);
                           
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+5);
                pushCommand("COPY D C");
                pushCommand("SUB C B");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D");  
            }        
        }
        else if(a.type == "IDE" && b.type == "IDE"){
            memToRegister(b.mem);
            memToRegister2(a.mem);
            pushCommand("SUB D D");
            pushCommandOneArg("JZERO B ",codeStack.size()+8);
            pushCommand("INC C");
            long long int jumpVal = codeStack.size();
            pushCommandOneArg("JZERO C ",codeStack.size()+5);
            pushCommand("COPY D C");
            pushCommand("SUB C B");
            pushCommandOneArg("JUMP ",jumpVal);
            pushCommand("DEC D");
            pushCommand("DEC D");
            pushCommand("COPY B D");             
        }
        else if(a.type == "ARR" && b.type == "ARR"){

            if(aI.type == "NUM" && bI.type == "NUM" ){ 
                long long int addr = b.mem + stoll(bI.name) + 1;
                memToRegister(addr);
                addr = a.mem + stoll(aI.name) + 1;
                memToRegister2(addr);           
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+5);
                pushCommand("COPY D C");
                pushCommand("SUB C B");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D"); 
            }         
            else if(aI.type == "IDE" && bI.type == "NUM" ){ 
                long long int addr = b.mem + stoll(bI.name) + 1;
                memToRegister2(a.mem); 
                memToRegister(aI.mem); 
                pushCommand("ADD B C");
                pushCommand("COPY A B"); 
                pushCommand("LOAD C"); 
                memToRegister(addr);        
                pushCommand("INC C");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO C ",codeStack.size()+5);
                pushCommand("COPY D C");
                pushCommand("SUB C B");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D"); 
            }
            else if(aI.type == "NUM" && bI.type == "IDE" ){ 
                long long int addr = a.mem + stoll(aI.name) + 1;
                memToRegister2(b.mem); 
                memToRegister(bI.mem); 
                pushCommand("ADD B C");
                pushCommand("COPY A B"); 
                pushCommand("LOAD C"); 
                memToRegister(addr);        
                pushCommand("INC B");
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO B ",codeStack.size()+5);
                pushCommand("COPY D B");
                pushCommand("SUB B C");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D"); 
            }
            else if(aI.type == "IDE" && bI.type == "IDE" ){ 
                 memToRegister2(a.mem); 
                memToRegister(aI.mem); 
                pushCommand("ADD B C");
                pushCommand("COPY A B"); 
                pushCommand("LOAD B");         
                pushCommand("INC B");
                memToRegister2(b.mem); 
                memToRegister(bI.mem); 
                pushCommand("ADD B C");
                pushCommand("COPY A B"); 
                pushCommand("LOAD C"); 
              
                long long int jumpVal = codeStack.size();
                pushCommandOneArg("JZERO B ",codeStack.size()+5);
                pushCommand("COPY D B");
                pushCommand("SUB B C");
                pushCommandOneArg("JUMP ",jumpVal);
                pushCommand("DEC D");
                pushCommand("DEC D");
                pushCommand("COPY B D"); 
            }
        }
        argumentsTabIndex[0] = "-1";
        argumentsTabIndex[1] = "-1";
        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
    }
;

condition:
    value EQ value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUM" && b.type == "NUM") {
            if(stoll(a.name) == stoll(b.name))
                setRegister("1");
            else
                setRegister("0");
            removeIdentifier(a.name);
            removeIdentifier(b.name);
            Jump jum;
            createJump(&jum, codeStack.size(), depth);
            jumpStack.push_back(jum);
            pushCommand("JZERO B");
        }
        else {
            Identifier aI, bI;
            if(identifierStack.count(argumentsTabIndex[0]) > 0)
                aI = identifierStack.at(argumentsTabIndex[0]);
            if(identifierStack.count(argumentsTabIndex[1]) > 0)
                bI = identifierStack.at(argumentsTabIndex[1]);

            if(a.type != "ARR" || b.type != "ARR")
                subTab(b, a, bI, aI, 0, 0);



            if(a.type != "ARR" && b.type != "ARR")
                sub(a, b, 0, 1);
            else
                subTab(a, b, aI, bI, 0, 1);

            pushCommandOneArg("JZERO B", codeStack.size()+2);
            Jump jj;
            createJump(&jj, codeStack.size(), depth);
            jumpStack.push_back(jj);
            pushCommand("JUMP");
        }

        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
        argumentsTabIndex[0] = "-1";
        argumentsTabIndex[1] = "-1";
    }
|   value NE value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUM" && b.type == "NUM") {
            if(stoll(a.name) != stoll(b.name))
                setRegister("1");
            else
                setRegister("0");
            removeIdentifier(a.name);
            removeIdentifier(b.name);
            Jump jum;
            createJump(&jum, codeStack.size(), depth);
            jumpStack.push_back(jum);
            pushCommand("JZERO B");
        }
        else {
            Identifier aI, bI;
            if(identifierStack.count(argumentsTabIndex[0]) > 0)
                aI = identifierStack.at(argumentsTabIndex[0]);
            if(identifierStack.count(argumentsTabIndex[1]) > 0)
                bI = identifierStack.at(argumentsTabIndex[1]);

            if(a.type != "ARR" && b.type != "ARR")
                sub(b, a, 0, 0);
            else
                subTab(b, a, bI, aI, 0, 0);

            pushCommandOneArg("JZERO B", codeStack.size()+2);
            Jump j;
            createJump(&j, codeStack.size(), depth);
            jumpStack.push_back(j);
            pushCommand("JUMP");

            if(a.type != "ARR" && b.type != "ARR")
                sub(a, b, 0, 1);
            else
                subTab(a, b, aI, bI, 0, 1);

            addInt(jumpStack.at(jumpStack.size()-1).placeInStack, codeStack.size()+1);
            jumpStack.pop_back();

            Jump jj;
            createJump(&jj, codeStack.size(), depth);
            jumpStack.push_back(jj);
            pushCommand("JZERO B");
        }

        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
        argumentsTabIndex[0] = "-1";
        argumentsTabIndex[1] = "-1";
    }
|   value LT value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUM" && b.type == "NUM") {
            if(stoll(a.name) < stoll(b.name))
                setRegister("1");
            else
                setRegister("0");
            removeIdentifier(a.name);
            removeIdentifier(b.name);
        }
        else {
            if(a.type != "ARR" && b.type != "ARR")
                sub(b, a, 0, 1);
            else {
                Identifier aI, bI;
                if(identifierStack.count(argumentsTabIndex[0]) > 0)
                    aI = identifierStack.at(argumentsTabIndex[0]);
                if(identifierStack.count(argumentsTabIndex[1]) > 0)
                    bI = identifierStack.at(argumentsTabIndex[1]);
                subTab(b, a, bI, aI, 0, 1);
                argumentsTabIndex[0] = "-1";
                argumentsTabIndex[1] = "-1";
            }
        }

        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
        pushCommand("JZERO B");

        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
    }
|   value GT value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUM" && b.type == "NUM") {
            if(stoll(b.name) < stoll(a.name))
                setRegister("1");
            else
                setRegister("0");
            removeIdentifier(a.name);
            removeIdentifier(b.name);
        }
        else {
            if(a.type != "ARR" && b.type != "ARR")
                sub(a, b, 0, 1);
            else {
                Identifier aI, bI;
                if(identifierStack.count(argumentsTabIndex[0]) > 0)
                    aI = identifierStack.at(argumentsTabIndex[0]);
                if(identifierStack.count(argumentsTabIndex[1]) > 0)
                    bI = identifierStack.at(argumentsTabIndex[1]);
                subTab(a, b, aI, bI, 0, 1);
                argumentsTabIndex[0] = "-1";
                argumentsTabIndex[1] = "-1";
            }
        }

        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);;
        pushCommand("JZERO B");

        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
    }
|   value LE value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUM" && b.type == "NUM") {
            if(stoll(a.name) <= stoll(b.name))
                setRegister("1");
            else
                setRegister("0");
            removeIdentifier(a.name);
            removeIdentifier(b.name);
        }
        else {
            if(a.type != "ARR" && b.type != "ARR")
                sub(b, a, 1, 1);
            else {
                Identifier aI, bI;
                if(identifierStack.count(argumentsTabIndex[0]) > 0)
                    aI = identifierStack.at(argumentsTabIndex[0]);
                if(identifierStack.count(argumentsTabIndex[1]) > 0)
                    bI = identifierStack.at(argumentsTabIndex[1]);
                subTab(b, a, bI, aI, 1, 1);
                argumentsTabIndex[0] = "-1";
                argumentsTabIndex[1] = "-1";
            }
        }

        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
        pushCommand("JZERO B");

        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
    }
|   value GE value {
        Identifier a = identifierStack.at(expressionArguments[0]);
        Identifier b = identifierStack.at(expressionArguments[1]);

        if(a.type == "NUM" && b.type == "NUM") {
            if(stoll(a.name) >= stoll(b.name))
                setRegister("1");
            else
                setRegister("0");
            removeIdentifier(a.name);
            removeIdentifier(b.name);
        }
        else {
            if(a.type != "ARR" && b.type != "ARR")
                sub(a, b, 1, 1);
            else {
                Identifier aI, bI;
                if(identifierStack.count(argumentsTabIndex[0]) > 0)
                    aI = identifierStack.at(argumentsTabIndex[0]);
                if(identifierStack.count(argumentsTabIndex[1]) > 0)
                    bI = identifierStack.at(argumentsTabIndex[1]);
                subTab(a, b, aI, bI, 1, 1);
                argumentsTabIndex[0] = "-1";
                argumentsTabIndex[1] = "-1";
            }
        }

        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
        pushCommand("JZERO B");

        expressionArguments[0] = "-1";
        expressionArguments[1] = "-1";
        argumentsTabIndex[0] = "-1";
        argumentsTabIndex[1] = "-1";
    }
;

value:
    NUM {
        if(assignFlag){
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Próba przypisania do stałej." << endl;
           	exit(1);
      	}
        Identifier s;
      	createIdentifier(&s, $1, 0, 0, "NUM");
        insertIdentifier($1, s);
      	if (expressionArguments[0] == "-1"){
      		expressionArguments[0] = $1;
      	}
      	else{
      		expressionArguments[1] = $1;
      	}
    }
|   identifier
;

identifier:
    IDE {
        if(identifierStack.find($1) == identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << $1 << " nie została zadeklarowana." << endl;
            exit(1);
        }
        if(identifierStack.at($1).tableSize == 0) {
            if(!assignFlag){
                if(identifierStack.at($1).initialized == 0) {
                    cout << "Błąd [okolice linii " << yylineno << \
                    "]: Próba użycia niezainicjalizowanej zmiennej " << $1 << "." << endl;
                    exit(1);
                }
                if (expressionArguments[0] == "-1"){
                    expressionArguments[0] = $1;
                }
                else{
                    expressionArguments[1] = $1;
                }

            }
            else {
                assignTarget = identifierStack.at($1);
            }
        }
        else {
          cout << "Błąd [okolice linii " << yylineno << \
          "]: Brak odwołania do elementu tablicy " << $1 << "." << endl;
          exit(1);
        }
    }
|   IDE LB IDE RB {
        if(identifierStack.find($1) == identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << $1 << " nie została zadeklarowana." << endl;
            exit(1);
        }
        if(identifierStack.find($3) == identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << $3 << " nie została zadeklarowana." << endl;
            exit(1);
        }

        if(identifierStack.at($1).tableSize == 0) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << $1 << " nie jest tablicą." << endl;
            exit(1);
        }
        else {
            if(identifierStack.at($3).initialized == 0) {
                cout << "Błąd [okolice linii " << yylineno << \
                "]: Próba użycia niezainicjalizowanej zmiennej " << $3 << "." << endl;
                exit(1);
            }

            if(!assignFlag){
                //TODO czy wywalać błąd niezainicjalizowanej
                //zmiennej dla elementu tablicy
                if (expressionArguments[0] == "-1"){
                    expressionArguments[0] = $1;
                    argumentsTabIndex[0] = $3;
                }
                else{
                    expressionArguments[1] = $1;
                    argumentsTabIndex[1] = $3;
                }

            }
            else {
                assignTarget = identifierStack.at($1);
                tabAssignTargetIndex = $3;
            }
        }
    }
|   IDE LB NUM RB {
        if(identifierStack.find($1) == identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << $1 << " nie została zadeklarowana." << endl;
            exit(1);
        }

        if(identifierStack.at($1).tableSize == 0) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << $1 << " nie jest tablicą." << endl;
            exit(1);
        }
        else {
            Identifier s;
            createIdentifier(&s, $3, 0, 0, "NUM");
            insertIdentifier($3, s);

            if(!assignFlag){
                //TODO czy wywalać błąd niezainicjalizowanej
                //zmiennej dla elementu tablicy
                if (expressionArguments[0] == "-1"){
                    expressionArguments[0] = $1;
                    argumentsTabIndex[0] = $3;
                }
                else{
                    expressionArguments[1] = $1;
                    argumentsTabIndex[1] = $3;
                }

            }
            else {
                assignTarget = identifierStack.at($1);
                tabAssignTargetIndex = $3;
            }
        }
    }
;

%%

void createIdentifier(Identifier *s, string name, long long int isLocal,
    long long int isArray, string type){
    s->name = name;
    s->mem = memCounter;
    s->type = type;
    s->initialized = 0;
    if(isLocal){
    	s->local = 1;
    }
    else{
    	s->local = 0;
    }
    if(isArray){
      s->tableSize = isArray;
    }
    else{
      s->tableSize = 0;
    }
}

void createJump(Jump *j, long long int stack, long long int depth) {
    j->placeInStack = stack;
    j->depth = depth;
}

long long int setToTempMem(Identifier a, Identifier aI, long long int tempMem, int isJZERO, int isRemoval) {
    long long int mem = 0;
    if(a.type == "NUM") {
        setRegister(a.name);
        if(isJZERO) {
            mem = codeStack.size();
            pushCommand("JZERO");
        }
        registerToMem(tempMem);
        if(isRemoval)
            removeIdentifier(a.name);
    }
    else if(a.type == "IDE") {
        memToRegister(a.mem);
        if(isJZERO) {
            mem = codeStack.size();
            pushCommand("JZERO"); //JZERO END
        }
        registerToMem(tempMem);
    }
    else if(a.type == "ARR" && aI.type == "NUM") {
        long long int addr = a.mem + stoll(aI.name) + 1;
        memToRegister(addr);
        if(isJZERO) {
            mem = codeStack.size();
            pushCommand("JZERO"); //JZERO END
        }
        registerToMem(tempMem);
        if(isRemoval)
            removeIdentifier(aI.name);
    }
    else if(a.type == "ARR" && aI.type == "IDE") {
        memToRegister(a.mem);
        pushCommandOneArg("ADD", aI.mem);
        registerToMem(tempMem);
        pushCommandOneArg("LOADI", tempMem);
        if(isJZERO) {
            mem = codeStack.size();
            pushCommand("JZERO"); //JZERO END
        }
        registerToMem(tempMem);
    }
    return mem;
}

void add(Identifier a, Identifier b) {

    if(a.type == "NUM" && b.type == "NUM") {
pushCommand("SUB B B");
        long long int val = stoll(a.name) + stoll(b.name);

                  vector<string> opcodes;
long long int startsFrom = val;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
    }
    else if(a.type == "NUM" && b.type == "IDE") {
        //trying to opt
pushCommand("SUB B B");
        if(stoll(a.name) < 8) {
            memToRegister(b.mem);
                     vector<string> opcodes;
long long int startsFrom = stoll(a.name);
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
            removeIdentifier(a.name);
        }
        else {
            setRegister(a.name);
            pushCommandOneArg("ADD", b.mem);
            removeIdentifier(a.name);
        }
    }
    else if(a.type == "IDE" && b.type == "NUM") {
        //trying to opt
pushCommand("SUB B B");
        if(stoll(b.name) < 8) {
            memToRegister(a.mem);
                     vector<string> opcodes;
long long int startsFrom =stoll( b.name);
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
            removeIdentifier(b.name);
        }
        else {
            setRegister(b.name);
            pushCommandOneArg("ADD", a.mem);
            removeIdentifier(b.name);
        }
    }
    else if(a.type == "IDE" && b.type == "IDE") {
        memToRegister(a.mem);
            memToRegister2(b.mem);
              pushCommand("ADD B C");
    }
}

void addTab(Identifier a, Identifier b, Identifier aIndex, Identifier bIndex) {
    if(a.type == "NUM" && b.type == "ARR") {
        if(bIndex.type == "NUM") {
            long long int addr = b.mem + stoll(bIndex.name) + 1;

            //trying to opt
            //if(stoll(a.name) < 8) {
                memToRegister(addr);
          vector<string> opcodes;
long long int startsFrom = stoll(a.name);
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
           // else {
           //     setRegister(a.name);
           //     pushCommandOneArg("ADD", addr);
           // }

            removeIdentifier(a.name);
            removeIdentifier(bIndex.name);
        }
        else if(bIndex.type == "IDE") {
            memToRegister(b.mem);
memToRegister2(bIndex.mem);
pushCommand("ADD B C");
pushCommand("COPY A B");
pushCommand("LOAD F");
//pushCommand("COPY F B");
vector<string> opcodes;
          long long int startsFrom = stoll(a.name);
          long long  int endsAt = 0;

          long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC F");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD F F");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC F");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
            	pushCommand(opcodes.at(i));
            }
pushCommand("COPY B F");
        }
    }
    else if(a.type == "ARR" && b.type == "NUM") {
        if(aIndex.type == "NUM") {
            long long int addr = a.mem + stoll(aIndex.name) + 1;
            //trying to opt
            
                memToRegister(addr);
                for(int i=0; i < stoll(b.name); i++) {
                    pushCommand("INC B");
                }
           
            removeIdentifier(b.name);
            removeIdentifier(aIndex.name);
        }
        else if(aIndex.type == "IDE") {
              memToRegister(a.mem);
memToRegister2(aIndex.mem);
pushCommand("ADD B C");
pushCommand("COPY A B");
pushCommand("LOAD F");
//pushCommand("COPY F B");
vector<string> opcodes;
          long long int startsFrom = stoll(b.name);
          long long  int endsAt = 0;

          long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC F");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD F F");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC F");
                }
            }
            std::reverse(opcodes.begin(),opcodes.end());
            for (long long int i=0; i<opcodes.size();i++)
            {
            	pushCommand(opcodes.at(i));
            }
pushCommand("COPY B F");
            removeIdentifier(b.name);
        }
    }
    else if(a.type == "IDE" && b.type == "ARR") {
        if(bIndex.type == "NUM") {
            long long int addr = b.mem + stoll(bIndex.name) + 1;
            memToRegister(a.mem);
           pushCommand("SUB A A");
                         vector<string> opcodes;
long long int startsFrom = addr;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD A A");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC A");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
                pushCommand("LOAD A");
                pushCommand("ADD B A");
            removeIdentifier(bIndex.name);
        }
        else if(bIndex.type == "IDE") {
            memToRegister(b.mem);
            pushCommandOneArg("ADD", bIndex.mem);
            registerToMem(1);
            memToRegister(a.mem);
            pushCommandOneArg("ADDI", 1);
        }
    }
    else if(a.type == "ARR" && b.type == "IDE") {
        if(aIndex.type == "NUM") {
            long long int addr = a.mem + stoll(aIndex.name) + 1;
            memToRegister(b.mem);
         pushCommand("SUB A A");
                          vector<string> opcodes;
long long int startsFrom = addr;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD A A");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC A");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
                pushCommand("LOAD A");
                pushCommand("ADD B A");
            removeIdentifier(aIndex.name);
        }
        else if(aIndex.type == "IDE") {
              memToRegister(a.mem);
memToRegister2(aIndex.mem);
pushCommand("ADD B C");
pushCommand("COPY A B");
pushCommand("LOAD F");
//pushCommand("COPY F B");
vector<string> opcodes;
         memToRegister2(b.mem);
pushCommand("ADD F C");
pushCommand("COPY B F");
        }
    }
    else if(a.type == "ARR" && b.type == "ARR") {
        if(aIndex.type == "NUM" && bIndex.type == "NUM") {
            long long int addrA = a.mem + stoll(aIndex.name) + 1;
            long long int addrB = b.mem + stoll(bIndex.name) + 1;
            if(a.name == b.name && addrA == addrB) {
                memToRegister(addrA);
                pushCommand("SUB A A");
                          vector<string> opcodes;
long long int startsFrom = addrA;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD A A");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC A");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
                pushCommand("LOAD B");
                pushCommand("ADD B B");
            }
            else {
                memToRegister(addrA);
                pushCommand("SUB A A");
                       vector<string> opcodes;
long long int startsFrom = addrB;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC C");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD C C");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC C");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
                pushCommand("LOAD A");
                pushCommand("ADD B A");
            }
            removeIdentifier(aIndex.name);
            removeIdentifier(bIndex.name);
        }
        else if(aIndex.type == "NUM" && bIndex.type == "IDE") {
memToRegister2(b.mem);
memToRegister(bIndex.mem);
pushCommand("ADD B C");
pushCommand("COPY A B");
pushCommand("LOAD F");
 long long int addrA = a.mem + stoll(aIndex.name) + 1;
     
                memToRegister2(addrA);
//pushCommand("COPY F B");

        // memToRegister2(b.mem);
pushCommand("ADD F C");
pushCommand("COPY B F");
            
            removeIdentifier(aIndex.name);
        }
        else if(aIndex.type == "IDE" && bIndex.type == "NUM") {
           memToRegister2(a.mem);
memToRegister(aIndex.mem);
pushCommand("ADD B C");
pushCommand("COPY A B");
pushCommand("LOAD F");
 long long int addrB = b.mem + stoll(bIndex.name) + 1;
     
                memToRegister2(addrB);
//pushCommand("COPY F B");

        // memToRegister2(b.mem);
pushCommand("ADD F C");
pushCommand("COPY B F");
            removeIdentifier(bIndex.name);
        }
        else if(aIndex.type == "IDE" && bIndex.type == "IDE") {
            if(a.name == b.name && aIndex.name == bIndex.name) {
  memToRegister2(a.mem);
               memToRegister(aIndex.mem);
pushCommand("ADD B C");
pushCommand("COPY A B");
pushCommand("LOAD F");
pushCommand("ADD F F");
pushCommand("COPY B F");
            }
            else {
                 memToRegister2(a.mem);
memToRegister(aIndex.mem);
pushCommand("ADD B C");
pushCommand("COPY A B");
pushCommand("LOAD F");

  memToRegister2(b.mem);
memToRegister(bIndex.mem);
pushCommand("ADD B C");
pushCommand("COPY A B");
pushCommand("LOAD G");
//pushCommand("COPY F B");

        // memToRegister2(b.mem);
pushCommand("ADD F G");
pushCommand("COPY B F");
            }
        }
    }
}

void sub(Identifier a, Identifier b, int isINC, int isRemoval) {
    if(a.type == "NUM" && b.type == "NUM") {
        long long int val = max(stoll(a.name) + isINC - stoll(b.name), (long long int) 0);
        setRegister(to_string(val));
        if(isRemoval) {
pushCommand("SUB B B");
                  vector<string> opcodes;
long long int startsFrom = val;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
            pushCommand("SUB C C");
            for(int i=0; i < stoll(b.name); i++) {
                pushCommand("INC C");
            }
 if(isINC)
pushCommand("INC B");
            pushCommand("SUB B C");
            
        }
    }
    else if(a.type == "NUM" && b.type == "IDE") {
        //setRegister(to_string(stoll(a.name) + isINC));
        pushCommand("SUB B B");
                  vector<string> opcodes;
long long int startsFrom = stoll(a.name);
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
 if(isINC)
pushCommand("INC B");
        memToRegister2(b.mem);
         pushCommand("SUB B C");
        if(isRemoval)
            removeIdentifier(a.name);
    }
    else if(a.type == "IDE" && b.type == "NUM") {
        //this is harder -- what is going on here -- i feel lost in my own code
        //just think I have made too many options... ok let's opt
        
            pushCommand("SUB C C");
                vector<string> opcodes;
long long int startsFrom = stoll(b.name);
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC C");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD C C");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC C");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
memToRegister(a.mem);
 if(isINC)
pushCommand("INC B");
pushCommand("SUB B C");
      
        if(isRemoval)
            removeIdentifier(b.name);
    }
    else if(a.type == "IDE" && b.type == "IDE") {
        if(a.name == b.name) {
memToRegister(a.mem);
            pushCommand("SUB B B");
          
        }
        else {
            memToRegister(a.mem);
            if(isINC)
pushCommand("INC B");
memToRegister2(b.mem);
pushCommand("SUB B C");
          
          //  pushCommandOneArg("SUB", b.mem);
        }
    }
}

void subTab(Identifier a, Identifier b, Identifier aIndex, Identifier bIndex, int isINC, int isRemoval) {
    if(a.type == "NUM" && b.type == "ARR") {
        if(bIndex.type == "NUM") {
            long long int addr = b.mem + stoll(bIndex.name) + 1;
            setRegister(to_string(stoll(a.name) + isINC));
pushCommand("SUB A A");
          vector<string> opcodes;
long long int startsFrom = addr;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD A A");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC A");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
pushCommand("LOAD A");
if(isINC)
pushCommand("INC B");
            pushCommand("SUB B A");
            if(isRemoval) {
                removeIdentifier(a.name);
                removeIdentifier(bIndex.name);
            }
        }
        else if(bIndex.type == "IDE") {
            memToRegister(b.mem);
memToRegister2(bIndex.mem);
           pushCommand("ADD B C");
 pushCommand("COPY A B");
 pushCommand("LOAD F");
pushCommand("SUB B B");
  vector<string> opcodes;
long long int startsFrom = stoll(a.name);
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
if(isINC)
pushCommand("INC B");

pushCommand("SUB B F");
//pushCommand("COPY B F");
                removeIdentifier(a.name);
        }
    }
    else if(a.type == "ARR" && b.type == "NUM") {
        if(aIndex.type == "NUM") {
            long long int addr = a.mem + stoll(aIndex.name) + 1;
            //this is harder -- what is going on here -- i feel lost in my own code
            //just think I have made too many options... ok let's opt
          
                memToRegister(addr);
if(isINC)
pushCommand("INC B");
                if(stoll(b.name)!=0 )
                    
                 {
                    for(int i=0; i < stoll(b.name) ; i++) {
                        pushCommand("DEC B");
                    }
                }
          
            if(isRemoval) {
                removeIdentifier(b.name);
                removeIdentifier(aIndex.name);
            }
        }
        else if(aIndex.type == "IDE") {
            //this is harder -- what is going on here -- i feel lost in my own code
            //just think I have made too many options... ok let's opt
            memToRegister(a.mem);
memToRegister2(aIndex.mem);
           pushCommand("ADD B C");
 pushCommand("COPY A B");
 pushCommand("LOAD F");
pushCommand("SUB B B");
  vector<string> opcodes;
long long int startsFrom = stoll(b.name);
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
if(isINC)
pushCommand("INC F");

pushCommand("SUB F B");
pushCommand("COPY B F");
                removeIdentifier(b.name);
        }
    }
    else if(a.type == "IDE" && b.type == "ARR") {
        if(bIndex.type == "NUM") {
              long long int addr = b.mem + stoll(bIndex.name) + 1;
            memToRegister2(addr);
           memToRegister(a.mem);
            
 if(isINC)
pushCommand("INC B");
                pushCommand("SUB B C");

               // pushCommand("SUB B A");
//pushCommand("COPY B A");

         
                removeIdentifier(bIndex.name);
        }
        else if(bIndex.type == "IDE") {
memToRegister(b.mem);
memToRegister2(bIndex.mem);
  pushCommand("ADD B C");
  pushCommand("COPY A B");
  pushCommand("LOAD B");
            memToRegister2(a.mem);
if(isINC)
pushCommand("INC C");
           pushCommand("SUB C B");
 pushCommand("COPY B C");
        }
    }
    else if(a.type == "ARR" && b.type == "IDE") {
        if(aIndex.type == "NUM") {
            long long int addr = a.mem + stoll(aIndex.name) + 1;
            memToRegister(addr);
           memToRegister2(b.mem);
            
      if(isINC)
pushCommand("INC B");
                pushCommand("SUB B C");

               // pushCommand("SUB B A");
//pushCommand("COPY B A");

            if(isRemoval)
                removeIdentifier(aIndex.name);
        }
        else if(aIndex.type == "IDE") {
            memToRegister(a.mem);
memToRegister2(aIndex.mem);
  pushCommand("ADD B C");
  pushCommand("COPY A B");
  pushCommand("LOAD B");
            memToRegister2(b.mem);
if(isINC)
pushCommand("INC B");
           pushCommand("SUB B C");

        }
    }
    else if(a.type == "ARR" && b.type == "ARR") {
        if(aIndex.type == "NUM" && bIndex.type == "NUM") {
            long long int addrA = a.mem + stoll(aIndex.name) + 1;
            long long int addrB = b.mem + stoll(bIndex.name) + 1;
            if(a.name == b.name && addrA == addrB) {

pushCommand("SUB B B");
              
            }
            else {
                memToRegister(addrA);
                if(isINC)
                    pushCommand("INC B");
memToRegister2(addrB);
                

               
              
                pushCommand("SUB B C");

            }
            if(isRemoval) {
                removeIdentifier(aIndex.name);
                removeIdentifier(bIndex.name);
            }
        }
        else if(aIndex.type == "NUM" && bIndex.type == "IDE") {
            long long int addrA = a.mem + stoll(aIndex.name) + 1;
                 memToRegister(b.mem);
memToRegister2(bIndex.mem);
  pushCommand("ADD B C");
  pushCommand("COPY A B");
  pushCommand("LOAD F");
            memToRegister2(addrA);
   
           // memToRegister2(b.mem);
if(isINC)
pushCommand("INC C");
           pushCommand("SUB C F");
pushCommand("COPY B C");

                removeIdentifier(aIndex.name);
        }
        else if(aIndex.type == "IDE" && bIndex.type == "NUM") {
            long long int addrB = b.mem + stoll(bIndex.name) + 1;
                             memToRegister(a.mem);
memToRegister2(aIndex.mem);
  pushCommand("ADD B C");
  pushCommand("COPY A B");
  pushCommand("LOAD F");
         //   memToRegister(addrB);
   
            memToRegister2(addrB);
if(isINC)
pushCommand("INC F");
           pushCommand("SUB F C");
pushCommand("COPY B F");
                removeIdentifier(bIndex.name);
        }
        else if(aIndex.type == "IDE" && bIndex.type == "IDE") {
            if(a.name == b.name && aIndex.name == bIndex.name) {
pushCommand("SUB B B");
            }
            else {
                memToRegister(a.mem);
memToRegister2(aIndex.mem);
  pushCommand("ADD B C");
  pushCommand("COPY A B");
  pushCommand("LOAD E");
     memToRegister(b.mem);
memToRegister2(bIndex.mem);
  pushCommand("ADD B C");
  pushCommand("COPY A B");
  pushCommand("LOAD B");
if(isINC)
pushCommand("INC E");
  pushCommand("SUB E B");
pushCommand("COPY B E");
            }
        }
    }
}

void addInt(long long int command, long long int val) {
    codeStack.at(command) = codeStack.at(command) + " " + to_string(val);
}

void setRegister(string number) {
    long long int n = stoll(number);
	/*if (n == registerValue) {
		return;
	}*/
    string bin = decToBin(n);
	long long int limit = bin.size();
    zeroRegister();
vector<string> opcodes;
long long int startsFrom = n;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC B");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD B B");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC B");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
}
void setRegister2(string number) {
    long long int n = stoll(number);
	/*if (n == registerValue) {
		return;
	}*/
    string bin = decToBin(n);
	long long int limit = bin.size();
   pushCommand("SUB  C C" );
vector<string> opcodes;
long long int startsFrom = n;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC C");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD C C");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC C");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
}

void zeroRegister() {
	/*if(registerValue != 0){*/
		pushCommand("SUB B B" );
		/*registerValue = 0;*/
	/*}*/
}

void memToRegister(long long int mem) {
pushCommand("SUB A A");
vector<string> opcodes;
long long int startsFrom = mem;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD A A");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC A");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
	pushCommand("LOAD B");
	/*registerValue = -1;*/
}

void memToRegister2(long long int mem) {
pushCommand("SUB A A");
vector<string> opcodes;
long long int startsFrom = mem;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD A A");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC A");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
	pushCommand("LOAD C");
	/*registerValue = -1;*/
}

string decToBin(long long int n) {
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

void registerToMem(long long int mem) {
pushCommand("SUB A A");
vector<string> opcodes;
long long int startsFrom = mem;
           long long  int endsAt = 0;

         long long   int current = startsFrom;
          long long  int cost = 0;

            

            while (current > endsAt)
            {
                if (current % 2 == 0 &&
                    current * 2 >= endsAt)
                {
                    if (current - current / 2 < 5)
                    {
                        current--;
                        cost++;
                        opcodes.push_back("INC A");
                    }
                    else
                    {
                        current /= 2;
                        cost += 5;
                        opcodes.push_back("ADD A A");
                    }
                }
                else
                {
                    current--;
                    cost++;
                    opcodes.push_back("INC A");
                }
            }
std::reverse(opcodes.begin(),opcodes.end());
for (long long int i=0; i<opcodes.size();i++)
{



	pushCommand(opcodes.at(i));
}
pushCommand("STORE B");
}

void insertIdentifier(string key, Identifier i) {
    if(identifierStack.count(key) == 0) {
        identifierStack.insert(make_pair(key, i));
        identifierStack.at(key).counter = 0;
        memCounter++;
    }
    else {
        identifierStack.at(key).counter = identifierStack.at(key).counter+1;
    }
    /*cout << "Add: " << key << " " << memCounter-1 << endl;*/
}

void removeIdentifier(string key) {
    if(identifierStack.count(key) > 0) {
        if(identifierStack.at(key).counter > 0) {
            identifierStack.at(key).counter = identifierStack.at(key).counter-1;
        }
        else {
            identifierStack.erase(key);
            memCounter--;
        }
    }
    /*cout << "Remove: " << key << endl;*/
}

void pushCommand(string str) {
    /*cout << str << endl;*/
    codeStack.push_back(str);
}

void pushCommandOneArg(string str, long long int num) {
    /*cout << str << endl;*/
    string temp = str + " " + to_string(num);
    codeStack.push_back(temp);
}
void pushCommandTwoArg(string str, long long int num, string str2) {
    /*cout << str << endl;*/
    string temp = str + " " + to_string(num) + " " + str2;
    codeStack.push_back(temp);
}

void printCode(string outFileName) {
    ofstream out_code(outFileName);
	long long int i;
	for(i = 0; i < codeStack.size(); i++)
        out_code << codeStack.at(i) << endl;
}

void printCodeStd() {
	long long int i;
	for(i = 0; i < codeStack.size(); i++)
        cout << codeStack.at(i) << endl;
}

void parser(long long int argv, char* argc[]) {
	assignFlag = 1;
	memCounter = 12;
    /*registerValue = -1;*/
	writeFlag = 0;
    depth = 0;

	yyparse();

    string file = "";
    if(argv < 2)
        /*file = "out";*/
        printCodeStd();
    else {
        file = argc[1];
        printCode(file);
    }
}

int main(int argv, char* argc[]){
	parser(argv, argc);
	return 0;
}

int yyerror(string str){
    cout << "Błąd [okolice linii " << yylineno << \
    "]: " << str << endl;
	/*return 1;*/
    exit(1);
}
