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
#line 2 "compiler_hw3.y" /* yacc.c:339  */

/*	insert the C library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern int yylex();
void yyerror(char *);
/* Sym
bol table function - you can add new function if need. */
//原來的 lex
	#include <stdio.h>
	#include <stdlib.h>
	#define TableSize 1000
	/* Symbol table function */
	void create_symbol();
	int insert_symbol(char*,int);
	int lookup_symbol(char*);
	void dump_symbol();
	void insert_value(int ret , double f_val, int i_val);
	int linecount=1;	
	int commentline=0;

	typedef struct symbol_table{
	char* id;
	char* type;
	union{
 			int i_val;
 			double f_val;
 	};
	int vaild;
	int scope_depth;
	//NEW
	int function;		//==1代表是function
	char sign[50];	//function的參數和return type
	}symboltable;

	symboltable* table[TableSize];
	int CreateTableFlag=0;	
	int CheckUndefined=0;
	int NowDepth=0;
	void ScopeOver();
	//NEW
	int printidscope=0;//表示目前是不是要print id 或是數字 
	int out=0;//要輸出的值
	//jasmin

	int ERROR=0;//程式有沒有錯誤
	FILE * fp;
	
	int labelStack[256];//目前存的 label
	int labeltop;//目前所在的label
	int globallabel=0;//目前label編到幾號

	int definefunct=0;//看看有沒有define function 如果沒有要把 global 視為 main
	//symbol_table Tempparameter[10];//先暫存起來，等等要傳進function的table裡面
	int Tempindex=0;//for上面的Tempparameter index
	symboltable* Temptable[TableSize];

#line 127 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    PRINT = 258,
    PRINTLN = 259,
    IF = 260,
    ELSE = 261,
    FOR = 262,
    VAR = 263,
    NEWLINE = 264,
    ADD = 265,
    SUB = 266,
    MUL = 267,
    DIV = 268,
    MOD = 269,
    GT = 270,
    LTGE = 271,
    LE = 272,
    EQ = 273,
    NE = 274,
    INC = 275,
    DEC = 276,
    LT = 277,
    GE = 278,
    ASSIGN = 279,
    ADD_ASSIGN = 280,
    SUB_ASSIGN = 281,
    MUL_ASSIGN = 282,
    DIV_ASSIGN = 283,
    MOD_ASSIGN = 284,
    AND = 285,
    OR = 286,
    NOT = 287,
    LB2 = 288,
    RB2 = 289,
    C_COMMENT = 290,
    SEM = 291,
    COM = 292,
    FUNC = 293,
    I_CONST = 294,
    F_CONST = 295,
    STRING = 296,
    INT = 297,
    FLOAT = 298,
    VOID = 299,
    ID = 300,
    UMINUS = 301
  };
#endif
/* Tokens.  */
#define PRINT 258
#define PRINTLN 259
#define IF 260
#define ELSE 261
#define FOR 262
#define VAR 263
#define NEWLINE 264
#define ADD 265
#define SUB 266
#define MUL 267
#define DIV 268
#define MOD 269
#define GT 270
#define LTGE 271
#define LE 272
#define EQ 273
#define NE 274
#define INC 275
#define DEC 276
#define LT 277
#define GE 278
#define ASSIGN 279
#define ADD_ASSIGN 280
#define SUB_ASSIGN 281
#define MUL_ASSIGN 282
#define DIV_ASSIGN 283
#define MOD_ASSIGN 284
#define AND 285
#define OR 286
#define NOT 287
#define LB2 288
#define RB2 289
#define C_COMMENT 290
#define SEM 291
#define COM 292
#define FUNC 293
#define I_CONST 294
#define F_CONST 295
#define STRING 296
#define INT 297
#define FLOAT 298
#define VOID 299
#define ID 300
#define UMINUS 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 64 "compiler_hw3.y" /* yacc.c:355  */

	struct{
		union{
    		int	i_val;
		double f_val;
		};
		int type;
		//NEW
		char buf[512];//為了插入i2f使用
	}val;
    char *string;

#line 272 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 289 "y.tab.c" /* yacc.c:358  */

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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   242

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      20,    21,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,    23,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   128,   132,   134,   132,   145,   146,   147,
     148,   149,   150,   151,   152,   161,   163,   169,   203,   168,
     290,   291,   292,   293,   296,   317,   338,   346,   346,   359,
     359,   367,   374,   384,   385,   391,   391,   401,   401,   413,
     446,   483,   511,   537,   564,   595,   612,   646,   680,   681,
     690,   720,   725,   730,   740,   750,   753,   756,   762,   802,
     840,   878,   916,   955,   998,  1044,  1099,  1150,  1196,  1242,
    1268,  1281,  1303,  1304,  1305,  1308,  1324,  1332,  1340,  1368
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PRINT", "PRINTLN", "IF", "ELSE", "FOR",
  "VAR", "NEWLINE", "ADD", "SUB", "MUL", "DIV", "MOD", "GT", "LTGE", "LE",
  "EQ", "NE", "'('", "')'", "'{'", "'}'", "INC", "DEC", "LT", "GE",
  "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "AND", "OR", "NOT", "LB2", "RB2", "C_COMMENT", "SEM",
  "COM", "FUNC", "I_CONST", "F_CONST", "STRING", "INT", "FLOAT", "VOID",
  "ID", "UMINUS", "$accept", "program", "stat", "$@1", "$@2", "function",
  "$@3", "$@4", "funct_type", "parameter_list", "if_block", "$@5",
  "ELSE_block", "$@6", "block_item_list", "for_loop", "$@7", "$@8",
  "For_block", "arith", "call_function", "argument_list", "compare_expr",
  "assign_expr", "declaration", "type", "initializer", "print_func", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      40,    41,   123,   125,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301
};
# endif

