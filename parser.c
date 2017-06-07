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
#line 1 "parser.y" /* yacc.c:339  */

    #include <stdio.h>
    #include "colors.h"
    #include <ctype.h>

    #define CP(x) printf("Checkpoint %s\n" , #x);
    #define PI(a,x) printf("Variable: %f\n" , x);

    int yyerror (char* yaccProvidedMessage);
    int yylex(void);
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    #include "SymbolTable.h"
    #include "instructions.h"

    expr* funcexpr;

#line 86 "parser.c" /* yacc.c:339  */

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
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    BREAK = 258,
    CONTINUE = 259,
    AND = 260,
    OR = 261,
    NOT = 262,
    ID = 263,
    LOCAL = 264,
    NUMBER = 265,
    STRING = 266,
    NIL = 267,
    TRUE = 268,
    FALSE = 269,
    IF = 270,
    ELSE = 271,
    WHILE = 272,
    FOR = 273,
    RETURN = 274,
    SEMICOLON = 275,
    FUNCTION = 276,
    DIVIDE = 277,
    DOT = 278,
    DOTx2 = 279,
    ASSIGN = 280,
    PLUS = 281,
    MINUS = 282,
    MUL = 283,
    DE = 284,
    IDE = 285,
    MODULO = 286,
    EQ = 287,
    NE = 288,
    PLUSx2 = 289,
    MINUSx2 = 290,
    GT = 291,
    LT = 292,
    GE = 293,
    LE = 294,
    LEFTB = 295,
    RIGHTB = 296,
    LEFTSB = 297,
    RIGHTSB = 298,
    LEFTPARENTHESIS = 299,
    RIGHTPARENTHESIS = 300,
    COMMA = 301,
    DOUBLEDOT = 302,
    DOUBLEDOTx2 = 303,
    COMMENTLINE = 304,
    COMMENTMYLTY = 305,
    INTEGER = 306,
    REAL = 307,
    UMINUS = 308
  };
#endif
/* Tokens.  */
#define BREAK 258
#define CONTINUE 259
#define AND 260
#define OR 261
#define NOT 262
#define ID 263
#define LOCAL 264
#define NUMBER 265
#define STRING 266
#define NIL 267
#define TRUE 268
#define FALSE 269
#define IF 270
#define ELSE 271
#define WHILE 272
#define FOR 273
#define RETURN 274
#define SEMICOLON 275
#define FUNCTION 276
#define DIVIDE 277
#define DOT 278
#define DOTx2 279
#define ASSIGN 280
#define PLUS 281
#define MINUS 282
#define MUL 283
#define DE 284
#define IDE 285
#define MODULO 286
#define EQ 287
#define NE 288
#define PLUSx2 289
#define MINUSx2 290
#define GT 291
#define LT 292
#define GE 293
#define LE 294
#define LEFTB 295
#define RIGHTB 296
#define LEFTSB 297
#define RIGHTSB 298
#define LEFTPARENTHESIS 299
#define RIGHTPARENTHESIS 300
#define COMMA 301
#define DOUBLEDOT 302
#define DOUBLEDOTx2 303
#define COMMENTLINE 304
#define COMMENTMYLTY 305
#define INTEGER 306
#define REAL 307
#define UMINUS 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 74 "parser.y" /* yacc.c:355  */

    char*               stringvalue;
    int                 intvalue;
    double              realvalue;
    struct expr_type*        exprvalue;
    struct symbolTable*     symbol;
    struct for_pre*	    forvalue;
    struct stmt_list*   stmtvalue;
    struct quad_t*          quadvalue;

#line 243 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 260 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   648

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   134,   134,   135,   138,   139,   140,   141,   142,   143,
     149,   157,   158,   159,   160,   165,   166,   172,   178,   184,
     190,   196,   209,   223,   237,   252,   266,   281,   314,   351,
     358,   359,   377,   389,   409,   430,   449,   470,   486,   486,
     565,   572,   589,   595,   600,   636,   676,   682,   685,   689,
     802,   811,   838,   839,   840,   846,   852,   856,   862,   868,
     875,   880,   890,   894,   910,   926,   930,   942,   942,   956,
     957,   960,   960,   975,   976,   979,  1006,  1006,  1014,  1015,
    1017,  1032,  1042,  1051,  1060,  1066,  1073,  1080,  1088,  1109,
    1130,  1134,  1149,  1153,  1153,  1154,  1157,  1157,  1157,  1167,
    1187,  1204,  1205,  1206,  1206,  1206,  1208,  1234,  1235,  1237,
    1270,  1301,  1301,  1318
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BREAK", "CONTINUE", "AND", "OR", "NOT",
  "ID", "LOCAL", "NUMBER", "STRING", "NIL", "TRUE", "FALSE", "IF", "ELSE",
  "WHILE", "FOR", "RETURN", "SEMICOLON", "FUNCTION", "DIVIDE", "DOT",
  "DOTx2", "ASSIGN", "PLUS", "MINUS", "MUL", "DE", "IDE", "MODULO", "EQ",
  "NE", "PLUSx2", "MINUSx2", "GT", "LT", "GE", "LE", "LEFTB", "RIGHTB",
  "LEFTSB", "RIGHTSB", "LEFTPARENTHESIS", "RIGHTPARENTHESIS", "COMMA",
  "DOUBLEDOT", "DOUBLEDOTx2", "COMMENTLINE", "COMMENTMYLTY", "INTEGER",
  "REAL", "UMINUS", "$accept", "program", "stmt", "expr", "term",
  "assignexpr", "$@1", "lvalue", "tableitem", "call", "primary",
  "callsuffix", "normcall", "methodcall", "elist", "tablemake", "indexed",
  "indexedelem", "$@2", "block_stmt", "block", "$@3", "funcname",
  "funcprefix", "funcargs", "$@4", "funcblockstart", "funcblockend",
  "funcbody", "funcdef", "const", "idlist", "ifprefix", "else", "elsestmt",
  "$@5", "ifstmt", "$@6", "$@7", "whilestart", "whilecond", "loopstart",
  "loopend", "loopstmt", "$@8", "$@9", "whilestmt", "N", "M", "forprefix",
  "forstmt", "returnstmt", "$@10", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF -164

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-164)))

