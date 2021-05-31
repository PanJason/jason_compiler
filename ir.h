/****************************************************/
/*File: ir.h                                        */
/*The class of Different Intermedia Representations */
/*for the jason compiller                           */
/*This genrator classs will store necessary         */
/*information of each AST Ptr                       */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#ifndef __IR_H
#define __IR_H
#include <memory>
#include <vector>
#include <iostream>

using TokenType = int;
class FunctionDef;
// Base class of all instructions
class InstBase{
public:
    virtual ~InstBase() = default;
    //dump intermediate representation of Eeyore
    virtual void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const = 0;
    virtual void Dump_Tigger(std::ostream &os, const FunctionDef &func) const = 0;

};
using InstPtr = std::shared_ptr<InstBase>;
using InstPtrList = std::vector<InstPtr>;

// Base class of all values
class ValueBase {
public:
    virtual ~ValueBase() = default;
    virtual void Dump_Eeyore(std::ostream &os) const = 0;
    virtual void Dump_Tigger(std::ostream &os ) const = 0;
    virtual void Dump_Tigger_Read(std::ostream &os) const = 0;
    virtual void Dump_Tigger_Write(std::ostream &os) const = 0;
    virtual void Dump_Tigger_offset(std::ostream &os) const {
        throw std::runtime_error("Not implemented. Should not be called!");
    };
    int is_array = -1;
    int is_arg_ref = -1;
    int is_int = -1;
};
using ValPtr = std::shared_ptr<ValueBase>;
using ValPtrList = std::vector<ValPtr>;

class FunctionDef{
public:
FunctionDef(const std::string &name, std::size_t num_args, TokenType ret_type)
: _func_name(name), _num_args(num_args), _ret_type(ret_type), _slot_num(0), _cur_offset(0){}

template <typename Inst, typename... Args>
void PushInst(Args &&...args){
    _insts.emplace_back(
        std::make_shared<Inst>(std::forward<Args>(args)...));
}

template <typename Inst, typename... Args>
void PushDeclInst(Args &&...args){
    _decl_insts.emplace_back(
        std::make_shared<Inst>(std::forward<Args>(args)...));
}

ValPtr AddSlot();
ValPtr AddVarSlot();
void Dump_Eeyore(std::ostream& os) const;
void Dump_Eeyore_GLOB(std::ostream& os) const;
std::string Dump_Tigger(std::ostream& os, bool dump2str) const;
std::string Dump_Tigger_GLOB(std::ostream& os, bool dump2str) const;
const std::string &func_name() const {return _func_name;}
std::size_t num_args() const {return _num_args;}
std::size_t slot_num() const {return _slot_num;}
std::size_t cur_offset() const {return _cur_offset;}
void add_cur_offset(std::size_t add_offset) {_cur_offset += add_offset;}
TokenType ret_type() const {return _ret_type;}
const InstPtrList& decl_insts() const {return _decl_insts;}
const InstPtrList& insts() const {return _insts;}

private:
std::string _func_name;
std::size_t _num_args, _slot_num, _cur_offset;
InstPtrList _insts;
InstPtrList _decl_insts; //This definsts list is used to generate declarations First.
TokenType _ret_type;
};
using FuncDefPtr = std::shared_ptr<FunctionDef>;

class DeclareVarInst : public InstBase {
public:
    DeclareVarInst(ValPtr val): _val(std::move(val)) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    ValPtr _val;
};

class DeclareArrInst : public InstBase {
public:
    DeclareArrInst(ValPtr val, std::size_t symbol_size): _val(std::move(val)), _symbol_size(symbol_size) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    ValPtr _val;
    std::size_t _symbol_size;
};

class AssignInst : public InstBase {
public:
    AssignInst(ValPtr dest, ValPtr val)
    : _dest(std::move(dest)), _val(std::move(val)) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    ValPtr _dest, _val;
};

class BranchInst : public InstBase {
public:
    BranchInst(bool bnez, ValPtr cond, ValPtr label)
    : _bnez(bnez), _cond(std::move(cond)), _label(std::move(label)) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    //bnez (true) or beqz (false)
    bool _bnez;
    ValPtr _cond, _label;
};

class JumpInst : public InstBase {
public:
    JumpInst(ValPtr label) : _label(std::move(label)) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    ValPtr _label;
};
class LabelInst : public InstBase {
public:
    LabelInst(ValPtr label) : _label(std::move(label)) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    ValPtr _label;
};

