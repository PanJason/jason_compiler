/****************************************************/
/*File: jason.y                                     */
/*Grammer Analysis for Jason Compiler               */
/*Yueyang (Jason) Pan                               */
/****************************************************/
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define parse.trace
%define parse.error verbose
%define api.token.prefix {TOK_}

%code requires{
    #include <string>
    #include <algorithm>
    #include <optional>
    #include <vector>
    #include <memory>
    #include <utility>
    #include <stdlib.h>
    #include "global.h"
    class driver;
}

%language "c++"
%locations
%param { driver& drv }

%code {
    #include "driver.h"
    #define DEBUG
}


%token IF THEN ELSE WHILE BREAK CONTINUE RETURN;
%token CONST INT VOID;
%token ASSIGN SEMI COMMA LLPAREN LRPAREN MLPAREN MRPAREN SLPAREN SRPAREN;
%token NOT EQ NEQ LT GT LTE GTE PLUS MINUS TIMES OVER MOD AND OR;
//%token SIN_COMMENT MUL_LCOMMENT MUL_RCOMMENT
%token ERROR 
%token
  END  0  "end of file"
;
%token <int> OCT_NUM DEC_NUM HEX_NUM
%token <std::string> ID
%type  <ASTPtr> program CompUnit Decl ConstDecl ConstDefList ConstDef
Dimension ConstInitVal ConstInitValArray ConstInitValList VarDecl VarDefList
InitVal VarDef InitValArray FuncDef InitValList FuncFParams FuncFParam
FuncFParamVar FuncFParamArray Block BlockItems BlockItem Stmt Assign_stmt
Exp_stmt If_stmt While_stmt Cond_stmt Return_stmt Exp Cond LVal PrimaryExp
UnaryExp FuncCallExp FuncRParams MulExp AddExp RelExp EqExp LAndExp LOrExp
IDENT

%% /* Grammar for SysY */
program     : CompUnit {drv.root = std::move($1); }
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
    $$ =  std::make_shared<ConstDeclAST>(token::TOK_INT, std::move($3));}
            ;

ConstDefList : ConstDef {
    ASTPtrList const_defs;
    const_defs.push_back(std::move($1));
    $$ = std::make_shared<ConstDefListAST>(std::move(const_defs));
}
            | ConstDefList COMMA ConstDef {
    auto p_ConstDefListAST = std::dynamic_pointer_cast<ConstDefListAST>($1);
    p_ConstDefListAST->const_defs().push_back(std::move($3));
    $$ = p_ConstDefListAST;
}
            ;

ConstDef    : IDENT ASSIGN ConstInitVal {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1);
    $$ = std::make_shared<ConstDefAST>(p_IdAST->id(), nullptr, std::move($3), 0);
}
            | IDENT Dimension ASSIGN ConstInitVal {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1);
    $$ = std::make_shared<ConstDefAST>(p_IdAST->id(), std::move($2), std::move($4), 1);
}
            ;

Dimension   : MLPAREN Exp MRPAREN {
    ASTPtrList const_exprs;
    const_exprs.push_back(std::move($2));
    $$ = std::make_shared<DimensionAST>(std::move(const_exprs));
}
            | Dimension MLPAREN Exp MRPAREN  {
    auto p_DimensionAST = std::dynamic_pointer_cast<DimensionAST>($1);
    p_DimensionAST->dims().push_back(std::move($3));
    $$ = p_DimensionAST;            
}
            ;

ConstInitVal: Exp { $$ = $1; }
            | ConstInitValArray { $$ = $1; }
            ;

ConstInitValArray : EMPTY {
    $$ = std::make_shared<ConstInitValArrayAST>(nullptr);
}
            | LLPAREN ConstInitValList LRPAREN {
    $$ = std::make_shared<ConstInitValArrayAST>(std::move($2));
}
            ;

EMPTY       : LLPAREN LRPAREN
            ;

ConstInitValList : ConstInitVal {
    ASTPtrList const_exprs;
    const_exprs.push_back(std::move($1));
    $$ = std::make_shared<ConstInitValAST>(std::move(const_exprs));
}
            | ConstInitValList COMMA ConstInitVal {
    auto p_ConstInitValList = std::dynamic_pointer_cast<ConstInitValAST>($1);
    p_ConstInitValList->const_exprs().push_back(std::move($3));
    $$ = p_ConstInitValList;
}
            ;

VarDecl     : INT VarDefList SEMI {
    $$ =  std::make_shared<VarDeclAST>(token::TOK_INT, std::move($2));
}
            ;

VarDefList  : VarDef {
    ASTPtrList var_defs;
    var_defs.push_back(std::move($1));
    $$ = std::make_shared<VarDefListAST>(std::move(var_defs));
}
            | VarDefList COMMA VarDef {
    auto p_VarDefList = std::dynamic_pointer_cast<VarDefListAST>($1);
    p_VarDefList->var_defs().push_back(std::move($3));
    $$ = p_VarDefList;
}
            ;