#define YYTABLE_NINF -4

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-4)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     124,    -4,    31,    33,   283,  -164,    35,  -164,  -164,  -164,
    -164,    12,  -164,    22,    56,  -164,    82,   283,    -3,    -3,
    -164,    23,   272,    83,  -164,  -164,    13,   124,   471,  -164,
    -164,   554,  -164,     5,  -164,  -164,  -164,    48,  -164,  -164,
    -164,  -164,    51,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,   283,   283,  -164,   283,  -164,  -164,  -164,    73,
       2,     5,     2,  -164,   283,   537,   -35,   -31,  -164,   334,
      52,  -164,  -164,  -164,  -164,  -164,  -164,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,    88,    90,
    -164,  -164,  -164,   283,   283,  -164,  -164,  -164,    92,   283,
     283,  -164,  -164,   226,   283,  -164,   283,   363,   -13,   495,
      57,   180,   316,  -164,   283,  -164,    61,  -164,    62,   283,
     283,  -164,  -164,  -164,  -164,  -164,   573,   573,   609,   609,
     609,   609,  -164,    63,   283,   411,   -27,  -164,   429,   -25,
     101,    70,  -164,  -164,   387,  -164,  -164,   -22,  -164,  -164,
    -164,    62,  -164,  -164,  -164,   537,  -164,   283,   591,   591,
     283,   537,  -164,  -164,  -164,  -164,  -164,    -7,  -164,    96,
    -164,   226,  -164,   283,   283,    14,    16,  -164,   105,  -164,
    -164,  -164,  -164,  -164,  -164,   519,   447,  -164,  -164,  -164,
     226,  -164,  -164,  -164,  -164,  -164,  -164,  -164
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,    40,     0,    84,    85,    86,
      87,     0,    99,     0,   111,    13,    74,     0,     0,     0,
      71,    62,     0,     0,    82,    83,     0,     0,     0,    29,
      15,    51,    43,    52,    37,    53,    11,     0,    12,    55,
      96,     5,     0,     6,   107,     7,     8,    14,     9,    10,
      32,    41,     0,    62,   113,     0,    73,    75,    31,     0,
      33,     0,    35,    70,     0,    60,     0,     0,    65,     0,
       0,    42,     1,     2,   108,   108,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    34,    36,     0,    62,    49,    56,    57,     0,     0,
      62,    76,    78,     0,     0,   101,    62,     0,     0,     0,
       0,     0,     0,    63,     0,    64,     0,    30,    54,     0,
       0,    19,    16,    17,    18,    20,    25,    26,    21,    23,
      22,    24,    44,     0,     0,     0,     0,    46,     0,     0,
      90,     0,    81,    97,     0,   103,   106,     0,    91,   108,
     112,     0,    72,    69,    67,    61,    66,    62,    27,    28,
      62,    39,    45,    58,    47,    48,    88,     0,    79,    95,
     100,     0,   107,     0,     0,     0,     0,    77,     0,    80,
      92,    93,    98,   104,   101,     0,     0,    50,    59,    89,
       0,   102,   107,   109,    68,    94,   105,   110
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -164,    89,  -101,     0,  -164,  -164,  -164,    50,  -164,    54,
    -164,  -164,  -164,  -164,   -52,  -164,  -164,    -1,  -164,  -164,
     -24,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,   -19,
    -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,   -66,  -164,  -164,  -164,  -163,   -61,  -164,
    -164,  -164,  -164
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    65,    29,    30,   134,    31,    32,    33,
      34,    95,    96,    97,    66,    35,    67,    68,   174,   111,
      36,    63,    57,    37,   102,   140,   141,   179,   142,    38,
      39,   167,    40,   181,   182,   190,    41,   103,   169,    42,
     105,   145,   196,   146,   171,   191,    43,   106,   119,    44,
      45,    46,    55
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,   108,   143,    70,    50,     5,     6,   149,   113,   184,
     153,   114,   115,    72,   120,   116,    47,    58,   163,   114,
     165,   114,    69,   172,   114,    88,    89,    28,    98,   197,
       4,     5,     6,   114,     7,     8,     9,    10,   177,   178,
     110,    59,   136,    51,    93,    23,    94,    99,   139,   100,
      17,    48,   107,    49,   147,   109,    52,    18,    19,   187,
     114,   188,   114,    64,   112,    21,    53,    22,    60,    62,
     183,    23,    61,    61,    24,    25,    54,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   173,   195,
      56,    71,   101,   135,    16,   104,   132,   118,   133,   138,
     137,    64,   151,    28,   144,   175,   157,   160,   176,   166,
      20,    28,   180,   189,   155,   156,    73,   168,   192,   158,
     159,     0,     0,     0,    -3,     1,     0,     2,     3,     0,
       0,     4,     5,     6,   161,     7,     8,     9,    10,    11,
       0,    12,    13,    14,    15,    16,     0,     0,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,    19,
       0,     0,     0,     0,    20,     0,    21,     0,    22,     0,
       0,    28,    23,   185,   186,    24,    25,     0,     0,     0,
       0,     1,     0,     2,     3,     0,     0,     4,     5,     6,
      28,     7,     8,     9,    10,    11,     0,    12,    13,    14,
      15,    16,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,    18,    19,     0,     0,     0,     0,
      20,   152,    21,     0,    22,     0,     0,     1,    23,     2,
       3,    24,    25,     4,     5,     6,     0,     7,     8,     9,
      10,    11,     0,    12,    13,    14,    15,    16,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
      18,    19,     0,     0,     0,     0,    20,     0,    21,     0,
      22,     0,     0,     0,    23,     0,     0,    24,    25,     4,
       5,     6,     0,     7,     8,     9,    10,     0,     0,     0,
       4,     5,     6,    16,     7,     8,     9,    10,     0,    17,
       0,     0,     0,     0,     0,     0,    18,    19,     0,     0,
      17,     0,     0,     0,    21,     0,    22,    18,    19,     0,
      23,    74,    75,    24,    25,    21,     0,    22,     0,     0,
       0,    23,     0,     0,    24,    25,     0,     0,    77,    74,
      75,     0,    78,    79,    80,     0,     0,    81,    82,    83,
       0,     0,    84,    85,    86,    87,    77,     0,     0,     0,
      78,    79,    80,   154,     0,    81,    82,    83,    74,    75,
      84,    85,    86,    87,     0,     0,     0,     0,     0,   117,
       0,     0,     0,     0,     0,    77,     0,     0,     0,    78,
      79,    80,    74,    75,    81,    82,    83,     0,     0,    84,
      85,    86,    87,     0,     0,     0,     0,     0,   148,    77,
       0,     0,     0,    78,    79,    80,    74,    75,    81,    82,
      83,     0,     0,    84,    85,    86,    87,     0,     0,     0,
       0,     0,   170,    77,    74,    75,     0,    78,    79,    80,
       0,     0,    81,    82,    83,     0,     0,    84,    85,    86,
      87,    77,    74,    75,   162,    78,    79,    80,     0,     0,
      81,    82,    83,     0,     0,    84,    85,    86,    87,    77,
       0,     0,   164,    78,    79,    80,    74,    75,    81,    82,
      83,     0,     0,    84,    85,    86,    87,     0,   194,     0,
       0,    76,     0,    77,     0,     0,     0,    78,    79,    80,
      74,    75,    81,    82,    83,     0,     0,    84,    85,    86,
      87,     0,     0,     0,     0,   150,     0,    77,     0,     0,
       0,    78,    79,    80,    74,    75,    81,    82,    83,     0,
       0,    84,    85,    86,    87,     0,     0,     0,     0,   193,
       0,    77,    74,    75,     0,    78,    79,    80,     0,     0,
      81,    82,    83,     0,     0,    84,    85,    86,    87,    77,
       0,     0,     0,    78,    79,    80,     0,     0,    81,    82,
      83,     0,     0,    84,    85,    86,    87,    88,    89,    90,
       0,     0,     0,     0,     0,     0,     0,     0,    91,    92,
       0,     0,     0,     0,     0,    77,    93,     0,    94,    78,
      79,    80,     0,     0,    81,    -4,    -4,     0,     0,    84,
      85,    86,    87,    77,     0,     0,     0,    78,    79,    80,
       0,     0,    81,    82,    83,     0,     0,    84,    85,    86,
      87,    77,     0,     0,     0,    78,    79,    80,     0,     0,
      81,     0,     0,     0,     0,    -4,    -4,    -4,    -4
};

static const yytype_int16 yycheck[] =
{
       0,    53,   103,    22,     4,     8,     9,    20,    43,   172,
     111,    46,    43,     0,    75,    46,    20,    17,    45,    46,
      45,    46,    22,    45,    46,    23,    24,    27,    23,   192,
       7,     8,     9,    46,    11,    12,    13,    14,    45,    46,
      59,    44,    94,     8,    42,    48,    44,    42,   100,    44,
      27,    20,    52,    20,   106,    55,    44,    34,    35,    45,
      46,    45,    46,    40,    64,    42,    44,    44,    18,    19,
     171,    48,    18,    19,    51,    52,    20,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,   149,   190,
       8,     8,    44,    93,    21,    44,     8,    45,     8,    99,
       8,    40,    45,   103,   104,   157,    44,    44,   160,     8,
      40,   111,    16,     8,   114,   116,    27,   141,   184,   119,
     120,    -1,    -1,    -1,     0,     1,    -1,     3,     4,    -1,
      -1,     7,     8,     9,   134,    11,    12,    13,    14,    15,
      -1,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      -1,    -1,    -1,    -1,    40,    -1,    42,    -1,    44,    -1,
      -1,   171,    48,   173,   174,    51,    52,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,    -1,    -1,     7,     8,     9,
     190,    11,    12,    13,    14,    15,    -1,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    -1,     1,    48,     3,
       4,    51,    52,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    -1,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    -1,    -1,    -1,    -1,    40,    -1,    42,    -1,
      44,    -1,    -1,    -1,    48,    -1,    -1,    51,    52,     7,
       8,     9,    -1,    11,    12,    13,    14,    -1,    -1,    -1,
       7,     8,     9,    21,    11,    12,    13,    14,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,
      27,    -1,    -1,    -1,    42,    -1,    44,    34,    35,    -1,
      48,     5,     6,    51,    52,    42,    -1,    44,    -1,    -1,
      -1,    48,    -1,    -1,    51,    52,    -1,    -1,    22,     5,
       6,    -1,    26,    27,    28,    -1,    -1,    31,    32,    33,
      -1,    -1,    36,    37,    38,    39,    22,    -1,    -1,    -1,
      26,    27,    28,    47,    -1,    31,    32,    33,     5,     6,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    26,
      27,    28,     5,     6,    31,    32,    33,    -1,    -1,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,    22,
      -1,    -1,    -1,    26,    27,    28,     5,     6,    31,    32,
      33,    -1,    -1,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,    22,     5,     6,    -1,    26,    27,    28,
      -1,    -1,    31,    32,    33,    -1,    -1,    36,    37,    38,
      39,    22,     5,     6,    43,    26,    27,    28,    -1,    -1,
      31,    32,    33,    -1,    -1,    36,    37,    38,    39,    22,
      -1,    -1,    43,    26,    27,    28,     5,     6,    31,    32,
      33,    -1,    -1,    36,    37,    38,    39,    -1,    41,    -1,
      -1,    20,    -1,    22,    -1,    -1,    -1,    26,    27,    28,
       5,     6,    31,    32,    33,    -1,    -1,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    -1,
      -1,    26,    27,    28,     5,     6,    31,    32,    33,    -1,
      -1,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    20,
      -1,    22,     5,     6,    -1,    26,    27,    28,    -1,    -1,
      31,    32,    33,    -1,    -1,    36,    37,    38,    39,    22,
      -1,    -1,    -1,    26,    27,    28,    -1,    -1,    31,    32,
      33,    -1,    -1,    36,    37,    38,    39,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      -1,    -1,    -1,    -1,    -1,    22,    42,    -1,    44,    26,
      27,    28,    -1,    -1,    31,    32,    33,    -1,    -1,    36,
      37,    38,    39,    22,    -1,    -1,    -1,    26,    27,    28,
      -1,    -1,    31,    32,    33,    -1,    -1,    36,    37,    38,
      39,    22,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    36,    37,    38,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     7,     8,     9,    11,    12,    13,
      14,    15,    17,    18,    19,    20,    21,    27,    34,    35,
      40,    42,    44,    48,    51,    52,    55,    56,    57,    58,
      59,    61,    62,    63,    64,    69,    74,    77,    83,    84,
      86,    90,    93,   100,   103,   104,   105,    20,    20,    20,
      57,     8,    44,    44,    20,   106,     8,    76,    57,    44,
      61,    63,    61,    75,    40,    57,    68,    70,    71,    57,
      83,     8,     0,    55,     5,     6,    20,    22,    26,    27,
      28,    31,    32,    33,    36,    37,    38,    39,    23,    24,
      25,    34,    35,    42,    44,    65,    66,    67,    23,    42,
      44,    44,    78,    91,    44,    94,   101,    57,    68,    57,
      83,    73,    57,    43,    46,    43,    46,    45,    45,   102,
     102,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,     8,     8,    60,    57,    68,     8,    57,    68,
      79,    80,    82,    56,    57,    95,    97,    68,    45,    20,
      20,    45,    41,    56,    47,    57,    71,    44,    57,    57,
      44,    57,    43,    45,    43,    45,     8,    85,    74,    92,
      45,    98,    45,   102,    72,    68,    68,    45,    46,    81,
      16,    87,    88,    56,   101,    57,    57,    45,    45,     8,
      89,    99,    97,    20,    41,    56,    96,   101
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    58,    58,    58,    58,    58,    58,    58,    60,    59,
      61,    61,    61,    61,    62,    62,    62,    62,    63,    63,
      63,    64,    64,    64,    64,    64,    65,    65,    66,    67,
      68,    68,    68,    69,    69,    70,    70,    72,    71,    73,
      73,    75,    74,    76,    76,    77,    79,    78,    80,    81,
      82,    83,    84,    84,    84,    84,    84,    84,    85,    85,
      85,    86,    87,    89,    88,    88,    91,    92,    90,    93,
      94,    95,    96,    98,    99,    97,   100,   101,   102,   103,
     104,   106,   105,   105
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     4,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     0,     4,
       1,     2,     2,     1,     3,     4,     3,     4,     4,     2,
       6,     1,     1,     1,     3,     1,     1,     1,     3,     5,
       1,     3,     0,     3,     3,     1,     3,     0,     6,     2,
       0,     0,     4,     1,     0,     2,     0,     4,     0,     0,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     1,     0,     3,     0,     0,     0,     5,     1,
       3,     0,     0,     0,     0,     5,     3,     0,     0,     7,
       7,     0,     4,     2
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
        case 8:
#line 142 "parser.y" /* yacc.c:1646  */
    { (yyval.stmtvalue) = (yyvsp[0].stmtvalue); }
#line 1577 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 144 "parser.y" /* yacc.c:1646  */
    {
                    if(loopcounter == 0) {printf(RED"ERROR" RESET ": Cant break outside a loop\n"); error++;}
                    breaklist = pushin(breaklist,nextquadlabel()+1);
                    emit(jump,NULL,NULL,NULL,0,currQuad);
                }
#line 1587 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 150 "parser.y" /* yacc.c:1646  */
    {
                    if(loopcounter == 0) {printf(RED"ERROR" RESET ": Cant continue outside a loop\n");   error++;}
                    int temp = conlist->toJump;
                    conlist = pushin(conlist,nextquadlabel()+1);
                    conlist->toJump = temp;
                    emit(jump,NULL,NULL,NULL,0,currQuad);
                }
#line 1599 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 165 "parser.y" /* yacc.c:1646  */
    {(yyval.exprvalue) = (yyvsp[0].exprvalue);}
#line 1605 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 166 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(add , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad);
                                 (yyval.exprvalue) = tempexpr; 
                                 }