class FuncCallInst : public InstBase {
public:
    FuncCallInst(ValPtr dest, FuncDefPtr func, ValPtrList args)
    : _dest(std::move(dest)), _func(std::move(func)), _args(std::move(args)){}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    ValPtr _dest;
    FuncDefPtr _func;
    ValPtrList _args;

};

class VoidFuncCallInst : public InstBase {
public:
    VoidFuncCallInst(FuncDefPtr func, ValPtrList args)
    :_func(std::move(func)), _args(std::move(args)){}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    FuncDefPtr _func;
    ValPtrList _args;

};

class ReturnInst : public InstBase{
public:
    ReturnInst(ValPtr val) : _val(std::move(val)) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    ValPtr _val;
};

class BinaryInst : public InstBase{
public:
    BinaryInst(TokenType op, ValPtr dest, ValPtr lhs, ValPtr rhs)
    :_op(op), _dest(std::move(dest)), _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    TokenType _op;
    ValPtr _dest, _lhs, _rhs;
};

class UnaryInst : public InstBase{
public:
    UnaryInst(TokenType op, ValPtr dest, ValPtr opr)
    : _op(op), _dest(std::move(dest)), _opr(std::move(opr)) {}
    void Dump_Eeyore(std::ostream &os, const FunctionDef &func) const override;
    void Dump_Tigger(std::ostream &os, const FunctionDef &func) const override;
private:
    TokenType _op;
    ValPtr _dest, _opr;
};

class SlotVal: public ValueBase{
public:
    SlotVal(std::size_t id, std::size_t offset) : _id(id), _offset(offset) {}
    void Dump_Eeyore(std::ostream &os) const override;
    void Dump_Tigger(std::ostream &os) const override;
    void Dump_Tigger_Read(std::ostream &os) const override;
    void Dump_Tigger_Write(std::ostream &os) const override;
    void Dump_Tigger_offset(std::ostream &os) const override;
private:
    std::size_t _offset; 
    std::size_t _id;
};

class VarSlotVal: public ValueBase{
public:
    VarSlotVal(std::size_t offset,bool is_global) : _id(_next_id++), _offset(offset), _is_global(is_global) {}
    void Dump_Eeyore(std::ostream &os) const override;
    void Dump_Tigger(std::ostream &os) const override;
    void Dump_Tigger_Read(std::ostream &os) const override;
    void Dump_Tigger_Write(std::ostream &os) const override;
    void Dump_Tigger_offset(std::ostream &os) const override;
private:
    static std::size_t _next_id;
    bool _is_global = 0;
    std::size_t _offset;
    std::size_t _id;
};

class ArgRefVal : public ValueBase{
public:
    ArgRefVal(std::size_t id) : _id(id) {is_arg_ref = 1;}
    void Dump_Eeyore(std::ostream &os) const override;
    void Dump_Tigger(std::ostream &os) const override;
    void Dump_Tigger_Read(std::ostream &os) const override;
    void Dump_Tigger_Write(std::ostream &os) const override;
private:
    std::size_t _id;
};

class ArrayRefVal : public ValueBase{
public:
    ArrayRefVal(ValPtr base, ValPtr offset)
    : _base(base), _offset(std::move(offset)) {is_array = 1;}
    void Dump_Eeyore(std::ostream &os) const override;
    void Dump_Tigger(std::ostream &os) const override;
    void Dump_Tigger_Read(std::ostream &os) const override;
    void Dump_Tigger_Write(std::ostream &os) const override;
private:
    ValPtr _base;
    ValPtr _offset;
};

class LabelVal : public ValueBase{
public:
    LabelVal() : _id(_next_id++) {}
    void Dump_Eeyore(std::ostream &os) const override;
    void Dump_Tigger(std::ostream &os) const override;
    void Dump_Tigger_Read(std::ostream &os) const override;
    void Dump_Tigger_Write(std::ostream &os) const override;
private:
    static std::size_t _next_id;
    std::size_t _id;
};

class IntVal : public ValueBase{
public:
    IntVal(int val): _val(val) {is_int = 1;}
    void Dump_Eeyore(std::ostream &os) const override;
    void Dump_Tigger(std::ostream &os) const override;
    void Dump_Tigger_Read(std::ostream &os) const override;
    void Dump_Tigger_Write(std::ostream &os) const override;
private:
    int _val;
};

#endif