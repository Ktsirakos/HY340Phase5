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
#line 74 "parser.y" /* yacc.c:1909  */

    char*               stringvalue;
    int                 intvalue;
    double              realvalue;
    struct expr_type*        exprvalue;
    struct symbolTable*     symbol;
    struct for_pre*	    forvalue;
    struct stmt_list*   stmtvalue;
    struct quad_t*          quadvalue;

#line 171 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