#line 1616 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 172 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(sub , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad); 
                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1627 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 178 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(mul , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad); 
                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1638 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 184 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(div_code , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad); 
                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1649 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 190 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                                 emit(mod , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad); 
                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1660 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 196 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin((yyval.exprvalue)->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin((yyval.exprvalue)->falselist , nextquadlabel() + 2);
                                
                                 emit(if_greater , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad); 
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                 isRelatioNal = 1;
                                 (yyval.exprvalue) = tempexpr;

                                 }
#line 1678 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 209 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin((yyval.exprvalue)->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin((yyval.exprvalue)->falselist , nextquadlabel() + 2);
                                                                
                            
                                 emit(if_greatereq , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad); 
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad); 
                                 isRelatioNal = 1;

                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1697 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 223 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin((yyval.exprvalue)->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin((yyval.exprvalue)->falselist , nextquadlabel() + 2);

                                 
                                 emit(if_less , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad);  
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                 isRelatioNal = 1;

                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1716 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 237 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin((yyval.exprvalue)->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin((yyval.exprvalue)->falselist , nextquadlabel() + 2);

                                  
                            
                                 emit(if_lesseq , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1, currQuad);  
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                 isRelatioNal = 1;

                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1736 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 252 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 
                            
                                 tempexpr->truelist = pushin((yyval.exprvalue)->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin((yyval.exprvalue)->falselist , nextquadlabel() + 2);

                                  
                                 emit(if_eq , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , nextquadlabel()+3 , currQuad);  
                                 emit(jump , NULL , NULL , NULL , nextquadlabel()+4 , currQuad);
                                 isRelatioNal = 1;

                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1755 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 266 "parser.y" /* yacc.c:1646  */
    { 
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol);  
                            
                                 tempexpr->truelist = pushin((yyval.exprvalue)->truelist , nextquadlabel()+1);
                                 tempexpr->falselist = pushin((yyval.exprvalue)->falselist , nextquadlabel() + 2);

                                 
                            
                                 emit(if_noteq , (yyvsp[-2].exprvalue) , (yyvsp[0].exprvalue) , tempexpr , -1 , currQuad);  
                                 emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                 isRelatioNal = 1;

                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1775 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 281 "parser.y" /* yacc.c:1646  */
    {
                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol);  
                            
                                 if(!((yyvsp[-3].exprvalue)->truelist || (yyvsp[-3].exprvalue)->falselist)){
                                      (yyvsp[-3].exprvalue)->truelist = pushin((yyvsp[-3].exprvalue)->truelist , nextquadlabel() + 1);
                                      (yyvsp[-3].exprvalue)->falselist = pushin((yyvsp[-3].exprvalue)->falselist , nextquadlabel() + 2);

                                     emit(if_eq,(yyvsp[-3].exprvalue),newexpr_constbool(1),NULL ,0,currQuad);
                                     emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                     (yyvsp[-1].intvalue) = (yyvsp[-1].intvalue) + 2;

                                 }

                                 if(!((yyvsp[0].exprvalue)->truelist || (yyvsp[0].exprvalue)->falselist)){
                                      (yyvsp[0].exprvalue)->truelist = pushin((yyvsp[0].exprvalue)->truelist , nextquadlabel() + 1);
                                      (yyvsp[0].exprvalue)->falselist = pushin((yyvsp[0].exprvalue)->falselist , nextquadlabel() + 2);

                                     emit(if_eq,(yyvsp[0].exprvalue),newexpr_constbool(1) ,NULL ,0,currQuad);
                                     emit(jump , NULL , NULL , NULL , 0, currQuad);

                                 }

                                 backpatch((yyvsp[-3].exprvalue)->truelist , (yyvsp[-1].intvalue));
                                 tempexpr->truelist = (yyvsp[0].exprvalue)->truelist;
                                 tempexpr->falselist = merge((yyvsp[-3].exprvalue)->falselist , (yyvsp[0].exprvalue)->falselist);
                                 backpatch((yyvsp[0].exprvalue)->truelist, nextquadlabel()+1);
                                 backpatch(tempexpr->falselist,nextquadlabel()+3);
                                 isRelatioNal = 1;

                                 //emit(and , $1 , $4 , tempexpr , -1 , curruad); 
                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1813 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 314 "parser.y" /* yacc.c:1646  */
    { 

                                 symbolTable* symbol = newtemp();
                                 expr* tempexpr = lvalue_expr(symbol); 

                                 if(!((yyvsp[-3].exprvalue)->truelist || (yyvsp[-3].exprvalue)->falselist)){
                                      (yyvsp[-3].exprvalue)->truelist = pushin((yyvsp[-3].exprvalue)->truelist , nextquadlabel() + 1);
                                      (yyvsp[-3].exprvalue)->falselist = pushin((yyvsp[-3].exprvalue)->falselist , nextquadlabel() + 2);

                                     emit(if_eq,(yyvsp[-3].exprvalue),newexpr_constbool(1),NULL ,0,currQuad);
                                     emit(jump , NULL , NULL , NULL , 0 , currQuad);
                                     (yyvsp[-1].intvalue) = (yyvsp[-1].intvalue) + 2;

                                 }

                                 if(!((yyvsp[0].exprvalue)->truelist || (yyvsp[0].exprvalue)->falselist)){
                                      (yyvsp[0].exprvalue)->truelist = pushin((yyvsp[0].exprvalue)->truelist , nextquadlabel() + 1);
                                      (yyvsp[0].exprvalue)->falselist = pushin((yyvsp[0].exprvalue)->falselist , nextquadlabel() + 2);

                                     emit(if_eq,(yyvsp[0].exprvalue),newexpr_constbool(1) ,NULL ,0,currQuad);
                                     emit(jump , NULL , NULL , NULL , 0, currQuad);

                                 }


                                 backpatch((yyvsp[-3].exprvalue)->falselist , (yyvsp[-1].intvalue));
                                 tempexpr->falselist = (yyvsp[0].exprvalue)->falselist;
                                 tempexpr->truelist = merge((yyvsp[-3].exprvalue)->truelist , (yyvsp[0].exprvalue)->truelist);
                                 backpatch((yyvsp[0].exprvalue)->falselist, nextquadlabel() + 3);
                                 backpatch(tempexpr->truelist,nextquadlabel()+1);


                                 isRelatioNal = 1;

                                 //emit(or , $1 , $4 , tempexpr , -1 , currQuad); 
                                 (yyval.exprvalue) = tempexpr;
                                 }
#line 1855 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 351 "parser.y" /* yacc.c:1646  */
    {  
                    (yyval.exprvalue) = (yyvsp[0].exprvalue);
                   }
#line 1863 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 358 "parser.y" /* yacc.c:1646  */
    { (yyval.exprvalue) = (yyvsp[-1].exprvalue);}
#line 1869 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 360 "parser.y" /* yacc.c:1646  */
    {   /*
                    checkuminus($2);
                    $$ = newexpr(arithexpr_e);
                    $$->sym = newtemp();
                    $$->strConst = $$->sym->name;
                    emit(uminus,$2,$$,NULL,-1,currQuad);
                    */
                    symbolTable* symbol = newtemp();
                    expr* tempexpr = lvalue_expr(symbol); 
                    symbol = newtemp();
                    expr* minus1 = lvalue_expr(symbol);
                    minus1->numConst = -1;
                    minus1->strConst = "-1";
                    minus1->type = constnum_e;
                    emit(mul , (yyvsp[0].exprvalue) , minus1 , tempexpr , -1 , currQuad); 
                    (yyval.exprvalue) = tempexpr;
                }
#line 1891 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 378 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprvalue) = newexpr(arithexpr_e);
                    (yyval.exprvalue)->sym = newtemp();
                    (yyval.exprvalue)->strConst = (yyval.exprvalue)->sym->name;

                    ValuesStack* temp = (yyval.exprvalue)->falselist;
                    (yyval.exprvalue)->falselist = (yyval.exprvalue)->truelist;
                    (yyval.exprvalue)->truelist = temp;

                    emit(not,(yyvsp[0].exprvalue),NULL,(yyval.exprvalue),-1,currQuad);
                }
#line 1907 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 389 "parser.y" /* yacc.c:1646  */
    { 
                                int code = ultimateLookUpForVariables(&(yyvsp[0].exprvalue),var_e);
                                if(code == 0){
                                    printf(RED"ERROR" RESET ": %s undeclared\n" , (yyvsp[0].exprvalue)->strConst);
                                    error++;
                                }
                            /*==========================================================*/

                                if((yyvsp[0].exprvalue)->type == tableitem_e ){
                                    (yyval.exprvalue) = emit_iftableitem((yyvsp[0].exprvalue));
                                    emit(add,(yyval.exprvalue),newexpr_constnum(1),(yyval.exprvalue),-1,currQuad);
                                    emit(tablesetelem,(yyvsp[0].exprvalue),(yyvsp[0].exprvalue)->index,(yyval.exprvalue),-1,currQuad);
                                }else{
                                    emit(add,(yyvsp[0].exprvalue),newexpr_constnum(1),(yyvsp[0].exprvalue),-1,currQuad);
                                    (yyval.exprvalue) = newexpr(arithexpr_e);
                                    (yyval.exprvalue)->sym = newtemp(); 
                                    (yyval.exprvalue)->strConst = (yyval.exprvalue)->sym->name;
                                    emit(assign,(yyvsp[0].exprvalue),NULL,(yyval.exprvalue),-1,currQuad);
                                }
                            }
#line 1932 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 409 "parser.y" /* yacc.c:1646  */
    {
                                int code = ultimateLookUpForVariables(&(yyvsp[-1].exprvalue),var_e);
                                if(code == 0){
                                    printf(RED"ERROR" RESET ": %s undeclared\n" , (yyvsp[-1].exprvalue)->strConst);
                                    error++;
                                }
                            /*==========================================================*/
                                (yyval.exprvalue) = newexpr(var_e);
                                (yyval.exprvalue)->sym = newtemp();
                                (yyval.exprvalue)->strConst = (yyval.exprvalue)->sym->name;

                                if((yyvsp[-1].exprvalue)->type == tableitem_e ){
                                    expr* value = emit_iftableitem((yyvsp[-1].exprvalue));
                                    emit(assign,value,NULL,(yyval.exprvalue),-1,currQuad);
                                    emit(add,value,newexpr_constnum(1),value,-1,currQuad);
                                    emit(tablesetelem,(yyvsp[-1].exprvalue),(yyvsp[-1].exprvalue)->index, value,-1,currQuad);
                                }else{
                                    emit(assign,(yyvsp[-1].exprvalue),NULL,(yyval.exprvalue),-1,currQuad);
                                    emit(add,(yyvsp[-1].exprvalue),newexpr_constnum(1),(yyvsp[-1].exprvalue),-1,currQuad);
                                }
                            }
#line 1958 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 430 "parser.y" /* yacc.c:1646  */
    {
                                int code = ultimateLookUpForVariables(&(yyvsp[0].exprvalue),var_e);
                                if(code == 0){
                                    printf(RED"ERROR" RESET ": %s undeclared\n" , (yyvsp[0].exprvalue)->strConst);
                                    error++;
                                }
                             /*==========================================================*/
                                if((yyvsp[0].exprvalue)->type == tableitem_e ){
                                    (yyval.exprvalue) = emit_iftableitem((yyvsp[0].exprvalue));
                                    emit(sub,(yyval.exprvalue),newexpr_constnum(1),(yyval.exprvalue),-1,currQuad);
                                    emit(tablesetelem,(yyvsp[0].exprvalue),(yyvsp[0].exprvalue)->index,(yyval.exprvalue),-1,currQuad);
                                }else{
                                    emit(sub,(yyvsp[0].exprvalue),newexpr_constnum(1),(yyvsp[0].exprvalue),-1,currQuad);
                                    (yyval.exprvalue) = newexpr(arithexpr_e);
                                    (yyval.exprvalue)->sym = newtemp(); 
                                    (yyval.exprvalue)->strConst = (yyval.exprvalue)->sym->name;
                                    emit(assign,(yyvsp[0].exprvalue),NULL,(yyval.exprvalue),-1,currQuad);
                                }
                            }
#line 1982 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 449 "parser.y" /* yacc.c:1646  */
    {
                                int code = ultimateLookUpForVariables(&(yyvsp[-1].exprvalue),var_e);
                                if(code == 0){
                                    printf(RED"ERROR" RESET ": %s undeclared\n" , (yyvsp[-1].exprvalue)->strConst);
                                    error++;
                                }
                             /*==========================================================*/
                                (yyval.exprvalue) = newexpr(var_e);
                                (yyval.exprvalue)->sym = newtemp();
                                (yyval.exprvalue)->strConst = (yyval.exprvalue)->sym->name;

                                if((yyvsp[-1].exprvalue)->type == tableitem_e ){
                                    expr* value = emit_iftableitem((yyvsp[-1].exprvalue));
                                    emit(assign,value,NULL,(yyval.exprvalue),-1,currQuad);
                                    emit(sub,value,newexpr_constnum(1),value,-1,currQuad);
                                    emit(tablesetelem,(yyvsp[-1].exprvalue),(yyvsp[-1].exprvalue)->index, value,-1,currQuad);
                                }else{
                                    emit(assign,(yyvsp[-1].exprvalue),NULL,(yyval.exprvalue),-1,currQuad);
                                    emit(sub,(yyvsp[-1].exprvalue),newexpr_constnum(1),(yyvsp[-1].exprvalue),-1,currQuad);
                                }
                            }
#line 2008 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 470 "parser.y" /* yacc.c:1646  */
    { 
                   /* symbolTable* symbol = newtemp();
                    expr* tempexpr = lvalue_expr(symbol);  
                            
                    tempexpr->truelist = pushin($$->truelist , nextquadlabel()+1);
                    tempexpr->falselist = pushin($$->falselist , nextquadlabel() + 2);

                    emit(if_eq , $1 , newexpr_constbool(1) , tempexpr , -1 , currQuad);  
                    emit(jump , NULL , NULL , NULL , 0 , currQuad);

                    $$ = tempexpr; */

                    (yyval.exprvalue) = (yyvsp[0].exprvalue);
                    }
#line 2027 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 486 "parser.y" /* yacc.c:1646  */
    {
                                if(lookup((yyvsp[-1].exprvalue)->strConst, 0) == -1){
                                    printf(RED"ERROR" RESET ": libfunction %s used as an l-value\n" , (yyvsp[-1].exprvalue)->strConst);
                                    found_error = 1;
                                    error++;
                                }
                                if(!found_error){
                                    if(globalscope == 1){
                                       if(lookup((yyvsp[-1].exprvalue)->strConst , 0) == 0){
                                           printf(RED"ERROR" RESET ": %s undeclared at global scope\n" , (yyvsp[-1].exprvalue)->strConst);
                                               error++;
                                       }else if(lookup((yyvsp[-1].exprvalue)->strConst , 0) == 1){
                                            if(findNode((yyvsp[-1].exprvalue)->strConst , 0)->funct == 1){
                                                printf(RED"ERROR" RESET ": programm function %s used as an l-value\n" , (yyvsp[-1].exprvalue)->strConst);
                                                error++;
                                            }else{
                                                (yyvsp[-1].exprvalue)->sym = findNode((yyvsp[-1].exprvalue)->strConst,0);
                                            }
                                        }
                                        globalscope = 0;
                                    }else{
                                        int code = ultimateLookUpForVariables(&(yyvsp[-1].exprvalue),var_e);
                                        if(code == 0){
                                            insert(0 , (yyvsp[-1].exprvalue)->strConst , Cscope , yylineno);
                                            (yyvsp[-1].exprvalue)->sym = findNode((yyvsp[-1].exprvalue)->strConst , Cscope);
                                            (yyvsp[-1].exprvalue)->type = var_e;
                                        }
                                    }
                                }
                                rightSideValue = 1;
                            }
#line 2063 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 517 "parser.y" /* yacc.c:1646  */
    {

                                if(isRelatioNal == 1){
                                    backpatch((yyvsp[0].exprvalue)->falselist , nextquadlabel() + 3);
                                    backpatch((yyvsp[0].exprvalue)->truelist , nextquadlabel() + 1);
                                    emit(assign , newexpr_constbool(1) , NULL , (yyvsp[0].exprvalue) , -1 , currQuad);
                                    emit(jump   , NULL , NULL , NULL , nextquadlabel() + 3 , currQuad);
                                    emit(assign , newexpr_constbool(0) , NULL , (yyvsp[0].exprvalue) , -1 , currQuad);
                                    isRelatioNal = 0;
                                }
                                
                                rightSideValue = 0;
                               if((yyvsp[-3].exprvalue)->type == tableitem_e){
                                    emit(tablesetelem,(yyvsp[-3].exprvalue)->table,(yyvsp[-3].exprvalue)->index,(yyvsp[0].exprvalue),-1,currQuad);
                                    (yyval.exprvalue) = emit_iftableitem((yyvsp[-3].exprvalue));
                                    (yyval.exprvalue)->type = assignexpr_e;
                                }else{

                                    //printf("%s %d\n ", $1->strConst , $1->type);
                                    //printf("Checking %s %d\n" , $4->strConst , $4->type);
                                    (yyvsp[-3].exprvalue)->type = (yyvsp[0].exprvalue)->type;
                                    emit(assign,(yyvsp[0].exprvalue),NULL,(yyvsp[-3].exprvalue),-1,currQuad);
                                    (yyval.exprvalue) = newexpr(assignexpr_e);
                                    (yyval.exprvalue)->sym = newtemp();
                                    (yyval.exprvalue)->strConst = (yyval.exprvalue)->sym->name;
                                    
                                    //printf("%s %d\n ", $1->strConst , $1->type);
                                    //printf("Checking %s %d\n" , $4->strConst , $4->type);
                                    expr* temp = (yyvsp[0].exprvalue);
                                    if((yyvsp[0].exprvalue)->type == newtable_e)   {
                                        (yyval.exprvalue)->type = newtable_e;
                                        (yyvsp[-3].exprvalue)->type = newtable_e;
                                        (yyval.exprvalue)->sym->table = 1; //------------------
                                        (yyvsp[-3].exprvalue)->sym->table = 1;
                                        printf("%s got type %d\n" , (yyval.exprvalue)->sym->name , (yyval.exprvalue)->sym->table);
                                    }
                                    
                                    else if((yyvsp[0].exprvalue)->type == tableitem_e) (yyval.exprvalue)->type = tableitem_e; //----------------
                                    else if((yyvsp[0].exprvalue)->type == newtable_e) (yyval.exprvalue)->type = newtable_e;
                                    else (yyvsp[-3].exprvalue)->type = var_e;  //---------------
                                    
                                    emit(assign,(yyvsp[-3].exprvalue),NULL,(yyval.exprvalue),-1,currQuad);
                                }

                            }
#line 2113 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 565 "parser.y" /* yacc.c:1646  */
    {
                                        expr* temp = (expr*)malloc(sizeof(expr));
                                        temp->strConst = strdup((yyvsp[0].stringvalue));
                                        temp->sym = findNode((yyvsp[0].stringvalue),Cscope);
                                        temp->type = var_e;
                                        (yyval.exprvalue) = temp;
                                    }
#line 2125 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 572 "parser.y" /* yacc.c:1646  */
    {
                                            if(lookup((yyvsp[0].stringvalue) , 0) == -1){
                                                 printf(RED"ERROR" RESET ": libfunction %s used as an l-value\n" , (yyvsp[0].stringvalue));
                                                 found_error = 1;
                                                 error++;
                                            }else if(lookup((yyvsp[0].stringvalue) , Cscope) == 0){
                                                insert(0 , (yyvsp[0].stringvalue) , Cscope , yylineno);
                                                found_local = 1;
                                                (yyval.exprvalue) = lvalue_expr(findNode((yyvsp[0].stringvalue),Cscope));
                                            }else if(findNode((yyvsp[0].stringvalue) , Cscope)->funct == 1){
                                                 printf(RED"ERROR" RESET ": %s declared as function in this scope\n" , (yyvsp[0].stringvalue));
                                                 found_error = 1;
                                                 error++;
                                            }else{
                                                (yyval.exprvalue) = lvalue_expr(findNode((yyvsp[0].stringvalue),Cscope));
                                            }
                                    }
#line 2147 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 589 "parser.y" /* yacc.c:1646  */
    {
                                        globalscope = 1;
                                        expr* temp = (expr*)malloc(sizeof(expr));
                                        temp->strConst = strdup((yyvsp[0].stringvalue));
                                        (yyval.exprvalue) = temp;
                                    }
#line 2158 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 595 "parser.y" /* yacc.c:1646  */
    {
                                        (yyval.exprvalue) = (yyvsp[0].exprvalue);
                                    }
#line 2166 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 600 "parser.y" /* yacc.c:1646  */
    {
                    if(!found_error){
                        if(lookup((yyvsp[-2].exprvalue)->strConst , 0) == -1){
                            printf(RED"ERROR" RESET ": libfunction %s used as an l-value\n" , (yyvsp[-2].exprvalue)->strConst);
                            error++;
                        }else if(globalscope == 1){
                            if(lookup((yyvsp[-2].exprvalue)->strConst , 0) == 0){
                                printf(RED"ERROR" RESET ": %s undeclared at global scope\n" , (yyvsp[-2].exprvalue)->strConst);
                                    error++;
                            }else if(lookup((yyvsp[-2].exprvalue)->strConst , 0) == 1){
                                 if(findNode((yyvsp[-2].exprvalue)->strConst , 0)->funct == 1){
                                     printf(RED"ERROR" RESET ": programm function %s used as an l-value\n" , (yyvsp[-2].exprvalue)->strConst);
                                     error++;
                                 }else{
                                    (yyvsp[-2].exprvalue)->sym = findNode((yyvsp[-2].exprvalue)->strConst,0);
                                 }
                            }   
                            globalscope = 0;
                        }else{
                            int code = ultimateLookUpForVariables(&(yyvsp[-2].exprvalue),newtable_e);
                            if(code == 0){
                                printf(RED"ERROR" RESET ": %s undeclared\n" , (yyvsp[-2].exprvalue)->strConst);
                                error++;
                            }
                        }
                    }
                    if((yyvsp[-2].exprvalue)->sym != NULL){
                        /*if($1->type == var_e){
                            $1->type = newtable_e;
                            $1->strConst = $1->sym->name;
                            emit(tablecreate,$1,NULL,NULL,-1,currQuad);
                        }*/
                        (yyval.exprvalue) = member_item((yyvsp[-2].exprvalue),(yyvsp[0].stringvalue));
                    }else{error++;}
                                    }
#line 2206 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 636 "parser.y" /* yacc.c:1646  */
    {
                    if(!found_error){
                        if(lookup((yyvsp[-3].exprvalue)->strConst , 0) == -1){
                            printf(RED"ERROR" RESET ": libfunction %s used as an l-value\n" , (yyvsp[-3].exprvalue)->strConst);
                            error++;
                        }else if(globalscope == 1){
                            if(lookup((yyvsp[-3].exprvalue)->strConst , 0) == 0){
                                printf(RED"ERROR" RESET ": %s undeclared at global scope\n" , (yyvsp[-3].exprvalue)->strConst);
                                    error++;
                            }else if(lookup((yyvsp[-3].exprvalue)->strConst , 0) == 1){
                                 if(findNode((yyvsp[-3].exprvalue)->strConst , 0)->funct == 1){
                                     printf(RED"ERROR" RESET ": programm function %s used as an l-value\n" , (yyvsp[-3].exprvalue)->strConst);
                                     error++;
                                 }else{
                                    (yyvsp[-3].exprvalue)->sym = findNode((yyvsp[-3].exprvalue)->strConst,0);
                                 }
                            }
                            globalscope = 0;
                        }else{
                            int code = ultimateLookUpForVariables(&(yyvsp[-3].exprvalue),newtable_e);
                            if(code == 0){
                                printf(RED"ERROR" RESET ": %s undeclared\n" , (yyvsp[-3].exprvalue)->strConst);
                                error++;
                            }
                        }
                    }                         
                    if((yyvsp[-3].exprvalue)->sym != NULL){
                        (yyvsp[-3].exprvalue)->index = (yyvsp[-1].exprvalue);
                        (yyvsp[-3].exprvalue) = emit_iftableitem((yyvsp[-3].exprvalue));
                        if((yyvsp[-3].exprvalue)->type != tableitem_e){
                            (yyvsp[-3].exprvalue)->table = malloc(sizeof(expr));
                            (yyvsp[-3].exprvalue)->table->type = (yyvsp[-3].exprvalue)->type;
                            (yyvsp[-3].exprvalue)->table->strConst = (yyvsp[-3].exprvalue)->strConst;
                            (yyvsp[-3].exprvalue)->table->index = (yyvsp[-3].exprvalue)->index;
                            (yyvsp[-3].exprvalue)->table->sym = (yyvsp[-3].exprvalue)->sym;
                        }
                        (yyval.exprvalue) = (yyvsp[-3].exprvalue);
                        (yyval.exprvalue)->type = tableitem_e;
                    }else{error++;}
                }
#line 2251 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 676 "parser.y" /* yacc.c:1646  */
    {
                                expr* temp = (expr*)malloc(sizeof(expr));
                                temp->strConst = strdup((yyvsp[0].stringvalue));
                                temp->sym = findNode((yyvsp[0].stringvalue),Cscope);
                                (yyval.exprvalue) = temp;
                            }
#line 2262 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 686 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprvalue) = make_call((yyvsp[-3].exprvalue) , (yyvsp[-1].exprvalue));
                }
#line 2270 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 689 "parser.y" /* yacc.c:1646  */
    {
                                        if(lookup((yyvsp[-1].exprvalue)->strConst , 0) == -1){
                                            (yyvsp[-1].exprvalue)->type = libraryfunc_e;
                                            (yyvsp[-1].exprvalue)->sym = findNode((yyvsp[-1].exprvalue)->strConst , 0);
                                        }else{
                                                if(!found_error){
                                                        int numberofblock = 0;
                                                        int i;
                                                        functionStack* p = stackF;
                                                        while(p != NULL){
                                                            if(strcmp(p->name , "_$block") == 0){
                                                                numberofblock++;
                                                                p = p->prev;
                                                            }else{
                                                                break;
                                                            }
                                                        }
                                                        symbolTable* symTemp;
                                                        int haveAccess = 0;
                                                        for(i = 0; i <= numberofblock; i++){
                                                            if(found_local){
                                                                if(lookup((yyvsp[-1].exprvalue)->strConst , Cscope) == 1){
                                                                    symTemp = findNode((yyvsp[-1].exprvalue)->strConst , Cscope);
                                                                    haveAccess = 1;
                                                                }
                                                                found_local = 0;
                                                                break;
                                                            }else if(lookup((yyvsp[-1].exprvalue)->strConst , Cscope - i) == 1){
                                                                symTemp = findNode((yyvsp[-1].exprvalue)->strConst , Cscope - i);
                                                                haveAccess = 1;
                                                                break;
                                                            }else if(i == numberofblock){
                                                                if(lookup((yyvsp[-1].exprvalue)->strConst , 0) == 1){
                                                                    symTemp = findNode((yyvsp[-1].exprvalue)->strConst , 0);
                                                                    haveAccess = 1;
                                                                }
                                                            }
                                                        }
                                                        if(haveAccess){
                                                            if((yyvsp[-1].exprvalue)->sym == NULL){
                                                                (yyvsp[-1].exprvalue)->sym = symTemp;
                                                                printf("callsufix %s %d\n" , (yyvsp[-1].exprvalue)->sym->name , (yyvsp[-1].exprvalue)->type);
                                                                if((yyvsp[-1].exprvalue)->sym->funct == 1){
                                                                    (yyvsp[-1].exprvalue)->type = programfunc_e;
                                                                }
                                                            }
                                                        }else{
                                                            printf("callsufix %s %d\n" , (yyvsp[-1].exprvalue)->sym->name , (yyvsp[-1].exprvalue)->type);
                                                            int NotAccess = 0;
                                                            for(i = 1; i <= Cscope-numberofblock; i++){
                                                                if(lookup((yyvsp[-1].exprvalue)->strConst , i) == 1){
                                                                    NotAccess = 1;
                                                                }
                                                            }
                                                            if(NotAccess){
                                                                printf(RED"ERROR" RESET ": %s not accessible\n" , (yyvsp[-1].exprvalue)->strConst);
                                                                error++;
                                                            }else{
                                                                printf(RED"ERROR" RESET ": %s undeclared\n" , (yyvsp[-1].exprvalue)->strConst);
                                                                error++;
                                                            }
                                                        }
                                        }else{
                                            found_error = 0;
                                        }
                                    }
                            /*========================================================*/
                            /*
                                if($1->sym->table == 1){    //--------
                                    $1->type = newtable_e;  //---------
                                  }                           //----------
                            
                                */
                                if((yyvsp[0].exprvalue)->boolConst){
                                    expr* self;
                                    self = (yyvsp[-1].exprvalue);
                                    (yyvsp[-1].exprvalue) = emit_iftableitem(member_item(self,(yyvsp[0].exprvalue)->strConst));
                                    self->next = (yyvsp[0].exprvalue)->next;
                                    (yyvsp[0].exprvalue)->next = self;
                                }
                                if((yyvsp[-1].exprvalue)->type != libraryfunc_e){
                                    expr* temp = (yyvsp[-1].exprvalue);
                                    if((yyvsp[-1].exprvalue)->sym->table == 1 && (yyvsp[-1].exprvalue)->sym->type != 4){
                                        (yyvsp[-1].exprvalue)->type = tableitem_e;
                                        (yyvsp[-1].exprvalue)->index = malloc(sizeof(expr));
                                        (yyvsp[-1].exprvalue)->index->strConst = strdup("\"()\"");
                                        (yyvsp[-1].exprvalue)->index->type = conststring_e;

                                        printf(".................\n");
                                        expr* temp = (yyvsp[-1].exprvalue);
                                        expr* to2 = (yyvsp[0].exprvalue);

                                        expr* to1 = (yyvsp[-1].exprvalue);
                                        to1->next = NULL;
                                        
                                        while(to2->next != NULL){
                                            to2 = to2->next;
                                        }

                                        to2->next = to1;


                                        // $1->next = $2->next;
                                        // $2->next = temp;
                                        printf("....................\n");
                                    
                                    }else{
                                        (yyvsp[-1].exprvalue)->type = programfunc_e;
                                    }
                                }
                                (yyvsp[-1].exprvalue) = emit_iftableitem((yyvsp[-1].exprvalue));
                                (yyval.exprvalue) = make_call((yyvsp[-1].exprvalue), (yyvsp[0].exprvalue)->next);
                            }
#line 2388 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 803 "parser.y" /* yacc.c:1646  */
    {
                    expr* func = newexpr(programfunc_e);
                    func->sym = (yyvsp[-4].symbol);
                    func->strConst = func->sym->name;
                    (yyval.exprvalue) = make_call(func , (yyvsp[-1].exprvalue));
                }
#line 2399 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 811 "parser.y" /* yacc.c:1646  */
    {
                    if(!found_error){
                        if(globalscope == 1){
                            if(lookup((yyvsp[0].exprvalue)->strConst , 0) == 0){
                                printf(RED"ERROR" RESET ": %s undeclared at global scope\n" , (yyvsp[0].exprvalue)->strConst);
                                error++;
                            }else{
                                (yyvsp[0].exprvalue)->sym = findNode((yyvsp[0].exprvalue)->strConst,0);
                            }
                            globalscope = 0;
                        }else{
                            int code = ultimateLookUpForVariables(&(yyvsp[0].exprvalue),var_e);
                            if(code == 0){
                                if(lookup((yyvsp[0].exprvalue)->strConst , 0) == -1){
                                    (yyvsp[0].exprvalue)->sym = findNode((yyvsp[0].exprvalue)->strConst , 0);
                                    (yyvsp[0].exprvalue)->type = libraryfunc_e;
                                }else{
                                    insert(0 , (yyvsp[0].exprvalue)->strConst , Cscope , yylineno);
                                    (yyvsp[0].exprvalue)->sym = findNode((yyvsp[0].exprvalue)->strConst , Cscope);
                                    (yyvsp[0].exprvalue)->type = var_e;
                                }
                            }
                        }
                        (yyval.exprvalue) = (yyvsp[0].exprvalue);
                    }
                    (yyval.exprvalue) = emit_iftableitem((yyvsp[0].exprvalue));
                }
#line 2431 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 839 "parser.y" /* yacc.c:1646  */
    {(yyval.exprvalue) = (yyvsp[0].exprvalue);}
#line 2437 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 841 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprvalue) = newexpr(programfunc_e);
                    (yyval.exprvalue)->sym = (yyvsp[-1].symbol);
                    (yyval.exprvalue)->strConst = (yyval.exprvalue)->sym->name;
                }
