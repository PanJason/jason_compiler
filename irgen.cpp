#include "irgen.h"
#include <iostream>
#include <utility>
#include <optional>
#include "source.tab.hpp"
#define __DEBUG_IRGEN__

#ifdef __DEBUG_IRGEN__
#define pr_debug(msg)  std::cout << msg << std::endl;
#else
#define pr_debug(msg)  do {} while (0)
#endif

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
xstl::Guard IRGen::NewConstVars(){
    _const_vars = xstl::MakeNestedMap(_const_vars);
    return xstl::Guard([this]{_const_vars = _const_vars->outer();});
}

std::optional<int> IRGen::EvalOn(const IntAST& ast){
    return ast.val();
}
std::optional<int> IRGen::EvalOn(const IdAST& ast)
{
    pr_debug("Evaluating Const ID");
    pr_debug("ID is "+ast.id());
    auto iter = _const_vars->GetItem(ast.id(),true);
    pr_debug(iter->at(0));
    if(iter == nullptr) assert("Not a const varible or evaluating unknown const variable");
    return iter->front();
}
std::optional<int> IRGen::EvalOn(const ArrayAST& ast){
    auto iter = _const_vars->GetItem(ast.id(),true);
    if(iter == nullptr) assert("Not a const array or evaluating unknown const array element");
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
    return iter->at(offset);
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
    _now_func->add_cur_offset(4);
    _now_func->PushDeclInst<DeclareVarInst>(dest);
    if(opr->is_array == 1){
        auto dest1 = _now_func->AddSlot();
        _now_func->add_cur_offset(4);
        _now_func->PushDeclInst<DeclareVarInst>(dest1);
        _now_func->PushInst<AssignInst>(dest1, std::move(opr));
        _now_func->PushInst<UnaryInst>(ast.op(), dest, std::move(dest1));
    }
    else{
        _now_func->PushInst<UnaryInst>(ast.op(), dest, std::move(opr));
    }
    return dest;
}

ValPtr IRGen::GenerateOn(const BinaryAST& ast){
    if(ast.op()==yy::parser::token::TOK_AND || ast.op() == yy::parser::token::TOK_OR){
        auto end_logic = std::make_shared<LabelVal>();
        auto lhs = ast.lhs()->GenerateIR(*this);
        auto dest1 = _now_func->AddSlot();
        _now_func->add_cur_offset(4);
        _now_func->PushDeclInst<DeclareVarInst>(dest1);
        if (lhs->is_array == 1)
        {
            auto dest3 = _now_func->AddSlot();
            _now_func->add_cur_offset(4);
            _now_func->PushDeclInst<DeclareVarInst>(dest3);
            _now_func->PushInst<AssignInst>(dest3, lhs);
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_NEQ,dest1,dest3,std::make_shared<IntVal>(0));
        }
        else{
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_NEQ,dest1,lhs,std::make_shared<IntVal>(0));
        }
        if (!lhs) return LogError("No left side");
        // generate conditional branch
        _now_func->PushInst<BranchInst>(ast.op() == yy::parser::token::TOK_OR, dest1, end_logic);
        // generate rhs
        auto rhs = ast.rhs()->GenerateIR(*this);
        if (!rhs) return LogError("No right side");
        auto dest2 = _now_func->AddSlot();
        _now_func->add_cur_offset(4);
        _now_func->PushDeclInst<DeclareVarInst>(dest2);
        if (rhs->is_array == 1)
        {
            auto dest4 = _now_func->AddSlot();
            _now_func->add_cur_offset(4);
            _now_func->PushDeclInst<DeclareVarInst>(dest4);
            _now_func->PushInst<AssignInst>(dest4, rhs);
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_NEQ,dest2,dest4,std::make_shared<IntVal>(0));
        }
        else{
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_NEQ,dest2,rhs,std::make_shared<IntVal>(0));
        }
        _now_func->PushInst<AssignInst>(dest1, std::move(dest2));
        // generate label definition
        _now_func->PushInst<LabelInst>(std::move(end_logic));
        return dest1;
    }
    else{
        auto lhs = ast.lhs()->GenerateIR(*this);
        auto rhs = ast.rhs()->GenerateIR(*this);
        if(!lhs || !rhs) return nullptr;
        auto dest = _now_func->AddSlot();
        _now_func->add_cur_offset(4);
        _now_func->PushDeclInst<DeclareVarInst>(dest);
        if (lhs->is_array == 1 && rhs->is_array == 1){
            auto dest1 = _now_func->AddSlot();
            _now_func->add_cur_offset(4);
            _now_func->PushDeclInst<DeclareVarInst>(dest1);
            _now_func->PushInst<AssignInst>(dest1, lhs);
            auto dest2 = _now_func->AddSlot();
            _now_func->add_cur_offset(4);
            _now_func->PushDeclInst<DeclareVarInst>(dest2);
            _now_func->PushInst<AssignInst>(dest2, rhs);
            _now_func->PushInst<BinaryInst>(ast.op(), dest, dest1, dest2);
        }
        else{ 
            if (lhs->is_array == 1)
            {
                auto dest1 = _now_func->AddSlot();
                _now_func->add_cur_offset(4);
                _now_func->PushDeclInst<DeclareVarInst>(dest1);
                _now_func->PushInst<AssignInst>(dest1, lhs);
                _now_func->PushInst<BinaryInst>(ast.op(), dest, dest1, std::move(rhs));
            }
            else{
                if (rhs->is_array == 1){
                    auto dest2 = _now_func->AddSlot();
                    _now_func->add_cur_offset(4);
                    _now_func->PushDeclInst<DeclareVarInst>(dest2);
                    _now_func->PushInst<AssignInst>(dest2, rhs);
                    _now_func->PushInst<BinaryInst>(ast.op(), dest, std::move(lhs), dest2);
                }
                else{
                    _now_func->PushInst<BinaryInst>(ast.op(), dest, std::move(lhs), std::move(rhs));
                }
            }
        }
        return dest;
    }
}