VarDef      : IDENT {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1);
    $$ = std::make_shared<VarDefAST>(p_IdAST->id(), nullptr, nullptr, 0);
}
            | IDENT ASSIGN InitVal {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1);
    $$ = std::make_shared<VarDefAST>(p_IdAST->id(), nullptr, std::move($3), 0);
}
            | IDENT Dimension {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1);
    $$ = std::make_shared<VarDefAST>(p_IdAST->id(), std::move($2), nullptr, 1);
}
            | IDENT Dimension ASSIGN InitVal {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1);
    $$ = std::make_shared<VarDefAST>(p_IdAST->id(), std::move($2), std::move($4), 1);
}
            ;

InitVal     : Exp { $$ = $1; }
            | InitValArray { $$ = $1; }
            ;

InitValArray : EMPTY {
    $$ = std::make_shared<InitValArrayAST>(nullptr);
}
            | LLPAREN InitValList LRPAREN {
    $$ = std::make_shared<InitValArrayAST>(std::move($2));
}
            ;

InitValList : InitVal {
    ASTPtrList exprs;
    exprs.push_back(std::move($1));
    $$ = std::make_shared<InitValAST>(std::move(exprs));
}
            | InitValList COMMA InitVal {
    auto p_InitValList = std::dynamic_pointer_cast<InitValAST>($1);
    p_InitValList->exprs().push_back(std::move($3));
    $$ = p_InitValList;
}
            ;

FuncDef     : VOID IDENT SLPAREN SRPAREN Block {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($2);
    $$ = std::make_shared<FuncDefAST>(token::TOK_VOID, p_IdAST->id(), nullptr, std::move($5));
}
            | VOID IDENT SLPAREN FuncFParams SRPAREN Block {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($2);
    $$ = std::make_shared<FuncDefAST>(token::TOK_VOID, p_IdAST->id(), std::move($4), std::move($6));
}
            | INT IDENT SLPAREN SRPAREN Block {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($2);
    $$ = std::make_shared<FuncDefAST>(token::TOK_INT, p_IdAST->id(), nullptr, std::move($5));
}
            | INT IDENT SLPAREN FuncFParams SRPAREN Block {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($2);
    $$ = std::make_shared<FuncDefAST>(token::TOK_INT, p_IdAST->id(), std::move($4), std::move($6));
}
            ;

FuncFParams : FuncFParam {
    ASTPtrList param_list;
    param_list.push_back(std::move($1));
    $$ = std::make_shared<FuncFParamsAST>(std::move(param_list));
}
            | FuncFParams COMMA FuncFParam {
    auto p_FuncFParams = std::dynamic_pointer_cast<FuncFParamsAST>($1);
    p_FuncFParams->param_list().push_back(std::move($3));
    $$ = p_FuncFParams;
}
            ;


FuncFParam  : FuncFParamVar { $$ = $1; }
            | FuncFParamArray { $$ = $1; }
            ;

FuncFParamVar : INT IDENT {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($2);
    $$ = std::make_shared<FuncFParamVarAST>(token::TOK_INT, p_IdAST->id());
}
            ;

FuncFParamArray : INT IDENT MLPAREN MRPAREN {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($2);
    $$ = std::make_shared<FuncFParamArrayAST>(token::TOK_INT, p_IdAST->id(), nullptr);
}
            | INT IDENT MLPAREN MRPAREN Dimension {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>($2);
    $$ = std::make_shared<FuncFParamArrayAST>(token::TOK_INT, p_IdAST->id(), std::move($5));
}
            ;

Block       : EMPTY {
    $$ = std::make_shared<BlockAST>(nullptr);
};
            | LLPAREN BlockItems LRPAREN {
    $$ = std::make_shared<BlockAST>(std::move($2));
}
            ;

BlockItems  : BlockItem {
    ASTPtrList items;
    items.push_back(std::move($1));
    $$ = std::make_shared<BlockItemsAST>(std::move(items));
}
            | BlockItems BlockItem {
    auto p_BlockItems = std::dynamic_pointer_cast<BlockItemsAST>($1);
    p_BlockItems->items().push_back(std::move($2));
    $$ = p_BlockItems;
}
            ;

BlockItem   : Decl {
    $$ = $1;
}
            | Stmt {
    $$ = $1;
}
            ;

Stmt        : Block { $$ = $1; }
            | Assign_stmt { $$ = $1; }
            | Exp_stmt { $$ = $1; }
            | If_stmt { $$ = $1; }
            | While_stmt { $$ = $1; }
            | Cond_stmt { $$ = $1; }
            | Return_stmt { $$ = $1; }
            ;

Assign_stmt : LVal ASSIGN Exp SEMI {
    $$ = std::make_shared<AssignAST>(std::move($1), std::move($3));
}
            ;

Exp_stmt    : SEMI {
    $$ = std::make_shared<ExpAST>(nullptr);
}
            | Exp SEMI {
    $$ = std::make_shared<ExpAST>(std::move($1));
}
            ;