#line 2447 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 846 "parser.y" /* yacc.c:1646  */
    {(yyval.exprvalue) = (yyvsp[0].exprvalue);}
#line 2453 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 853 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprvalue) = (yyvsp[0].exprvalue);
                }
#line 2461 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 857 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprvalue) = (yyvsp[0].exprvalue);
                }
#line 2469 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 863 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprvalue) = calls((yyvsp[-1].exprvalue),0,NULL);
                }
#line 2477 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 869 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprvalue) = calls((yyvsp[-1].exprvalue),1,(yyvsp[-3].stringvalue));
                }
#line 2485 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 876 "parser.y" /* yacc.c:1646  */
    {
                    (yyvsp[0].exprvalue)->next = NULL;
                    (yyval.exprvalue) = (yyvsp[0].exprvalue);
                }
#line 2494 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 881 "parser.y" /* yacc.c:1646  */
    {
                    (yyvsp[0].exprvalue)->next = (yyvsp[-2].exprvalue);
                    /*
                    $3->next = NULL;
                    expr* temp = $1;
                    while(temp->next != NULL)   temp = temp->next;
                    temp->next = $3;*/
                    (yyval.exprvalue) = (yyvsp[0].exprvalue);
                }
#line 2508 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 890 "parser.y" /* yacc.c:1646  */
    {(yyval.exprvalue) = NULL;}