//[Exp][Exp]...[Exp]
//Here is wrong 
//Could not generate index only using dimension
//Should change ConstDefAST and ValDefAST
//This function should not be called directly 
//ValPtr IRGen::GenerateOn(const DimensionAST& ast){
//    return LogError("The Generate Dimension Function should not be called directly.!");
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
//}


//ID Dim 
//Should merge with DimensionAST
//Here ArrayAST only appear in the LVal and LVal won't appear in the constdef and vardef
//which would be generated explicitly later on.
ValPtr IRGen::GenerateOn(const ArrayAST& ast){
    pr_debug("Entering ArrayAST for LVal");
    auto base = _vars->GetItem(ast.id());
    if(!base) return LogError(
        "Symbol has not been defined"
    );
    //Generate a series of add and times like DimensionAST.
    //Not finished yet.
    auto dims = std::dynamic_pointer_cast<DimensionAST>(ast.exprs());
    auto dest = _now_func->AddSlot();
    _now_func->add_cur_offset(4);
    _now_func->PushDeclInst<DeclareVarInst>(dest);
    auto middle = _now_func->AddSlot();
    _now_func->add_cur_offset(4);
    _now_func->PushDeclInst<DeclareVarInst>(middle);
    auto func_table = _func_table.find(_now_func->func_name());
    //if(func_table == _func_table.end()) return LogError("Current Function has no Function Table!");
    pr_debug("Found entry in _func_table");
    auto func_table_entry = func_table->second.find(ast.id());
    if(func_table_entry == func_table->second.end()){
        auto entry = _symbol_table->GetItem(ast.id(),true);
        if (entry == nullptr) return LogError("Symbol Not Found!");
        pr_debug("Found entry in _vars");
        std::size_t offset = 0;
        pr_debug("Symbol Size is ");
        pr_debug(entry->symbol_size());
        pr_debug("Dim is ");
        pr_debug(entry->dim());
        std::size_t start = entry->symbol_size() / sizeof(int);
        _now_func->PushInst<AssignInst>(dest, std::make_shared<IntVal>(0));
        for (std::size_t i = 0; i < entry->dim(); i++){
            start = start/entry->shape().at(i);
            auto tmp = dims->const_dims().at(i)->GenerateIR(*this);
            if(!tmp) assert("Fail to evaluate a dimension!");
            if(tmp->is_array ==1){
                auto dest2 = _now_func->AddSlot();
                _now_func->add_cur_offset(4);
                _now_func->PushDeclInst<DeclareVarInst>(dest2);
                _now_func->PushInst<AssignInst>(dest2, std::move(tmp));
                _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_TIMES, middle, std::move(dest2), std::make_shared<IntVal>(start));
            }
            else{
                _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_TIMES, middle, std::move(tmp), std::make_shared<IntVal>(start));
            } 
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_PLUS, dest, dest, middle);
        }
        assert(start == 1);
    }
    else{
        std::size_t offset = 0;
        pr_debug("Symbol Size is ");
        pr_debug(func_table_entry->second->symbol_size());
        pr_debug("Dim is ");
        pr_debug(func_table_entry->second->dim());
        std::size_t start = func_table_entry->second->symbol_size()/sizeof(int);
        //Dimension n , n-1 dimensions in the vector.
        _now_func->PushInst<AssignInst>(dest, std::make_shared<IntVal>(0));
        for (std::size_t i = 0; i < func_table_entry->second->dim()-1; i++){
            auto tmp = dims->const_dims().at(i)->GenerateIR(*this);
            if(!tmp) assert("Fail to evaluate a dimension!");
            if(tmp->is_array ==1){
                auto dest2 = _now_func->AddSlot();
                _now_func->add_cur_offset(4);
                _now_func->PushDeclInst<DeclareVarInst>(dest2);
                _now_func->PushInst<AssignInst>(dest2, std::move(tmp));
                _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_TIMES, middle, std::move(dest2), std::make_shared<IntVal>(start));
            }
            else{
                _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_TIMES, middle, std::move(tmp), std::make_shared<IntVal>(start));
            }
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_PLUS, dest, dest, middle);
            start = start/func_table_entry->second->shape().at(i);
        }
        assert(start == 1);
        auto tmp = dims->const_dims().at(func_table_entry->second->dim()-1)->GenerateIR(*this);
        if(!tmp) assert("Fail to evaluate a dimension!");
        if(tmp->is_array ==1){
            auto dest3 = _now_func->AddSlot();
            _now_func->add_cur_offset(4);
            _now_func->PushDeclInst<DeclareVarInst>(dest3);
            _now_func->PushInst<AssignInst>(dest3, std::move(tmp));
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_PLUS, dest, dest, std::move(dest3));
        }
        else{
            _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_PLUS, dest, dest, std::move(tmp));
        }
    }
    _now_func->PushInst<BinaryInst>(yy::parser::token::TOK_TIMES, dest, dest, std::make_shared<IntVal>(4));
    return std::make_shared<ArrayRefVal>(base, dest);
}

