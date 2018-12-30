/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_OPT_COMPILER_TAB_H_INCLUDED
# define YY_YY_OPT_COMPILER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    VAR = 259,
    BEG = 260,
    END = 261,
    IF = 262,
    THEN = 263,
    ELSE = 264,
    ENDIF = 265,
    DO = 266,
    WHILE = 267,
    ENDWHILE = 268,
    FOR = 269,
    FROM = 270,
    ENDFOR = 271,
    ENDDO = 272,
    WRITE = 273,
    READ = 274,
    IDE = 275,
    SEM = 276,
    TO = 277,
    DOWNTO = 278,
    LB = 279,
    RB = 280,
    ASG = 281,
    EQ = 282,
    LT = 283,
    GT = 284,
    LE = 285,
    GE = 286,
    NE = 287,
    ADD = 288,
    SUB = 289,
    MUL = 290,
    DIV = 291,
    MOD = 292,
    COLON = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 77 "opt_compiler.y" /* yacc.c:1909  */

    char* str;
    long long int num;

#line 98 "opt_compiler.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_OPT_COMPILER_TAB_H_INCLUDED  */
