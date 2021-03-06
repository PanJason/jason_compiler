/****************************************************/
/*File: global.h                                    */
/*Define Global Variables and data types            */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#ifndef __GLOBALS_H_
#define __GLOBALS_H_
#include <optional>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include <stdexcept>
#include "ir.h"

using TokenType = int;
class IRGen;

class SymbolTableEntry{
public:
    SymbolTableEntry(TokenType symbol_type, bool is_const, 
    bool is_pointer)
    : _symbol_type(symbol_type), _is_const(is_const),
    _is_pointer(is_pointer), _symbol_size(4),_dim(1&is_pointer),_shape() {}
    TokenType symbol_type() {return _symbol_type;}
    bool is_const() {return _is_const; }
    bool is_pointer() {return _is_pointer; }
    std::size_t symbol_size() {return _symbol_size;}
    std::size_t dim() {return _dim;}
    std::vector<std::size_t> &shape() {return _shape;}
    TokenType _symbol_type;
    bool _is_const;
    bool _is_pointer;
    std::size_t _symbol_size;
    //the dim of a variable is 0;
    std::size_t _dim;
    std::vector<std::size_t> _shape;
};
using STEPtr = std::shared_ptr<SymbolTableEntry>;

class FuncTableEntry{
public:
    FuncTableEntry(TokenType param_type, bool is_pointer)
    : _param_type(param_type), _is_pointer(is_pointer),_symbol_size(4),_dim(1&is_pointer),_shape(){}
    TokenType param_type() {return _param_type;}
    bool is_pointer() {return _is_pointer;}
    std::size_t symbol_size() {return _symbol_size;}
    std::size_t dim() {return _dim;}
    std::vector<std::size_t> &shape() {return _shape;}
    TokenType _param_type;
    bool _is_pointer;
    //the dim of a variable is 0;
    std::size_t _symbol_size;
    std::size_t _dim;
    std::vector<std::size_t> _shape;

};
using FTEPtr = std::shared_ptr<FuncTableEntry>;

class BaseAst {
public:
    virtual ~BaseAst() = default;
    virtual std::optional<int> Eval(IRGen &gen) const {
        throw std::runtime_error("Not implemented. Should not be called!");
    };
    virtual ValPtr GenerateIR(IRGen &gen) const {
        throw std::runtime_error("Not implemented. Should not be called!");
    };
    int is_decl = 0;
    //zero if this node is a variable, one if this node is a array;
    //-1 otherwise
    int is_array = -1;

    int is_lval_array = -1;

};
using ASTPtr = std::shared_ptr<BaseAst>;
using ASTPtrList = std::vector<ASTPtr>;
using IdList = std::vector<std::string>;