ValPtr IRGen::GenerateOn(const ReturnAST& ast){
    if (ast.expr()!= nullptr){
        auto expr = ast.expr()->GenerateIR(*this);
        if(!expr) return nullptr;
        if (expr->is_array == 1){
            auto dest = _now_func->AddSlot();
            _now_func->add_cur_offset(4);
            _now_func->PushDeclInst<DeclareVarInst>(dest);
            _now_func->PushInst<AssignInst>(dest, std::move(expr));
            _now_func->PushInst<ReturnInst>(std::move(dest));
        }
        else{
            _now_func->PushInst<ReturnInst>(std::move(expr));
        }
        
    }
    else{
        _now_func->PushInst<ReturnInst>(nullptr);
    }
    return nullptr;
}

ValPtr IRGen::GenerateOn(const FuncCallAST& ast){
    auto it = _funcs.find(ast.name());
    if (it == _funcs.end()){
        it = _lib_funcs.find(ast.name());
        if(it == _lib_funcs.end()) return LogError("Function Not Defined!");
    }
    ValPtrList args;
    if(ast.params()!=nullptr){
        auto param_list = std::dynamic_pointer_cast<FuncRParamsAST>(ast.params());
        if (param_list->const_exprs().size() != it->second->num_args()){
            return LogError("Argument Count Mismatch");
        }
        for (const auto &i: param_list->const_exprs()){
            auto arg = i->GenerateIR(*this);
            if (!arg) return nullptr;
            if (arg->is_array == 1){
                auto dest1 = _now_func->AddSlot();
                _now_func->add_cur_offset(4);
                _now_func->PushDeclInst<DeclareVarInst>(dest1);
                _now_func->PushInst<AssignInst>(dest1, std::move(arg));
                args.push_back(std::move(dest1));
            }
            else{
                args.push_back(std::move(arg));
            }
        }
    }
    else{
        if (0 != it->second->num_args()){
            return LogError("Argument Count Mismatch");
        }
    }
    
    //Some type type check can be carried out here.
    
    
    if(it->second->ret_type()==yy::parser::token::TOK_INT){
        auto dest = _now_func->AddSlot();
        _now_func->add_cur_offset(4);
        _now_func->PushDeclInst<DeclareVarInst>(dest);
        _now_func->PushInst<FuncCallInst>(dest, it->second, std::move(args));
        return dest;
    }
    if(it->second->ret_type()==yy::parser::token::TOK_VOID){
        _now_func->PushInst<VoidFuncCallInst>(it->second, std::move(args));
        return nullptr;
    }
    return LogError("Unknown Function Return Type");
}

ValPtr IRGen::GenerateOn(const ExpAST& ast){
    if (ast.expr() != std::make_shared<ExpAST>(nullptr)) ast.expr()->GenerateIR(*this);
    return nullptr;
}

ValPtr IRGen::GenerateOn(const IfAST& ast){
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Entering IfAST"<<std::endl;
    #endif
    auto cond = ast.cond()->GenerateIR(*this);
    if (!cond) return nullptr;
    auto false_branch = std::make_shared<LabelVal>();
    auto end_if = ast.else_then() ? std::make_shared<LabelVal>() : nullptr;
    // generate contional branch
    if (cond->is_array == 1){
        auto dest = _now_func->AddSlot();
        _now_func->add_cur_offset(4);
        _now_func->PushDeclInst<DeclareVarInst>(dest);
        _now_func->PushInst<AssignInst>(dest, std::move(cond));
        _now_func->PushInst<BranchInst>(false, std::move(dest), false_branch);
    }
    else{
        _now_func->PushInst<BranchInst>(false, std::move(cond), false_branch);
    }
    // generate the true branch
    ast.then()->GenerateIR(*this);
    if (ast.else_then()) {_now_func->PushInst<JumpInst>(end_if);pr_debug("Generating Label for else_then");}
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
    pr_debug("Entering WhileAST");
    auto judge_label = std::make_shared<LabelVal>();
    _now_func->PushInst<LabelInst>(judge_label);
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Generating judge_label"<<std::endl;
    #endif
    auto cond = ast.cond()->GenerateIR(*this);
    if (!cond) return nullptr;
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Generating condition"<<std::endl;
    #endif
    auto false_branch = std::make_shared<LabelVal>();
    if (cond->is_array == 1){
        auto dest = _now_func->AddSlot();
        _now_func->add_cur_offset(4);
        _now_func->PushDeclInst<DeclareVarInst>(dest);
        _now_func->PushInst<AssignInst>(dest, std::move(cond));
        _now_func->PushInst<BranchInst>(false, std::move(dest), false_branch);
    }
    else{
        _now_func->PushInst<BranchInst>(false, std::move(cond), false_branch);
    }
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Generating False Jump"<<std::endl;
    #endif
    auto loop_env = NewLoopEnv();
    _loop_labels->AddItem("judge_label", judge_label);
    _loop_labels->AddItem("false_branch", false_branch);
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Entering New Loop Env"<<std::endl;
        if(ast.stmt() == nullptr){
            std::cout<<"Null Pointer!"<<std::endl;
        }
    #endif
    ast.stmt()->GenerateIR(*this);
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Entering Block"<<std::endl;
    #endif
    _now_func->PushInst<JumpInst>(std::move(judge_label));
    _now_func->PushInst<LabelInst>(false_branch);
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Generating WhileAST"<<std::endl;
    #endif
    return nullptr;
}

