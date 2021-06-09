/****************************************************/
/*File: ir.cpp                                        */
/*This file is used to define the functions that    */
/*generate the target Eeyore representations.       */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#include "ir.h"
#include "source.tab.hpp"
#include <sstream>
#define __DEBUG_IR__
const std::string kResult3Reg = "t4";
const std::string kResult2Reg = "t3";
const std::string kResultReg = "t2";
const std::string kTempReg = "t1";
const std::string kArrReg = "t0";
std::size_t LabelVal::_next_id = 0;
std::size_t VarSlotVal::_next_id = 0;

ValPtr FunctionDef::AddSlot() {return std::make_shared<SlotVal>(_slot_num++, _cur_offset);}
ValPtr FunctionDef::AddVarSlot(bool is_addr) {return std::make_shared<VarSlotVal>(_cur_offset, _func_name == "00_GLOBAL", is_addr);}

void FunctionDef::Dump_Tigger(std::ostream &os, std::stringstream& global_inst) const{
    os<<"f_"<<_func_name<<" ["<<_num_args<<"] ["<<(_cur_offset + 4*8)/4 <<"]"<<std::endl;
    if(_func_name == "main"){
        os<<global_inst.str();
    }
    for (std::size_t i = 0; i < _num_args; ++i) {
        os << "store a"<<i<<" "<<i<<std::endl;
    }
    for (const auto &inst: _insts) inst->Dump_Tigger(os, *this);
    os<<"end f_"<<_func_name<<std::endl;
}

void FunctionDef::Dump_Tigger_GLOB(std::ostream &os, std::stringstream& global_inst) const{
    for (const auto &decl : _decl_insts) decl->Dump_Tigger(os, *this);
    for (const auto &inst: _insts) {
        auto assign_inst = std::dynamic_pointer_cast<AssignInst>(inst);
        if((!assign_inst->val()->is_int == 1 )||( !assign_inst->val()->get_RISC_V_offset() == 0)){
            inst->Dump_Tigger(global_inst, *this);
        }
    }
}



void FunctionDef::Dump_Eeyore(std::ostream &os) const {
    os<<"f_"<<_func_name<<" ["<<_num_args<<"]"<<std::endl;
    for (const auto &decl : _decl_insts) decl->Dump_Eeyore(os, *this);
    for (const auto &inst : _insts) inst->Dump_Eeyore(os, *this);
    os<<"end f_"<<_func_name<<std::endl;
}
void FunctionDef::Dump_Eeyore_GLOB(std::ostream &os) const {
    for (const auto &decl : _decl_insts) decl->Dump_Eeyore(os, *this);
    for (const auto &inst : _insts) inst->Dump_Eeyore(os, *this);
}
void DeclareVarInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    os<<"var ";
    _val->Dump_Eeyore(os);
    os<<std::endl;
}
void DeclareArrInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    os<<"var "<<_symbol_size<<" ";
    _val->Dump_Eeyore(os);
    os<<std::endl;
}
void AssignInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    _dest->Dump_Eeyore(os);
    os<<" = ";
    _val->Dump_Eeyore(os);
    os<<std::endl;
}
void BranchInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    os <<"if ";
    _cond->Dump_Eeyore(os);
    if(_bnez){
        os<<" != 0 goto ";
    }
    else{
        os<<" == 0 goto ";
    }
    _label->Dump_Eeyore(os);
    os<<std::endl;
}
void JumpInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    os<<"goto ";
    _label->Dump_Eeyore(os);
    os<<std::endl;
}
void LabelInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    _label->Dump_Eeyore(os);
    os<<":"<<std::endl;
}
void FuncCallInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    for(const auto &i: _args){
        os<<"param ";
        i->Dump_Eeyore(os);
        os<<std::endl;
    }
    _dest->Dump_Eeyore(os);
    os<<" = call f_"<<_func->func_name()<<std::endl;
}
void VoidFuncCallInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    for(const auto &i: _args){
        os<<"param ";
        i->Dump_Eeyore(os);
        os<<std::endl;
    }
    os<<"call f_"<<_func->func_name()<<std::endl;
}
void ReturnInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    os<<"return ";
    if (_val!=nullptr)
        _val->Dump_Eeyore(os);
    os<<std::endl;
}
void BinaryInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    _dest->Dump_Eeyore(os);
    os<<" = ";
    _lhs->Dump_Eeyore(os);
    switch (_op) {
      case yy::parser::token::TOK_PLUS: {os<<" + "; break;}
      case yy::parser::token::TOK_MINUS: {os<<" - "; break;}
      case yy::parser::token::TOK_TIMES: {os<<" * "; break;}
      case yy::parser::token::TOK_OVER: {os<<" / "; break;}
      case yy::parser::token::TOK_MOD: {os<<" % "; break;}
      case yy::parser::token::TOK_LT: {os<<" < "; break;}
      case yy::parser::token::TOK_LTE: {os<<" <= "; break;}
      case yy::parser::token::TOK_GT: {os<<" > "; break;}
      case yy::parser::token::TOK_GTE: {os<<" >= "; break;}
      case yy::parser::token::TOK_EQ: {os<<" == "; break;}
      case yy::parser::token::TOK_NEQ: {os<<" != "; break;}
      case yy::parser::token::TOK_AND: {os<<" && "; break;}
      case yy::parser::token::TOK_OR: {os<<" || "; break;}
      default: assert(false && "unknown binary operator");
    }
    _rhs->Dump_Eeyore(os);
    os<<std::endl;
}
void UnaryInst::Dump_Eeyore(std::ostream &os, const FunctionDef &func) const{
    _dest->Dump_Eeyore(os);
    os<<" = ";
    switch (_op) {
      case yy::parser::token::TOK_PLUS: {break;}
      case yy::parser::token::TOK_MINUS: {os<<"-"; break;}
      case yy::parser::token::TOK_NOT: {os<<"!"; break;}
      default: assert(false && "unknown binary operator");
    }
    _opr->Dump_Eeyore(os);
    os<<std::endl;
}