#define YYPACT_NINF -110

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-110)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -110,    61,  -110,     1,     4,  -110,   -17,   -37,  -110,   153,
     153,  -110,  -110,   -32,  -110,  -110,   197,  -110,  -110,  -110,
    -110,   193,  -110,  -110,  -110,  -110,  -110,    42,   149,    13,
    -110,    83,    12,    11,     3,  -110,    -3,   139,    34,   153,
    -110,  -110,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,    39,
      63,    46,   221,   153,   153,  -110,  -110,  -110,  -110,    35,
    -110,  -110,   139,  -110,   116,   -16,   116,   116,   116,   116,
     116,   116,    66,    66,  -110,  -110,  -110,   116,   116,   116,
     116,   116,   116,  -110,  -110,  -110,  -110,   193,    67,    68,
     153,   153,  -110,    59,    41,  -110,   153,   139,   139,    57,
     116,  -110,  -110,    11,   -15,   116,     7,  -110,    50,  -110,
      48,    52,  -110,  -110,  -110,     5,  -110,  -110,  -110,  -110,
    -110,    11,   139,   139,   139,    80,  -110,  -110,  -110,  -110,
     139,   114,  -110
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     0,     0,    27,     0,     0,    11,     0,
       0,     4,    15,     0,    51,    52,    50,     2,    16,     9,
       7,    14,    53,    13,    12,     8,    10,     0,     0,     0,
      37,     0,     0,     0,    50,    48,     0,     0,     0,    57,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    72,    73,    74,    70,
      49,    33,     5,    17,    56,     0,    64,    65,    66,    67,
      68,    69,    41,    42,    43,    44,    45,    58,    61,    62,
      63,    59,    60,    76,    78,    77,    79,     0,     0,     0,
       0,     0,    34,     0,    26,    54,     0,     0,     0,     0,
      75,    71,     6,     0,     0,    55,    32,    38,     0,    24,
      23,     0,    29,    31,    28,     0,    36,    20,    21,    22,
      18,     0,     0,     0,     0,     0,    25,    30,    40,    39,
       0,     0,    19
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -110,  -110,    -1,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,  -110,  -110,   -31,  -110,  -110,  -110,  -110,    -8,
    -110,  -110,   -49,   102,  -110,  -109,  -110,  -110
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    71,    37,   103,    18,   104,   135,   130,   114,
      19,    29,   124,   132,    72,    20,   100,    64,   126,    21,
      22,    75,    23,    24,    25,    69,   111,    26
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      17,    35,    36,    30,   119,   105,   120,    48,    49,    50,
      51,    52,    33,   122,    98,    99,   123,    38,    70,    60,
      62,    27,   136,    39,    28,   106,   121,    40,    41,   133,
     134,    74,    31,    63,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   109,    65,     9,    73,    97,    97,    66,    67,    68,
      93,     2,    10,   101,     3,     4,     5,    95,     6,     7,
       8,   102,     9,    48,    49,    50,    51,    52,    50,    51,
      52,    10,   112,    11,    94,    14,    15,    59,   107,   108,
     113,    34,    97,   110,   127,   128,   129,   118,   115,   125,
      12,   131,   140,    13,    14,    15,   116,   117,    32,   141,
      16,    42,    43,    44,    45,    46,    47,     3,     4,     5,
       0,     6,     7,     8,     0,     9,    48,    49,    50,    51,
      52,   137,   138,   139,    10,     0,    11,   142,     0,     0,
     102,     0,     3,     4,     5,     0,     6,     7,     8,     0,
       9,     0,     0,    12,     0,     0,    13,    14,    15,    10,
       9,    11,     0,    16,     9,     0,     0,     0,     0,    10,
       0,     0,     0,    10,     0,     0,     0,     0,    12,     0,
       0,    13,    14,    15,     0,     0,     0,     0,    16,     0,
       0,     0,    14,    15,    61,     0,    14,    15,    34,     0,
       0,     0,    34,    48,    49,    50,    51,    52,    53,     0,
      54,    55,    56,     0,     0,     0,     0,    39,     0,    57,
      58,    40,    41,     0,     0,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,     0,     0,     0,     0,
       0,     0,    96
};