ValPtr IRGen::GenerateOn(const CondAST& ast){
    //Continue jmp to current judge label
    //Break jmp to current false_branch
    //Have to store the current false_branch and judge label.
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Entering CondAST"<<std::endl;
    #endif
    switch (ast.cond_type())
    {
    case yy::parser::token::TOK_BREAK:{
        #ifdef __DEBUG_IRGEN__
            std::cout<<"Entering Break"<<std::endl;
        #endif
        auto false_branch = _loop_labels->GetItem("false_branch", false);
        if(!false_branch) {pr_debug("No False Branch"); return LogError("break statement not within a loop");}
        _now_func->PushInst<JumpInst>(false_branch);
        #ifdef __DEBUG_IRGEN__
            std::cout<<"Leaving Break"<<std::endl;
        #endif
        break;}
    case yy::parser::token::TOK_CONTINUE:{
        #ifdef __DEBUG_IRGEN__
            std::cout<<"Entering Continue"<<std::endl;
        #endif
        auto judge_label = _loop_labels->GetItem("judge_label", false);
        if(!judge_label) return LogError("continue statement not within a loop");
        _now_func->PushInst<JumpInst>(judge_label);
        #ifdef __DEBUG_IRGEN__
            std::cout<<"Leaving Continue"<<std::endl;
        #endif
        break;}
    default:
        return LogError("Undefined Branch Type");
    }
    return nullptr;
}

//Here if both the LVal and the Exp are Array Element,
//There is problem because Eeyore does not allow 

ValPtr IRGen::GenerateOn(const AssignAST& ast){
    pr_debug("Entering AssignAST");
    auto expr = ast.expr()->GenerateIR(*this);
    pr_debug("Finishing Evaluating the expr");
    if(!expr) return nullptr;
    auto slot = ast.lval()->GenerateIR(*this);
    pr_debug("Finishing Evaluating the LVal");
    if(!slot) return LogError("Symbol Undefined");
    if(ast.expr()->is_lval_array == 1 && ast.lval()->is_lval_array == 1){
        auto dest = _now_func->AddSlot();
        _now_func->add_cur_offset(4);
        _now_func->PushDeclInst<DeclareVarInst>(dest);
        _now_func->PushInst<AssignInst>(dest, std::move(expr));
        _now_func->PushInst<AssignInst>(std::move(slot), std::move(dest));
    }
    else{
        _now_func->PushInst<AssignInst>(std::move(slot), std::move(expr));
    }
    pr_debug("Leaving AssignAST");
    return nullptr;
}

//; OR {BlockItems} BlockItems should be in a new environment.
ValPtr IRGen::GenerateOn(const BlockAST& ast){
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Entering BlockAST"<<std::endl;
    #endif
    if (ast.blockitem() == nullptr) return nullptr;
    auto env = NewEnvironment();
    auto sym = NewSymTable();
    auto convars = NewConstVars();
    ast.blockitem()->GenerateIR(*this);
    if(_error_num) return LogError("There is Error in this block!");
    return nullptr;
}

