/****************************************************/
/* File: globals.h                                  */
/* Yacc/Bison Version                               */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Yacc/Bison generates internally its own values
 * for the tokens. Other files can access these values
 * by including the tab.h file generated using the
 * Yacc/Bison option -d ("generate header")
 *
 * The YYPARSER flag prevents inclusion of the tab.h
 * into the Yacc/Bison output itself
 */

#ifndef YYPARSER

/* the name of the following file may change */
#include "y.tab.h"

/* ENDFILE is implicitly defined by Yacc/Bison,
 * and not included in the tab.h file
 */
#define ENDFILE 0

#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

/* Yacc/Bison generates its own integer values
   for tokens
   */
   typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code;

extern int lineno; /* source line number for listing */

/*******************************************/
/********* Syntax Tree for parsing *********/
/*******************************************/

typedef enum {StmtK, ExpK, DecK} NodeKind;
typedef enum {IfK,AssignK,CompK, SelK, IterK, RetK,RepeatK,ReadK,WriteK} StmtKind;
typedef enum {VarK, ArrVarK, OpK, CallK, ConstK, IdK} ExpKind;
typedef enum {TypeK, DecVarK, DecFunK, DecArrK, ParamVarK, ParamArrK} DecKind;

/* ExpType is used for type checking */
typedef enum {Void, Integer, Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
{
	struct treeNode* child[MAXCHILDREN];
	struct treeNode* sibling;
	int lineno;
	NodeKind nodekind;
	union { StmtKind stmt; 
		ExpKind exp; 
		DecKind dec; } kind;
	union { TokenType op; 
		int val; 
		char* name;
	//	int size;
		} attr;
	//int arrsize;
	ExpType type; /* for type checking of exps */
} TreeNode;

/*******************************************/
/************ Flags for tracing ************/
/*******************************************/

/* TraceScan = TRUE causes token information to be 
 * printed to the listing file as each token is
 * recognized by the scanner
 */

extern int EchoSource;
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;
extern int TraceAnalyze;
extern int TraceCode;

extern int Error;
#endif

