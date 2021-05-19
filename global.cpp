/****************************************************/
/*File: global.cpp                                  */
/*This file define the functions in global.h mainly */
/*Eval and GenerateIR                               */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#include "global.h"
#include "irgen.h"
std::optional<int> IdAST::Eval(IRGen &gen) const{
    return gen.EvalOn(*this);
}
std::optional<int> IntAST::Eval(IRGen &gen) const{
    return gen.EvalOn(*this);
}
std::optional<int> ArrayAST::Eval(IRGen &gen) const{
    return gen.EvalOn(*this);
}
std::optional<int> UnaryAST::Eval(IRGen &gen) const{
    return gen.EvalOn(*this);
}
std::optional<int> BinaryAST::Eval(IRGen &gen) const{
    return gen.EvalOn(*this);
}

ValPtr CompUnitAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr ConstDeclAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr ConstDefAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr ConstDefListAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr VarDeclAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr VarDefListAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr VarDefAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr FuncDefAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr BlockAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr BlockItemsAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr AssignAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr ExpAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr IfAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr WhileAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr CondAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr ReturnAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr BinaryAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr UnaryAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr FuncCallAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr IntAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr IdAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}
ValPtr ArrayAST::GenerateIR(IRGen &gen) const{
    return gen.GenerateOn(*this);
}