void SlotVal::Dump_Eeyore(std::ostream &os) const{
    os<<"t"<<_id;
}
void VarSlotVal::Dump_Eeyore(std::ostream &os) const{
    os<<"T"<<_id;
}
void ArgRefVal::Dump_Eeyore(std::ostream &os) const{
    os<<"p"<<_id;
}
void ArrayRefVal::Dump_Eeyore(std::ostream &os) const{
    _base->Dump_Eeyore(os);
    os<<"[";
    _offset->Dump_Eeyore(os);
    os<<"]";
}
void LabelVal::Dump_Eeyore(std::ostream &os) const{
    os<<"l"<<_id;
}
void IntVal::Dump_Eeyore(std::ostream &os) const{
    os<<_val;
}


void DeclareVarInst::Dump_Tigger(std::ostream &os, const FunctionDef &func) const{
    if (func.func_name()!="00_GLOBAL"){
        assert(false && "DeclareVarInst won't generate anything out global area!");
    }
    _val->Dump_Tigger(os);
    os<<" = 0"<<std::endl;
}

void DeclareArrInst::Dump_Tigger(std::ostream &os, const FunctionDef &func) const{
    if (func.func_name()!="00_GLOBAL"){
        assert(false && "DeclareArrInst won't generate anything out global area!");
    }
    _val->Dump_Tigger(os);
    os<<" = malloc "<<_symbol_size<<std::endl;
}

