/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"
#include "util.h"

static char * funcName;
static int preserveLastScope = FALSE;

/* counter for variable memory locations */

/* Procedure traverse is a generic recursive
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL)
  { preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

static void inoutput(void)
{ TreeNode *func;
  TreeNode *typeSpec;
  TreeNode *param;
  TreeNode *compStmt;

  func = newDeclNode(FuncK);

  typeSpec = newTypeNode(FuncK);
  typeSpec->attr.type = INT;
  func->type = Integer;

  compStmt = newStmtNode(CompK);
  compStmt->child[0] = NULL;     
  compStmt->child[1] = NULL;     
  func->lineno = 0;
  func->attr.name = "input";
  func->child[0] = typeSpec;
  func->child[1] = NULL;        
  func->child[2] = compStmt;

  st_insert("input", -1, addLocation(), func);

  func = newDeclNode(FuncK);

  typeSpec = newTypeNode(FuncK);
  typeSpec->attr.type = VOID;
  func->type = Void;

  param = newParamNode(NonArrParamK);
  param->attr.name = "arg";
  param->child[0] = newTypeNode(FuncK);
  param->child[0]->attr.type = INT;
  param->type=Integer;
  compStmt = newStmtNode(CompK);
  compStmt->child[0] = NULL;      
  compStmt->child[1] = NULL;      
  func->lineno = 0;
  func->attr.name = "output";
  func->child[0] = typeSpec;
  func->child[1] = param;
  func->child[2] = compStmt;

  st_insert("output", -1, addLocation(), func);
}

/* nullProc is a do-nothing procedure to
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}

static void symbolError(TreeNode * t, char * message)
{ fprintf(listing,"Symbol error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure insertNode inserts
 * identifiers stored in t into
 * the symbol table
 */
static void insertNode( TreeNode * t)
{ switch (t->nodekind)
  { case StmtK:
      switch (t->kind.stmt)
      { case CompK:
          if (preserveLastScope) {
            preserveLastScope = FALSE;
          } else {
            Scope scope = sc_create(funcName);
            sc_push(scope);
          }
          t->attr.scope = sc_top();
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case IdK:
        case ArrIdK:
        case CallK:
          if (st_lookup(t->attr.name) == -1)
            symbolError(t, "undelcared symbol");
          else
            st_add_lineno(t->attr.name,t->lineno);
          break;
        default:
          break;
      }
      break;
    case DeclK:
      switch (t->kind.decl)
      { case FuncK:
          funcName = t->attr.name;
          if (st_lookup_top(funcName) >= 0) {
            symbolError(t,"function already declared");
            break;
          }
          st_insert(funcName,t->lineno,addLocation(),t);
          sc_push(sc_create(funcName));
          preserveLastScope = TRUE;
          switch (t->child[0]->attr.type)
          { case INT:
              t->type = Integer;
              break;
            case VOID:
            default:
              t->type = Void;
              break;
          }
          break;
        case VarK:
        case ArrVarK:
          { char *name;
		//		  fprintf(listing,"aaaaaaaaaaa\m");
            if (t->child[0]->attr.type == VOID) {
              symbolError(t,"variable should have non-void type");
              break;
            }
            if (t->kind.decl == VarK) {
              name = t->attr.name;
              t->type = Integer;
            } else {
              name = t->attr.arr.name;
              t->type = IntegerArray;
            }
			//fprintf(listing, "%s\n",name);
            if (st_lookup_top(name) < 0){
              st_insert(name,t->lineno,addLocation(),t);
			}
            else
			{		
              symbolError(t,"symbol already declared");
			}
          }
          break;
        default:
          break;
      }
      break;
    case ParamK:
      if (t->child[0]->attr.type == VOID)
	  {
        symbolError(t->child[0],"void type parameter is not allowed");
	  }//if (st_lookup(t->attr.name) == -1) {
	  else{
	  if(st_lookup(t->attr.name)==-1){
		st_insert(t->attr.name,t->lineno,addLocation(),t);
        if (t->kind.param == NonArrParamK)
          t->type = Integer;
        else{
		//		fprintf(listing, "abcd\n");
			t->type=IntegerArray;
		}
		
        	//symbolError(t,"symbol already declared");
	  }}
      break;
    default:
      break;
  }
}