static const yytype_int16 yycheck[] =
{
       1,     9,    10,    20,   113,    21,    21,    10,    11,    12,
      13,    14,    49,     6,    63,    64,     9,    49,    21,    27,
      28,    20,   131,    20,    20,    41,    41,    24,    25,    24,
      25,    39,    49,    20,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,   100,    40,    11,    20,    63,    64,    46,    47,    48,
      21,     0,    20,    28,     3,     4,     5,    21,     7,     8,
       9,    72,    11,    10,    11,    12,    13,    14,    12,    13,
      14,    20,    23,    22,    21,    43,    44,    45,    21,    21,
      49,    49,   100,   101,    46,    47,    48,    40,   106,    49,
      39,    49,    22,    42,    43,    44,   107,   108,     6,   140,
      49,    28,    29,    30,    31,    32,    33,     3,     4,     5,
      -1,     7,     8,     9,    -1,    11,    10,    11,    12,    13,
      14,   132,   133,   134,    20,    -1,    22,    23,    -1,    -1,
     141,    -1,     3,     4,     5,    -1,     7,     8,     9,    -1,
      11,    -1,    -1,    39,    -1,    -1,    42,    43,    44,    20,
      11,    22,    -1,    49,    11,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    43,    44,    45,    -1,    43,    44,    49,    -1,
      -1,    -1,    49,    10,    11,    12,    13,    14,    15,    -1,
      17,    18,    19,    -1,    -1,    -1,    -1,    20,    -1,    26,
      27,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,     0,     3,     4,     5,     7,     8,     9,    11,
      20,    22,    39,    42,    43,    44,    49,    53,    56,    61,
      66,    70,    71,    73,    74,    75,    78,    20,    20,    62,
      20,    49,    74,    49,    49,    70,    70,    54,    49,    20,
      24,    25,    28,    29,    30,    31,    32,    33,    10,    11,
      12,    13,    14,    15,    17,    18,    19,    26,    27,    45,
      70,    45,    70,    20,    68,    40,    46,    47,    48,    76,
      21,    53,    65,    20,    70,    72,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    21,    21,    21,    21,    70,    73,    73,
      67,    28,    53,    55,    57,    21,    41,    21,    21,    73,
      70,    77,    23,    49,    60,    70,    53,    53,    40,    76,
      21,    41,     6,     9,    63,    49,    69,    46,    47,    48,
      59,    49,    64,    24,    25,    58,    76,    53,    53,    53,
      22,    65,    23
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    54,    55,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    57,    58,    56,
      59,    59,    59,    59,    60,    60,    60,    62,    61,    64,
      63,    63,    63,    65,    65,    67,    66,    68,    66,    69,
      69,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    72,    72,    72,    73,    73,
      73,    73,    73,    73,    74,    74,    74,    74,    74,    74,
      75,    75,    76,    76,    76,    77,    78,    78,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     0,     0,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     0,    11,
       1,     1,     1,     0,     2,     4,     0,     0,     7,     0,
       3,     1,     0,     1,     2,     0,     7,     0,     6,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     3,
       1,     1,     1,     1,     4,     3,     1,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     1,     1,     1,     1,     4,     4,     4,     4
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
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
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
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
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
  switch (yyn)
    {
        case 4:
#line 132 "compiler_hw3.y" /* yacc.c:1646  */
    {NowDepth++;}
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 134 "compiler_hw3.y" /* yacc.c:1646  */
    {
							
							printf("Scope %d\n",NowDepth);
						}
#line 1497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 139 "compiler_hw3.y" /* yacc.c:1646  */
    {	
						// NEW 把目前scope的vaild設為2表示dead不能用
						ScopeOver();
						NowDepth--; 
						//printf("-------------------------Scope %d\n",NowDepth);
						}
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 145 "compiler_hw3.y" /* yacc.c:1646  */
    {		}
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 149 "compiler_hw3.y" /* yacc.c:1646  */
    {linecount++;}
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 152 "compiler_hw3.y" /* yacc.c:1646  */
    {	
/*				 if($1.type==1)//int
				printf("ans = %d\n", $1.i_val);
				else
				printf("ans = %lf\n", $1.f_val);*/
			//printf("--------------------------------------------\n%s-----------------------------------------",$1.buf);
			fprintf(fp,"%s",(yyvsp[0].val).buf);
				
			}
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 169 "compiler_hw3.y" /* yacc.c:1646  */
    { //注意這個大括號好像是 $4 ??
				int i; 
					for(i=0;i<TableSize;i++){

						//NEW temptable
						Temptable[i]= malloc(sizeof(struct symbol_table));
						Temptable[i]->type=NULL;
						Temptable[i]->id=NULL;
						Temptable[i]->vaild=0;
						Temptable[i]->scope_depth=-1;
					}	

				//因為宣告function，所以要先把上面的main拿掉重開
				if(definefunct==0){
				fclose(fp);
				fp= fopen("Computer.j", "w" );
				fprintf(fp,"%s",".class public main\n");
				fprintf(fp,"%s",".super java/lang/Object\n\n");
				definefunct=1;
				}
				fprintf(fp,".method public static %s(",(yyvsp[-1].string));
				
					//先交換一次table以讓parameter插入
					symboltable* temp[TableSize];
					for(i=0;i<TableSize;i++){	
					temp[i]=Temptable[i];
					Temptable[i]=table[i];
					table[i]=temp[i];
					}
					
				
			}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 203 "compiler_hw3.y" /* yacc.c:1646  */
    {
				//1.交換回來
				int i;
				symboltable* temp[TableSize];
					for(i=0;i<TableSize;i++){	
					temp[i]=Temptable[i];
					Temptable[i]=table[i];
					table[i]=temp[i];
					}
				char sign[50];//function 的參數和return type
				//把parameter list寫入
				

				if(strcmp((yyvsp[-5].string),"main")==0)
					sprintf(sign,"[Ljava/lang/String;");
				else
					sprintf(sign,"%s",(yyvsp[-2].string));

				if(strcmp((yyvsp[0].string),"float32")==0)
					strcat(sign,")F\n");
				else if (strcmp((yyvsp[0].string),"int")==0)
					strcat(sign,")I\n");
				else if (strcmp((yyvsp[0].string),"void")==0)
					strcat(sign,")V\n");	

				fprintf(fp,"%s",sign);
				fprintf(fp, ".limit stack 100\n");
				fprintf(fp, ".limit locals 100\n");
				
				//---------------插入到symboltable 因為下面要用
				int ret;
				if (strcmp((yyvsp[0].string),"int")==0){
					printf("---------------------\n");
					ret=insert_symbol((yyvsp[-5].string),1);
					table[ret]->function=1;//代表是function ID
					sprintf(table[ret]->sign,"(%s",sign);

				}
				else if(strcmp((yyvsp[0].string),"float32")==0){
					ret=insert_symbol((yyvsp[-5].string),0);
					table[ret]->function=1;//代表是function ID
					sprintf(table[ret]->sign,"(%s",sign);

				}
				else if(strcmp((yyvsp[0].string),"void")==0){
					ret=insert_symbol((yyvsp[-5].string),2);
					table[ret]->function=1;//代表是function ID
					sprintf(table[ret]->sign,"(%s",sign);

				}

					//開始進入function

					//1.先交換table
					for(i=0;i<TableSize;i++){	
					temp[i]=Temptable[i];
					Temptable[i]=table[i];
					table[i]=temp[i];
					}
						
			}
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 267 "compiler_hw3.y" /* yacc.c:1646  */
    {
				if(strcmp((yyvsp[-4].string),"float32")==0)
					fprintf(fp,"%s","\tfreturn\n.end method\n\n");
				else if (strcmp((yyvsp[-4].string),"int")==0)
					fprintf(fp,"%s","\tireturn\n.end method\n\n");
				else if (strcmp((yyvsp[-4].string),"void")==0)
					fprintf(fp,"%s","\treturn\n.end method\n\n");	
				
				Tempindex=0;
				//出function
				//2.再交換一次
				int i;
				symboltable* temp[TableSize];
				for(i=0;i<TableSize;i++){	
				temp[i]=Temptable[i];
				Temptable[i]=table[i];
				table[i]=temp[i];
				free(Temptable[i]);
				}
			}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 290 "compiler_hw3.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 291 "compiler_hw3.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 292 "compiler_hw3.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 293 "compiler_hw3.y" /* yacc.c:1646  */
    {(yyval.string)="void";}
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 297 "compiler_hw3.y" /* yacc.c:1646  */
    {	
					int ret;
							if(strcmp((yyvsp[0].string),"int")==0){
								ret=insert_symbol((yyvsp[-1].string),1);
								
								strcat((yyval.string),"I");
							}else{
								ret=insert_symbol((yyvsp[-1].string),0);
								strcat((yyval.string),"F");
							}	
//					sprintf(Tempparameter[Tempindex++],"%s",$1);
					sprintf((yyval.string),"%s","");//先清空
/*
					if(strcmp($2,"float32")==0)
						strcat($$,"F");
					else if (strcmp($2,"int")==0)
						strcat($$,"I");
*/
						
				}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 318 "compiler_hw3.y" /* yacc.c:1646  */
    {
							int ret;
							if(strcmp((yyvsp[0].string),"int")==0){
								ret=insert_symbol((yyvsp[-1].string),1);
								strcat((yyval.string),"I");
							}else{
								ret=insert_symbol((yyvsp[-1].string),0);
								strcat((yyval.string),"F");
							}	
//				sprintf(Tempparameter[Tempindex++],"%s",$3);
				sprintf((yyval.string),"%s",(yyvsp[-3].string));		
/*
					if(strcmp($4,"float32")==0)
						strcat($$,"F");
					else if (strcmp($4,"int")==0)
						strcat($$,"I");	
*/					

				}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 338 "compiler_hw3.y" /* yacc.c:1646  */
    {
					strcat((yyval.string),"");//不加會有warning 其實沒作用
				}
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 346 "compiler_hw3.y" /* yacc.c:1646  */
    {//進到if表示新label開始
							labeltop++;//pointer往前
							labelStack[labeltop]=globallabel;//Stack內的暫存label=我的label
							globallabel++;
						}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 351 "compiler_hw3.y" /* yacc.c:1646  */
    {
							//printf("-----------------------------asdsad\n");
							labeltop--;
						
						}
#line 1763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 359 "compiler_hw3.y" /* yacc.c:1646  */
    {								
							fprintf(fp,"\tgoto EXIT_%d\n",labelStack[labeltop]);
							fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
						}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 363 "compiler_hw3.y" /* yacc.c:1646  */
    {
							fprintf(fp,"EXIT_%d:\n",labelStack[labeltop]);
							//nowlabel--;//結束這個scope，要還原到上個scope的
						}
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 367 "compiler_hw3.y" /* yacc.c:1646  */
    {//沒有else的情況，可以想成else的do something 沒東西
											linecount++;
											//printf("-----------------------------label_%d\n",labelStack[labeltop]);
											fprintf(fp,"\tgoto EXIT_%d\n",labelStack[labeltop]);
											fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
											fprintf(fp,"EXIT_%d:\n",labelStack[labeltop]);
						}
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 374 "compiler_hw3.y" /* yacc.c:1646  */
    {//EOF
											linecount++;
											fprintf(fp,"\tgoto EXIT_%d\n",labelStack[labeltop]);
											fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
											fprintf(fp,"EXIT_%d:\n",labelStack[labeltop]);
						}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 391 "compiler_hw3.y" /* yacc.c:1646  */
    {//初始化值後，準備進入for
																labeltop++;//pointer往前
																labelStack[labeltop]=globallabel;//Stack內的暫存label=我的label
																globallabel++;	
																//For label的數字會跟裡面的if數字一樣
																fprintf(fp,"FORLabel_%d:\n",labelStack[labeltop]);
															}
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 398 "compiler_hw3.y" /* yacc.c:1646  */
    {//for loop 的 body結束後才會進來
																labeltop--;
															}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 401 "compiler_hw3.y" /* yacc.c:1646  */
    {//準備進入for
																labeltop++;//pointer往前
																labelStack[labeltop]=globallabel;//Stack內的暫存label=我的label
																globallabel++;	
																//For label的數字會跟裡面的if數字一樣
																fprintf(fp,"FORLabel_%d:\n",labelStack[labeltop]);
															}
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 408 "compiler_hw3.y" /* yacc.c:1646  */
    {
																fprintf(fp,"\tgoto FORLabel_%d\n",labelStack[labeltop]);
																fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
															}
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 413 "compiler_hw3.y" /* yacc.c:1646  */
    {
													//---------------------------本來ID做的事		
													int ret=-1;
													CheckUndefined = 1;
													ret=lookup_symbol((yyvsp[-2].string));
													CheckUndefined = 0;
													if(ret==-1)
														printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-2].string),linecount);
													else{
															if(strcmp(table[ret]->type,"float32")==0)
															{
																insert_value(ret,(table[ret]->f_val)+1,0);
																char *tmp=malloc(30);
																fprintf(fp,"\tfload %d\n",ret);
																fprintf(fp,"\tldc 1.0\n");
																fprintf(fp,"\tfsub\n");
																fprintf(fp,"\tfstore %d\n",ret);
															}
															else if(strcmp(table[ret]->type,"int")==0)
															{
																insert_value(ret,0.0,(table[ret]->i_val)+1);
																char *tmp=malloc(30);
																fprintf(fp,"\tiload %d\n",ret);
																fprintf(fp,"\tldc 1\n");
																fprintf(fp,"\tisub\n");
																fprintf(fp,"\tistore %d\n",ret);
															}
														}
													//------------------------------------------------------------					
													fprintf(fp,"\tgoto FORLabel_%d\n",labelStack[labeltop]);
													fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
													labeltop--;
												}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 446 "compiler_hw3.y" /* yacc.c:1646  */
    {
													//---------------------------本來ID做的事		
													int ret=-1;
													CheckUndefined = 1;
													ret=lookup_symbol((yyvsp[-2].string));
													CheckUndefined = 0;
													if(ret==-1)
														printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-2].string),linecount);
													else{
															if(strcmp(table[ret]->type,"float32")==0)
															{
																insert_value(ret,(table[ret]->f_val)+1,0);
																char *tmp=malloc(30);
																fprintf(fp,"\tfload %d\n",ret);
																fprintf(fp,"\tldc 1.0\n");
																fprintf(fp,"\tfadd\n");
																fprintf(fp,"\tfstore %d\n",ret);
															}
															else if(strcmp(table[ret]->type,"int")==0)
															{
																insert_value(ret,0.0,(table[ret]->i_val)+1);
																char *tmp=malloc(30);
																fprintf(fp,"\tiload %d\n",ret);
																fprintf(fp,"\tldc 1\n");
																fprintf(fp,"\tiadd\n");
																fprintf(fp,"\tistore %d\n",ret);
															}
														}
													//------------------------------------------------------------					
													fprintf(fp,"\tgoto FORLabel_%d\n",labelStack[labeltop]);
													fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
													labeltop--;
												}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 483 "compiler_hw3.y" /* yacc.c:1646  */
    { 
		sprintf((yyval.val).buf,"%s","");//先清空	
	
		if ((yyvsp[-2].val).type == 1 && (yyvsp[0].val).type == 1) {//integer
                        (yyval.val).type = 1;
                        (yyval.val).i_val = (yyvsp[-2].val).i_val + (yyvsp[0].val).i_val;
				
			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			strcat((yyval.val).buf, "\tiadd\n");
			
                      } else {//double
                        double v1 = (yyvsp[-2].val).type == 1 ? (double)(yyvsp[-2].val).i_val
                                                   : (yyvsp[-2].val).f_val;
                        double v2 = (yyvsp[0].val).type == 1 ? (double)(yyvsp[0].val).i_val
                                                   : (yyvsp[0].val).f_val;
                        (yyval.val).type = 0;
                        (yyval.val).f_val = v1 + v2;


			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			if((yyvsp[-2].val).type == 1){strcat((yyval.val).buf,"\ti2f\n");}//如果是int要轉成float
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			if((yyvsp[0].val).type == 1)strcat((yyval.val).buf,"\ti2f\n");
			strcat((yyval.val).buf, "\tfadd\n");
                      }
						printf("%s\n","ADD");
						}
