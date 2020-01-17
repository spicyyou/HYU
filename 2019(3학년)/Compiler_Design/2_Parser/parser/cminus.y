%{
#define YYPARSER
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode*
static char* savedName; /* for use in assignments as a name */
static int savedNumber; /* for use in assignments as a number */
static int savedLineNo; /* ditto */
static TreeNode* savedTree; /* stores syntax tree for later return */
static int yylex(void);
%}

%token IF ELSE INT RETURN VOID WHILE THEN END REPEAT UNTIL READ WRITE
%token ID NUM
%token LBRACE RBRACE LCURLY RCURLY LT LE GT GE NE COMMA
%token ERROR
%token ASSIGN EQ PLUS MINUS TIMES OVER LPAREN RPAREN SEMI

%%

program
	: declaration_list
	  { savedTree = $1; }
	;


declaration_list
	: declaration_list declaration	
	  {	
		YYSTYPE t = $1;
		if ( t != NULL )
		{
			while ( t -> sibling != NULL )
				t = t -> sibling;
			t -> sibling = $2;
			$$ = $1;
		}		
 		else
			$$ = $2;
	  }
	| declaration 	
	  { $$ = $1; }
	;


declaration
	: var_declaration	
	  { $$ = $1; }
	| fun_declaration	
	  { $$ = $1; }
	;


identifier
	: ID
	  {
		$$ = newExpNode(IdK);
		$$ -> attr.name = copyString(tokenString);
	  	//savedName = copyString(tokenString);
		//savedLineNo = lineno;
	  }
	;


number
	: NUM
	  {
		$$ = newExpNode(ConstK);
		$$->attr.val=atoi(tokenString);
		///savedLineNo=lineno;
		//savedNumber = atoi(tokenString);
		//savedLineNo=lineno;
	  }
	;


var_declaration
	: type_specifier identifier SEMI	
	  { 
		$$ = newDecNode(DecVarK);
		$$ -> child[0] = $1;
		$$ -> child[1] = $2;
		//$$->attr.name=savedName;
		//$$->lineno=lineno;
	  }
	| /*type_specifier identifier
{
		$$ = newDecNode(DecArrK);
		$$->attr.name=savedName;
		$$->child[0]=$1;

} LBRACE number RBRACE SEMI
{
		$$->attr.size=savedNumber;

}*/
	type_specifier identifier LBRACE number RBRACE SEMI	
	  {
		$$ = newDecNode(DecArrK);
		$$ -> child[0] = $1;
		$$ -> child[1] = $2;//name
		$$ -> child[2] = $4;//numberi
		//$$->lineno=lineno;
		//$$->attr.name=savedName;
		//$$->arrsize=savedNumber;
		//$$->attr.size = savedNumber;
		//$$->child[0]=$1;
		//$$->lineno=lineno;
	  }
	;


type_specifier
	: INT	
	  { 
		$$ = newDecNode(TypeK); 
	  	$$ -> type = Integer;	
	  }
	| VOID	
	  { 
		$$ = newDecNode(TypeK); 
		$$ -> type = Void;
	  }  
	;
/*fun_declaration : type_specifier identifier{
						  $$=newDecNode(DecFunK);
						  $$->lineno=lineno;
						  $$->attr.name = savedName;
				  } LPAREN params RPAREN compound_stmt{
						  $$=$3;
						  $$->child[0]=$1;
						  $$->child[1]=$5;
						  $$->child[2]=$7;
				  }
;
*/

fun_declaration
	: type_specifier identifier LPAREN params RPAREN compound_stmt
	  {
		$$ = newDecNode(DecFunK);
		$$ -> attr.name = copyString($2->attr.name);
		//$$->lineno=lineno;
		$$ -> child[0] = $1;
		$$ -> child[1] = $4;
		$$ -> child[2] = $6;
	  }
	;
	

params
	: param_list	
	  { $$ = $1; }
	| VOID		
	  { $$ = NULL;
	  }
	;


param_list
	: param_list COMMA param
	  {  
		YYSTYPE t = $1;
		if ( t != NULL )
		{
			while ( t -> sibling != NULL )
				t = t -> sibling;
			t -> sibling = $3;
			$$ = $1;
		}		
		else
			$$ = $3;
	  }  
	| param 
	  { $$ = $1; }
	;


param
	: type_specifier identifier
	  {
		$$ = newDecNode(ParamVarK);
		$$ -> child[0] = $1;
		$$ -> child[1] = $2;
		//$$->attr.name = savedName;
	  }
	| type_specifier identifier LBRACE RBRACE
	  {
		$$ = newDecNode(ParamArrK);
		$$ -> child[0] = $1;
		$$ -> child[1] = $2;
	//	$$->attr.name=savedName;
	  }
	;


compound_stmt
	: LCURLY local_declarations statement_list RCURLY
	  {
		$$ = newStmtNode(CompK);
		$$ -> child[0] = $2;
		$$ -> child[1] = $3;
	  }
	;


local_declarations
	: local_declarations var_declaration
	  {
		YYSTYPE t = $1;
		if ( t != NULL )
		{
			while ( t -> sibling != NULL )
				t = t -> sibling;
			t -> sibling = $2;
			$$ = $1;
		}		
		else
			$$ = $2;
	  }
	| %empty
	  { $$ = NULL; }
	;


