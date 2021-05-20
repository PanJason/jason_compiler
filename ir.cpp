/****************************************************/
/*File: ir.cpp                                        */
/*This file is used to define the functions that    */
/*generate the target Eeyore representations.       */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#include "ir.h"
#include "source.tab.hpp"
std::size_t LabelVal::_next_id = 0;
std::size_t VarSlotVal::_next_id = 0;

ValPtr FunctionDef::AddSlot() {return std::make_shared<SlotVal>(_slot_num++);}
ValPtr FunctionDef::AddVarSlot() {return std::make_shared<VarSlotVal>();}

void FunctionDef::Dump_Eeyore(std::ostream &os) const {
    os<<"f_"<<_func_name<<" ["<<_num_args<<"]"<<std::endl;
    for (const auto &decl : _decl_insts) decl->Dump_Eeyore(os, *this);
    for (const auto &inst : _insts) inst->Dump_Eeyore(os, *this);
    os<<"end f_"<<_func_name<<std::endl;
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
      case yy::parser::token::TOK_MINUS: {os<<" -"; break;}
      case yy::parser::token::TOK_NOT: {os<<" !"; break;}
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