#line 1954 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 511 "compiler_hw3.y" /* yacc.c:1646  */
    {
			sprintf((yyval.val).buf,"%s","");//先清空	
			
			if ((yyvsp[-2].val).type == 1 && (yyvsp[0].val).type == 1) {//integer
                        (yyval.val).type = 1;
                        (yyval.val).i_val = (yyvsp[-2].val).i_val - (yyvsp[0].val).i_val;

			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			strcat((yyval.val).buf, "\tisub\n");
                      } else {//double
                        double v1 = (yyvsp[-2].val).type == 1 ? (double)(yyvsp[-2].val).i_val
                                                   : (yyvsp[-2].val).f_val;
                        double v2 = (yyvsp[0].val).type == 1 ? (double)(yyvsp[0].val).i_val
                                                   : (yyvsp[0].val).f_val;
                        (yyval.val).type = 0;
                        (yyval.val).f_val = v1 - v2;

			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			if((yyvsp[-2].val).type == 1){strcat((yyval.val).buf,"\ti2f\n");}//如果是int要轉成float
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			if((yyvsp[0].val).type == 1)strcat((yyval.val).buf,"\ti2f\n");
			strcat((yyval.val).buf, "\tfsub\n");
                      }
						printf("%s\n","SUB");
						}
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 537 "compiler_hw3.y" /* yacc.c:1646  */
    { 
			sprintf((yyval.val).buf,"%s","");//先清空	
			
			if ((yyvsp[-2].val).type == 1 && (yyvsp[0].val).type == 1) {//integer
                        (yyval.val).type = 1;
                        (yyval.val).i_val = (yyvsp[-2].val).i_val * (yyvsp[0].val).i_val;

			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			strcat((yyval.val).buf, "\timul\n");
                      } else {//double
                        double v1 = (yyvsp[-2].val).type == 1 ? (double)(yyvsp[-2].val).i_val
                                                   : (yyvsp[-2].val).f_val;
                        double v2 = (yyvsp[0].val).type == 1 ? (double)(yyvsp[0].val).i_val
                                                   : (yyvsp[0].val).f_val;
                        (yyval.val).type = 0;
                        (yyval.val).f_val = v1 * v2;

			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			if((yyvsp[-2].val).type == 1){strcat((yyval.val).buf,"\ti2f\n");}//如果是int要轉成float
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			if((yyvsp[0].val).type == 1)strcat((yyval.val).buf,"\ti2f\n");
			strcat((yyval.val).buf, "\tfmul\n");
                      }
		
							printf("%s\n","MUL");
						}
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 564 "compiler_hw3.y" /* yacc.c:1646  */
    { 
			sprintf((yyval.val).buf,"%s","");//先清空	

			if ((yyvsp[-2].val).type == 1 && (yyvsp[0].val).type == 1) {//integer
                        (yyval.val).type = 1;
						if((yyvsp[0].val).i_val==0)
							printf("<ERROR> The divisor can’t be 0 (line %d)\n",linecount);
						else
                        				(yyval.val).i_val = (yyvsp[-2].val).i_val / (yyvsp[0].val).i_val;

			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			strcat((yyval.val).buf, "\tidiv\n");
                      } else {//double
                        double v1 = (yyvsp[-2].val).type == 1 ? (double)(yyvsp[-2].val).i_val
                                                   : (yyvsp[-2].val).f_val;
                        double v2 = (yyvsp[0].val).type == 1 ? (double)(yyvsp[0].val).i_val
                                                   : (yyvsp[0].val).f_val;
                        (yyval.val).type = 0;
						if(v2==0)
							printf("<ERROR> The divisor can’t be 0 (line %d)\n",linecount);
						else
                        				(yyval.val).f_val = v1 / v2;

			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			if((yyvsp[-2].val).type == 1){strcat((yyval.val).buf,"\ti2f\n");}//如果是int要轉成float
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			if((yyvsp[0].val).type == 1)strcat((yyval.val).buf,"\ti2f\n");
			strcat((yyval.val).buf, "\tfdiv\n");
                      }
							printf("%s\n","DIV");}
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 595 "compiler_hw3.y" /* yacc.c:1646  */
    { 
			sprintf((yyval.val).buf,"%s","");//先清空
			
			if ((yyvsp[-2].val).type == 1 && (yyvsp[0].val).type == 1) {//integer
                        (yyval.val).type = 1;
                        (yyval.val).i_val = (yyvsp[-2].val).i_val % (yyvsp[0].val).i_val;
						printf("%s\n","MOD");
			
			strcat((yyval.val).buf,(yyvsp[-2].val).buf);
			strcat((yyval.val).buf,(yyvsp[0].val).buf);
			strcat((yyval.val).buf, "\tirem\n");
                      } else {//double
						printf("ERROR:The modulo does not involve any floating-points (line %d)\n",linecount);
                     				 (yyval.val).i_val=0;(yyval.val).type = 1;
				}

						}