statement_list
	: statement_list statement
	  {	
		YYSTYPE t = $1;
		if ( t != NULL )
		{
			while ( t -> sibling != NULL )
				t = t -> sibling;
			t -> sibling = $2;
			$$ = $1;
		}		
		else
			$$ = $2;
	  }
	| %empty
	  { $$ = NULL; }
	;


statement
	: expression_stmt
	  { $$ = $1; }
	| compound_stmt
	  { $$ = $1; }
	| selection_stmt
	  { $$ = $1; }
	| iteration_stmt
	  { $$ = $1; }
	| return_stmt
	  { $$ = $1; }
	;


expression_stmt
	: expression SEMI
	  { $$ = $1; }
	| SEMI
	  { $$ = NULL; }
	;


selection_stmt
	: IF LPAREN expression RPAREN statement
	  { 
		$$ = newStmtNode(SelK);
		$$ -> child[0] = $3;
		$$ -> child[1] = $5;
		$$->child[2]=NULL;
	  }
	| IF LPAREN expression RPAREN statement ELSE statement
	  {
		$$ = newStmtNode(SelK);
		$$ -> child[0] = $3;
		$$ -> child[1] = $5;
		$$ -> child[2] = $7;
	  }
	;


iteration_stmt
	: WHILE LPAREN expression RPAREN statement
	  {
		$$ = newStmtNode(IterK);
		$$ -> child[0] = $3;
		$$ -> child[1] = $5;
	  }
	;


return_stmt
	: RETURN SEMI
	  {
		$$ = newStmtNode(RetK);
		$$->child[0]=NULL;
	  }
	| RETURN expression SEMI
	  {
		$$ = newStmtNode(RetK);
		$$ -> child[0] = $2;
	  }
	;

expression
	: var ASSIGN expression
	  {
		$$ = newStmtNode(AssignK);
		$$ -> child[0] = $1;
		$$ -> child[1] = $3;
	  }
	| simple_expression
	  {
		$$ = $1;
	  }
	;

var
	: identifier
	  {
		$$=$1;
		//$$ = newExpNode(IdK);
		//$$->attr.name=savedName;
	  }
	| /*identifier
{
		$$=newExpNode(ArrVarK);
		$$->attr.name = savedName;
} LBRACE expression RBRACE
{
		$$->child[0]=$3;
}*/
	 identifier LBRACE expression RBRACE
	  {
		$$ = newExpNode(ArrVarK);
		//$$->attr.name=savedName;
		$$ -> child[0] = $1;
		$$ -> child[1] = $3;
	  }
	;


simple_expression
	: additive_expression relop additive_expression
	  {
		$$ = $2;
		$$ -> child[0] = $1;
		$$ -> child[1] = $3;	
	  }
	| additive_expression
	  {
		$$ = $1;
	  }
	;


relop
	: LE
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = LE;
	  }
	| LT
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = LT;
	  }
	| GT
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = GT;
	  }
	| GE
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = GE;
	  }
	| EQ
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = EQ;
	  }
	| NE
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = NE;
	  }
	;


additive_expression
	: additive_expression addop term
	  {
		$$ = $2;
		$$ -> child[0] = $1;
		$$ -> child[1] = $3;
	  }
	| term
	  {
		$$ = $1;
	  }
	;


addop
	: PLUS
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = PLUS;
	  }
	| MINUS
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = MINUS;
	  }

	;


term
	: term mulop factor 
	  {
	  	$$ = $2;
		$$ -> child[0] = $1;
		$$ -> child[1] = $3;
	  }
	| factor
	  {
		$$ = $1;
	  }
	  ;


mulop
	: TIMES
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = TIMES;
	  }
	| OVER
	  {
		$$ = newExpNode(OpK);
		$$ -> attr.op = OVER;
	  }
	;


factor
	: LPAREN expression RPAREN
	  {
		$$ = $2;
	  }
	| var
	  {
		$$ = $1;
	  }
	| call
	  {
		$$ = $1;
	  }
	| number
	  {
		$$=$1;
			  //$$ = newExpNode(ConstK);
		//$$->attr.val = atoi(tokenString);
	  }
	;


call
	:/* identifier{
			$$=newExpNode(CallK);
			$$->attr.name=savedName;
	}LPAREN args RPAREN
{
		$$=$2;
		$$->child[0]=$4;
}*/
	
	identifier LPAREN args RPAREN
	  {
		$$ = newExpNode(CallK);
		//$$->attr.name=savedName;
		$$ -> child[0] = $1;
		$$ -> child[1] = $3;	
	  }
;

args
	: arg_list
	  { $$ = $1; }
	| %empty
	  { $$ = NULL; }
	;


arg_list
	: arg_list COMMA expression
	  {
		YYSTYPE t = $1;
		if (t != NULL)
              	{
			while (t -> sibling)
               	   		t = t -> sibling;
                	t -> sibling = $3;
                	$$ = $1;
              	}
              	else
                	$$ = $3;
	   }
	| expression
	  { $$ = $1; }
	;
	

%%

int yyerror(char* message)
{
	fprintf(listing, "Syntax error at line %d: %s\n", lineno, message);
	fprintf(listing, "Current token: ");
	fprintf(listing, "%c %s\n", yychar, tokenString);
	Error = TRUE;
	return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier version of the TINY scanner */
static int yylex()
{
	return getToken();
}

TreeNode* parse()
{
	yyparse();
	return savedTree;
}	


