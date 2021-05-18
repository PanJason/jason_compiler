#include "irgen.h"
#include <iostream>
#include <utility>
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

xstl::Guard IRGen::NewSymTable(){
    _symbol_table = xstl::MakeNestedMap(_symbol_table);
    return xstl::Guard([this]{_symbol_table = _symbol_table->outer();});
}

std::optional<int> IRGen::EvalOn(const IntAST& ast){
    return ast.val();
}
std::optional<int> IRGen::EvalOn(const IdAST& ast)
{
    auto iter = _const_vars.find(ast.id());
    if(iter == _const_vars.end()) assert("Not a const varible or evaluating unknown const variable");
    return iter->second.front();
}
std::optional<int> IRGen::EvalOn(const ArrayAST& ast){
    auto iter = _const_vars.find(ast.id());
    if(iter == _const_vars.end()) assert("Not a const array or evaluating unknown const array element");
    auto entry = _symbol_table->GetItem(ast.id(), true);
    if(!entry) assert("Array not defined yet!");
    auto dims = std::dynamic_pointer_cast<DimensionAST>(ast.exprs());
    assert(dims->const_dims().size()==entry->dim());
    std::size_t offset = 0;
    std::size_t start = entry->symbol_size() / sizeof(int);
    for (std::size_t i = 0; i < entry->dim(); i++){
        start = start/entry->shape().at(i);
        auto tmp = dims->const_dims().at(i)->Eval(*this);
        if(!tmp) assert("Fail to evaluate a dimension!");
        offset += start * (*tmp);
    }
    assert(start == 1);
    return iter->second.at(offset);
}

std::optional<int> IRGen::EvalOn(const BinaryAST& ast){
  if (ast.op() == yy::parser::token::TOK_AND || ast.op() == yy::parser::token::TOK_OR) {
    // evaluate lhs first
    auto lhs = ast.lhs()->Eval(*this);
    if (!lhs || (ast.op() == yy::parser::token::TOK_AND && !*lhs) ||
        (ast.op() == yy::parser::token::TOK_OR && *lhs)) {
      return lhs;
    }
    // then evaluate rhs
    return ast.rhs()->Eval(*this);
  }
  else {
    // evaluate the lhs & rhs
    auto lhs = ast.lhs()->Eval(*this), rhs = ast.rhs()->Eval(*this);
    if (!lhs || !rhs) return {};
    // perform binary operation
    switch (ast.op()) {
      case yy::parser::token::TOK_PLUS: return *lhs + *rhs;
      case yy::parser::token::TOK_MINUS: return *lhs - *rhs;
      case yy::parser::token::TOK_TIMES: return *lhs * *rhs;
      case yy::parser::token::TOK_OVER: return *lhs / *rhs;
      case yy::parser::token::TOK_MOD: return *lhs % *rhs;
      case yy::parser::token::TOK_LT: return *lhs < *rhs;
      case yy::parser::token::TOK_LTE: return *lhs <= *rhs;
      case yy::parser::token::TOK_GT: return *lhs > *rhs;
      case yy::parser::token::TOK_GTE: return *lhs >= *rhs;
      case yy::parser::token::TOK_EQ: return *lhs == *rhs;
      case yy::parser::token::TOK_NEQ: return *lhs != *rhs;
      default: assert(false && "unknown binary operator");
    }
    return {};
  }
}
std::optional<int> IRGen::EvalOn(const UnaryAST& ast){
  auto opr = ast.opr()->Eval(*this);
  if (!opr) return {};
  // perform unary operation
  switch (ast.op()) {
    case yy::parser::token::TOK_MINUS: return -*opr;
    case yy::parser::token::TOK_NOT: return !*opr;
    case yy::parser::token::TOK_PLUS: return *opr;
    default: assert(false && "unknown unary operator");
  }
  return {};
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
//This function should not be called directly 
ValPtr IRGen::GenerateOn(const DimensionAST& ast){
    return LogError("The Generate Dimension Function should not be called directly.!");
    /*
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
    */
}


//ID Dim 
//Should merge with DimensionAST
//Here ArrayAST only appear in the LVal and LVal won't appear in the constdef and vardef
//which would be generated explicitly later on.
ValPtr IRGen::GenerateOn(const ArrayAST& ast){
    auto base = _vars->GetItem(ast.id());
    if(!base) return LogError(
        "Symbol has not been defined"
    );
    auto entry = _symbol_table->GetItem(ast.id(),true);

    //Generate a series of add and times like DimensionAST.
    //Not finished yet.
    auto dims = std::dynamic_pointer_cast<DimensionAST>(ast.exprs());
    auto dest = _now_func->AddSlot();
    auto middle = _now_func->AddSlot();
    if(entry){
        std::size_t offset = 0;
        std::size_t start = entry->symbol_size() / sizeof(int);
        for (std::size_t i = 0; i < entry->dim(); i++){
            start = start/entry->shape().at(i);
            auto tmp = dims->const_dims().at(i)->GenerateIR(*this);
            if(!tmp) assert("Fail to evaluate a dimension!");
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_TIMES, middle, std::move(tmp), std::move(std::make_shared<IntVal>(start)));
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_PLUS, dest, dest, middle);
        }
        assert(start == 1);
    }
    else{
        auto func_table = _func_table.find(_now_func->func_name());
        if(func_table == _func_table.end()) return LogError("Current Function has no Function Table!");
        auto func_table_entry = func_table->second.find(ast.id());
        if(func_table_entry == func_table->second.end()) return LogError("Symbol has not been defined in the function table!");
        //Found in function table
        std::size_t offset = 0;
        std::size_t start = func_table_entry->second->symbol_size()/sizeof(int);
        //Dimension n , n-1 dimensions in the vector.
        for (std::size_t i = 0; i < func_table_entry->second->dim()-1; i++){
            auto tmp = dims->const_dims().at(i)->GenerateIR(*this);
            if(!tmp) assert("Fail to evaluate a dimension!");
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_TIMES, middle, std::move(tmp), std::move(std::make_shared<IntVal>(start)));
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_PLUS, dest, dest, middle);
            start = start/func_table_entry->second->shape().at(i);
        }
        assert(start == 1);
        auto tmp = dims->const_dims().at(func_table_entry->second->dim()-1)->GenerateIR(*this);
        if(!tmp) assert("Fail to evaluate a dimension!");
        _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_PLUS, dest, dest, std::move(tmp));
    }
    return std::make_shared<ArrayRefVal>(base, dest);
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
    if (ast.expr() != std::make_shared<ExpAST>(nullptr)) ast.expr()->GenerateIR(*this);
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