#line 2075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 612 "compiler_hw3.y" /* yacc.c:1646  */
    {
						sprintf((yyval.val).buf,"%s","");//先清空
						int ret=-1;
						CheckUndefined = 1;
						ret=lookup_symbol((yyvsp[-1].string));
						CheckUndefined = 0;
						if(ret==-1)
							printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-1].string),linecount);
						else{
								if(strcmp(table[ret]->type,"float32")==0){
								insert_value(ret,(table[ret]->f_val)+1,0);
								//id+1;
								char *tmp=malloc(30);	
								sprintf(tmp,"\tfload %d\n",ret);
								strcat( (yyval.val).buf,tmp);
								
								strcat((yyval.val).buf,"\tldc 1.0\n");
								strcat((yyval.val).buf,"\tfadd\n");
								sprintf(tmp,"\tfstore %d\n",ret);
								strcat((yyval.val).buf,tmp);
								}
								else if(strcmp(table[ret]->type,"int")==0){
								insert_value(ret,0.0,(table[ret]->i_val)+1);
								char *tmp=malloc(30);	
								sprintf(tmp,"\tiload %d\n",ret);
								strcat( (yyval.val).buf,tmp);
								
								strcat((yyval.val).buf,"\tldc 1\n");
								strcat((yyval.val).buf,"\tiadd\n");
								sprintf(tmp,"\tistore %d\n",ret);
								strcat((yyval.val).buf,tmp);
								}
							}
						}
#line 2114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 646 "compiler_hw3.y" /* yacc.c:1646  */
    {
						sprintf((yyval.val).buf,"%s","");//先清空
						int ret=-1;
						CheckUndefined = 1;
						ret=lookup_symbol((yyvsp[-1].string));
						CheckUndefined = 0;
						if(ret==-1)
							printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-1].string),linecount);
						else{
								if(strcmp(table[ret]->type,"float32")==0){
								insert_value(ret,(table[ret]->f_val)-1,0);
								//id+1;
								char *tmp=malloc(30);	
								sprintf(tmp,"\tfload %d\n",ret);
								strcat( (yyval.val).buf,tmp);
								
								strcat((yyval.val).buf,"\tldc 1.0\n");
								strcat((yyval.val).buf,"\tfsub\n");
								sprintf(tmp,"\tfstore %d\n",ret);
								strcat((yyval.val).buf,tmp);
								}
								else if(strcmp(table[ret]->type,"int")==0){
								insert_value(ret,0.0,(table[ret]->i_val)-1);
								char *tmp=malloc(30);	
								sprintf(tmp,"\tiload %d\n",ret);
								strcat( (yyval.val).buf,tmp);
								
								strcat((yyval.val).buf,"\tldc 1\n");
								strcat((yyval.val).buf,"\tisub\n");
								sprintf(tmp,"\tistore %d\n",ret);
								strcat((yyval.val).buf,tmp);
								}
							}
						}
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 680 "compiler_hw3.y" /* yacc.c:1646  */
    {(yyval.val).i_val = (yyvsp[0].val).i_val*(-1); }
#line 2159 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 681 "compiler_hw3.y" /* yacc.c:1646  */
    { 
							if((yyvsp[-1].val).type==1)
								{(yyval.val).i_val = (yyvsp[-1].val).i_val;(yyval.val).type=1;}
							else
								{(yyval.val).f_val = (yyvsp[-1].val).f_val;(yyval.val).type=0;}

							sprintf((yyval.val).buf,"%s",(yyvsp[-1].val).buf);
 
						}
#line 2173 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 690 "compiler_hw3.y" /* yacc.c:1646  */
    {				
							sprintf((yyval.val).buf,"%s","");//先清空			
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol((yyvsp[0].string));
							CheckUndefined = 0;
							if(ret==-1)
								printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[0].string),linecount);
							else{
								if(strcmp(table[ret]->type,"float32")==0)
								{
									(yyval.val).f_val=table[ret]->f_val;
									(yyval.val).type=0;
									char *tmp=malloc(30);
									sprintf(tmp,"\tfload %d\n",ret);
									strcat( (yyval.val).buf,tmp);
								}
								else if(strcmp(table[ret]->type,"int")==0)
								{
									(yyval.val).i_val=table[ret]->i_val;
									(yyval.val).type=1;
									char *tmp=malloc(30);
									sprintf(tmp,"\tiload %d\n",ret);
									strcat( (yyval.val).buf,tmp);
								}
							//NEW
							printidscope=1;
							out=table[ret]->scope_depth;
							}
						}
#line 2208 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 720 "compiler_hw3.y" /* yacc.c:1646  */
    {(yyval.val).i_val = (yyvsp[0].val).i_val; (yyval.val).type=1;    
								char *tmp=malloc(30);
								sprintf(tmp,"\tldc %d\n",(yyvsp[0].val).i_val);
								strcat( (yyval.val).buf,tmp);
						}
#line 2218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 725 "compiler_hw3.y" /* yacc.c:1646  */
    {(yyval.val).f_val = (yyvsp[0].val).f_val; (yyval.val).type=0;  
								char *tmp=malloc(30);
								sprintf(tmp,"\tldc %lf\n",(yyvsp[0].val).f_val);
								strcat( (yyval.val).buf,tmp);
						}
#line 2228 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 730 "compiler_hw3.y" /* yacc.c:1646  */
    {
							if((yyvsp[0].val).type==1)
								{(yyval.val).i_val = (yyvsp[0].val).i_val;(yyval.val).type=1;}
							else
								{(yyval.val).f_val = (yyvsp[0].val).f_val;(yyval.val).type=0;}
							sprintf((yyval.val).buf,"%s",(yyvsp[0].val).buf);
						}
#line 2240 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 741 "compiler_hw3.y" /* yacc.c:1646  */
    {
				sprintf((yyval.val).buf,"\tinvokestatic main/%s",(yyvsp[-3].string));//call function
				//找到 type 和 argument
				int ret ;
				ret=lookup_symbol((yyvsp[-3].string));
				strcat((yyval.val).buf,table[ret]->sign);
				}
#line 2252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 750 "compiler_hw3.y" /* yacc.c:1646  */
    { 
								fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束要寫入
							}
#line 2260 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 753 "compiler_hw3.y" /* yacc.c:1646  */
    { 
				fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束要寫入
			}
#line 2268 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 756 "compiler_hw3.y" /* yacc.c:1646  */
    {sprintf((yyval.val).buf," ");}