#line 2514 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 895 "parser.y" /* yacc.c:1646  */
    {
                    
                    expr* x = (yyvsp[-1].exprvalue);
                    expr* t = newexpr(newtable_e);
                    t->sym = newtemp();
                    t->strConst = t->sym->name;
                    emit(tablecreate,t,NULL,NULL,-1,currQuad);
                    int i=0;
                    while(x != NULL){
                        t->table = t;
                        emit(tablesetelem,t,newexpr_constnum(i++),x,-1,currQuad);
                        x = x->next;
                    }
                    (yyval.exprvalue) = t;
                }
#line 2534 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 911 "parser.y" /* yacc.c:1646  */
    {
                    expr* x = (yyvsp[-1].exprvalue);
                    expr* t = newexpr(newtable_e);
                    t->sym = newtemp();
                    t->strConst = t->sym->name;
                    emit(tablecreate,t,NULL,NULL,-1,currQuad);
                    while(x != NULL){
                        t->table = t;
                        emit(tablesetelem,t,x->index,x,-1,currQuad);
                        x = x->next;
                    }
                    (yyval.exprvalue) = t;
                }
#line 2552 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 927 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprvalue) = (yyvsp[0].exprvalue);
                }
#line 2560 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 931 "parser.y" /* yacc.c:1646  */
    {
                    expr* temp = (yyvsp[-2].exprvalue);
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = (yyvsp[0].exprvalue);
                    (yyval.exprvalue) = (yyvsp[-2].exprvalue);
                }