//Here if both the LVal and the Exp are Array Element,
//There is problem because Eeyore does not allow 

ValPtr IRGen::GenerateOn(const AssignAST& ast){
    auto expr = ast.expr()->GenerateIR(*this);
    if(!expr) return nullptr;
    auto slot = ast.lval()->GenerateIR(*this);
    if(!slot) return LogError("Symbol Undefined");
    if(ast.expr()->is_lval_array == 1 && ast.lval()->is_lval_array == 1){
        auto dest = _now_func->AddSlot();
        _now_func->PushInst<AssignInst>(dest, std::move(expr));
        _now_func->PushInst<AssignInst>(std::move(slot), std::move(dest));
    }
    else{
        _now_func->PushInst<AssignInst>(std::move(slot), std::move(expr));
    }
    return nullptr;
}

//; OR {BlockItems} BlockItems should be in a new environment.
ValPtr IRGen::GenerateOn(const BlockAST& ast){
    if (ast.blockitem() == nullptr) return nullptr;
    auto env = NewEnvironment();
    auto sym = NewSymTable();
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
    _func_table.insert(std::make_pair(ast.name(),std::unordered_map<std::string, FTEPtr>()));
    auto table = _func_table.find(ast.name());
    //Insert the params to some function table
    auto env = NewEnvironment();
    auto sym = NewSymTable();
    int p = 0;
    for(const auto &i : param_list->const_params()){
        if(i->is_array == 1)
        {
            auto tmp = std::dynamic_pointer_cast<FuncFParamArrayAST>(i);
            _vars->AddItem(tmp->name(), std::make_shared<ArgRefVal>(p++));
            
            auto entry = std::make_shared<FuncTableEntry>(tmp->param_type(),1);
            //Evaluate each dimension and insert
            if(tmp->dimension()!=nullptr){
                auto dims = std::dynamic_pointer_cast<DimensionAST>(tmp->dimension());
                entry->_dim = 1 + dims->const_dims().size();
                for(const auto &i : dims->const_dims()){
                    auto tmp = i->Eval(*this);
                    if(!tmp) return LogError("Fail To Evaluate the dimension!");
                    entry->_symbol_size *= (*tmp);
                    entry->_shape.push_back(*tmp);
                }
            }
            table->second.insert(std::make_pair<const std::string&, FTEPtr>(tmp->name(), std::move(entry)));
        }
        if(i->is_array == 0){
            auto tmp = std::dynamic_pointer_cast<FuncFParamVarAST>(i);
            _vars->AddItem(tmp->name(), std::make_shared<ArgRefVal>(p++));
            auto entry = std::make_shared<FuncTableEntry>(tmp->param_type(),0);
            table->second.insert(std::make_pair<const std::string&, FTEPtr>(tmp->name(), std::move(entry)));
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
    if(ast.is_array_def()){
        //2. Generate on Arrays
        //Evaluate expr or {expr, expr, {expr, expr},{expr}}
        //To-do
        //Create slot
        auto slot = _now_func->AddSlot();
        //Add slot to _vars
        if (!_vars->AddItem(ast.id(), slot)) {
            return LogError("Array has already been defined");
        }
        //Evaluate each dimension
        std::vector<std::optional<int> > dim_list;
        auto dim_exprs = std::dynamic_pointer_cast<DimensionAST>(ast.const_exprs());
        for(const auto &i : dim_exprs->const_dims()){
            auto expr = i->Eval(*this);
            if(!expr) return LogError("Can not Evaluate the Dimension of the const Array");
            dim_list.push_back(std::move(expr));
        }
        //Create Entry in the Symbol Table
        auto ste = std::make_shared<SymbolTableEntry>(yy::parser::token::TOK_INT, 1, 1);
        ste->_dim = dim_list.size();
        for(const auto &i: dim_list){
            ste->_symbol_size *= (*i);
            ste->_shape.push_back(*i);
        }
        //Insert Array Declaration Instruction
        _now_func->PushDeclInst<DeclareArrInst>(slot, ste->symbol_size());
        _symbol_table->AddItem(ast.id(), ste);
        //Store the value
        std::vector<int> temp_const_values;
        //First have to check _const_init_value points to a single expression or 
        //ConstInitValArray
        if (ast.const_init_val()->is_array == 1){
            auto civ = std::dynamic_pointer_cast<ConstInitValArrayAST>(ast.const_init_val());
            if(civ->init_vals() == nullptr){
                for(size_t i = 0; i < ste->_symbol_size/4 ; i++){
                    temp_const_values.push_back(0);
                }
            }
            else{
                //In this case we have to deal with {val, {val,val},val,val,{val}}
                //To-do

            }
        }
        else{
            auto val = ast.const_init_val()->Eval(*this);
            if(!val) return LogError("Can not Evaluate the Initial Const Value!");
            for(size_t i = 0; i < ste->_symbol_size/4 ; i++){
                temp_const_values.push_back(*val);
            }
        }
        if(_const_vars.find(ast.id())!=_const_vars.end()) return LogError("Const Array already been defined!");
        for(size_t i = 0; i < ste->_symbol_size ; i+=4){
            _now_func->PushInst<AssignInst>(std::make_shared<ArrayRefVal>(slot,std::make_shared<IntVal>(i)), std::make_shared<IntVal>(temp_const_values.at(i/4)));
        }
        _const_vars.insert(std::make_pair<const std::string &, std::vector<int> >(ast.id(), std::move(temp_const_values)));
        return nullptr;
    }
    else{
        //1. Generate on Variables
        auto expr = ast.const_init_val()->Eval(*this);
        if (!expr) return LogError("Can not evaluate the Init Value of a const Variable");
        //Create slot
        auto slot = _now_func->AddSlot();
        //Add slot to _vars
        if (!_vars->AddItem(ast.id(), slot)) {
            return LogError("symbol has already been defined");
        }
        //Insert Variable Declaration Instruction
        _now_func->PushDeclInst<DeclareVarInst>(slot);
        //Create Entry in the Symbol Table
        auto ste = std::make_shared<SymbolTableEntry>(yy::parser::token::TOK_INT,1,0);
        _symbol_table->AddItem(ast.id(), std::move(ste));
        //Evaluate and Store init value;
        if(_const_vars.find(ast.id())!=_const_vars.end()) return LogError("Const Variable already been defined!");
        _const_vars.insert(std::make_pair<const std::string &, std::vector<int> >(ast.id(), {*expr}));
        _now_func->PushInst<AssignInst>(std::move(slot), std::make_shared<IntVal>((*expr)));
        return nullptr;
    }

}
/*
    ValPtr GenerateOn(const VarDeclAST& ast);
    ValPtr GenerateOn(const VarDefListAST& ast);
    ValPtr GenerateOn(const VarDefAST& ast);
    ValPtr GenerateOn(const InitValArrayAST& ast);
    ValPtr GenerateOn(const InitValAST& ast);
*/
ValPtr IRGen::GenerateOn(const VarDeclAST& ast){
    ast.var_defs()->GenerateIR(*this);
    return nullptr;
}
ValPtr IRGen::GenerateOn(const VarDefListAST& ast){
    for(const auto &i : ast.const_var_defs()){
        auto tmp = std::dynamic_pointer_cast<VarDefAST>(i);
        tmp->GenerateIR(*this);
    }
    if(_error_num) return LogError("Error in Var Definitions!");
    return nullptr;
}
ValPtr IRGen::GenerateOn(const VarDefAST& ast){

}
//Todo: ConstDefAST, VarDefAST;
//Todo: Finish ConstDefAST, VarDefAST
//Todo: Finish Eval and GenerateIR in global.cpp
//Todo: Finish irgen.cpp to dump the Eeyore.s
//Todo: define a new InstPtrList just for Declarations