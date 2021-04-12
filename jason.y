/****************************************************/
/*File: jason.y                                     */
/*Grammer Analysis for Jason Compiler               */
/*Yueyang (Jason) Pan                               */
/****************************************************/
%{
    #include "globals.hpp"

%}

%token IF THEN ELSE WHILE BREAK CONTINUE RETURN
%token CONST INT VOID
%token ID DEC_NUM OCT_NUM HEX_NUM
%token ASSIGN SEMI COMMA LLPAREN LRPAREN MLPAREN MRPAREN SLPAREN SRPAREN
%token NOT EQ NEQ LT GT LTE GTE PLUS MINUS TIMES OVER MOD AND OR
%token SIN_COMMENT MUL_LCOMMENT MUL_RCOMMENT
%token ERROR

%% /* Grammar for SysY */
program     : CompUnit
                {}
            ;
CompUnit    : Decl {}
            | FuncDef {}
            | CompUnit Decl {}
            | CompUnit FuncDef {}
            ;

Decl        : ConstDecl {}
            | VarDecl {}
            ;

ConstDecl   : CONST INT ConstDef SEMI {}
            | CONST INT ConstDef MulConstDef SEMI {}
            ;

MulConstDef : COMMA ConstDef {}
            | COMMA ConstDef MulConstDef {}
            ;

ConstDef    : ID EQ ConstInitVal {}
            | ID Dimension EQ ConstInitVal {}
            ;

Dimension   : MLPAREN ConstExp MRPAREN {}
            | MLPAREN ConstExp MRPAREN Dimension {}
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
