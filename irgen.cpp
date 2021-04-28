#include "irgen.h"
#include <iostream>
#include "source.tab.hpp"

ValPtr IRGen::LogError(std::string_view message){
    std::cerr<<"Error From IRGen (Jason Compiler): "<< message << std::endl;
    _error_num++;
    return nullptr;
}

xstl::Guard IRGen::NewEnvironment(){
    //Enter the new enrionment
    _vars = xstl::MakeNestedMap(_vars);
    //Return an Guard object with a function.
    //When the object is destructed, the function is executed.
    return xstl::Guard([this] {_vars = _vars->outer(); });
}

xstl::Guard IRGen::NewLoopEnv(){
    _loop_labels = xstl::MakeNestedMap(_loop_labels);
    return xstl::Guard([this] {_loop_labels = _loop_labels->outer();});
}

/*
    ValPtr GenerateOn(const CompUnitAST& ast);
*/

ValPtr IRGen::GenerateOn(const IdAST& ast){
    auto slot = _vars->GetItem(ast.id());
    if(!slot) return LogError(
        "Symbol has not been defined"
    );
    return slot;
}

ValPtr IRGen::GenerateOn(const IntAST& ast){
    return std::make_shared<IntVal>(ast.val());
}

ValPtr IRGen::GenerateOn(const UnaryAST& ast){
    auto opr = ast.opr()->GenerateIR(*this);
    if (!opr) return nullptr;
    auto dest = _now_func->AddSlot();
    _now_func->PushInst<UnaryInst>(ast.op(), dest, std::move(opr));
    return dest;
}

ValPtr IRGen::GenerateOn(const BinaryAST& ast){
    if(ast.op()==yy::parser::token::TOK_AND || ast.op() == yy::parser::token::TOK_OR){
        auto end_logic = std::make_shared<LabelVal>();
        auto lhs = ast.lhs()->GenerateIR(*this);
        if (!lhs) return nullptr;
        // generate conditional branch
        _now_func->PushInst<BranchInst>(ast.op() == yy::parser::token::TOK_OR, lhs, end_logic);
        // generate rhs
        auto rhs = ast.rhs()->GenerateIR(*this);
        if (!rhs) return nullptr;
        _now_func->PushInst<AssignInst>(lhs, rhs);
        // generate label definition
        _now_func->PushInst<LabelInst>(std::move(end_logic));
        return lhs;
    }
    else{
        auto lhs = ast.lhs()->GenerateIR(*this);
        auto rhs = ast.rhs()->GenerateIR(*this);
        if(!lhs || !rhs) return nullptr;
        auto dest = _now_func->AddSlot();
        _now_func->PushInst<BinaryInst>(ast.op(), dest, std::move(lhs), std::move(rhs));
        return dest;
    }
}

//[Exp][Exp]...[Exp]
//Here is wrong 
//Could not generate index only using dimension
//Should change ConstDefAST and ValDefAST
ValPtr IRGen::GenerateOn(const DimensionAST& ast){
    ValPtr old_dest = nullptr;
    for(auto &i : ast.const_dims()){
        if (old_dest == nullptr){
            auto arg = i->GenerateIR(*this);
            old_dest = arg;
        }
        else{
            auto arg = i->GenerateIR(*this);
            auto dest = _now_func->AddSlot();
            _now_func ->PushInst<BinaryInst>(yy::parser::make_TIMES, dest, arg, old_dest);
            old_dest = dest;
        }
    }
    return old_dest;
}


//ID Dim
ValPtr IRGen::GenerateOn(const ArrayAST& ast){
    auto base = _vars->GetItem(ast.id());
    if(!base) return LogError(
        "Symbol has not been defined"
    );
    auto exprs = ast.exprs()->GenerateIR(*this);
    return std::make_shared<ArrayRefVal>(base, std::move(exprs));
}

ValPtr IRGen::GenerateOn(const ReturnAST& ast){
    auto expr = ast.expr()->GenerateIR(*this);
    if(!expr) return nullptr;
    _now_func->PushInst<ReturnInst>(std::move(expr));
}