static void afterInsertNode( TreeNode * t )
{ switch (t->nodekind)
  { case StmtK:
      switch (t->kind.stmt)
      { case CompK:
          sc_pop();
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/* Function buildSymtab constructs the symbol
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ globalScope = sc_create(NULL);
  sc_push(globalScope);
  inoutput();
  traverse(syntaxTree,insertNode,afterInsertNode);
  sc_pop();
  if (TraceAnalyze)
  { fprintf(listing,"\nSymbol table:\n\n");
    printSymTab(listing);
  }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

static void beforeCheckNode(TreeNode * t)
{ switch (t->nodekind)
  { case DeclK:
      switch (t->kind.decl)
      { case FuncK:
          funcName = t->attr.name;
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case CompK:
          sc_push(t->attr.scope);
          break;
        default:
          break;
      }
    default:
      break;
  }
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ switch (t->nodekind)
  { case StmtK:
      switch (t->kind.stmt)
      { case CompK:
          sc_pop();
          break;
		case IfK:
		  if(t->child[0]->type==Void)
				  typeError(t->child[0],"if can not has void value");
        case IterK:
          if (t->child[0]->type == Void)
            typeError(t->child[0],"while can not has void value");
          break;
        case RetK:
          { const TreeNode * funcDecl =
                st_bucket(funcName)->treeNode;
            const ExpType funcType = funcDecl->type;
            const TreeNode * expr = t->child[0];

            if (funcType == Void &&(expr != NULL && expr->type != Void)) {
              typeError(t,"expected no return value");
            } else if (funcType == Integer &&(expr == NULL || expr->type == Void)) {
              typeError(t,"expected return value");
            } else if(funcType != expr->type){
					typeError(t,"return value must be same");
          }
		  }
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case AssignK:
          if (t->child[0]->type == IntegerArray)
            typeError(t->child[0],"assignment to array variable");
          else if (t->child[1]->type == Void)
            typeError(t->child[0],"assignment of void value");
		  else if(t->child[0]->type != t->child[1]->type)
				  typeError(t->child[0],"invalid expression");
          else
            t->type = t->child[0]->type;
          break;
        case OpK:
          { ExpType leftType, rightType;
            TokenType op;
            leftType = t->child[0]->type;
            rightType = t->child[1]->type;
            op = t->attr.op;
			if(leftType!=rightType){
					typeError(t, "invaild expression");
			}
			else if (leftType == Void ||
                rightType == Void)
              typeError(t,"two operands should have non-void type");
            else if (leftType == IntegerArray &&
                rightType == IntegerArray)
              typeError(t,"not both of operands can be array");
            else if (op == MINUS &&
                leftType == Integer &&
                rightType == IntegerArray)
              typeError(t,"invalid operands to binary expression");
            else if ((op == TIMES || op == OVER) &&
                (leftType == IntegerArray ||
                 rightType == IntegerArray))
              typeError(t,"invalid operands to binary expression");
            else {
              t->type = Integer;
            }
          }
          break;
        case ConstK:
          t->type = Integer;
          break;
        case IdK:
        case ArrIdK:
          { const char *symbolName = t->attr.name;
            const BucketList bucket =
                st_bucket(symbolName);
            TreeNode *symbolDecl = NULL;

            if (bucket == NULL)
              break;
            symbolDecl = bucket->treeNode;

            if (t->kind.exp == ArrIdK) {
              if (symbolDecl->kind.decl != ArrVarK &&
                  symbolDecl->kind.param != ArrParamK)
                typeError(t,"expected array symbol");
              else if (t->child[0]->type != Integer)
                typeError(t,"index expression should have integer type");
              else
                t->type = Integer;
            } else {
              t->type = symbolDecl->type;
            }
          }
          break;
        case CallK:
          { const char *callingFuncName = t->attr.name;
            const TreeNode * funcDecl =
                st_bucket(callingFuncName)->treeNode;
            TreeNode *arg;
            TreeNode *param;

            if (funcDecl == NULL)
              break;

            arg = t->child[0];
            param = funcDecl->child[1];

            if (funcDecl->kind.decl != FuncK)
            { typeError(t,"expected function symbol");
              break;
            }

            while (arg != NULL)
            { if (param == NULL)
                typeError(arg,"the number of parameters is wrong");
              else if (arg->type == Void){
				//fprintf(listing, "%s\n",arg->attr.name);
                typeError(arg,"void value cannot be passed as an argument");
			  }else if(arg->type !=param->type){
					  //fprintf(listing, "%s\n",arg->attr.name);
					 /* if(param->type==Void){
							  fprintf(listing, "void\n");
					  }else{
							  fprintf(listing,"else\n");
					  }*/
			 	typeError(arg,"arg and param should have same type");
			  }
			  else {  
                arg = arg->sibling;
                param = param->sibling;
                continue;
              }
         
              break;
            }

            if (arg == NULL && param != NULL)
              typeError(t->child[0],"the number of parameters is wrong");

            t->type = funcDecl->type;
          }
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/* Procedure typeCheck performs type checking
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ sc_push(globalScope);
  traverse(syntaxTree,beforeCheckNode,checkNode);
  sc_pop();
}
