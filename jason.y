/****************************************************/
/*File: jason.y                                     */
/*Grammer Analysis for Jason Compiler               */
/*Yueyang (Jason) Pan                               */
/****************************************************/
%{
    #include "globals.h"
    #include <algorithm>
    #define YYSTYPE ASTPtr
    static ASTPtr root;
%}


%token IF THEN ELSE WHILE BREAK CONTINUE RETURN
%token CONST INT VOID
%token ID DEC_NUM OCT_NUM HEX_NUM
%token ASSIGN SEMI COMMA LLPAREN LRPAREN MLPAREN MRPAREN SLPAREN SRPAREN
%token NOT EQ NEQ LT GT LTE GTE PLUS MINUS TIMES OVER MOD AND OR
%token SIN_COMMENT MUL_LCOMMENT MUL_RCOMMENT
%token ERROR

%% /* Grammar for SysY */
program     : CompUnit {root = std::move($1); }
            ;
CompUnit    : Decl { 
    ASTPtrList units;
    units.push_back(std::move($1));
    $$ = std::make_shared<CompUnitAST>(std::move(units));  }
            | FuncDef {
    ASTPtrList units;
    units.push_back(std::move($1));
    $$ = std::make_shared<CompUnitAST>(std::move(units));  }
            | CompUnit Decl {
    auto p_CompUnitAST = std::dynamic_pointer_cast<CompUnitAST>($1);
    p_CompUnitAST->_units.push_back(std::move($2));
    $$ = p_CompUnitAST;
            }
            | CompUnit FuncDef {
    auto p_CompUnitAST = std::dynamic_pointer_cast<CompUnitAST>($1);
    p_CompUnitAST->_units.push_back(std::move($2));
    $$ = p_CompUnitAST;
            }
            ;

Decl        : ConstDecl {$$ = $1;}
            | VarDecl {$$ = $1;}
            ;

ConstDecl   : CONST INT ConstDefList SEMI { 
    $$ =  std::make_shared<ConstDeclAST>(INT, std::move($3));}
            ;

ConstDefList : ConstDef {
    ASTPtrList const_defs;
    const_defs.push_back(std::move($1));
    $$ = std::make_shared<ConstDefListAST>(std::move(const_defs));
}
            | ConstDefList COMMA ConstDef {
    auto p_ConstDefListAST = std::dynamic_pointer_cast<ConstDefListAST>($1);
    p_ConstDefListAST.const_defs().push_back(std::move($3));
    $$ = p_ConstDefListAST;
}
            ;

ConstDef    : ID EQ ConstInitVal {
    auto p_IDAST = std::dynamic_pointer_cast<IDAST>($1);
    $$ = std::make_shared<ConstDefAST>(p_IDAST.id(),nullptr, std::move($3));
}
            | ID Dimension EQ ConstInitVal {
    auto p_IDAST = std::dynamic_pointer_cast<IDAST>($1);
    $$ = std::make_shared<ConstDefAST>(p_IDAST.id(),std::move($2), std::move($4));
}
            ;

Dimension   : MLPAREN ConstExp MRPAREN {
    ASTPtrList const_exprs;
    const_exprs.push_back(std::move($2));
    $$ = std::make_shared<ConstDefListAST>(std::move(const_exprs));
}
            | Dimension MLPAREN ConstExp MRPAREN  {
    auto p_DimensionAST = std::dynamic_pointer_cast<DimensionAST>($1);
    p_DimensionAST.dims().push_back(std::move($3));
    $$ = p_DimensionAST;            
}
            ;

ConstInitVal: ConstExp {}
            | EMPTY {}
            | LLPAREN ConstInitVal LRPAREN {}
            | LLPAREN ConstInitVal MulConstInitVal LRPAREN {}
            ;

EMPTY       : LLPAREN LRPAREN {}
            ;

MulConstInitVal : COMMA ConstInitVal {}
                | COMMA ConstInitVal MulConstInitVal {}
                ;
VarDecl     : INT VarDef SEMI {}
            | INT VarDef MulVarDef SEMI {}
            ;

MulVarDef   : COMMA VarDef {}
            | COMMA VarDef MulVarDef {}
            ;

VarDef      : ID {}
            | ID EQ InitVal {}
            | ID Dimension {}
            | ID Dimension EQ InitVal {}
            ;

InitVal     : Exp {}
            | EMPTY {}
            | LLPAREN InitVal LRPAREN {}
            | LLPAREN InitVal MulInitVal LRPAREN {}
            ;

MulInitVal  : COMMA InitVal {}
            | COMMA InitVal MulInitVal {}
            ;

FuncDef     : FuncType ID SLPAREN SRPAREN Block {}
            | FuncType ID SLPAREN FuncFParams SRPAREN Block {}
            ;

FuncType    : VOID {}
            | INT {}
            ;

FuncFParams : FuncFParam {}
            | FuncFParam MulFuncFParam {}
            ;

MulFuncFParam : COMMA FuncFParams {}
            | COMMA FuncFParams MulFuncFParam {}
            ;

FuncFParam  : INT ID {}
            | INT ID MLPAREN MRPAREN {}
            | INT ID MLPAREN MRPAREN Dimension {}
            ;

Block       : EMPTY {};
            | LLPAREN BlockItem LRPAREN {}
            ;

BlockItem   : Decl {}
            | Stmt {}
            ;

Stmt        : Block {}
            | LVal EQ Exp SEMI {}
            | SEMI {}
            | Exp SEMI {}
            | IF SLPAREN Cond SRPAREN Stmt {}
            | IF SLPAREN Cond SRPAREN Stmt ELSE Stmt {}
            | WHILE SLPAREN Cond SRPAREN Stmt {}
            | BREAK SEMI {}
            | CONTINUE SEMI {}
            | RETURN SEMI {}
            | RETURN Exp SEMI {}
            ;

Exp         : AddExp {}
            ;

ConstExp    : AddExp {}
            ;

Cond        : LOrExp {}
            ;

LVal        : ID {}
            | ID DimExp {}
            ;

DimExp      : MLPAREN Exp MRPAREN {}
            | MLPAREN Exp MRPAREN DimExp {}
            ;

PrimaryExp  : SLPAREN Exp SRPAREN {}
            | LVal {}
            | DEC_NUM {}
            | OCT_NUM {}
            | HEX_NUM {}
            ;

UnaryExp    : PrimaryExp {}
            | ID SLPAREN SRPAREN {}
            | ID SLPAREN FuncRParams SRPAREN
            | UnaryOp UnaryExp {}
            ;

UnaryOp     : PLUS {}
            | MINUS {}
            | NOT {}
            ;

FuncRParams : Exp {}
            | Exp MultiExp {}
            ;

MultiExp    : COMMA Exp {}
            | COMMA Exp MultiExp {}
            ;

MulExp      : UnaryExp {}
            | MulExp TIMES UnaryExp {}
            | MulExp OVER UnaryExp {}
            | MulExp MOD UnaryExp {}
            ;

AddExp      : MulExp {}
            | AddExp PLUS MulExp {}
            | AddExp MINUS MulExp {}
            ;

RelExp      : AddExp {}
            | RelExp LT AddExp {}
            | RelExp GT AddExp {}
            | RelExp LTE AddExp {}
            | RelExp GTE AddExp {}
            ;

EqExp       : RelExp {}
            | EqExp EQ RelExp {}
            | EqExp NEQ RelExp {}
            ;

LAndExp     : EqExp {}
            | LAndExp AND EqExp {}

LOrExp      : LAndExp {}
            | LOrExp OR LAndExp {}


%%