ValPtr IRGen::GenerateOn(const FuncCallAST& ast){
    auto it = _funcs.find(ast.name());
    if (it == _funcs.end()){
        it = _lib_funcs.find(ast.name());
        if(it == _lib_funcs.end()) return LogError("Function Not Defined!");
    }
    auto param_list = std::dynamic_pointer_cast<FuncRParamsAST>(ast.params());
    if (param_list->const_exprs().size() != it->second->num_args()){
        return LogError("Argument Count Mismatch");
    }
    //Some type type check can be carried out here.
    ValPtrList args;
    for (const auto &i: param_list->const_exprs()){
        auto arg = i->GenerateIR(*this);
        if (!arg) return nullptr;
        args.push_back(std::move(arg));
    }
    auto dest = _now_func->AddSlot();
    _now_func->PushInst<FuncCallInst>(dest, it->second, std::move(args));
    return dest;
}

ValPtr IRGen::GenerateOn(const ExpAST& ast){
    ast.expr()->GenerateIR(*this);
    return nullptr;
}

ValPtr IRGen::GenerateOn(const IfAST& ast){
    auto cond = ast.cond()->GenerateIR(*this);
    if (!cond) return nullptr;
    auto false_branch = std::make_shared<LabelVal>();
    auto end_if = ast.else_then() ? std::make_shared<LabelVal>() : nullptr;
    // generate contional branch
    _now_func->PushInst<BranchInst>(false, std::move(cond), false_branch);
    // generate the true branch
    ast.then()->GenerateIR(*this);
    if (ast.else_then()) _now_func->PushInst<JumpInst>(end_if);
    // generate the false branch
    _now_func->PushInst<LabelInst>(std::move(false_branch));
    if (ast.else_then()) {
        ast.else_then()->GenerateIR(*this);
        _now_func->PushInst<LabelInst>(std::move(end_if));
    }
    return nullptr;
}
//While cond do stmt
ValPtr IRGen::GenerateOn(const WhileAST& ast){
    auto judge_label = std::make_shared<LabelVal>();
    _now_func->PushInst<LabelInst>(std::move(judge_label));
    auto cond = ast.cond()->GenerateIR(*this);
    if (!cond) return nullptr;
    auto false_branch = std::make_shared<LabelVal>();
    _now_func->PushInst<BranchInst>(false, std::move(cond), false_branch);
    auto loop_env = NewLoopEnv();
    _loop_labels->AddItem("judge_label", judge_label);
    _loop_labels->AddItem("false_branch", false_branch);
    ast.stmt()->GenerateIR(*this);
    _now_func->PushInst<JumpInst>(judge_label);
    _now_func->PushInst<LabelInst>(false_branch);
    return nullptr;
}

ValPtr IRGen::GenerateOn(const CondAST& ast){
    //Continue jmp to current judge label
    //Break jmp to current false_branch
    //Have to store the current false_branch and judge label.
    switch (ast.cond_type())
    {
    case yy::parser::token::TOK_BREAK:{
        auto false_branch = _loop_labels->GetItem("false_branch", false);
        if(!false_branch) return LogError("break statement not within a loop");
        _now_func->PushInst<JumpInst>(false_branch);
        break;}
    case yy::parser::token::TOK_CONTINUE:{
        auto judge_label = _loop_labels->GetItem("judge_label", false);
        if(!judge_label) return LogError("continue statement not within a loop");
        _now_func->PushInst<JumpInst>(judge_label);
        break;}
    
    default:
        return LogError("Undefined Branch Type");
    }
    return nullptr;
}

ValPtr IRGen::GenerateOn(const AssignAST& ast){
    auto expr = ast.expr()->GenerateIR(*this);
    if(!expr) return nullptr;
    auto slot = ast.lval()->GenerateIR(*this);
    if(!slot) return LogError("Symbol Undefined");
    _now_func->PushInst<AssignInst>(std::move(slot), std::move(expr));
    return nullptr;
}

//; OR {BlockItems} BlockItems should be in a new environment.
ValPtr IRGen::GenerateOn(const BlockAST& ast){
    if (ast.blockitem() == nullptr) return nullptr;
    auto env = NewEnvironment();
    ast.blockitem()->GenerateIR(*this);
    if(_error_num) return LogError("There is Error in this block!");
    return nullptr;
}