void AssignInst::Dump_Tigger(std::ostream &os, const FunctionDef &func) const{
    _val->Dump_Tigger_Read(os);
    _dest->Dump_Tigger_Write(os);
}
void JumpInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    os<<"goto ";
    _label->Dump_Tigger(os);
    os<<std::endl;
}
void LabelInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    _label->Dump_Tigger(os);
    os<<":"<<std::endl;
}
void UnaryInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    _opr->Dump_Tigger_Read(os);
    switch (_op) {
    case yy::parser::token::TOK_PLUS: {break;}
    case yy::parser::token::TOK_MINUS: {os<<kResultReg<<" = -"<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_NOT: {os<<kResultReg<<" = !"<<kResultReg<<std::endl; break;}
    default: assert(false && "unknown binary operator");
    }
    _dest->Dump_Tigger_Write(os);
}
void BinaryInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    _lhs->Dump_Tigger_Read(os);
    os << kResult2Reg<<" = "<<kResultReg<<std::endl;
    _rhs->Dump_Tigger_Read(os);
    switch (_op) {
    case yy::parser::token::TOK_PLUS: {os<<kResultReg<<" = "<<kResult2Reg<<" + "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_MINUS: {os<<kResultReg<<" = "<<kResult2Reg<<" - "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_TIMES: {os<<kResultReg<<" = "<<kResult2Reg<<" * "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_OVER: {os<<kResultReg<<" = "<<kResult2Reg<<" / "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_MOD: {os<<kResultReg<<" = "<<kResult2Reg<<" % "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_LT: {os<<kResultReg<<" = "<<kResult2Reg<<" < "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_LTE: {os<<kResultReg<<" = "<<kResult2Reg<<" <= "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_GT: {os<<kResultReg<<" = "<<kResult2Reg<<" > "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_GTE: {os<<kResultReg<<" = "<<kResult2Reg<<" >= "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_EQ: {os<<kResultReg<<" = "<<kResult2Reg<<" == "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_NEQ: {os<<kResultReg<<" = "<<kResult2Reg<<" != "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_AND: {os<<kResultReg<<" = "<<kResult2Reg<<" && "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_OR: {os<<kResultReg<<" = "<<kResult2Reg<<" || "<<kResultReg<<std::endl; break;}
    default: assert(false && "unknown binary operator");
    }
    _dest->Dump_Tigger_Write(os);
}

void BranchInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    _cond->Dump_Tigger_Read(os);
    os <<"if "<<kResultReg;
    if(_bnez){
        os<<" != x0 goto ";
    }
    else{
        os<<" == x0 goto ";
    }
    _label->Dump_Tigger(os);
    os<<std::endl;
}
void FuncCallInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    std::size_t j = 0;
    for(const auto &i: _args){
        i->Dump_Tigger_Read(os);
        os<<"a"<<j++<<" = "<<kResultReg<<std::endl;
    }
    os<<"call f_"<<_func->func_name()<<std::endl;
    os<<kResultReg<<" = a0"<<std::endl;
    for (std::size_t i = 0; i < _args.size(); ++i) {
        os << "load "<<i<<" a"<<i<<std::endl;
    }
    _dest->Dump_Tigger_Write(os);
}
void ReturnInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    if (_val!=nullptr)
        _val->Dump_Tigger_Read(os);
        os<< "a0 = "<<kResultReg<<std::endl;
    os<<"return"<<std::endl;
}

//2*FuncDef Bugs in load store loadaddr
void VoidFuncCallInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    std::size_t j = 0;
    for(const auto &i: _args){
        i->Dump_Tigger_Read(os);
        os<<"a"<<j++<<" = "<<kResultReg<<std::endl;
    }
    os<<"call f_"<<_func->func_name()<<std::endl;
    for (std::size_t i = 0; i < _args.size(); ++i) {
        os << "load "<<i<<" a"<<i<<std::endl;
    }
}



void SlotVal::Dump_Tigger(std::ostream &os ) const{
    os<<_offset;
}
void SlotVal::Dump_Tigger_Read(std::ostream &os ) const{
    os<<"load "<<(_offset/4 + 8)<<" "<<kResultReg<<std::endl;
}
void SlotVal::Dump_Tigger_Write(std::ostream &os ) const{
    os<<"store "<<kResultReg<<" "<<_offset/4 + 8<<std::endl;
}
void SlotVal::Dump_Tigger_offset(std::ostream &os ) const{
    os<<_offset/4 + 8;
}
void VarSlotVal::Dump_Tigger(std::ostream &os ) const{
    if (_is_global == 1){
        os<<"v"<<_id;
    }
    else{
        os<<_offset;
    }
}
void VarSlotVal::Dump_Tigger_offset(std::ostream &os ) const{
    if (_is_global == 1){
        os<<"v"<<_id;
    }
    else{
        os<<_offset/4 + 8;
    }
}
void VarSlotVal::Dump_Tigger_Read(std::ostream &os ) const{
    if (_is_global == 1){
        if (_is_addr){
            os<<"loadaddr v"<<_id<<" "<<kResultReg<<std::endl;
        }
        else{
            os<<"load v"<<_id<<" "<<kResultReg<<std::endl;
        }
    }
    else{
        if (_is_addr){
            os<<"loadaddr "<<_offset/4 + 8<<" "<<kResultReg<<std::endl;
        }
        else{
            os<<"load "<<_offset/4 + 8 <<" "<<kResultReg<<std::endl;
        }
    }
}
void VarSlotVal::Dump_Tigger_Write(std::ostream &os ) const{
    if (_is_global == 1){
        os<<"loadaddr v"<<_id<<" "<<kArrReg<<std::endl;
        os<<kArrReg<<"[0]"<<" = "<<kResultReg<<std::endl;
    }
    else{
        os<<"store "<<kResultReg<<" "<<_offset/4 + 8<<std::endl;
    }
}
void ArgRefVal::Dump_Tigger(std::ostream &os ) const{
    os<<"a"<<_id;
}
void ArgRefVal::Dump_Tigger_Read(std::ostream &os ) const{
    os<<"load "<<_id<<" "<<kResultReg<<std::endl;
}
void ArgRefVal::Dump_Tigger_Write(std::ostream &os ) const{
    os<<"store "<<kResultReg<<" "<<_id<<std::endl;
}
void ArrayRefVal::Dump_Tigger(std::ostream &os ) const{
    assert(false && "Should not call Dump_Tigger of ArrayRefVal Directly!");
}
void ArrayRefVal::Dump_Tigger_Read(std::ostream &os ) const{
    if(_offset->is_int == 1){
        if (_base->is_arg_ref == 1){
            os<<kArrReg<<" = ";
            _base->Dump_Tigger(os);
            os<<std::endl;
        }
        else{
            os <<"loadaddr ";
            _base->Dump_Tigger_offset(os);
            os<<" "<<kArrReg<<std::endl;
        }
        os << kResultReg << " = "<<kArrReg<<"[";
        _offset->Dump_Tigger(os);
        os<<"]"<<std::endl;
        
    }
    else{
        if (_base->is_arg_ref == 1){
            os<<kArrReg<<" = ";
            _base->Dump_Tigger(os);
            os<<std::endl;
        }
        else{
            os <<"loadaddr ";
            _base->Dump_Tigger_offset(os);
            os<<" "<<kArrReg<<std::endl;
        }
        if (_offset->is_arg_ref == 1){
            os<<kTempReg<<" = ";
            _offset->Dump_Tigger(os);
            os<<std::endl;
        }
        else{
            os <<"load ";
            _offset->Dump_Tigger_offset(os);
            os<<" "<<kTempReg<<std::endl;
        }
        os << kArrReg << " = "<<kArrReg<< " + "<< kTempReg<<std::endl; 
        os << kResultReg << " = "<<kArrReg<<"[0]"<<std::endl;
    }
}
void ArrayRefVal::Dump_Tigger_Write(std::ostream &os ) const{
    if(_offset->is_int == 1){
        if (_base->is_arg_ref == 1){
            os<<kArrReg<<" = ";
            _base->Dump_Tigger(os);
            os<<std::endl;
        }
        else{
            os <<"loadaddr ";
            _base->Dump_Tigger_offset(os);
            os<<" "<<kArrReg<<std::endl;
        }
        os <<kArrReg<<"[";
        _offset->Dump_Tigger(os);
        os<<"]"<<" = "<<kResultReg << std::endl;
        
    }
    else{
        if (_base->is_arg_ref == 1){
            os<<kArrReg<<" = ";
            _base->Dump_Tigger(os);
            os<<std::endl;
        }
        else{
            os <<"loadaddr ";
            _base->Dump_Tigger_offset(os);
            os<<" "<<kArrReg<<std::endl;
        }
        if (_offset->is_arg_ref == 1){
            os<<kTempReg<<" = ";
            _offset->Dump_Tigger(os);
            os<<std::endl;
        }
        else{
            os <<"load ";
            _offset->Dump_Tigger_offset(os);
            os<<" "<<kTempReg<<std::endl;
        }
        os << kArrReg << " = "<<kArrReg<< " + "<< kTempReg<<std::endl; 
        os << kArrReg<<"[0]" << " = "<<kResultReg<<std::endl;
    }
}


void LabelVal::Dump_Tigger(std::ostream &os ) const{
    os<<"l"<<_id;
}
void LabelVal::Dump_Tigger_Read(std::ostream &os ) const{
    assert(false && "reading a label");
}
void LabelVal::Dump_Tigger_Write(std::ostream &os ) const{
    assert(false && "writing a label");
}
void IntVal::Dump_Tigger(std::ostream &os ) const{
    os<<_val;
}
void IntVal::Dump_Tigger_Read(std::ostream &os ) const{
    os<<kResultReg<<" = "<<_val<<std::endl;
}
void IntVal::Dump_Tigger_Write(std::ostream &os ) const{
    assert(false && "writing an integer");
}

//Bugs in MakeVarSlot if a global variable do not need to add
//2 FuncDefs not implemented yet.
//irgen not implemented yet.

//Not sure is there any bugs in VarSlot Dump_Tigger_Write
//Not sure what is going on with the rest two?

void FunctionDef::Dump_RISC_V(std::ostream &os, std::stringstream& global_inst) const{
/*
STK = (int2 / 4 + 1) * 16
  .text
  .align  2
  .global func
  .type   func, @function
func:
  addi    sp, sp, -STK
  sw      ra, STK-4(sp)

  ...

  .size   func, .-func
*/
    std::size_t stk = ((_cur_offset + 4*8)/16 + 1) * 16;
    os<<"  .text"<<std::endl;
    os<<"  .align  2"<<std::endl;
    os<<"  .global "<<_func_name<<std::endl;
    os<<"  .type   "<<_func_name<<", @function"<<std::endl;
    os<<_func_name<<":"<<std::endl;
    if (stk < 2048){
        os<<"addi sp, sp, -"<<stk<<std::endl;
        os<<"sw ra, "<<stk-4<<"(sp)"<<std::endl;
    }
    else{
        os<<"li "<<kResult3Reg<<", "<<-stk<<std::endl;
        os<<"add sp, sp, "<<kResult3Reg<<std::endl;
        os<<"li "<<kResult3Reg<<", "<<stk-4<<std::endl;
        os<<"add "<<kResult3Reg<<", sp, "<<kResult3Reg<<std::endl;
        os<<"sw ra, 0("<<kResult3Reg<<")"<<std::endl;
    }
    
    if(_func_name == "main"){
        os<<global_inst.str();
    }
    for (std::size_t i = 0; i < _num_args; ++i) {
        //sw reg, int10*4(sp)
        os<<"sw a"<<i<<", "<<i*4<<"(sp)"<<std::endl;
    }
    for (const auto &inst: _insts) inst->Dump_RISC_V(os, *this);
    os<<"  .size   "<<_func_name<<", .-"<<_func_name<<std::endl;
}

void FunctionDef::Dump_RISC_V_GLOB(std::ostream &os, std::stringstream& global_inst) const{
    for (const auto &decl : _decl_insts) decl->Dump_RISC_V(os, *this);
    for (const auto &inst: _insts) {
        auto assign_inst = std::dynamic_pointer_cast<AssignInst>(inst);
        if((!assign_inst->val()->is_int == 1 )||( !assign_inst->val()->get_RISC_V_offset() == 0)){
            inst->Dump_RISC_V(global_inst, *this);
        }
    }
}
void DeclareVarInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func) const{
    if (func.func_name()!="00_GLOBAL"){
        assert(false && "DeclareVarInst won't generate anything out global area!");
    }

    os<<"  .global   "; _val->Dump_RISC_V(os); os <<std::endl;
    os<<"  .section  .sdata"<<std::endl;
    os<<"  .align    2"<<std::endl;
    os<<"  .type     "; _val->Dump_RISC_V(os); os<<", @object"<<std::endl;
    os<<"  .size     "; _val->Dump_RISC_V(os); os<<", 4"<<std::endl;
    _val->Dump_RISC_V(os); os<<":"<<std::endl;
    os<<"  .word     0"<<std::endl;
}

void DeclareArrInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func) const{
    if (func.func_name()!="00_GLOBAL"){
        assert(false && "DeclareArrInst won't generate anything out global area!");
    }

    os<<"  .comm ";
    _val->Dump_RISC_V(os);
    os<<", "<<_symbol_size<<", 4"<<std::endl;
}

void AssignInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func) const{
    _val->Dump_RISC_V_Read(os);
    _dest->Dump_RISC_V_Write(os);
}
void JumpInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func ) const{
    os<<"j ";
    _label->Dump_RISC_V(os);
    os<<std::endl;
}
void LabelInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func ) const{
    _label->Dump_RISC_V(os);
    os<<":"<<std::endl;
}
void UnaryInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func ) const{
    _opr->Dump_RISC_V_Read(os);
    switch (_op) {
    case yy::parser::token::TOK_PLUS: {break;}
    case yy::parser::token::TOK_MINUS: {os<<"neg "<<kResultReg<<", "<<kResultReg<<std::endl; break;}
    case yy::parser::token::TOK_NOT: {os<<"seqz "<<kResultReg<<", "<<kResultReg<<std::endl; break;}
    default: assert(false && "unknown binary operator");
    }
    _dest->Dump_RISC_V_Write(os);
}

void BinaryInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func ) const{
    _lhs->Dump_RISC_V_Read(os);
    os << "mv " << kResult2Reg << ", " << kResultReg << std::endl;
    _rhs->Dump_RISC_V_Read(os);
    if (_op == yy::parser::token::TOK_LTE || _op ==yy::parser::token::TOK_GTE) {
        os << (_op == yy::parser::token::TOK_LTE ? "sgt " : "slt ")<< kResultReg << ", " << kResult2Reg << ", " << kResultReg<< std::endl;
        os << "seqz " << kResultReg << ", " << kResultReg << std::endl;
    }
    else if (_op == yy::parser::token::TOK_EQ || _op == yy::parser::token::TOK_NEQ) {
        os << "xor " << kResultReg << ", " << kResult2Reg << ", " << kResultReg<< std::endl;
        os << (_op == yy::parser::token::TOK_EQ ? "seqz" : "snez") << ' '
        << kResultReg << ", " << kResultReg << std::endl;
    }
    else if (_op == yy::parser::token::TOK_AND){
        //snez reg1, reg2
        //snez t0, reg3
        //and reg1, reg1, t0
        os <<"snez "<<kResultReg<<", "<<kResult2Reg<<std::endl;
        os <<"snez "<<kResult3Reg<<", "<<kResultReg<<std::endl;
        os <<"and "<<kResultReg<<", "<<kResultReg<<", "<<kResult3Reg<<std::endl;
    }
    else if (_op == yy::parser::token::TOK_OR){
        //or reg1, reg2, reg3
        //snez reg1, reg1
        os <<"or "<<kResultReg<<", "<<kResult2Reg<<", "<<kResultReg<<std::endl;
        os <<"snez "<<kResultReg<<", "<<kResultReg<<std::endl;
    }
    else {
        switch (_op) {
        case yy::parser::token::TOK_PLUS: os << "add"; break;
        case yy::parser::token::TOK_MINUS: os << "sub"; break;
        case yy::parser::token::TOK_TIMES: os << "mul"; break;
        case yy::parser::token::TOK_OVER: os << "div"; break;
        case yy::parser::token::TOK_MOD: os << "rem"; break;
        case yy::parser::token::TOK_LT: os << "slt"; break;
        case yy::parser::token::TOK_GT: os << "sgt"; break;
        default: assert(false && "unknown binary operator");
        }
        os << ' ' << kResultReg << ", " << kResult2Reg << ", " << kResultReg
        << std::endl;
    }

    _dest->Dump_RISC_V_Write(os);
}

void BranchInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func ) const{
    _cond->Dump_RISC_V_Read(os);
    os <<(_bnez ? "bnez" : "beqz") << ' ' << kResultReg << ", ";
    _label->Dump_RISC_V(os);
    os<<std::endl;
}

void FuncCallInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func ) const{
    std::size_t j = 0;
    for(const auto &i: _args){
        i->Dump_RISC_V_Read(os);
        os<<"mv a"<<j++<<", "<<kResultReg<<std::endl;
    }
    os<<"call "<<_func->func_name()<<std::endl;
    os<<"mv "<<kResultReg<<", a0"<<std::endl;
    for (std::size_t i = 0; i < _args.size(); ++i) {
        os << "lw a"<<i<<", "<<i*4<<"(sp)"<<std::endl;
    }
    _dest->Dump_RISC_V_Write(os);
}
void ReturnInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func ) const{
    if (_val!=nullptr)
        _val->Dump_RISC_V_Read(os);
        os<< "mv a0, "<<kResultReg<<std::endl;

    std::size_t stk = ((func.cur_offset()/4 + 8)/4 + 1) * 16;
    if (stk < 2048){
        os<<"lw ra, "<<stk - 4<<"(sp)"<<std::endl;
        os<<"addi sp, sp, "<<stk<<std::endl;
    }
    else{
        os<<"li "<<kResult3Reg<<", "<<stk-4<<std::endl;
        os<<"add "<<kResult3Reg<<", sp, "<<kResult3Reg<<std::endl;
        os<<"lw ra, 0("<<kResult3Reg<<")"<<std::endl;
        os<<"li "<<kResult3Reg<<", "<<stk<<std::endl;
        os<<"add sp, sp, "<<kResult3Reg<<std::endl;
    }
    os<<"ret"<<std::endl;
}