class CompUnitAST : public BaseAst {
public:
    CompUnitAST(ASTPtrList units)
    : _units(std::move(units)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtrList &units() const {return _units; }
    ASTPtrList _units;
};

class ConstDeclAST : public BaseAst{
public:
    ConstDeclAST(const TokenType decl_type, ASTPtr const_defs)
    : _decl_type(decl_type), _const_defs(std::move(const_defs)) {is_decl = 1;}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const TokenType decl_type() const {return _decl_type; }
    const ASTPtr &const_defs() const {return _const_defs; }
private:
    TokenType _decl_type;
    ASTPtr _const_defs;
};

class ConstDefListAST : public BaseAst{
public:
    ConstDefListAST(ASTPtrList const_defs)
    : _const_defs(std::move(const_defs)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    ASTPtrList &const_defs() {return _const_defs;}
    const ASTPtrList &const_const_defs() const {return _const_defs;}
private:
    ASTPtrList _const_defs;
};

class ConstDefAST : public BaseAst{
public:
    ConstDefAST(const std::string &id, ASTPtr const_exprs, ASTPtr const_init_val, bool is_array_def)
    : _id(id), _const_exprs(std::move(const_exprs)), _const_init_val(std::move(const_init_val)), _is_array_def(is_array_def) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const std::string &id() const {return _id;}
    const ASTPtr &const_exprs() const {return _const_exprs;}
    const ASTPtr &const_init_val() const {return _const_init_val; }
    const bool is_array_def() const {return _is_array_def;}
private:
    std::string _id;
    ASTPtr _const_exprs;
    ASTPtr _const_init_val;
    bool _is_array_def;
};

class ConstInitValArrayAST : public BaseAst{
public:
    ConstInitValArrayAST(ASTPtr init_vals): _init_vals(std::move(init_vals)){is_array = 1;}
    //std::optional<int> Eval(IRGen &gen) const override;
    //ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtr &init_vals() const {return _init_vals;}
private:
    ASTPtr _init_vals;
};

class ConstInitValAST : public BaseAst{
public:
    ConstInitValAST(ASTPtrList const_exprs)
    : _const_exprs(std::move(const_exprs)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    //ValPtr GenerateIR(IRGen &gen) const override;
    ASTPtrList &const_exprs()  {return _const_exprs; }
private:
    ASTPtrList _const_exprs;
};

class VarDeclAST : public BaseAst{
public:
    VarDeclAST(const TokenType decl_type, ASTPtr var_defs)
    : _decl_type(decl_type), _var_defs(std::move(var_defs)) {is_decl = 1;}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const TokenType decl_type() const {return _decl_type; }
    const ASTPtr &var_defs() const {return _var_defs; }
private:
    TokenType _decl_type;
    ASTPtr _var_defs;
};

class VarDefListAST : public BaseAst{
public:
    VarDefListAST(ASTPtrList var_defs)
    : _var_defs(std::move(var_defs)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    ASTPtrList &var_defs()  {return _var_defs; }
    const ASTPtrList &const_var_defs() const {return _var_defs;}
private:
    ASTPtrList _var_defs;
};

class VarDefAST : public BaseAst{
public:
    VarDefAST(const std::string &id, ASTPtr const_exprs, ASTPtr init_val, bool is_array_def)
    : _id(id), _const_exprs(std::move(const_exprs)), _init_val(std::move(init_val)), _is_array_def(is_array_def) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const std::string &id() const {return _id;}
    const ASTPtr &const_exprs() const {return _const_exprs;}
    const ASTPtr &init_val() const {return _init_val; }
    const bool &is_array_def() const {return _is_array_def;}
private:
    std::string _id;
    ASTPtr _const_exprs;
    ASTPtr _init_val;
    bool _is_array_def;
};

class InitValArrayAST : public BaseAst{
public:
    InitValArrayAST(ASTPtr init_vals)
    : _init_vals(std::move(init_vals)) {is_array = 1;}
    //std::optional<int> Eval(IRGen &gen) const override;
    //ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtr &init_vals() const {return _init_vals; }
private:
    ASTPtr _init_vals;
};

class InitValAST : public BaseAst{
public:
    InitValAST(ASTPtrList exprs)
    : _exprs(std::move(exprs)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    //ValPtr GenerateIR(IRGen &gen) const override;
    ASTPtrList &exprs()  {return _exprs; }
private:
    ASTPtrList _exprs;
};



class FuncDefAST : public BaseAst{
public:
    FuncDefAST(const TokenType func_type, const std::string &name, ASTPtr params, ASTPtr block) 
    : _func_type(func_type), _name(name), _params(std::move(params)), _block(std::move(block)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const TokenType func_type() const {return _func_type;}
    const std::string &name() const {return _name;}
    const ASTPtr &params() const {return _params;}
    const ASTPtr &block() const {return _block;}
private:
    TokenType _func_type;
    std::string _name;
    ASTPtr _params;
    ASTPtr _block;
};

class FuncFParamsAST : public BaseAst{
public:
    FuncFParamsAST(ASTPtrList param_list)
    : _param_list(std::move(param_list)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    //ValPtr GenerateIR(IRGen &gen) const override;
    ASTPtrList &param_list() {return _param_list;}
    const ASTPtrList &const_params() const {return _param_list;}
private:
    ASTPtrList _param_list;
};

class FuncFParamVarAST : public BaseAst{
public:
    FuncFParamVarAST(const TokenType param_type, const std::string &name)
    : _param_type(param_type), _name(name) {is_array = 0;}
    //std::optional<int> Eval(IRGen &gen) const override;
    //ValPtr GenerateIR(IRGen &gen) const override;
    const TokenType param_type() const {return _param_type;}
    const std::string &name() const {return _name; }
private:
    TokenType _param_type;
    std::string _name;
};

class FuncFParamArrayAST : public BaseAst{
public:
    FuncFParamArrayAST(const TokenType param_type, const std::string &name, ASTPtr dimension)
    : _param_type(param_type), _name(name), _dimension(std::move(dimension)){is_array = 1;}
    //std::optional<int> Eval(IRGen &gen) const override;
    //ValPtr GenerateIR(IRGen &gen) const override;
    const TokenType param_type() const {return _param_type;}
    const std::string &name() const {return _name; }
    const ASTPtr &dimension() const {return _dimension;}
private:
    TokenType _param_type;
    std::string _name;
    ASTPtr _dimension;
};

class DimensionAST : public BaseAst {
public:
    DimensionAST(ASTPtrList dims)
    : _dims(std::move(dims)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    //ValPtr GenerateIR(IRGen &gen) const override;
    ASTPtrList &dims() {return _dims; }
    const ASTPtrList &const_dims() const {return _dims; }
private:
    ASTPtrList _dims;
};

class BlockAST : public BaseAst {
public:
    BlockAST(ASTPtr blockitems)
    : _blockitems(std::move(blockitems)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtr &blockitem() const {return _blockitems; }
private:
    ASTPtr _blockitems;
};

class BlockItemsAST : public BaseAst {
public:
    BlockItemsAST(ASTPtrList items)
    : _items(std::move(items)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    ASTPtrList &items() {return _items;}
    const ASTPtrList &const_items() const {return _items;}
private:
    ASTPtrList _items;
};

class AssignAST : public BaseAst {
public:
    AssignAST(ASTPtr lval, ASTPtr expr)
    : _lval(std::move(lval)), _expr(std::move(expr)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtr &lval() const {return _lval; }
    const ASTPtr &expr() const {return _expr; }
private:
    ASTPtr _lval;
    ASTPtr _expr;
};

class ExpAST : public BaseAst {
public:
    ExpAST(ASTPtr expr)
    : _expr(std::move(expr)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtr &expr() const {return _expr; }
private:
    ASTPtr _expr;
};

class IfAST : public BaseAst {
public:
    IfAST(ASTPtr cond, ASTPtr then, ASTPtr else_then)
    : _cond(std::move(cond)), _then(std::move(then)), _else_then(std::move(else_then)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtr &cond() const {return _cond; }
    const ASTPtr &then() const {return _then; }
    const ASTPtr &else_then() const {return _else_then; }
private:
    ASTPtr _cond, _then, _else_then;
};

class WhileAST : public BaseAst {
public:
    WhileAST(ASTPtr cond, ASTPtr stmt)
    : _cond(std::move(cond)), _stmt(std::move(stmt)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtr &cond() const {return _cond; }
    const ASTPtr &stmt() const {return _stmt; }
private:
    ASTPtr _cond, _stmt;
};

class CondAST : public BaseAst {
public:
    CondAST(const TokenType cond_type) : _cond_type(cond_type) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const TokenType cond_type() const {return _cond_type; }
private:
    TokenType _cond_type;
};

class ReturnAST : public BaseAst {
public:
    ReturnAST(ASTPtr expr) : _expr(std::move(expr)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const ASTPtr &expr() const {return _expr; }
private:
    ASTPtr _expr;
};

class BinaryAST :  public BaseAst {
public:
    BinaryAST(TokenType op, ASTPtr lhs, ASTPtr rhs)
    : _op(op), _lhs(std::move(lhs)), _rhs(std::move(rhs)){}
    std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const TokenType op() const {return _op; }
    const ASTPtr &lhs() const {return _lhs; }
    const ASTPtr &rhs() const {return _rhs; }
private:
    TokenType _op;
    ASTPtr _lhs, _rhs;
};

class UnaryAST: public BaseAst {
public:
    UnaryAST(TokenType op, ASTPtr opr)
    : _op(op), _opr(std::move(opr)) {}
    std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const TokenType op() const {return _op; }
    const ASTPtr &opr() const {return _opr;}
private:
    TokenType _op;
    ASTPtr _opr;
};

class FuncCallAST : public BaseAst {
public:
    FuncCallAST(const std::string &name, ASTPtr params)
    : _name(name), _params(std::move(params)) {}
    //std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const std::string &name() const {return _name; }
    const ASTPtr &params() const {return _params; }
private:
    std::string _name;
    ASTPtr _params;
};

class FuncRParamsAST : public BaseAst {
public:
    FuncRParamsAST(ASTPtrList exprs)
    : _exprs(std::move(exprs)) {}
    ASTPtrList &exprs() {return _exprs;}
    const ASTPtrList &const_exprs() const {return _exprs;}
private:
    ASTPtrList _exprs;
};

class IntAST : public BaseAst {
public:
    IntAST(int val)
    : _val(val) {}
    std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const int val() const {return _val; }
private:
    int _val;
};

class IdAST : public BaseAst {
public:
    IdAST(const std::string &id) : _id(id) {}
    IdAST(const char* text): _id(text) {}
    std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const std::string &id() const {return _id; }
private:
    std::string _id;
};

class ArrayAST : public BaseAst {
public:
    ArrayAST(const std::string &id, ASTPtr exprs)
    : _id(id), _exprs(std::move(exprs)) {is_lval_array = 1;}
    std::optional<int> Eval(IRGen &gen) const override;
    ValPtr GenerateIR(IRGen &gen) const override;
    const std::string &id() const {return _id;}
    const ASTPtr &exprs() const {return _exprs;}
private:
    std::string _id;
    ASTPtr _exprs;
};

#endif