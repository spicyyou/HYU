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
    ELSE = 258,
    IF = 259,
    INT = 260,
    RETURN = 261,
    VOID = 262,
    WHILE = 263,
    ID = 264,
    NUM = 265,
    PLUS = 266,
    MINUS = 267,
    TIMES = 268,
    OVER = 269,
    LT = 270,
    LTEQ = 271,
    GT = 272,
    GTEQ = 273,
    EQ = 274,
    NEQ = 275,
    ASSIGN = 276,
    SEMI = 277,
    COMMA = 278,
    LPAREN = 279,
    RPAREN = 280,
    LBRACK = 281,
    RBRACK = 282,
    LBRACE = 283,
    RBRACE = 284,
    ERROR = 285
  };
#endif
/* Tokens.  */
#define ELSE 258
#define IF 259
#define INT 260
#define RETURN 261
#define VOID 262
#define WHILE 263
#define ID 264
#define NUM 265
#define PLUS 266
#define MINUS 267
#define TIMES 268
#define OVER 269
#define LT 270
#define LTEQ 271
#define GT 272
#define GTEQ 273
#define EQ 274
#define NEQ 275
#define ASSIGN 276
#define SEMI 277
#define COMMA 278
#define LPAREN 279
#define RPAREN 280
#define LBRACK 281
#define RBRACK 282
#define LBRACE 283
#define RBRACE 284
#define ERROR 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