//2*FuncDef Bugs in load store loadaddr
void VoidFuncCallInst::Dump_RISC_V(std::ostream &os, const FunctionDef &func ) const{
    std::size_t j = 0;
    for(const auto &i: _args){
        i->Dump_RISC_V_Read(os);
        os<<"mv a"<<j++<<", "<<kResultReg<<std::endl;
    }
    if (_func->func_name() == "starttime"){
        os<<"li a0, 1"<<std::endl;
        os<<"call _sysy_starttime"<<std::endl;
    }else{
        if (_func->func_name() == "stoptime"){
            os<<"li a0, 2"<<std::endl;
            os<<"call _sysy_stoptime"<<std::endl;
        }
        else{
            os<<"call "<<_func->func_name()<<std::endl;
        }
    }
    //lw reg, int10*4(sp)
    for (std::size_t i = 0; i < _args.size(); ++i) {
        os << "lw a"<<i<<", "<<i*4<<"(sp)"<<std::endl;
    }
}



void SlotVal::Dump_RISC_V(std::ostream &os ) const{
    os<<_offset;
}
void SlotVal::Dump_RISC_V_Read(std::ostream &os ) const{
    //load int10 reg
    //lw reg, int10*4(sp)
    if (_offset + 32 < 2048){
        os<<"lw "<<kResultReg<<", "<<_offset + 32<<"(sp)"<<std::endl;
    }
    else{
        os<<"li "<<kResult3Reg<<", "<<_offset + 32<<std::endl;
        os<<"add "<<kResult3Reg<<", sp, "<<kResult3Reg<<std::endl;
        os<<"lw "<<kResultReg<<", 0("<<kResult3Reg<<")"<<std::endl;
    }
    
}
void SlotVal::Dump_RISC_V_Write(std::ostream &os ) const{
    if (_offset + 32 < 2048){
        os<<"sw "<<kResultReg<<", "<<_offset + 32<<"(sp)"<<std::endl;
    }
    else{
        os<<"li "<<kResult3Reg<<", "<<_offset + 32<<std::endl;
        os<<"add "<<kResult3Reg<<", sp, "<<kResult3Reg<<std::endl;
        os<<"sw "<<kResultReg<<", 0("<<kResult3Reg<<")"<<std::endl;
    }
}
void SlotVal::Dump_RISC_V_offset(std::ostream &os ) const{
    os<<_offset + 32;
}
void VarSlotVal::Dump_RISC_V(std::ostream &os ) const{
    if (_is_global == 1){
        os<<"v"<<_id;
    }
    else{
        os<<_offset;
    }
}
void VarSlotVal::Dump_RISC_V_offset(std::ostream &os ) const{
    if (_is_global == 1){
        os<<"v"<<_id;
    }
    else{
        os<<_offset + 32;
    }
}
void VarSlotVal::Dump_RISC_V_Read(std::ostream &os ) const{
    if (_is_global == 1){
        if (_is_addr){
            //loadaddr global_var reg	la reg, global_var
            os<<"la "<<kResultReg<<", v"<<_id<<std::endl;
        }
        else{
            //load global_var reg	lui reg, %hi(global_var) lw reg, %lo(global_var)(reg)
            os<<"lui "<<kResultReg<<", %hi(v"<<_id<<")"<<std::endl;
            os<<"lw "<<kResultReg<<", %lo(v"<<_id<<")("<<kResultReg<<")"<<std::endl;
        }
    }
    else{
        if (_is_addr){
            //loadaddr int10 reg	addi reg, sp, int10*4
            //os <<"li "<<kResult3Reg<<_offset + 32<<std::endl;
            if (_offset + 32 < 2048){
                os<<"addi "<<kResultReg<<", sp, "<<_offset + 32<<std::endl;
            }
            else{
                os<<"li "<<kResult3Reg<<", "<<_offset + 32<<std::endl;
                os<<"add "<<kResultReg<<", sp, "<<kResult3Reg<<std::endl;
            }
            
        }
        else{
            //load int10 reg	lw reg, int10*4(sp)
            if (_offset + 32 < 2048){
                os<<"lw "<<kResultReg<<", "<<_offset + 32<<"(sp)"<<std::endl;
            }
            else{
                os<<"li "<<kResult3Reg<<", "<<_offset + 32<<std::endl;
                os<<"add "<<kResult3Reg<<", sp, "<<kResult3Reg<<std::endl;
                os<<"lw "<<kResultReg<<", 0("<<kResult3Reg<<")"<<std::endl;
            }
        }
    }
}
void VarSlotVal::Dump_RISC_V_Write(std::ostream &os ) const{
    if (_is_global == 1){
        os<<"la "<<kArrReg<<", v"<<_id<<std::endl;
        //reg1[int12] = reg2 sw reg2, int12(reg1)
        os<<"sw "<<kResultReg<<", 0("<<kArrReg<<")"<<std::endl;
    }
    else{
        if (_offset + 32 < 2048){
            os<<"sw "<<kResultReg<<", "<<_offset + 32<<"(sp)"<<std::endl;
        }
        else{
            os<<"li "<<kResult3Reg<<", "<<_offset + 32<<std::endl;
            os<<"add "<<kResult3Reg<<", sp, "<<kResult3Reg<<std::endl;
            os<<"sw "<<kResultReg<<", 0("<<kResult3Reg<<")"<<std::endl;
        }
        
    }
}
void ArgRefVal::Dump_RISC_V(std::ostream &os ) const{
    os<<"a"<<_id;
}
void ArgRefVal::Dump_RISC_V_Read(std::ostream &os ) const{
    os<<"lw "<<kResultReg<<", "<<_id * 4<<"(sp)"<<std::endl;
}
void ArgRefVal::Dump_RISC_V_Write(std::ostream &os ) const{
    os<<"sw "<<kResultReg<<", "<<_id * 4<<"(sp)"<<std::endl;
}

