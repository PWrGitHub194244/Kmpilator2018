/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "opt_compiler.y" /* yacc.c:339  */

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


#line 140 "opt_compiler.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "opt_compiler.tab.h".  */
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
#line 77 "opt_compiler.y" /* yacc.c:355  */

    char* str;
    long long int num;

#line 224 "opt_compiler.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_OPT_COMPILER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 241 "opt_compiler.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    99,   111,   132,   136,   137,   141,   141,
     211,   213,   211,   216,   222,   222,   216,   226,   232,   226,
     257,   271,   257,   272,   272,   304,   304,   378,   378,   403,
     419,   419,   656,   656,   918,   947,   965,   983,  1272,  1828,
    2391,  2436,  2489,  2524,  2559,  2594,  2634,  2650,  2654,  2685,
    2728
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "VAR", "BEG", "END", "IF", "THEN",
  "ELSE", "ENDIF", "DO", "WHILE", "ENDWHILE", "FOR", "FROM", "ENDFOR",
  "ENDDO", "WRITE", "READ", "IDE", "SEM", "TO", "DOWNTO", "LB", "RB",
  "ASG", "EQ", "LT", "GT", "LE", "GE", "NE", "ADD", "SUB", "MUL", "DIV",
  "MOD", "COLON", "$accept", "program", "vdeclarations", "commands",
  "command", "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9",
  "$@10", "$@11", "$@12", "ifbody", "$@13", "forbody", "$@14", "$@15",
  "expression", "condition", "value", "identifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

#define YYPACT_NINF -20

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-20)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,   -20,    16,     3,   -20,   154,    11,   -20,   -20,   -20,
       4,   -20,    14,    12,    19,   -20,    15,   -20,    37,     0,
     154,     0,   -20,     0,   -20,     2,   -20,   -20,   -20,     7,
     -20,   -20,    99,   -20,   164,   -20,    27,    22,    26,    29,
      31,     0,    57,    53,     0,     0,     0,     0,     0,     0,
     -20,    51,     0,   -20,   -20,   -20,   -20,    44,    34,    48,
     154,   -20,   -20,   -20,   -20,   -20,   -20,     0,   154,   -20,
     -20,     0,     0,     0,     0,     0,    54,   105,   -20,    -1,
       5,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
      59,   -20,     0,     0,   -20,   154,   -20,    66,    67,    39,
     -20,   -20,   -20,   154,   154,   130,   144,   -20,   -20
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     0,     1,     0,     0,    10,    13,    17,
       0,    25,     0,    48,     0,     7,     0,     3,     0,     0,
       0,     0,    20,     0,    23,     0,     2,     6,     8,     0,
      46,    11,     0,    47,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      14,     0,     0,    26,    24,    50,    49,     0,    34,     0,
       0,    40,    42,    43,    44,    45,    41,     0,     0,    21,
       9,     0,     0,     0,     0,     0,     0,     0,    15,     0,
       0,    35,    36,    37,    38,    39,     4,    27,    29,    12,
       0,    19,     0,     0,    22,     0,    16,     0,     0,     0,
      32,    30,    28,     0,     0,     0,     0,    33,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -20,   -20,   -20,   -16,   -13,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,   -20,   -19,    61,    -5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    14,    15,    41,    19,    43,    20,    67,
      90,    21,    51,    36,    80,    38,    23,    89,    95,    94,
     104,   103,    57,    31,    32,    33
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      16,    27,    35,    30,    34,    39,     7,    24,     5,    16,
       8,     9,    91,    10,     1,    16,     4,    11,    12,    13,
      13,    27,    40,     6,    22,    26,     7,    92,    93,    16,
       8,     9,    17,    10,    13,    18,    25,    11,    12,    13,
      29,    28,    52,    53,    77,    42,     7,    54,    78,   102,
       8,     9,    79,    10,    55,    16,    56,    11,    12,    13,
      59,    60,    68,    16,    27,    70,    27,    71,    72,    73,
      74,    75,    16,    76,    16,    86,    96,   100,   101,    99,
       0,     0,     0,     0,    37,     0,    27,   105,   106,     0,
      16,     0,    27,    27,    16,     0,     0,     0,    16,    16,
      16,    16,    58,     0,     0,    61,    62,    63,    64,    65,
      66,     0,     7,    69,    87,    88,     8,     9,     0,    10,
       0,     0,     0,    11,    12,    13,    44,    45,    46,    47,
      48,    49,    81,    82,    83,    84,    85,     7,     0,     0,
       0,     8,     9,     0,    10,     0,   107,     0,    11,    12,
      13,     7,     0,    97,    98,     8,     9,     0,    10,     0,
     108,     7,    11,    12,    13,     8,     9,     0,    10,     0,
       0,     7,    11,    12,    13,     8,    50,     0,    10,     0,
       0,     0,    11,    12,    13
};