//Decl|Stmt Decl|Stmt ... Decl|Stmt
//Have to think of a way to do all the declaration First.
//Add a new indicator to tree nodes.
ValPtr IRGen::GenerateOn(const BlockItemsAST& ast){
    for (const auto &i : ast.const_items()){
        if(i->is_decl == 1){
            i->GenerateIR(*this);
            if(_error_num) return LogError("Error in this Declaration");
        }
    }
    for (const auto &i : ast.const_items()){
        if(i->is_decl != 1){
            i->GenerateIR(*this);
            if(_error_num) return LogError("Error in this Statement");
        }
    }
    return nullptr;
}

//INT/VOID ID ( [Params] ) Body
//INT ID | INT Arr[] ...
/*
    ValPtr GenerateOn(const FuncFParamsAST& ast);
    ValPtr GenerateOn(const FuncFParamVarAST& ast);
    ValPtr GenerateOn(const FuncFParamArrayAST& ast);
*/
ValPtr IRGen::GenerateOn(const FuncDefAST& ast){
    auto param_list = std::dynamic_pointer_cast<FuncFParamsAST>(ast.params());
    _now_func = std::make_shared<FunctionDef>(ast.name(),param_list->const_params().size(), ast.func_type());
    if(!_funcs.insert({_now_func->func_name(), _now_func}).second){
        return LogError("Function has already beed defined!");
    }
    //Create a function table
    _func_table.insert(std::make_pair(ast.name(),std::vector<FuncTableEntry>()));

    //Insert the params to some function table
    auto env = NewEnvironment();
    int p = 0;
    for(const auto &i : param_list->const_params()){
        if(i->is_array == 1)
        {
            auto tmp = std::dynamic_pointer_cast<FuncFParamArrayAST>(i);
            _vars->AddItem(tmp->name(), std::make_shared<ArgRefVal>(p++));
            auto iter = _func_table.find(ast.name());
            iter->second.push_back(FuncTableEntry(tmp->param_type(), 1));
        }
        if(i->is_array == 0){
            auto tmp = std::dynamic_pointer_cast<FuncFParamVarAST>(i);
            _vars->AddItem(tmp->name(), std::make_shared<ArgRefVal>(p++));
            auto iter = _func_table.find(ast.name());
            iter->second.push_back(FuncTableEntry(tmp->param_type(), 0));
        }
    }
    ast.block()->GenerateIR(*this);
    return nullptr;
}

/*
    ValPtr GenerateOn(const ConstDeclAST& ast);
    ValPtr GenerateOn(const ConstDefAST& ast);
    ValPtr GenerateOn(const ConstDefListAST& ast);
    ValPtr GenerateOn(const ConstInitValArrayAST& ast);
    ValPtr GenerateOn(const ConstInitValAST& ast);
    always some variables or some arrays adding some exps;
    
*/
//CONST INT ConstDefListAST;
//ConstDef, ConstDef, ... ConstDef
//
ValPtr IRGen::GenerateOn(const ConstDeclAST& ast){
    ast.const_defs()->GenerateIR(*this);
    return nullptr;
}

ValPtr IRGen::GenerateOn(const ConstDefListAST& ast){
    for(const auto &i : ast.const_const_defs()){
        auto tmp = std::dynamic_pointer_cast<ConstDefAST>(i);
        tmp->GenerateIR(*this);
    }
    if(_error_num) return LogError("Error in Const Definitions!");
    return nullptr;
}
//Somethings Have to do
//Evaluate each expression
//Store Values
//Generate Declaration
//Generate Assignment
ValPtr IRGen::GenerateOn(const ConstDefAST& ast){


}
/*
    ValPtr GenerateOn(const VarDeclAST& ast);
    ValPtr GenerateOn(const VarDefListAST& ast);
    ValPtr GenerateOn(const VarDefAST& ast);
    ValPtr GenerateOn(const InitValArrayAST& ast);
    ValPtr GenerateOn(const InitValAST& ast);
*/