void ArrayRefVal::Dump_RISC_V(std::ostream &os ) const{
    assert(false && "Should not call Dump_Tigger of ArrayRefVal Directly!");
}
void ArrayRefVal::Dump_RISC_V_Read(std::ostream &os ) const{
    if(_offset->is_int == 1){
        if (_base->is_arg_ref == 1){
            //mv reg1, reg2
            os<<"mv "<<kArrReg<<", ";
            _base->Dump_RISC_V(os);
            os<<std::endl;
        }
        else{
            //loadaddr int10 reg	addi reg, sp, int10*4
            //loadaddr global_var reg	la reg, global_var
            if(_base->_is_global == 1){
                os<< "la "<<kArrReg<<", ";
                _base->Dump_RISC_V_offset(os);
                os<<std::endl;
            }
            else{
                std::size_t base_offset = _base->get_RISC_V_offset();
                if (base_offset < 2048){
                    os<<"addi "<<kArrReg<<", sp, "<<base_offset<<std::endl;
                }
                else{
                    os<<"li "<<kResult3Reg<<", "<<base_offset<<std::endl;
                    os<<"add "<<kArrReg<<", sp, "<<kResult3Reg<<std::endl;
                }
            }
        }
        //reg1 = reg2[int12]	lw reg1, int12(reg2)
        //Bugs here
        std::size_t off_offset = _offset->get_RISC_V_offset();
        if (off_offset < 2048){
            os<<"lw "<<kResultReg<<", "<<off_offset<<"("<<kArrReg<<")"<<std::endl;
        }
        else{
            os<<"li "<<kResult3Reg<<", "<<off_offset<<std::endl;
            os<<"add "<<kResult3Reg<<", "<<kArrReg<<", "<<kResult3Reg<<std::endl;
            os<<"lw "<<kResultReg<<", 0("<<kResult3Reg<<")"<<std::endl;
        }
    }
    else{
        if (_base->is_arg_ref == 1){
            os<<"mv "<<kArrReg<<", ";
            _base->Dump_RISC_V(os);
            os<<std::endl;
        }
        else{
            if(_base->_is_global == 1){
                os<< "la "<<kArrReg<<", ";
                _base->Dump_RISC_V_offset(os);
                os<<std::endl;
            }
            else{
                //Bugs here
                std::size_t base_offset = _base->get_RISC_V_offset();
                if (base_offset < 2048){
                    os<<"addi "<<kArrReg<<", sp, "<<base_offset<<std::endl;
                }
                else{
                    os<<"li "<<kResult3Reg<<", "<<base_offset<<std::endl;
                    os<<"add "<<kArrReg<<", sp, "<<kResult3Reg<<std::endl;
                }
            }
        }
        if (_offset->is_arg_ref == 1){
            os<<"mv "<<kTempReg<<", ";
            _offset->Dump_RISC_V(os);
            os<<std::endl;
        }
        else{
            //load int10 reg	lw reg, int10*4(sp)
            //load global_var reg	lui reg, %hi(global_var) lw reg, %lo(global_var)(reg)
            if(_offset->_is_global == 1){
                os<<"lui "<<kTempReg<<", %hi(";
                _offset->Dump_RISC_V_offset(os);
                os<<")"<<std::endl;

                os<<"lw "<<kTempReg<<", %lo(";
                _offset->Dump_RISC_V_offset(os);
                os<<")("<<kTempReg<<")"<<std::endl;
            }
            else{
                //Bugs here
                std::size_t off_offset = _offset->get_RISC_V_offset();
                if (off_offset < 2048){
                    os<<"lw "<<kTempReg<<", "<<off_offset<<"(sp)"<<std::endl;
                }
                else{
                    os<<"li "<<kResult3Reg<<", "<<off_offset<<std::endl;
                    os<<"add "<<kResult3Reg<<", sp, "<<kResult3Reg<<std::endl;
                    os<<"lw "<<kTempReg<<", 0("<<kResult3Reg<<")"<<std::endl;
                }
            }
        }
        //reg1 = reg2 + reg3	add reg1, reg2, reg3
        os << "add "<<kArrReg << ", "<<kArrReg<< ", "<< kTempReg<<std::endl; 
        //lw reg1, int12(reg2)
        os << "lw "<<kResultReg << ", 0("<<kArrReg<<")"<<std::endl;
    }
}
void ArrayRefVal::Dump_RISC_V_Write(std::ostream &os ) const{
    if(_offset->is_int == 1){
        if (_base->is_arg_ref == 1){
            //mv reg1, reg2
            os<<"mv "<<kArrReg<<", ";
            _base->Dump_RISC_V(os);
            os<<std::endl;
        }
        else{
            //loadaddr int10 reg	addi reg, sp, int10*4
            //loadaddr global_var reg	la reg, global_var
            if(_base->_is_global == 1){
                os<< "la "<<kArrReg<<", ";
                _base->Dump_RISC_V_offset(os);
                os<<std::endl;
            }
            else{
                std::size_t base_offset = _base->get_RISC_V_offset();
                if (base_offset < 2048){
                    os<<"addi "<<kArrReg<<", sp, "<<base_offset<<std::endl;
                }
                else{
                    os<<"li "<<kResult3Reg<<", "<<base_offset<<std::endl;
                    os<<"add "<<kArrReg<<", sp, "<<kResult3Reg<<std::endl;
                }
            }
        }
        //reg1[int12] = reg2	sw reg2, int12(reg1)
        std::size_t off_offset = _offset->get_RISC_V_offset();
        if (off_offset < 2048){
            os<<"sw "<<kResultReg<<", "<<off_offset<<"("<<kArrReg<<")"<<std::endl;
        }
        else{
            os<<"li "<<kResult3Reg<<", "<<off_offset<<std::endl;
            os<<"add "<<kResult3Reg<<", "<<kArrReg<<", "<<kResult3Reg<<std::endl;
            os<<"sw "<<kResultReg<<", 0("<<kResult3Reg<<")"<<std::endl;
        }
        
    }
    else{
        if (_base->is_arg_ref == 1){
            os<<"mv "<<kArrReg<<", ";
            _base->Dump_RISC_V(os);
            os<<std::endl;
        }
        else{
            if(_base->_is_global == 1){
                os<< "la "<<kArrReg<<", ";
                _base->Dump_RISC_V_offset(os);
                os<<std::endl;
            }
            else{
                std::size_t base_offset = _base->get_RISC_V_offset();
                if (base_offset < 2048){
                    os<<"addi "<<kArrReg<<", sp, "<<base_offset<<std::endl;
                }
                else{
                    os<<"li "<<kResult3Reg<<", "<<base_offset<<std::endl;
                    os<<"add "<<kArrReg<<", sp, "<<kResult3Reg<<std::endl;
                }
            }
        }
        if (_offset->is_arg_ref == 1){
            os<<"mv "<<kTempReg<<", ";
            _offset->Dump_RISC_V(os);
            os<<std::endl;
        }
        else{
            //load int10 reg	lw reg, int10*4(sp)
            //load global_var reg	lui reg, %hi(global_var) lw reg, %lo(global_var)(reg)
            if(_offset->_is_global == 1){
                os<<"lui "<<kTempReg<<", %hi(";
                _offset->Dump_RISC_V_offset(os);
                os<<")"<<std::endl;

                os<<"lw "<<kTempReg<<", %lo(";
                _offset->Dump_RISC_V_offset(os);
                os<<")("<<kTempReg<<")"<<std::endl;
            }
            else{
                std::size_t off_offset = _offset->get_RISC_V_offset();
                if (off_offset < 2048){
                    os<<"lw "<<kTempReg<<", "<<off_offset<<"(sp)"<<std::endl;
                }
                else{
                    os<<"li "<<kResult3Reg<<", "<<off_offset<<std::endl;
                    os<<"add "<<kResult3Reg<<", sp, "<<kResult3Reg<<std::endl;
                    os<<"lw "<<kTempReg<<", 0("<<kResult3Reg<<")"<<std::endl;
                }
            }
        }
        //reg1 = reg2 + reg3	add reg1, reg2, reg3
        os << "add "<<kArrReg << ", "<<kArrReg<< ", "<< kTempReg<<std::endl; 
        //lw reg1, int12(reg2)
        os << "sw "<<kResultReg << ", 0("<<kArrReg<<")"<<std::endl;
    }
}


void LabelVal::Dump_RISC_V(std::ostream &os ) const{
    os<<".label"<<_id;
}
void LabelVal::Dump_RISC_V_Read(std::ostream &os ) const{
    assert(false && "reading a label");
}
void LabelVal::Dump_RISC_V_Write(std::ostream &os ) const{
    assert(false && "writing a label");
}
void IntVal::Dump_RISC_V(std::ostream &os ) const{
    os<<_val;
}
void IntVal::Dump_RISC_V_Read(std::ostream &os ) const{
    os<<"li "<<kResultReg<<", "<<_val<<std::endl;
}
void IntVal::Dump_RISC_V_Write(std::ostream &os ) const{
    assert(false && "writing an integer");
}