static const yytype_int8 yycheck[] =
{
       5,    14,    21,     3,    20,     3,     7,    12,     5,    14,
      11,    12,    13,    14,     4,    20,     0,    18,    19,    20,
      20,    34,    20,    20,    20,     6,     7,    22,    23,    34,
      11,    12,    21,    14,    20,    24,    24,    18,    19,    20,
       3,    26,    15,    21,    60,    38,     7,    21,    67,    10,
      11,    12,    68,    14,    25,    60,    25,    18,    19,    20,
       3,     8,    11,    68,    77,    21,    79,    33,    34,    35,
      36,    37,    77,    25,    79,    21,    17,    11,    11,    95,
      -1,    -1,    -1,    -1,    23,    -1,    99,   103,   104,    -1,
      95,    -1,   105,   106,    99,    -1,    -1,    -1,   103,   104,
     105,   106,    41,    -1,    -1,    44,    45,    46,    47,    48,
      49,    -1,     7,    52,     9,    10,    11,    12,    -1,    14,
      -1,    -1,    -1,    18,    19,    20,    27,    28,    29,    30,
      31,    32,    71,    72,    73,    74,    75,     7,    -1,    -1,
      -1,    11,    12,    -1,    14,    -1,    16,    -1,    18,    19,
      20,     7,    -1,    92,    93,    11,    12,    -1,    14,    -1,
      16,     7,    18,    19,    20,    11,    12,    -1,    14,    -1,
      -1,     7,    18,    19,    20,    11,    12,    -1,    14,    -1,
      -1,    -1,    18,    19,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    40,    41,     0,     5,    20,     7,    11,    12,
      14,    18,    19,    20,    42,    43,    64,    21,    24,    45,
      47,    50,    20,    55,    64,    24,     6,    43,    26,     3,
       3,    62,    63,    64,    42,    62,    52,    63,    54,     3,
      20,    44,    38,    46,    27,    28,    29,    30,    31,    32,
      12,    51,    15,    21,    21,    25,    25,    61,    63,     3,
       8,    63,    63,    63,    63,    63,    63,    48,    11,    63,
      21,    33,    34,    35,    36,    37,    25,    42,    62,    42,
      53,    63,    63,    63,    63,    63,    21,     9,    10,    56,
      49,    13,    22,    23,    58,    57,    17,    63,    63,    42,
      11,    11,    10,    60,    59,    42,    42,    16,    16
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    42,    42,    44,    43,
      45,    46,    43,    47,    48,    49,    43,    50,    51,    43,
      52,    53,    43,    54,    43,    55,    43,    57,    56,    56,
      59,    58,    60,    58,    61,    61,    61,    61,    61,    61,
      62,    62,    62,    62,    62,    62,    63,    63,    64,    64,
      64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     3,     8,     0,     2,     1,     0,     5,
       0,     0,     7,     0,     0,     0,     8,     0,     0,     7,
       0,     0,     7,     0,     4,     0,     4,     0,     4,     1,
       0,     6,     0,     6,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     4,
       4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 2:
#line 93 "opt_compiler.y" /* yacc.c:1646  */
    {
        pushCommand("HALT");
    }
#line 1639 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 99 "opt_compiler.y" /* yacc.c:1646  */
    {
        if(identifierStack.find((yyvsp[-1].str))!=identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno \
            << "]: Kolejna deklaracja zmiennej " << (yyvsp[-1].str) << "." << endl;
            exit(1);
        }
        else {
            Identifier s;
            createIdentifier(&s, (yyvsp[-1].str), 0, 0, "IDE");
            insertIdentifier((yyvsp[-1].str), s);
        }
    }
#line 1656 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 111 "opt_compiler.y" /* yacc.c:1646  */
    {
        if(identifierStack.find((yyvsp[-6].str))!=identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno \
            << "]: Kolejna deklaracja zmiennej " << (yyvsp[-6].str) << "." << endl;
            exit(1);
        }
        else if (atoll((yyvsp[-2].str))-atoll((yyvsp[-4].str)) <= 0) {
            cout << "Błąd [okolice linii " << yylineno \
            << "]: Deklarowanie tablicy " << (yyvsp[-6].str) << " o rozmiarze zero." << endl;
            exit(1);
        }
        else {
            long long int size = (yyvsp[-2].str)- (yyvsp[-4].str);
            Identifier s;
            createIdentifier(&s, (yyvsp[-6].str), 0, size, "ARR");
            insertIdentifier((yyvsp[-6].str), s);
            memCounter += size;
            setRegister(to_string(s.mem+1));
            registerToMem(s.mem);
        }
    }
#line 1682 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 141 "opt_compiler.y" /* yacc.c:1646  */
    {
        assignFlag = 0;
    }
#line 1690 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 143 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 1763 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 211 "opt_compiler.y" /* yacc.c:1646  */
    {assignFlag = 0;
        depth++;
    }
#line 1771 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 213 "opt_compiler.y" /* yacc.c:1646  */
    {
        assignFlag = 1;
    }
#line 1779 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 216 "opt_compiler.y" /* yacc.c:1646  */
    {
        assignFlag = 0;
        depth++;
        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
    }
#line 1791 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 222 "opt_compiler.y" /* yacc.c:1646  */
    { assignFlag = 0;}
#line 1797 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 222 "opt_compiler.y" /* yacc.c:1646  */
    {  long long int stack;
codeStack.at(codeStack.size()-1)="JZERO B "+to_string(codeStack.size()+1);
        long long int jumpCount = jumpStack.size()-1; stack = jumpStack.at(jumpCount-1).placeInStack;   stack = jumpStack.at(jumpCount-1).placeInStack;
           pushCommandOneArg("JUMP",stack);  depth--;}
#line 1806 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 226 "opt_compiler.y" /* yacc.c:1646  */
    {
        assignFlag = 0;
        depth++;
        Jump j;
        createJump(&j, codeStack.size(), depth);
        jumpStack.push_back(j);
    }
#line 1818 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 232 "opt_compiler.y" /* yacc.c:1646  */
    {
        assignFlag = 1;
    }
#line 1826 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 234 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 1853 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 257 "opt_compiler.y" /* yacc.c:1646  */
    {
        if(identifierStack.find((yyvsp[0].str))!=identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno \
            << "]: Kolejna deklaracja zmiennej " << (yyvsp[0].str) << "." << endl;
            exit(1);
        }
        else {
            Identifier s;
            createIdentifier(&s, (yyvsp[0].str), 1, 0, "IDE");
            insertIdentifier((yyvsp[0].str), s);
        }
        assignFlag = 0;
        assignTarget = identifierStack.at((yyvsp[0].str));
        depth++;
    }
#line 1873 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 271 "opt_compiler.y" /* yacc.c:1646  */
    {pushCommand("INC B");}
#line 1879 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 272 "opt_compiler.y" /* yacc.c:1646  */
    {
        assignFlag = 1;
    }
#line 1887 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 274 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 1922 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 304 "opt_compiler.y" /* yacc.c:1646  */
    {
        assignFlag = 0;
        writeFlag = 1;
    }
#line 1931 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 307 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 2002 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 378 "opt_compiler.y" /* yacc.c:1646  */
    {
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
    }
#line 2023 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 393 "opt_compiler.y" /* yacc.c:1646  */
    {
        addInt(jumpStack.at(jumpStack.size()-1).placeInStack, codeStack.size());
        jumpStack.pop_back();
        jumpStack.pop_back();
        if(jumpStack.size() >= 1 && jumpStack.at(jumpStack.size()-1).depth == depth) {
            jumpStack.pop_back();
        }
        depth--;
        assignFlag = 1;
    }
#line 2038 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 403 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 2056 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 419 "opt_compiler.y" /* yacc.c:1646  */
    {
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
    }
#line 2138 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 495 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 2304 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 656 "opt_compiler.y" /* yacc.c:1646  */
    {

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
#line 2394 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 742 "opt_compiler.y" /* yacc.c:1646  */
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
#line 2572 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 918 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 2606 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 947 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 2629 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 965 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 2652 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 983 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 2946 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1272 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 3507 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1828 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 4072 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 2391 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 4122 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 2436 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 4180 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 2489 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 4220 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 2524 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 4260 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 2559 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 4300 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 2594 "opt_compiler.y" /* yacc.c:1646  */
    {
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
#line 4342 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 2634 "opt_compiler.y" /* yacc.c:1646  */
    {
        if(assignFlag){
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Próba przypisania do stałej." << endl;
           	exit(1);
      	}
        Identifier s;
      	createIdentifier(&s, (yyvsp[0].str), 0, 0, "NUM");
        insertIdentifier((yyvsp[0].str), s);
      	if (expressionArguments[0] == "-1"){
      		expressionArguments[0] = (yyvsp[0].str);
      	}
      	else{
      		expressionArguments[1] = (yyvsp[0].str);
      	}
    }
#line 4363 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 2654 "opt_compiler.y" /* yacc.c:1646  */
    {
        if(identifierStack.find((yyvsp[0].str)) == identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << (yyvsp[0].str) << " nie została zadeklarowana." << endl;
            exit(1);
        }
        if(identifierStack.at((yyvsp[0].str)).tableSize == 0) {
            if(!assignFlag){
                if(identifierStack.at((yyvsp[0].str)).initialized == 0) {
                    cout << "Błąd [okolice linii " << yylineno << \
                    "]: Próba użycia niezainicjalizowanej zmiennej " << (yyvsp[0].str) << "." << endl;
                    exit(1);
                }
                if (expressionArguments[0] == "-1"){
                    expressionArguments[0] = (yyvsp[0].str);
                }
                else{
                    expressionArguments[1] = (yyvsp[0].str);
                }

            }
            else {
                assignTarget = identifierStack.at((yyvsp[0].str));
            }
        }
        else {
          cout << "Błąd [okolice linii " << yylineno << \
          "]: Brak odwołania do elementu tablicy " << (yyvsp[0].str) << "." << endl;
          exit(1);
        }
    }
#line 4399 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 2685 "opt_compiler.y" /* yacc.c:1646  */
    {
        if(identifierStack.find((yyvsp[-3].str)) == identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << (yyvsp[-3].str) << " nie została zadeklarowana." << endl;
            exit(1);
        }
        if(identifierStack.find((yyvsp[-1].str)) == identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << (yyvsp[-1].str) << " nie została zadeklarowana." << endl;
            exit(1);
        }

        if(identifierStack.at((yyvsp[-3].str)).tableSize == 0) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << (yyvsp[-3].str) << " nie jest tablicą." << endl;
            exit(1);
        }
        else {
            if(identifierStack.at((yyvsp[-1].str)).initialized == 0) {
                cout << "Błąd [okolice linii " << yylineno << \
                "]: Próba użycia niezainicjalizowanej zmiennej " << (yyvsp[-1].str) << "." << endl;
                exit(1);
            }

            if(!assignFlag){
                //TODO czy wywalać błąd niezainicjalizowanej
                //zmiennej dla elementu tablicy
                if (expressionArguments[0] == "-1"){
                    expressionArguments[0] = (yyvsp[-3].str);
                    argumentsTabIndex[0] = (yyvsp[-1].str);
                }
                else{
                    expressionArguments[1] = (yyvsp[-3].str);
                    argumentsTabIndex[1] = (yyvsp[-1].str);
                }

            }
            else {
                assignTarget = identifierStack.at((yyvsp[-3].str));
                tabAssignTargetIndex = (yyvsp[-1].str);
            }
        }
    }
#line 4447 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 2728 "opt_compiler.y" /* yacc.c:1646  */
    {
        if(identifierStack.find((yyvsp[-3].str)) == identifierStack.end()) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << (yyvsp[-3].str) << " nie została zadeklarowana." << endl;
            exit(1);
        }

        if(identifierStack.at((yyvsp[-3].str)).tableSize == 0) {
            cout << "Błąd [okolice linii " << yylineno << \
            "]: Zmienna " << (yyvsp[-3].str) << " nie jest tablicą." << endl;
            exit(1);
        }
        else {
            Identifier s;
            createIdentifier(&s, (yyvsp[-1].str), 0, 0, "NUM");
            insertIdentifier((yyvsp[-1].str), s);

            if(!assignFlag){
                //TODO czy wywalać błąd niezainicjalizowanej
                //zmiennej dla elementu tablicy
                if (expressionArguments[0] == "-1"){
                    expressionArguments[0] = (yyvsp[-3].str);
                    argumentsTabIndex[0] = (yyvsp[-1].str);
                }
                else{
                    expressionArguments[1] = (yyvsp[-3].str);
                    argumentsTabIndex[1] = (yyvsp[-1].str);
                }

            }
            else {
                assignTarget = identifierStack.at((yyvsp[-3].str));
                tabAssignTargetIndex = (yyvsp[-1].str);
            }
        }
    }
#line 4488 "opt_compiler.tab.c" /* yacc.c:1646  */
    break;


#line 4492 "opt_compiler.tab.c" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2766 "opt_compiler.y" /* yacc.c:1906  */


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