#line 2274 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 762 "compiler_hw3.y" /* yacc.c:1646  */
    {//>
							sprintf((yyval.val).buf,"%s","");//先清空
							int ret;
							if((yyvsp[-2].val).type==1&&(yyvsp[0].val).type==1)// compare between int
							{
								ret=((yyvsp[-2].val).i_val>(yyvsp[0].val).i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tisub\n");
								sprintf(tmp,"\tifle Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
						
								
							}
							else if((yyvsp[-2].val).type==0&&(yyvsp[0].val).type==0)// compare between float
							{
								ret=((yyvsp[-2].val).f_val>(yyvsp[0].val).f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tfsub\n");
								sprintf(tmp,"\tifle Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
								
							else
								printf("<ERROR>:compare between different type (line %d)\n",linecount);						

						}
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 802 "compiler_hw3.y" /* yacc.c:1646  */
    {//<
							sprintf((yyval.val).buf,"%s","");//先清空
							int ret;
							if((yyvsp[-2].val).type==1&&(yyvsp[0].val).type==1)
							{
								ret=((yyvsp[-2].val).i_val<(yyvsp[0].val).i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tisub\n");
								sprintf(tmp,"\tifge Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
							else if((yyvsp[-2].val).type==0&&(yyvsp[0].val).type==0)
							{
								ret=((yyvsp[-2].val).f_val<(yyvsp[0].val).f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tfsub\n");
								sprintf(tmp,"\tifge Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
								
							else
								printf("<ERROR>:compare between different type (line %d)\n",linecount);						

						}
#line 2362 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 840 "compiler_hw3.y" /* yacc.c:1646  */
    {//>=
							sprintf((yyval.val).buf,"%s","");//先清空
							int ret;
							if((yyvsp[-2].val).type==1&&(yyvsp[0].val).type==1)
							{
								ret=((yyvsp[-2].val).i_val>=(yyvsp[0].val).i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tisub\n");
								sprintf(tmp,"\tiflt Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
							else if((yyvsp[-2].val).type==0&&(yyvsp[0].val).type==0)
							{
								ret=((yyvsp[-2].val).f_val>=(yyvsp[0].val).f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tfsub\n");
								sprintf(tmp,"\tiflt Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
								
							else
								printf("<ERROR>:compare between different type (line %d)\n",linecount);						

						}
#line 2405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 878 "compiler_hw3.y" /* yacc.c:1646  */
    {//<=
							sprintf((yyval.val).buf,"%s","");//先清空
							int ret;
							if((yyvsp[-2].val).type==1&&(yyvsp[0].val).type==1)
							{
								ret=((yyvsp[-2].val).i_val<=(yyvsp[0].val).i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tisub\n");
								sprintf(tmp,"\tifgt Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
							else if((yyvsp[-2].val).type==0&&(yyvsp[0].val).type==0)
							{
								ret=((yyvsp[-2].val).f_val<=(yyvsp[0].val).f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tfsub\n");
								sprintf(tmp,"\tifgt Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
								
							else
								printf("<ERROR>:compare between different type (line %d)\n",linecount);						

						}
#line 2448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 916 "compiler_hw3.y" /* yacc.c:1646  */
    {//==
							sprintf((yyval.val).buf,"%s","");//先清空
							int ret;
							if((yyvsp[-2].val).type==1&&(yyvsp[0].val).type==1)
							{
								ret=((yyvsp[-2].val).i_val==(yyvsp[0].val).i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	

								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tisub\n");
								sprintf(tmp,"\tifne Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);		
							}
							else if((yyvsp[-2].val).type==0&&(yyvsp[0].val).type==0)
							{
								ret=((yyvsp[-2].val).f_val==(yyvsp[0].val).f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tfsub\n");
								sprintf(tmp,"\tifne Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
								
							else
								printf("<ERROR>:compare between different type (line %d)\n",linecount);						

						}
#line 2492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 955 "compiler_hw3.y" /* yacc.c:1646  */
    {//!=
							sprintf((yyval.val).buf,"%s","");//先清空
							int ret;
							if((yyvsp[-2].val).type==1&&(yyvsp[0].val).type==1)
							{
								ret=((yyvsp[-2].val).i_val!=(yyvsp[0].val).i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tisub\n");
								sprintf(tmp,"\tifeq Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
							else if((yyvsp[-2].val).type==0&&(yyvsp[0].val).type==0)
							{
								ret=((yyvsp[-2].val).f_val!=(yyvsp[0].val).f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	

								char* tmp=malloc(30);
								strcat((yyval.val).buf,(yyvsp[-2].val).buf);
								strcat((yyval.val).buf,(yyvsp[0].val).buf);
								strcat((yyval.val).buf, "\tfsub\n");
								sprintf(tmp,"\tifeq Label_%d\n",labelStack[labeltop]);	
								strcat((yyval.val).buf,tmp);	
								fprintf(fp,"%s",(yyval.val).buf);	
							}
								
							else
								printf("<ERROR>:compare between different type (line %d)\n",linecount);						

						}
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 998 "compiler_hw3.y" /* yacc.c:1646  */
    {
							printf("ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol((yyvsp[-2].string));
							CheckUndefined = 0;
							if(ret==-1)
								printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-2].string),linecount);
							else{
								if(strcmp(table[ret]->type,"float32")==0){//如果ID是float
									if((yyvsp[0].val).type==0)//如果arith是float
									{
										insert_value(ret,(yyvsp[0].val).f_val,0);
										fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
										fprintf(fp, "\tfstore %d\n",ret);
										
									}
									else//如果arith是int
									{
										insert_value(ret,(float)(yyvsp[0].val).i_val,0);
										fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
										fprintf(fp, "\ti2f\n");
										fprintf(fp, "\tistore %d\n",ret);
		
									}

								}
								else if(strcmp(table[ret]->type,"int")==0){//ID是int
									if((yyvsp[0].val).type==0)//如果arith是float
									{
										insert_value(ret,0.0,(int)(yyvsp[0].val).f_val);
										fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
										fprintf(fp, "\tf2i\n");
										fprintf(fp, "\tistore %d\n",ret);										
									}
									else//如果arith是int
									{
										insert_value(ret,0.0,(yyvsp[0].val).i_val);
										fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
										fprintf(fp, "\tistore %d\n",ret);		
									}
								
								}
							}

							}
#line 2587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1044 "compiler_hw3.y" /* yacc.c:1646  */
    {
							printf("ADD_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol((yyvsp[-2].string));
							CheckUndefined = 0;
							if(ret==-1)
								printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-2].string),linecount);
							else{
								if(strcmp(table[ret]->type,"float32")==0){
								if((yyvsp[0].val).type==0){//ID是float且arith是float
									table[ret]->f_val +=(yyvsp[0].val).f_val;

									//x+arith
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入

									fprintf(fp,"\tfadd\n");
									fprintf(fp, "\tfstore %d\n",ret);									
								}
								else{//ID是float且arith是int
									table[ret]->f_val +=(double)(yyvsp[0].val).i_val;

									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									//x+arith
									fprintf(fp,"\ti2f\n");
									fprintf(fp,"\tfadd\n");
									fprintf(fp,"\tfstore %d\n",ret);	
								}
								}
								else if(strcmp(table[ret]->type,"int")==0){
								if((yyvsp[0].val).type==1){//ID是int且arith是int
									table[ret]->i_val +=(yyvsp[0].val).i_val;

									//x+arith
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tiadd\n");
									fprintf(fp, "\tistore %d\n",ret);		
								}
								else{//ID是int且arith是float
									//printf("<ERROR>:assign float to int variable (line %d)\n",linecount);

									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									//x+arith
									fprintf(fp,"\tf2i\n");
									fprintf(fp,"\tiadd\n");
									fprintf(fp, "\tistore %d\n",ret);	
								}
								}

							}
							}
#line 2647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1099 "compiler_hw3.y" /* yacc.c:1646  */
    {
							printf("SUB_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol((yyvsp[-2].string));
							CheckUndefined = 0;
							if(ret==-1)
								printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-2].string),linecount);
							else{
							if(strcmp(table[ret]->type,"float32")==0){
								if((yyvsp[0].val).type==0){//ID是float，arith是float
									table[ret]->f_val -=(yyvsp[0].val).f_val;

									//x-arith
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tfsub\n");
									fprintf(fp, "\tfstore %d\n",ret);	
								}
								else{//ID是float，arith是int
									table[ret]->f_val -=(double)(yyvsp[0].val).i_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\ti2f\n");
									fprintf(fp,"\tfsub\n");
									fprintf(fp,"\tfstore %d\n",ret);	
								}

							}
							else if(strcmp(table[ret]->type,"int")==0){
								if((yyvsp[0].val).type==1){//ID是int，arith是int
									table[ret]->i_val -=(yyvsp[0].val).i_val;
									
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tisub\n");
									fprintf(fp, "\tistore %d\n",ret);
								}	
								else{//ID是int，arith是float
									//printf("<ERROR>:assign float to int variable (line %d)\n",linecount);
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tf2i\n");
									fprintf(fp,"\tisub\n");
									fprintf(fp, "\tistore %d\n",ret);	
								}
							}
								

							}
							}
#line 2703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1150 "compiler_hw3.y" /* yacc.c:1646  */
    {
							printf("MUL_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol((yyvsp[-2].string));
							CheckUndefined = 0;
							if(ret==-1)
								printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-2].string),linecount);
							else{
							if(strcmp(table[ret]->type,"float32")==0){
								if((yyvsp[0].val).type==0){//ID是float，arith是float
									table[ret]->f_val *=(yyvsp[0].val).f_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tfmul\n");
									fprintf(fp, "\tfstore %d\n",ret);	
								}
								else{//ID是float，arith是int
									table[ret]->f_val *=(double)(yyvsp[0].val).i_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\ti2f\n");
									fprintf(fp,"\tfmul\n");
									fprintf(fp,"\tfstore %d\n",ret);	
								}

							}
							else if(strcmp(table[ret]->type,"int")==0){
								if((yyvsp[0].val).type==1){//ID是int，arith是int
									table[ret]->i_val *=(yyvsp[0].val).i_val;
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\timul\n");
									fprintf(fp, "\tistore %d\n",ret);
								}	
								else{//ID是int，arith是float
									//printf("<ERROR>:assign float to int variable (line %d)\n",linecount);
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tf2i\n");
									fprintf(fp,"\timul\n");
									fprintf(fp, "\tistore %d\n",ret);	
								}
							}
							}
							}
#line 2754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1196 "compiler_hw3.y" /* yacc.c:1646  */
    {
							printf("DIV_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol((yyvsp[-2].string));
							CheckUndefined = 0;
							if(ret==-1)
								printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-2].string),linecount);
							else{
							if(strcmp(table[ret]->type,"float32")==0){
								if((yyvsp[0].val).type==0){//ID是float，arith是float
									table[ret]->f_val /=(yyvsp[0].val).f_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tfdiv\n");
									fprintf(fp, "\tfstore %d\n",ret);	
								}
								else{//ID是float，arith是int
									table[ret]->f_val /=(double)(yyvsp[0].val).i_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\ti2f\n");
									fprintf(fp,"\tfdiv\n");
									fprintf(fp,"\tfstore %d\n",ret);	
								}

							}
							else if(strcmp(table[ret]->type,"int")==0){
								if((yyvsp[0].val).type==1){//ID是int，arith是int
									table[ret]->i_val /=(yyvsp[0].val).i_val;
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tidiv\n");
									fprintf(fp, "\tistore %d\n",ret);
								}	
								else{//ID是int，arith是float
									//printf("<ERROR>:assign float to int variable (line %d)\n",linecount);
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tf2i\n");
									fprintf(fp,"\tidiv\n");
									fprintf(fp, "\tistore %d\n",ret);	
								}
							}
							}
						}
#line 2805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1242 "compiler_hw3.y" /* yacc.c:1646  */
    {
							printf("MOD_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol((yyvsp[-2].string));
							CheckUndefined = 0;
							if(ret==-1)
								printf("<ERROR>:Undefined variable %s (line %d)\n",(yyvsp[-2].string),linecount);
							else{
								if(strcmp(table[ret]->type,"int")==0&&(yyvsp[0].val).type==1){
									table[ret]->i_val %=(yyvsp[0].val).i_val;
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",(yyvsp[0].val).buf);//所有arith結束都要寫入
									fprintf(fp,"\tirem\n");
									fprintf(fp, "\tistore %d\n",ret);
								}
								else{
									printf("<ERROR>:assign float to int variable (line %d)\n",linecount);
								} 
							}
							}
#line 2831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1268 "compiler_hw3.y" /* yacc.c:1646  */
    {
//							printf("declare : %s %s\n",$2,$3) ;
							int ret;
							if(strcmp((yyvsp[0].string),"int")==0){
								ret=insert_symbol((yyvsp[-1].string),1);
								fprintf(fp, "\tldc %d\n",0);
								fprintf(fp, "\tistore %d\n",ret);
							}else{
								ret=insert_symbol((yyvsp[-1].string),0);
								fprintf(fp, "\tldc %f\n",0.0);
								fprintf(fp, "\tfstore %d\n",ret);
							}
						}
#line 2849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1281 "compiler_hw3.y" /* yacc.c:1646  */
    {
				if(strcmp((yyvsp[-2].string),"float32")==0){//float
					int ret;
//					printf("declare : %s %s %lf\n",$2,$3,$5.f_val) ;
					ret = insert_symbol((yyvsp[-3].string),0);
					insert_value(ret,(yyvsp[0].val).f_val,0);
					
					fprintf(fp,"%s",(yyvsp[0].val).buf);//有關arith結束都要寫入
					fprintf(fp, "\tfstore %d\n",ret);					
				}else if(strcmp((yyvsp[-2].string),"int")==0){//int
					int ret;
//					printf("declare : %s %s %d\n",$2,$3,$5.i_val) ;
					ret = insert_symbol((yyvsp[-3].string),1);
					insert_value(ret,0.0,(yyvsp[0].val).i_val);

					fprintf(fp,"%s",(yyvsp[0].val).buf);//有關arith結束都要寫入
					fprintf(fp, "\tistore %d\n",ret);
					}
			}
#line 2873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1303 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string);}
#line 2879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1304 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1305 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1308 "compiler_hw3.y" /* yacc.c:1646  */
    { 
				sprintf((yyval.val).buf,"%s",(yyvsp[0].val).buf);
				if((yyvsp[0].val).type==0)//double
				{
					(yyval.val).type=0;
					(yyval.val).f_val=(yyvsp[0].val).f_val;
				}
				else{//int
					(yyval.val).type=1;
					(yyval.val).i_val=(yyvsp[0].val).i_val;
				}
			}
#line 2908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1324 "compiler_hw3.y" /* yacc.c:1646  */
    {

							printf("PRINT : %s\n",(yyvsp[-1].string)) ;
							fprintf(fp, "\tldc \"%s\"\n",(yyvsp[-1].string));
							fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
							fprintf(fp, "\tswap\n");
							fprintf(fp, "\tinvokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
						}
#line 2921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1332 "compiler_hw3.y" /* yacc.c:1646  */
    {
							printf("PRINTLN : %s\n",(yyvsp[-1].string)) ;
							fprintf(fp, "\tldc \"%s\"\n",(yyvsp[-1].string));
							fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
							fprintf(fp, "\tswap\n");
							fprintf(fp, "\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");

						}
#line 2934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1341 "compiler_hw3.y" /* yacc.c:1646  */
    {	
							
							fprintf(fp,"%s",(yyvsp[-1].val).buf);//有關arith結束都要寫入
										
							fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
							fprintf(fp, "\tswap\n");
														                  
							if((yyvsp[-1].val).type==1)//int
								{	
									fprintf(fp, "\tinvokevirtual java/io/PrintStream/print(I)V\n");	
									if(printidscope==0)//要印出數字
										{	
                 									printf("PRINT : %d\n", (yyvsp[-1].val).i_val);
										}
									else//印出id
										printf("PRINT : %d (Block:%d)\n", (yyvsp[-1].val).i_val,out);
								}
                 					else
								{	
									fprintf(fp, "\tinvokevirtual java/io/PrintStream/print(F)V\n");	
									if(printidscope==0)
                 								printf("PRINT : %lf\n", (yyvsp[-1].val).f_val);
									else
										printf("PRINT : %lf (Block:%d)\n", (yyvsp[-1].val).f_val,out);
								}
						printidscope=0;
						}
#line 2966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1369 "compiler_hw3.y" /* yacc.c:1646  */
    {	
							fprintf(fp,"%s",(yyvsp[-1].val).buf);//有關arith結束都要寫入
							//printf("--------------------------------------------\n%s-----------------------------------------",$3.buf);					
							fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
							fprintf(fp, "\tswap\n");
								
	                  
							if((yyvsp[-1].val).type==1)//int
								{	
									fprintf(fp, "\tinvokevirtual java/io/PrintStream/println(I)V\n");	
									if(printidscope==0)
                 								printf("PRINTLN : %d\n", (yyvsp[-1].val).i_val);
									else
										printf("PRINTLN : %d (Block:%d)\n", (yyvsp[-1].val).i_val,out);
								}
                 					else
								{	

									fprintf(fp, "\tinvokevirtual java/io/PrintStream/println(F)V\n");	
									if(printidscope==0)
                 								printf("PRINTLN : %lf\n", (yyvsp[-1].val).f_val);
									else
										printf("PRINTLN : %lf (Block:%d)\n", (yyvsp[-1].val).f_val,out);
								}
						printidscope=0;
						}
#line 2997 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3001 "y.tab.c" /* yacc.c:1646  */
      default: break;
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
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
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

#if !defined yyoverflow || YYERROR_VERBOSE
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
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1398 "compiler_hw3.y" /* yacc.c:1906  */



/* C code section */
int main(int argc, char** argv)
{
    	yylineno = 0;
	fp= fopen("Computer.j", "w" );	
	if( fp == NULL )  {
		fprintf( stdout, "Open  file  error\n" );
		exit(-1);
	}
	//把lablestack設成-1
	int i;
	for(i=0;i<256;i++)labelStack[i]=-1;
	labeltop=-1;
	
	//----basic program --------------------
	
	fprintf(fp, ".class public main\n");
	fprintf(fp, ".super java/lang/Object\n");
	fprintf(fp, ".method public static main([Ljava/lang/String;)V\n");
	fprintf(fp, ".limit stack 100\n");
	fprintf(fp, ".limit locals 100\n");
	
    	yyparse();
if(definefunct==0){
	fprintf(fp, "\treturn\n");
	fprintf(fp, ".end method\n");
	}
	fclose(fp);
	//------------------------------------------------
	printf("\nParse over, the line number is %d\n",linecount);
	printf("\ncomment: %d lines\n",commentline);

	if(CreateTableFlag==1)//如果有建立symbol table
		dump_symbol();

	if(ERROR==1){//有錯誤不要產生.j檔
		remove("Computer.j");

	}

	
    return 0;
}



void create_symbol() 
{
	
	CreateTableFlag=1;
	printf("Create a symbol table\n");
	int i;
	for(i=0;i<TableSize;i++){
	table[i]= malloc(sizeof(struct symbol_table));
	table[i]->type=NULL;
	table[i]->id=NULL;
	table[i]->vaild=0;
	table[i]->scope_depth=-1;

	}	

}
int insert_symbol(char* id , int type) {
	
	if(CreateTableFlag==0){//not create table yet
		create_symbol();
		table[0]->id = malloc(strlen(id)+1);
		strcpy(table[0]->id,id);
		table[0]->vaild = 1 ;//vaild表示有symbol在表中
		printf("Insert a symbol: %s\n",id);
		if(type==1)//int
			table[0]->type="int";
		else if(type==0)//float
			table[0]->type="float32";
		else if(type==2)//void
			table[0]->type="void";
		//New
		table[0]->scope_depth=NowDepth;

		return 0;
	}
	else{
		if(lookup_symbol(id)==-1){//not declare yet(id not in symbol table)
		int i;
		
		
			printf("----------------%s\n",Temptable[0]->id);
		for(i=0;i<TableSize;i++)//look for space to place id
			if(table[i]->vaild==0){
				table[i]->id = malloc(strlen(id)+1);
				strcpy(table[i]->id,id);
				table[i]->vaild = 1 ;//vaild表示有symbol在表中
				printf("Insert a symbol: %s\n",id);
				
		                if(type==1)//int
	                	        table[i]->type="int";
        		        else if(type==0)//float
                        		table[i]->type="float32";
				else if(type==2)//void
					table[i]->type="void";
				//New
				table[i]->scope_depth=NowDepth;
				
				return i;
			}
		}
	}
	return -1;

}

void insert_value(int ret , double f_val, int i_val){
		if(CreateTableFlag==0)return ;
		if(ret==-1)
			return;
		else{
			if(table[ret]->vaild==1&&strcmp(table[ret]->type,"float32")==0)
			{
				table[ret]->f_val=f_val;
			}
			else if(table[ret]->vaild==1&&strcmp(table[ret]->type,"int")==0)	
			{

				table[ret]->i_val=i_val;
			}
		
		}
		return;

}
int lookup_symbol(char *id) {//command=0:declare command=1:取出var
	int smallest=-1;//NEW先設定最小scope=-1(沒有defined)
	int i;
	//查看是否undefined
	if(CreateTableFlag==0)return -1;
	if(CheckUndefined==1){//表示是要取出id,是非宣告狀態（宣告狀態是要去看下面的redefined）
		for(i=0;i<TableSize;i++)
			//NEW  只能取 <= 目前 scope的人 但是要看最小的，所以for要走完
                        if(table[i]->vaild==1&&strcmp(table[i]->id,id)==0&&table[i]->scope_depth<=NowDepth)
                        	{
					if(smallest<=i)smallest=i;
				}//會進來表示有defined
	
//        	printf("<ERROR>:Undefined variable %s (line %d)\n",id,linecount);
		return smallest;//沒有defined
	}
	//查看是否redefined
	for(i=0;i<TableSize;i++){
			//NEW 會進到這裡表示是宣告				
			if(table[i]->vaild==1&&strcmp(table[i]->id,id)==0&&table[i]->scope_depth==NowDepth){		
			printf("<ERROR>:Redefined variable %s,table index:%d (line %d)\n",id,i+1,linecount);
			return i;
			}
	}
	return -1;
}
void dump_symbol() {

	printf("\nThe symbol table dump:\n");
	int i ;
	printf("%3s\t%6s\t%8s\t%10s\t%5s\n","index","ID","type","value","Scope");
	for(i=0;i<TableSize;i++){
		if(table[i]->vaild!=0){
		printf("%3d\t%6s\t%8s",i+1,table[i]->id,table[i]->type);
		if(strcmp(table[i]->type,"float32")==0)
		{
		printf("\t%10lf",table[i]->f_val);
		}
		else if(strcmp(table[i]->type,"int")==0)
		{
		printf("\t%10d",table[i]->i_val);
		}
		//NEW
		printf("\t%5d\n",table[i]->scope_depth);
		}


	}

}

void yyerror(char *s) {
    printf("%s on %d line \n", s , linecount);
}

//NEW
void ScopeOver()
{
	int i ;
	for(i=0;i<TableSize;i++){
		if(table[i]->vaild!=0&&NowDepth==table[i]->scope_depth){
			table[i]->vaild=2;
		}
	}
}