#line 2573 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 942 "parser.y" /* yacc.c:1646  */
    {rightSideValue = 1;}
#line 2579 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 943 "parser.y" /* yacc.c:1646  */
    {
                    rightSideValue = 0;
                    (yyvsp[-1].exprvalue)->index = (yyvsp[-4].exprvalue);
                    (yyvsp[-1].exprvalue)->next = NULL;
                    (yyval.exprvalue) = (yyvsp[-1].exprvalue);
                }
#line 2590 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 960 "parser.y" /* yacc.c:1646  */
    { if(isFuncBlock != 0) {
                            Cscope++; 
                            if(getStackSize() < Cscope){
                                push("_$block");
                            }
                        } 
                    }
#line 2602 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 966 "parser.y" /* yacc.c:1646  */
    {
                                            if(isFuncBlock != 0){
                                                hide(Cscope);
                                                Cscope--;
                                                funcexpr = (expr*)malloc(sizeof(expr));
                                                funcexpr = lvalue_expr(findNode(pop(),Cscope));
                                                }
                                        }
#line 2615 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 975 "parser.y" /* yacc.c:1646  */
    { (yyval.stringvalue) = (yyvsp[0].stringvalue);}
#line 2621 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 976 "parser.y" /* yacc.c:1646  */
    { (yyval.stringvalue) = newtempfuncname(); }