//Decl|Stmt Decl|Stmt ... Decl|Stmt
//Have to think of a way to do all the declaration First.
//Add a new indicator to tree nodes.
ValPtr IRGen::GenerateOn(const BlockItemsAST& ast){
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Entering BlockItemAST"<<std::endl;
    #endif
    for (const auto &i : ast.const_items()){
        i->GenerateIR(*this);
        if(_error_num) return LogError("Error in this Declaration");
    }
    /*
    for (const auto &i : ast.const_items()){
        if(i->is_decl != 1){
            i->GenerateIR(*this);
            if(_error_num) return LogError("Error in this Statement");
        }
    }*/
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
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Entering FuncDefAST "<<ast.name()<<std::endl;
    #endif
    if(ast.params()!=nullptr){
        auto param_list = std::dynamic_pointer_cast<FuncFParamsAST>(ast.params());
        _now_func = std::make_shared<FunctionDef>(ast.name(),param_list->const_params().size(), ast.func_type());
    }
    else{
        _now_func = std::make_shared<FunctionDef>(ast.name(),0, ast.func_type());
    }
    
    if(!_funcs.insert({_now_func->func_name(), _now_func}).second){
        return LogError("Function has already beed defined!");
    }
    //Create a function table
    _func_table.insert(std::make_pair(ast.name(),std::unordered_map<std::string, FTEPtr>()));
    auto table = _func_table.find(ast.name());
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Initializing functable of "<<_now_func->func_name()<<std::endl;
    #endif
    //Insert the params to some function table
    auto env = NewEnvironment();
    auto sym = NewSymTable();
    auto convars = NewConstVars();
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Initializing Env of "<<_now_func->func_name()<<std::endl;
    #endif
    if(ast.params()!=nullptr){
        int p = 0;
        auto param_list = std::dynamic_pointer_cast<FuncFParamsAST>(ast.params());
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
    }
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Initializing Variables of "<<_now_func->func_name()<<std::endl;
    #endif
    ast.block()->GenerateIR(*this);
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Initializing Block Content of "<<_now_func->func_name()<<std::endl;
    #endif
    if(ast.func_type() == yy::parser::token_type::TOK_VOID){
        _now_func->PushInst<ReturnInst>(nullptr);
    }
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
ValPtr IRGen::process_value(std::shared_ptr<ConstInitValArrayAST> ast, std::vector<std::size_t>& shape, std::size_t dim, std::vector<int>& result){
    if(ast->init_vals() == nullptr){
        std::size_t total = 1;
        for (auto ii : shape){
            total *= ii;
        }
        for(std::size_t ii = 0; ii < total ; ii++){
            result.push_back(0);
        }
        return nullptr;
    }
    auto values = std::dynamic_pointer_cast<ConstInitValAST>(ast->init_vals());
    std::vector<std::size_t> position;
    //Start from all zeros;
    for(std::size_t i = 0; i < dim; i++){
        position.push_back(0);
    }
    
    for(const auto &i: values->const_exprs()){
        if(i->is_array == 1){
            // Is a ConstInitValArrayAST
            auto sub_ast = std::dynamic_pointer_cast<ConstInitValArrayAST>(i);
            auto back = dim - 1;
            while (position.at(back) == 0 && back >= 1){
                back -=1;
            }
            std::vector<std::size_t> sub_shape;
            for (std::size_t ii = back + 1; ii < dim ;ii++){
                sub_shape.push_back(shape.at(ii));
            }
            process_value(sub_ast, sub_shape, dim - 1 - back, result);
            position.at(back) += 1;
            while (position.at(back) == shape.at(back) && back >=1 )
            {
                position.at(back) = 0;
                position.at(back-1) += 1;
                back -= 1;
            }
        }
        else{
            auto expr = i->Eval(*this);
            if (!expr) return LogError("Can not evaluate the Init Value of a const Variable");
            result.push_back(*expr);
            position.at(dim-1) += 1;
            auto back = dim -1;
            while (position.at(back) == shape.at(back) && back >=1 )
            {
                position.at(back) = 0;
                position.at(back-1) += 1;
                back -= 1;
            }
            
        }
    }
    //Padding With Zeros.
    while (position.at(0)!=shape.at(0))
    {
        result.push_back(0);
        position.at(dim - 1) +=1;
        auto back = dim -1;
        while (position.at(back) == shape.at(back) && back >=1 )
        {
            position.at(back) = 0;
            position.at(back-1) += 1;
            back -= 1;
        }
    }
    
    return nullptr;
}
ValPtr IRGen::process_init_val(std::shared_ptr<InitValArrayAST> ast, std::vector<std::size_t>& shape, std::size_t dim, std::vector<int>& result){
    if(ast->init_vals() == nullptr){
        std::size_t total = 1;
        for (auto ii : shape){
            total *= ii;
        }
        for(std::size_t ii = 0; ii < total ; ii++){
            result.push_back(0);
        }
        return nullptr;
    }
    auto values = std::dynamic_pointer_cast<InitValAST>(ast->init_vals());
    std::vector<std::size_t> position;
    //Start from all zeros;
    for(std::size_t i = 0; i < dim; i++){
        position.push_back(0);
    }
    
    for(const auto &i: values->exprs()){
        if(i->is_array == 1){
            // Is a ConstInitValArrayAST
            auto sub_ast = std::dynamic_pointer_cast<InitValArrayAST>(i);
            auto back = dim - 1;
            while (position.at(back) == 0 && back >= 1){
                back -=1;
            }
            std::vector<std::size_t> sub_shape;
            for (std::size_t ii = back + 1; ii < dim ;ii++){
                sub_shape.push_back(shape.at(ii));
            }
            process_init_val(sub_ast, sub_shape, dim - 1 - back, result);
            position.at(back) += 1;
            while (position.at(back) == shape.at(back) && back >=1 )
            {
                position.at(back) = 0;
                position.at(back-1) += 1;
                back -= 1;
            }
        }
        else{
            auto expr = i->Eval(*this);
            if (!expr) return LogError("Can not evaluate the Init Value of a const Variable");
            result.push_back(*expr);
            position.at(dim-1) += 1;
            auto back = dim -1;
            while (position.at(back) == shape.at(back) && back >=1 )
            {
                position.at(back) = 0;
                position.at(back-1) += 1;
                back -= 1;
            }
            
        }
    }
    //Padding With Zeros.
    while (position.at(0)!=shape.at(0))
    {
        result.push_back(0);
        position.at(dim - 1) +=1;
        auto back = dim -1;
        while (position.at(back) == shape.at(back) && back >=1 )
        {
            position.at(back) = 0;
            position.at(back-1) += 1;
            back -= 1;
        }
    }
    
    return nullptr;
}
ValPtr IRGen::GenerateOn(const ConstDefAST& ast){
    if(ast.is_array_def() == 1){
        //2. Generate on Arrays
        //Evaluate expr or {expr, expr, {expr, expr},{expr}}
        //To-do
        //Create slot
        auto slot = _now_func->AddVarSlot(1);
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
        if (_now_func->func_name() != "00_GLOBAL") _now_func->add_cur_offset(ste->symbol_size());
        _now_func->PushDeclInst<DeclareArrInst>(slot, ste->symbol_size());
        _symbol_table->AddItem(ast.id(), ste);
        //Store the value
        std::vector<int> temp_const_values;
        //First have to check _const_init_value points to a single expression or 
        //ConstInitValArray
        if (ast.const_init_val()->is_array == 1){
            process_value(std::dynamic_pointer_cast<ConstInitValArrayAST>(ast.const_init_val()),ste->_shape,ste->_dim, temp_const_values);
            assert(temp_const_values.size() == ste->_symbol_size /4);

        }
        else{
            auto val = ast.const_init_val()->Eval(*this);
            if(!val) return LogError("Can not Evaluate the Initial Const Value!");
            for(size_t i = 0; i < ste->_symbol_size/4 ; i++){
                temp_const_values.push_back(*val);
            }
        }
        if(_const_vars->GetItem(ast.id())) return LogError("Const Array already been defined!");
        for(size_t i = 0; i < ste->_symbol_size ; i+=4){
            _now_func->PushInst<AssignInst>(std::make_shared<ArrayRefVal>(slot,std::make_shared<IntVal>(i)), std::make_shared<IntVal>(temp_const_values.at(i/4)));
        }
        _const_vars->AddItem(ast.id(), std::make_shared<std::vector<int> >(temp_const_values));
        return nullptr;
    }
    else{
        //1. Generate on Variables
        auto expr = ast.const_init_val()->Eval(*this);
        if (!expr) return LogError("Can not evaluate the Init Value of a const Variable");
        //Create slot
        auto slot = _now_func->AddVarSlot(0);
        if (_now_func->func_name() != "00_GLOBAL") _now_func->add_cur_offset(4);
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
        if(_const_vars->GetItem(ast.id())) return LogError("Const Variable already been defined!");
        pr_debug("Const Value is ");
        pr_debug(*expr);
        pr_debug("Const ID is ")
        pr_debug(ast.id());
        std::vector<int> tmp = {*expr};
        _const_vars->AddItem(ast.id(), std::make_shared<std::vector<int> >(tmp));
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
ValPtr IRGen::process_slot(std::shared_ptr<InitValArrayAST> ast, std::vector<std::size_t>& shape, std::size_t dim, ValPtrList& result){
    if(ast->init_vals() == nullptr){
        std::size_t total = 1;
        for (auto ii : shape){
            total *= ii;
        }
        for(std::size_t ii = 0; ii < total ; ii++){
            result.push_back(std::make_shared<IntVal>(0));
        }
        return nullptr;
    }
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Entering process_slot"<<std::endl;
    #endif
    auto values = std::dynamic_pointer_cast<InitValAST>(ast->init_vals());
    std::vector<std::size_t> position;
    //Start from all zeros;
    for(std::size_t i = 0; i < dim; i++){
        position.push_back(0);
    }
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing initializing position"<<std::endl;
        std::cout<<"The number of exprs in the first level is "<<values->exprs().size()<<std::endl;
    #endif
    for(const auto &i: values->exprs()){
        if(i->is_array == 1){
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Entering nested bracket"<<std::endl;
            #endif
            // Is a ConstInitValArrayAST
            auto sub_ast = std::dynamic_pointer_cast<InitValArrayAST>(i);
            auto back = dim - 1;
            while (position.at(back) == 0 && back >= 1){
                back -=1;
            }
            std::vector<std::size_t> sub_shape;
            for (std::size_t ii = back + 1; ii < dim ;ii++){
                sub_shape.push_back(shape.at(ii));
            }
            process_slot(sub_ast, sub_shape, dim - 1 - back, result);
            position.at(back) += 1;
            while (position.at(back) == shape.at(back) && back >=1 )
            {
                position.at(back) = 0;
                position.at(back-1) += 1;
                back -= 1;
            }
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Leaving nested bracket"<<std::endl;
            #endif
        }
        else{
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Entering expr"<<std::endl;
            #endif
            auto expr = i->GenerateIR(*this);
            if (!expr) return LogError("Can not evaluate the Init Value of a const Variable");
            result.push_back(expr);
            position.at(dim-1) += 1;
            auto back = dim -1;
            while (position.at(back) == shape.at(back) && back >=1 )
            {
                position.at(back) = 0;
                position.at(back-1) += 1;
                back -= 1;
            }
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Leaving expr"<<std::endl;
            #endif
        }
    }
    //Padding With Zeros.
    while (position.at(0)!=shape.at(0))
    {
        result.push_back(std::make_shared<IntVal>(0));
        position.at(dim - 1) +=1;
        auto back = dim -1;
        while (position.at(back) == shape.at(back) && back >=1 )
        {
            position.at(back) = 0;
            position.at(back-1) += 1;
            back -= 1;
        }
    }
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing padding"<<std::endl;
    #endif
    return nullptr;
}

ValPtr IRGen::GenerateOn(const VarDefAST& ast){
    if(ast.is_array_def() == 1){
        if (ast.init_val() == nullptr){
            pr_debug("Entering VarDef of Array with no init Value");
            //2. Generate on Arrays
            //Evaluate expr or {expr, expr, {expr, expr},{expr}}
            //To-do
            //Create slot
            auto slot = _now_func->AddVarSlot(1);
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
            auto ste = std::make_shared<SymbolTableEntry>(yy::parser::token::TOK_INT, 0, 1);
            ste->_dim = dim_list.size();
            for(const auto &i: dim_list){
                pr_debug("Each Dimension is ")
                pr_debug(*i);
                ste->_symbol_size *= (*i);
                ste->_shape.push_back(*i);
            }
            //Insert Array Declaration Instruction
            if (_now_func->func_name() != "00_GLOBAL") _now_func->add_cur_offset(ste->symbol_size());
            _now_func->PushDeclInst<DeclareArrInst>(slot, ste->symbol_size());
            _symbol_table->AddItem(ast.id(), ste);
            return nullptr;
        }
        else{
            //2. Generate on Arrays
            //Evaluate expr or {expr, expr, {expr, expr},{expr}}
            //To-do
            //Create slot
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Entering the most complex VarDefAST "<<ast.id()<<std::endl;
            #endif
            auto slot = _now_func->AddVarSlot(1);
            //Add slot to _vars
            if (!_vars->AddItem(ast.id(), slot)) {
                return LogError("Array has already been defined");
            }
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Finishing adding slot in the most complex VarDefAST"<<std::endl;
            #endif
            //Evaluate each dimension
            std::vector<std::optional<int> > dim_list;
            auto dim_exprs = std::dynamic_pointer_cast<DimensionAST>(ast.const_exprs());
            for(const auto &i : dim_exprs->const_dims()){
                auto expr = i->Eval(*this);
                if(!expr) return LogError("Can not Evaluate the Dimension of the const Array");
                dim_list.push_back(std::move(expr));
            }
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Finishing evaluating each dimension in the most complex VarDefAST"<<std::endl;
            #endif
            //Create Entry in the Symbol Table
            auto ste = std::make_shared<SymbolTableEntry>(yy::parser::token::TOK_INT, 0, 1);
            ste->_dim = dim_list.size();
            for(const auto &i: dim_list){
                ste->_symbol_size *= (*i);
                ste->_shape.push_back(*i);
            }
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Finishing creating entry in the most complex VarDefAST"<<std::endl;
            #endif
            //Insert Array Declaration Instruction
            if (_now_func->func_name() != "00_GLOBAL") _now_func->add_cur_offset(ste->symbol_size());
            _now_func->PushDeclInst<DeclareArrInst>(slot, ste->symbol_size());
            _symbol_table->AddItem(ast.id(), ste);
            #ifdef __DEBUG_IRGEN__
                std::cout<<"Finishing inserting decl insts in the most complex VarDefAST"<<std::endl;
            #endif
            if (_now_func->func_name() == "00_GLOBAL"){
                std::vector<int> temp_const_values;
                if (ast.init_val()->is_array == 1){
                    process_init_val(std::dynamic_pointer_cast<InitValArrayAST>(ast.init_val()),ste->_shape,ste->_dim, temp_const_values);
                    assert(temp_const_values.size() == ste->_symbol_size /4);
                }
                else{
                    auto val = ast.init_val()->Eval(*this);
                    if(!val) return LogError("Can not Evaluate the Initial Const Value!");
                    for(size_t i = 0; i < ste->_symbol_size/4 ; i++){
                        temp_const_values.push_back(*val);
                    }
                }
                for(size_t i = 0; i < ste->_symbol_size ; i+=4){
                    _now_func->PushInst<AssignInst>(std::make_shared<ArrayRefVal>(slot,std::make_shared<IntVal>(i)), std::make_shared<IntVal>(temp_const_values.at(i/4)));
                }
            }
            else{
                //Store the value
                ValPtrList temp_values;
                //First have to check _const_init_value points to a single expression or 
                //ConstInitValArray
                if (ast.init_val()->is_array == 1){
                    process_slot(std::dynamic_pointer_cast<InitValArrayAST>(ast.init_val()),ste->_shape,ste->_dim, temp_values);
                    assert(temp_values.size() == ste->_symbol_size /4);
                }
                else{
                    auto val = ast.init_val()->GenerateIR(*this);
                    if(!val) return LogError("Can not Generate Slot for the Initial Value!");
                    for(size_t i = 0; i < ste->_symbol_size/4 ; i++){
                        temp_values.push_back(val);
                    }
                }
                #ifdef __DEBUG_IRGEN__
                    std::cout<<"Finishing generating slots insts in the most complex VarDefAST"<<std::endl;
                #endif
                for(size_t i = 0; i < ste->_symbol_size ; i+=4){
                    if(temp_values.at(i/4)->is_array == 1)
                        {
                            auto dest1 = _now_func->AddSlot();
                            _now_func->add_cur_offset(4);
                            _now_func->PushDeclInst<DeclareVarInst>(dest1);
                            _now_func->PushInst<AssignInst>(dest1, temp_values.at(i/4));
                            _now_func->PushInst<AssignInst>(std::make_shared<ArrayRefVal>(slot,std::make_shared<IntVal>(i)),std::move(dest1));
                        }
                    else
                        {_now_func->PushInst<AssignInst>(std::make_shared<ArrayRefVal>(slot,std::make_shared<IntVal>(i)), temp_values.at(i/4));}
                }
                #ifdef __DEBUG_IRGEN__
                    std::cout<<"Finishing inserting assign insts in the most complex VarDefAST"<<std::endl;
                #endif
            }
            return nullptr;
        }
    }
    else{
        //1. Generate on Variables
        if (ast.init_val() == nullptr){
            //Create slot
            auto slot = _now_func->AddVarSlot(0);
            if (_now_func->func_name() != "00_GLOBAL") _now_func->add_cur_offset(4);
            //Add slot to _vars
            if (!_vars->AddItem(ast.id(), slot)) {
                return LogError("symbol has already been defined");
            }
            //Insert Variable Declaration Instruction
            _now_func->PushDeclInst<DeclareVarInst>(slot);
            //Create Entry in the Symbol Table
            auto ste = std::make_shared<SymbolTableEntry>(yy::parser::token::TOK_INT,0,0);
            _symbol_table->AddItem(ast.id(), std::move(ste));
            return nullptr;
        }
        else{
            auto expr = _now_func->func_name() == "00_GLOBAL" ? (std::make_shared<IntVal>(*(ast.init_val()->Eval(*this)))):(ast.init_val()->GenerateIR(*this));
            if (!expr) return LogError("Can not Geneate the Init Value of a Variable");
            //Create slot
            auto slot = _now_func->AddVarSlot(0);
            if (_now_func->func_name() != "00_GLOBAL") _now_func->add_cur_offset(4);
            //Add slot to _vars
            if (!_vars->AddItem(ast.id(), slot)) {
                return LogError("symbol has already been defined");
            }
            //Insert Variable Declaration Instruction
            _now_func->PushDeclInst<DeclareVarInst>(slot);
            //Create Entry in the Symbol Table
            auto ste = std::make_shared<SymbolTableEntry>(yy::parser::token::TOK_INT,0,0);
            _symbol_table->AddItem(ast.id(), std::move(ste));
            //Generate Assign Expression;
            if(expr->is_array == 1)
                {
                    auto dest1 = _now_func->AddSlot();
                    _now_func->add_cur_offset(4);
                    _now_func->PushDeclInst<DeclareVarInst>(dest1);
                    _now_func->PushInst<AssignInst>(dest1, std::move(expr));
                    _now_func->PushInst<AssignInst>(std::move(slot),std::move(dest1));
                }
            else
                {_now_func->PushInst<AssignInst>(std::move(slot), std::move(expr));}
            return nullptr;
        }
    }

}
//Todo: Finish CompUnitAST to initialize the global environment.
//Todo: How to deal with Global?
ValPtr IRGen::GenerateOn(const CompUnitAST& ast){
    _now_func = std::make_shared<FunctionDef>("00_GLOBAL",0, yy::parser::token_type::TOK_VOID);
    if(!_funcs.insert({_now_func->func_name(), _now_func}).second){
        return LogError("GLOBAL Environment has already been defined!");
    }
    //Create a function table
    _func_table.insert(std::make_pair("00_GLOBAL",std::unordered_map<std::string, FTEPtr>()));
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Initializing GLOBAL"<<std::endl;
    #endif
    auto env = NewEnvironment();
    auto sym = NewSymTable();
    auto convars = NewConstVars();
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Initializing New Env"<<std::endl;
    #endif
    for (const auto &i : ast.units()){
        if(i->is_decl == 1){
            i->GenerateIR(*this);
            if(_error_num) return LogError("Error in this Declaration");
        }
    }
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Declarations"<<std::endl;
    #endif
    for (const auto &i : ast.units()){
        if(i->is_decl != 1){
            i->GenerateIR(*this);
            if(_error_num) return LogError("Error in this Function Definition");
        }
    }
    #ifdef __DEBUG_IRGEN__
        std::cout<<"Finishing Function Defs"<<std::endl;
    #endif
    return nullptr;
}

void IRGen::Dump_Eeyore(std::ostream &os) const {
    auto glob = _funcs.find("00_GLOBAL");
    glob->second->Dump_Eeyore_GLOB(os);
    for (const auto &it : _funcs) {
        if (it.first != "00_GLOBAL")
        {
            it.second->Dump_Eeyore(os);
        }
    }
}

void IRGen::Dump_Tigger(std::ostream &os) {
    auto glob = _funcs.find("00_GLOBAL");
    glob->second->Dump_Tigger_GLOB(os, global_assign_Tigger);
    for (const auto &it : _funcs) {
        if (it.first != "00_GLOBAL")
        {
            it.second->Dump_Tigger(os, global_assign_Tigger);
        }
    }
}
void IRGen::Dump_RISC_V(std::ostream &os) {
    auto glob = _funcs.find("00_GLOBAL");
    glob->second->Dump_RISC_V_GLOB(os, global_assign_RISC_V);
    for (const auto &it : _funcs) {
        if (it.first != "00_GLOBAL")
        {
            it.second->Dump_RISC_V(os, global_assign_RISC_V);
        }
    }
}
//Todo: 2 Bugs left
//Todo: 2. In evaluating ArrayAST, the function table entry should be looked up first.
//Todo: 2. Change the sequence of searching
