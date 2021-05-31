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

const std::string kResult2Reg = "t3";
const std::string kResultReg = "t2";
const std::string kTempReg = "t1";
const std::string kArrReg = "t0";
std::size_t LabelVal::_next_id = 0;
std::size_t VarSlotVal::_next_id = 0;

ValPtr FunctionDef::AddSlot() {return std::make_shared<SlotVal>(_slot_num++, _cur_offset);}
ValPtr FunctionDef::AddVarSlot() {return std::make_shared<VarSlotVal>(_cur_offset, _func_name == "00_GLOBAL");}

std::string FunctionDef::Dump_Tigger(std::ostream &os, bool dump2str) const{
    std::stringstream s;
    if (dump2str == 1){
        s<<"f_"<<_func_name<<" ["<<_num_args<<"] ["<<_cur_offset + 4*27 <<"]"<<std::endl;
        for (std::size_t i=0; i< 11; i++){
            s << "store s"<<i<<" "<<_cur_offset + i * 4<<std::endl;
        }
        s<<"end f_"<<_func_name<<std::endl;
    }
    else{
        os<<"f_"<<_func_name<<" ["<<_num_args<<"] ["<<_cur_offset + 4*27 <<"]"<<std::endl;
        for (std::size_t i=0; i< 11; i++){
            os << "store s"<<i<<" "<<_cur_offset + i * 4<<std::endl;
        }
        os<<"end f_"<<_func_name<<std::endl;
    }
    return s.str();
}

std::string FunctionDef::Dump_Tigger_GLOB(std::ostream &os, bool dump2str) const{
    for (const auto &decl : _decl_insts) decl->Dump_Tigger(os, *this);
    std::stringstream s;
    return s.str();
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
    os <<"if ";
    if(_bnez){
        os<<" != x0 goto ";
    }
    else{
        os<<" == x0 goto ";
    }
    _label->Dump_Tigger_Read(os);
    os<<std::endl;
}
void FuncCallInst::Dump_Tigger(std::ostream &os, const FunctionDef &func ) const{
    for (std::size_t i = 0; i < _args.size(); ++i) {
        os << "store a"<<i<<" "<<(_func->cur_offset() + i * 4)/4<<std::endl;
    }
    std::size_t j = 0;
    for(const auto &i: _args){
        i->Dump_Tigger_Read(os);
        os<<"a"<<j++<<" = "<<kResultReg<<std::endl;
    }
    os<<"call f_"<<_func->func_name()<<std::endl;
    os<<kResultReg<<" = a0"<<std::endl;
    for (std::size_t i = 0; i < _args.size(); ++i) {
        os << "load "<<(_func->cur_offset() + i * 4)/4<<" a"<<i<<std::endl;
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
    for (std::size_t i = 0; i < _args.size(); ++i) {
        os << "store a"<<i<<" "<<(_func->cur_offset() + i * 4)/4<<std::endl;
    }
    std::size_t j = 0;
    for(const auto &i: _args){
        i->Dump_Tigger_Read(os);
        os<<"a"<<j++<<" = "<<kResultReg<<std::endl;
    }
    os<<"call f_"<<_func->func_name()<<std::endl;
    for (std::size_t i = 0; i < _args.size(); ++i) {
        os << "load "<<(_func->cur_offset() + i * 4)/4<<" a"<<i<<std::endl;
    }
}



void SlotVal::Dump_Tigger(std::ostream &os ) const{
    os<<_offset;
}
void SlotVal::Dump_Tigger_Read(std::ostream &os ) const{
    os<<"load "<<_offset/4<<" "<<kResultReg<<std::endl;
}
void SlotVal::Dump_Tigger_Write(std::ostream &os ) const{
    os<<"store "<<kResultReg<<" "<<_offset/4<<std::endl;
}
void SlotVal::Dump_Tigger_offset(std::ostream &os ) const{
    os<<_offset/4;
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
        os<<_offset/4;
    }
}
void VarSlotVal::Dump_Tigger_Read(std::ostream &os ) const{
    if (_is_global == 1){
        os<<"load v"<<_id<<" "<<kResultReg<<std::endl;
    }
    else{
        os<<"load "<<_offset/4<<" "<<kResultReg<<std::endl;
    }
}
void VarSlotVal::Dump_Tigger_Write(std::ostream &os ) const{
    if (_is_global == 1){
        os<<"loadaddr v"<<_id<<" "<<kArrReg<<std::endl;
        os<<kArrReg<<"[0]"<<" = "<<kResultReg<<std::endl;
    }
    else{
        os<<"store "<<kResultReg<<" "<<_offset/4<<std::endl;
    }
}
void ArgRefVal::Dump_Tigger(std::ostream &os ) const{
    os<<"a"<<_id;
}
void ArgRefVal::Dump_Tigger_Read(std::ostream &os ) const{
    os<<kResultReg<<" = a"<<_id<<std::endl;
}
void ArgRefVal::Dump_Tigger_Write(std::ostream &os ) const{
    os<<"a"<<_id<<" = "<<kResultReg<<std::endl;
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