#line 2627 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 979 "parser.y" /* yacc.c:1646  */
    {
                                        (yyval.symbol) = findNode((yyvsp[0].stringvalue) , Cscope);  
                                         if((yyval.symbol) == NULL){
                                             insert(1 , (yyvsp[0].stringvalue) , Cscope , yylineno);
                                             (yyval.symbol) = findNode((yyvsp[0].stringvalue) , Cscope);
                                             functionNode = (yyval.symbol);
                                         }else{
                                                if((yyval.symbol)->type == 3) printf(RED"ERROR" RESET ": %s already defined as an libfunct\n" ,(yyvsp[-1].stringvalue));
                                                else printf(RED"ERROR" RESET ": %s already defined\n" , (yyvsp[0].stringvalue));
                                                found_error = 1;
                                                error++;
                                              }
                                        

                                        funcname_string = strdup((yyvsp[0].stringvalue));

                                        //emit(jump , NULL , NULL , NULL , -1 , currQuad);
                                        //funcJumpToPatch = currQuad;
                                        emit(functstart , lvalue_expr((yyval.symbol)) , NULL , NULL , -1 , currQuad);
                                        forfunctionsLocalStack = pushin(forfunctionsLocalStack , functionLocalOffset);
                                        forfunctionsScopeSpace = pushin(forfunctionsScopeSpace , currscopespace());
                                        resetScopeSpace();
                                        enterscopespace();
                                        resetformalargsoffset();
                                        
                                    }
#line 2658 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1006 "parser.y" /* yacc.c:1646  */
    {Cscope++; }
#line 2664 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1006 "parser.y" /* yacc.c:1646  */
    {
                                    Cscope--;
                                    push(functionNode->name); 
                                    enterscopespace();
                                    resetfunctionlocaloffset();
                               }
#line 2675 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1014 "parser.y" /* yacc.c:1646  */
    {forloops = pushin(forloops,loopcounter);   loopcounter = 0;    isFuncBlock++;}
#line 2681 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1015 "parser.y" /* yacc.c:1646  */
    { loopcounter = topin(forloops); forloops = popin(forloops); isFuncBlock--;}
#line 2687 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1017 "parser.y" /* yacc.c:1646  */
    {
                        emit(functend , funcexpr , NULL , NULL , -1 , currQuad);
                        //printf("CUrrequad : %d\n" , currQuad);
                        //quads[funcJumpToPatch - 1].label = currQuad + 1;

                        functionLocalsToSym = functionLocalOffset;
                        functionLocalOffset = topin(forfunctionsLocalStack);
                        forfunctionsLocalStack = popin(forfunctionsLocalStack);
                        
                         
                        scopespace = topin(forfunctionsScopeSpace);
                        forfunctionsScopeSpace = popin(forfunctionsScopeSpace);
                    }
#line 2705 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1033 "parser.y" /* yacc.c:1646  */
    {
                    
                        (yyval.symbol)->totallocals = functionLocalsToSym;
                        if(found_error == 1) found_error = 0;
                        (yyval.symbol) = (yyvsp[-2].symbol);
               }
#line 2716 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1042 "parser.y" /* yacc.c:1646  */
    { 
                        expr* dummy = (expr*) malloc(sizeof(expr));
                        char number[30];
                        dummy->numConst = (yyvsp[0].intvalue);
                        dummy->type = constnum_e;
                        sprintf(number,"%d",(yyvsp[0].intvalue));
                        dummy->strConst = strdup(number);
                        (yyval.exprvalue) = dummy;
                      }
#line 2730 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1051 "parser.y" /* yacc.c:1646  */
    { 
                        expr* dummy = (expr*) malloc(sizeof(expr));
                        char number[30];
                        dummy->numConst = (yyvsp[0].realvalue);
                        dummy->type = constnum_e;
                        sprintf(number,"%3f",(yyvsp[0].realvalue));
                        dummy->strConst = strdup(number);
                        (yyval.exprvalue) = dummy;
                      }
#line 2744 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1060 "parser.y" /* yacc.c:1646  */
    {
                        struct expr_type* dummy = (expr*) malloc(sizeof(expr));
                        dummy->type = conststring_e;
                        dummy->strConst = strdup((yyvsp[0].stringvalue));
                        (yyval.exprvalue) = dummy;
                      }
#line 2755 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1066 "parser.y" /* yacc.c:1646  */
    { 
                        struct expr_type* dummy = (expr*) malloc(sizeof(expr));
                        dummy->type == nil_e;
                        dummy->boolConst = (unsigned char)0;
                        dummy->strConst = "null";
                        (yyval.exprvalue) = dummy;
                      }
#line 2767 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1073 "parser.y" /* yacc.c:1646  */
    { 
                        struct expr_type* dummy = (expr*) malloc(sizeof(expr));
                        dummy->type = constbool_e;
                        dummy->boolConst = 1;
                        dummy->strConst = "true";
                        (yyval.exprvalue) = dummy;
                      }
#line 2779 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1080 "parser.y" /* yacc.c:1646  */
    { 
                        struct expr_type* dummy = (expr*) malloc(sizeof(expr));
                        dummy->type = constbool_e;
                        dummy->boolConst = 0;
                        dummy->strConst = "false";
                        (yyval.exprvalue) = dummy;
                      }
#line 2791 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1088 "parser.y" /* yacc.c:1646  */
    {
                                    if(!found_error){
                                        if(lookup((yyvsp[0].stringvalue) , Cscope) == -1){
                                            printf(RED"ERROR " RESET ": Argument %s is a libfunc\n" , (yyvsp[0].stringvalue));
                                        }else{

                                            int code = lookup((yyvsp[0].stringvalue) , Cscope);
                                            if(code == 0){
                                                insertArgv(functionNode ,
                                                        0 , 
                                                        (yyvsp[0].stringvalue),
                                                        Cscope,
                                                        yylineno
                                                        );
                                            }else if(code == 1){
                                                printf(RED"ERROR " RESET ": function argument %s redefined!\n" , (yyvsp[0].stringvalue));
                                            }
                                        }
                                    }
                                }
#line 2816 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1109 "parser.y" /* yacc.c:1646  */
    {
                                    if(!found_error){
                                        if(lookup((yyvsp[0].stringvalue) , Cscope) == -1){
                                            printf(RED"ERROR: " RESET "Argument %s is a libfunc\n" , (yyvsp[0].stringvalue));
                                        }else{


                                            int code = lookup((yyvsp[0].stringvalue) , Cscope);
                                            if(code == 0){
                                                insertArgv(functionNode ,
                                                        0 , 
                                                        (yyvsp[0].stringvalue),
                                                        Cscope,
                                                        yylineno
                                                        );
                                            }else if(code == 1){
                                                printf(RED"ERROR: " RESET "function argument %s redefined!\n" , (yyvsp[0].stringvalue));
                                            }
                                        }                                                                              
                                    }
                                }
#line 2842 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1135 "parser.y" /* yacc.c:1646  */
    {
                if(isRelatioNal == 1){
                    backpatch((yyvsp[-1].exprvalue)->falselist , nextquadlabel() + 3);
                    backpatch((yyvsp[-1].exprvalue)->truelist , nextquadlabel() + 1);
                    emit(assign , newexpr_constbool(1) , NULL , (yyvsp[-1].exprvalue) , -1 , currQuad);
                    emit(jump   , NULL , NULL , NULL , nextquadlabel() + 3 , currQuad);
                    emit(assign , newexpr_constbool(0) , NULL , (yyvsp[-1].exprvalue) , -1 , currQuad);
                    isRelatioNal = 0;
                }

                emit(if_eq , (yyvsp[-1].exprvalue) , newexpr_constbool(1),NULL,nextquadlabel() + 3,currQuad);
                (yyval.intvalue) = nextquadlabel()+1;
                emit(jump , NULL , NULL , NULL , 0 , currQuad);
            }
#line 2861 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1149 "parser.y" /* yacc.c:1646  */
    {   emit(jump,NULL,NULL,NULL,0,currQuad);
                    (yyval.intvalue) = nextquadlabel();
                }
