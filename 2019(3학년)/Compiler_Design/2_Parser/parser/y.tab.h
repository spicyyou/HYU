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
    IF = 258,
    ELSE = 259,
    INT = 260,
    RETURN = 261,
    VOID = 262,
    WHILE = 263,
    THEN = 264,
    END = 265,
    REPEAT = 266,
    UNTIL = 267,
    READ = 268,
    WRITE = 269,
    ID = 270,
    NUM = 271,
    LBRACE = 272,
    RBRACE = 273,
    LCURLY = 274,
    RCURLY = 275,
    LT = 276,
    LE = 277,
    GT = 278,
    GE = 279,
    NE = 280,
    COMMA = 281,
    ERROR = 282,
    ASSIGN = 283,
    EQ = 284,
    PLUS = 285,
    MINUS = 286,
    TIMES = 287,
    OVER = 288,
    LPAREN = 289,
    RPAREN = 290,
    SEMI = 291
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define INT 260
#define RETURN 261
#define VOID 262
#define WHILE 263
#define THEN 264
#define END 265
#define REPEAT 266
#define UNTIL 267
#define READ 268
#define WRITE 269
#define ID 270
#define NUM 271
#define LBRACE 272
#define RBRACE 273
#define LCURLY 274
#define RCURLY 275
#define LT 276
#define LE 277
#define GT 278
#define GE 279
#define NE 280
#define COMMA 281
#define ERROR 282
#define ASSIGN 283
#define EQ 284
#define PLUS 285
#define MINUS 286
#define TIMES 287
#define OVER 288
#define LPAREN 289
#define RPAREN 290
#define SEMI 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