If_stmt     : IF SLPAREN Cond SRPAREN Stmt {
    $$ = std::make_shared<IfAST>(std::move($3), std::move($5), nullptr);
}
            | IF SLPAREN Cond SRPAREN Stmt ELSE Stmt {
    $$ = std::make_shared<IfAST>(std::move($3), std::move($5), std::move($7));
}
            ;

While_stmt  : WHILE SLPAREN Cond SRPAREN Stmt {
    $$ = std::make_shared<WhileAST>(std::move($3), std::move($5));
}
            ;

Cond_stmt   : BREAK SEMI {
    $$ = std::make_shared<CondAST>(token::TOK_BREAK);
}
            | CONTINUE SEMI {
    $$ = std::make_shared<CondAST>(token::TOK_CONTINUE);
}
            ;

Return_stmt : RETURN SEMI {
    $$ = std::make_shared<ReturnAST>(nullptr);
}
            | RETURN Exp SEMI {
    $$ = std::make_shared<ReturnAST>(std::move($2));
}
            ;

Exp         : AddExp { $$ = $1; }
            ;

Cond        : LOrExp { $$ = $1; }
            ;

LVal        : IDENT { $$ = $1; }
            | IDENT Dimension {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1); 
                $$ = std::make_shared<ArrayAST>(p_IdAST->id(), std::move($2));
            }
            ;

PrimaryExp  : SLPAREN Exp SRPAREN { $$ = $2; }
            | LVal { $$ = $1; }
            | DEC_NUM {
                $$ = std::make_shared<IntAST>($1);
                #ifdef DEBUG
                    printf("%d\n", $1);
                #endif 
            }
            | OCT_NUM {
                $$ = std::make_shared<IntAST>($1);
                #ifdef DEBUG
                    printf("%d\n", $1);
                #endif
            }
            | HEX_NUM {
                $$ = std::make_shared<IntAST>($1);
                #ifdef DEBUG
                    printf("%d\n", $1);
                #endif
            }
            ;

UnaryExp    : PrimaryExp { $$ = $1; }
            | FuncCallExp { $$ = $1; }
            | PLUS UnaryExp {
                $$ = std::make_shared<UnaryAST>(token::TOK_PLUS, std::move($2));
            }
            | MINUS UnaryExp {
                $$ = std::make_shared<UnaryAST>(token::TOK_MINUS, std::move($2));
            }
            | NOT UnaryExp {
                $$ = std::make_shared<UnaryAST>(token::TOK_NOT, std::move($2));
            }
            ;

FuncCallExp : IDENT SLPAREN SRPAREN {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1);
                $$ = std::make_shared<FuncCallAST>(p_IdAST->id(), nullptr); 
            }
            | IDENT SLPAREN FuncRParams SRPAREN {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>($1);
                $$ = std::make_shared<FuncCallAST>(p_IdAST->id(), std::move($3)); 
            }
            ;

FuncRParams : Exp {
    ASTPtrList exprs;
    exprs.push_back(std::move($1));
    $$ = std::make_shared<FuncRParamsAST>(std::move(exprs));
}
            | FuncRParams COMMA Exp {
    auto p_FuncRParams = std::dynamic_pointer_cast<FuncRParamsAST>($1);
    p_FuncRParams->exprs().push_back(std::move($3));
    $$ = p_FuncRParams;
}
            ;


MulExp      : UnaryExp { $$ = $1; }
            | MulExp TIMES UnaryExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_TIMES,
                std::move($1), std::move($3));
            }
            | MulExp OVER UnaryExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_OVER,
                std::move($1), std::move($3));
            }
            | MulExp MOD UnaryExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_MOD,
                std::move($1), std::move($3));
            }
            ;

AddExp      : MulExp { $$ = $1; }
            | AddExp PLUS MulExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_PLUS,
                std::move($1), std::move($3));
            }
            | AddExp MINUS MulExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_MINUS,
                std::move($1), std::move($3));
            }
            ;

RelExp      : AddExp { $$ = $1; }
            | RelExp LT AddExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_LT,
                std::move($1), std::move($3));
            }
            | RelExp GT AddExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_GT,
                std::move($1), std::move($3));
            }
            | RelExp LTE AddExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_LTE,
                std::move($1), std::move($3));
            }
            | RelExp GTE AddExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_GTE,
                std::move($1), std::move($3));
            }
            ;

EqExp       : RelExp { $$ = $1; }
            | EqExp EQ RelExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_EQ,
                std::move($1), std::move($3));
            }
            | EqExp NEQ RelExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_NEQ,
                std::move($1), std::move($3));
            }
            ;

LAndExp     : EqExp { $$ = $1; }
            | LAndExp AND EqExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_AND,
                std::move($1), std::move($3));
            }

LOrExp      : LAndExp { $$ = $1; }
            | LOrExp OR LAndExp {
                $$ = std::make_shared<BinaryAST>(token::TOK_OR,
                std::move($1), std::move($3));
            }

IDENT       : ID{
    $$ = std::make_unique<IdAST>($1);
}
            ;

%%

void yy::parser::error(const location_type& l, const std::string &m)
{
    std::cerr << l << ":" <<m <<std::endl;
}