#line 2869 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1153 "parser.y" /* yacc.c:1646  */
    {pushF(isFuncBlock);isFuncBlock=0;}
#line 2875 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1153 "parser.y" /* yacc.c:1646  */
    {isFuncBlock = popF();  (yyval.intvalue) = (yyvsp[-2].intvalue);}
#line 2881 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1154 "parser.y" /* yacc.c:1646  */
    {(yyval.intvalue) = 0;}
#line 2887 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1157 "parser.y" /* yacc.c:1646  */
    { pushF(isFuncBlock); isFuncBlock=0;}
#line 2893 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1157 "parser.y" /* yacc.c:1646  */
    {
                            isFuncBlock = popF();
                            patchlabel((yyvsp[-2].intvalue),nextquadlabel()+1);
                          }
#line 2902 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1160 "parser.y" /* yacc.c:1646  */
    {
                              if((yyvsp[0].intvalue) != 0){
                                  patchlabel((yyvsp[-4].intvalue),(yyvsp[0].intvalue)+1);
                                  patchlabel((yyvsp[0].intvalue),nextquadlabel()+1);
                              }
                          }
#line 2913 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1167 "parser.y" /* yacc.c:1646  */
    {
                    if(breaklist != NULL){
                        breakStack = pushStack(breakStack,breaklist);
                    }
                    ValuesStack* dummy = (ValuesStack*)malloc(sizeof(ValuesStack));
                    dummy->value = -1;
                    dummy->prev = NULL;
                    breaklist = dummy;
                    if(conlist != NULL){
                        conStack = pushStack(conStack,conlist);
                    }
                    dummy = (ValuesStack*)malloc(sizeof(ValuesStack));
                    dummy->value = -1;
                    dummy->prev = NULL;
                    conlist = dummy;

                    toJumpexpr = nextquadlabel() +1;
                  }
#line 2936 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1187 "parser.y" /* yacc.c:1646  */
    {
                    if(isRelatioNal == 1){
                        backpatch((yyvsp[-1].exprvalue)->falselist , nextquadlabel() + 3);
                        backpatch((yyvsp[-1].exprvalue)->truelist , nextquadlabel() + 1);
                        emit(assign , newexpr_constbool(1) , NULL , (yyvsp[-1].exprvalue) , -1 , currQuad);
                        emit(jump   , NULL , NULL , NULL , nextquadlabel() + 3 , currQuad);
                        emit(assign , newexpr_constbool(0) , NULL , (yyvsp[-1].exprvalue) , -1 , currQuad);
                        isRelatioNal = 0;
                    }

                    emit(if_eq , (yyvsp[-1].exprvalue) , newexpr_constbool(1) , NULL ,  nextquadlabel() + 3 , currQuad);
                    //$$ = $2;
                    conlist->toJump = toJumpexpr;
                    emit(jump , NULL , NULL , NULL , 0 , currQuad);
                    breaklist = pushin(breaklist,nextquadlabel());
            }
#line 2957 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1204 "parser.y" /* yacc.c:1646  */
    {++loopcounter;}
#line 2963 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1205 "parser.y" /* yacc.c:1646  */
    {--loopcounter;}
#line 2969 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1206 "parser.y" /* yacc.c:1646  */
    {pushF(isFuncBlock); isFuncBlock=0;}
#line 2975 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1206 "parser.y" /* yacc.c:1646  */
    {isFuncBlock = popF();}
#line 2981 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1206 "parser.y" /* yacc.c:1646  */
    {(yyval.stmtvalue) = (yyvsp[-2].stmtvalue);}
#line 2987 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1209 "parser.y" /* yacc.c:1646  */
    {
                emit(jump , NULL , NULL , NULL , conlist->toJump , currQuad);
                
                ValuesStack* temp = breaklist;
                while(temp->value != -1){
                    patchlabel(temp->value, nextquadlabel()+1);
                    temp = temp->prev;
                }

                temp = conlist;
                while(temp->value != -1){
                    patchlabel(temp->value, temp->toJump);
                    temp = temp->prev;
                }
                if(breakStack != NULL){
                    breaklist = breakStack->stack;
                    breakStack = popStack(breakStack);
                }
                if(conStack != NULL){
                    conlist = conStack->stack;
                    conStack = popStack(conStack);
                }
                toJumpexpr = -1;
            }
#line 3016 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1234 "parser.y" /* yacc.c:1646  */
    {(yyval.intvalue) = nextquadlabel()+1; emit(jump,NULL,NULL,NULL,0,currQuad);}
#line 3022 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1235 "parser.y" /* yacc.c:1646  */
    {(yyval.intvalue) = nextquadlabel()+1;}
#line 3028 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1238 "parser.y" /* yacc.c:1646  */
    {
                if(isRelatioNal == 1){
                        backpatch((yyvsp[-1].exprvalue)->falselist , nextquadlabel() + 3);
                        backpatch((yyvsp[-1].exprvalue)->truelist , nextquadlabel() + 1);
                        emit(assign , newexpr_constbool(1) , NULL , (yyvsp[-1].exprvalue) , -1 , currQuad);
                        emit(jump   , NULL , NULL , NULL , nextquadlabel() + 3 , currQuad);
                        emit(assign , newexpr_constbool(0) , NULL , (yyvsp[-1].exprvalue) , -1 , currQuad);
                        isRelatioNal = 0;
                }
                for_pre* temp = (for_pre*)malloc(sizeof(for_pre));

                if(breaklist != NULL){
                    breakStack = pushStack(breakStack,breaklist);
                }
                ValuesStack* dummy = (ValuesStack*)malloc(sizeof(ValuesStack));
                dummy->value = -1;
                dummy->prev = NULL;
                breaklist = dummy;
                if(conlist != NULL){
                    conStack = pushStack(conStack,conlist);
                }
                dummy = (ValuesStack*)malloc(sizeof(ValuesStack));
                dummy->value = -1;
                dummy->prev = NULL;
                conlist = dummy;
                
                temp->toExpr = (yyvsp[-2].intvalue);
                temp->enter = nextquadlabel()+1;
                emit(if_eq,(yyvsp[-1].exprvalue),newexpr_constbool(1),NULL,0,currQuad);
                (yyval.forvalue) = temp;
            }
#line 3064 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1271 "parser.y" /* yacc.c:1646  */
    {
                conlist->toJump = (yyvsp[-5].intvalue)+1;
                patchlabel((yyvsp[-6].forvalue)->enter, (yyvsp[-2].intvalue)+1);
                patchlabel((yyvsp[-5].intvalue), nextquadlabel()+1);
                patchlabel((yyvsp[-2].intvalue),(yyvsp[-6].forvalue)->toExpr);
                patchlabel((yyvsp[0].intvalue),(yyvsp[-5].intvalue)+1);

                ValuesStack* temp = breaklist;
                while(temp->value != -1){
                    patchlabel(temp->value, nextquadlabel()+1);
                    temp = temp->prev;
                }
                temp = conlist;
                while(temp->value != -1){
                    patchlabel(temp->value, temp->toJump);
                    temp = temp->prev;
                }
                if(breakStack != NULL){
                    breaklist = breakStack->stack;
                    breakStack = popStack(breakStack);
                }
                if(conStack != NULL){
                    conlist = conStack->stack;
                    conStack = popStack(conStack);
                }

                /*
                patchlabel($6->breaklist->value,nextquadlabel()+1);
                patchlabel($6->conlist->value,$2+1);    */
            }
#line 3099 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1301 "parser.y" /* yacc.c:1646  */
    { 
                        ret = 1; 
                        if(top() == NULL){
                                printf(RED"ERROR" RESET ": Can't return outside a function!\n");   
                                found_error = 1;
                                error++;
                        }
                    }
#line 3112 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1308 "parser.y" /* yacc.c:1646  */
    {
                        if((yyvsp[-1].exprvalue)->type == newtable_e){
                            symbolTable* temp; //--------------------
                            temp = findNode(top()->name , Cscope - 1);      //-------------------
                            temp->table = 1;        //-----------------
                        }
                        emit(ret_code,(yyvsp[-1].exprvalue),NULL,NULL,-1,currQuad);
                        (yyval.stmtvalue) = (yyvsp[-1].exprvalue);
                        ret = 0;
                    }
#line 3127 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1318 "parser.y" /* yacc.c:1646  */
    {
                                        if(top() == NULL){
                                            printf(RED"ERROR" RESET ": Can't return outside a function!\n");   
                                            found_error = 1;
                                            error++;
                                        }
                                        emit(ret_code,NULL,NULL,NULL,-1,currQuad);
                                    }
#line 3140 "parser.c" /* yacc.c:1646  */
    break;


#line 3144 "parser.c" /* yacc.c:1646  */
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
#line 1329 "parser.y" /* yacc.c:1906  */


int yyerror (char* yaccProvidedMessage){ fprintf(stderr , RED"Fatal" RESET " %s in line %d\n" , yaccProvidedMessage , yylineno); error++;}

int main(int argc , char** argv){
    
    initHashTable();

    if(argc > 1){
        if(!(yyin = fopen(argv[1] , "r"))) {
            fprintf(stderr , "Cannot read file: %s\n" , argv[1]);
            return 1;
       }
    }else{
        yyin = stdin;
    }
    
    initialize_Arrays();
    yyparse(); 
    emit(program_end,NULL,NULL,NULL,-1,currQuad);
    if(error>0){
        printf(RED"Compile failed" RESET " with %d error "GREEN"NOOB"RESET" (Νατάσα όχι για σένα.)\n",error);
    }else{
        printQuads();
            ;
        generate();
        printf("----------------------------------------------------------------------------------\n");
        printInst();
        printHash();
        printArrays();
        writeBinaryFile();
    }
    return 0;
}
