/****************************************************/
/*File: irgen.h                                     */
/*The class of Intermediate Representation Generator*/
/*for the jason compiller                           */
/*This genrator classs will evaluate all nodes and  */ 
/*generate the Intermedia Representation in Eeyore  */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#ifndef __IRGEN_H
#define __IRGEN_H
#include <memory>
#include "ir.h"
#include "global.h"
#include "guard.h"
#include "nested.h"
#include "source.tab.hpp"
using ConVarPTR = std::shared_ptr<std::vector<int> >;
class IRGen{
    public:
    IRGen() : _error_num(0){
        //register the lib functions
        //To do
        //getint
        _lib_funcs.insert({"getint",std::make_shared<FunctionDef>("getint", 0, yy::parser::token_type::TOK_INT)});
        //getch
        _lib_funcs.insert({"getch",std::make_shared<FunctionDef>("getch", 0, yy::parser::token_type::TOK_INT)});
        //getarray
        _lib_funcs.insert({"getarray",std::make_shared<FunctionDef>("getarray", 1, yy::parser::token_type::TOK_INT)});
        //putint
        _lib_funcs.insert({"putint",std::make_shared<FunctionDef>("putint", 1, yy::parser::token_type::TOK_VOID)});
        //putchar
        _lib_funcs.insert({"putch",std::make_shared<FunctionDef>("putch", 1, yy::parser::token_type::TOK_VOID)});
        //putarray
        _lib_funcs.insert({"putarray",std::make_shared<FunctionDef>("putarray", 2, yy::parser::token_type::TOK_VOID)});
        //starttime
        _lib_funcs.insert({"starttime",std::make_shared<FunctionDef>("starttime", 0, yy::parser::token_type::TOK_VOID)});
        //stoptime
        _lib_funcs.insert({"stoptime",std::make_shared<FunctionDef>("stoptime", 0, yy::parser::token_type::TOK_VOID)});
    }

    //dump eeyore representations
    void Dump_Eeyore(std::ostream &os) const;

    //vistor methods here
    ValPtr GenerateOn(const CompUnitAST& ast);
    ValPtr GenerateOn(const ConstDeclAST& ast);
    ValPtr GenerateOn(const ConstDefAST& ast);
    ValPtr GenerateOn(const ConstDefListAST& ast);
    //ValPtr GenerateOn(const ConstInitValArrayAST& ast);
    //ValPtr GenerateOn(const ConstInitValAST& ast);
    ValPtr GenerateOn(const VarDeclAST& ast);
    ValPtr GenerateOn(const VarDefListAST& ast);
    ValPtr GenerateOn(const VarDefAST& ast);
    //ValPtr GenerateOn(const InitValArrayAST& ast);
    //ValPtr GenerateOn(const InitValAST& ast);
    ValPtr GenerateOn(const FuncDefAST& ast);
    //ValPtr GenerateOn(const FuncFParamsAST& ast);
    //ValPtr GenerateOn(const FuncFParamVarAST& ast);
    //ValPtr GenerateOn(const FuncFParamArrayAST& ast);
    //ValPtr GenerateOn(const DimensionAST& ast);
    ValPtr GenerateOn(const BlockAST& ast);
    ValPtr GenerateOn(const BlockItemsAST& ast);
    ValPtr GenerateOn(const AssignAST& ast);
    ValPtr GenerateOn(const ExpAST& ast);
    ValPtr GenerateOn(const IfAST& ast);
    ValPtr GenerateOn(const WhileAST& ast);
    ValPtr GenerateOn(const CondAST& ast);
    ValPtr GenerateOn(const ReturnAST& ast);
    ValPtr GenerateOn(const BinaryAST& ast);
    ValPtr GenerateOn(const UnaryAST& ast);
    ValPtr GenerateOn(const FuncCallAST& ast);
    //ValPtr GenerateOn(const FuncRParamsAST& ast);
    ValPtr GenerateOn(const IntAST& ast);
    ValPtr GenerateOn(const IdAST& ast);
    ValPtr GenerateOn(const ArrayAST& ast);

    std::optional<int> EvalOn(const IdAST& ast);
    std::optional<int> EvalOn(const IntAST& ast);
    std::optional<int> EvalOn(const ArrayAST& ast);
    std::optional<int> EvalOn(const UnaryAST& ast);
    std::optional<int> EvalOn(const BinaryAST& ast);

    ValPtr process_value(std::shared_ptr<ConstInitValArrayAST> ast, std::vector<std::size_t>& shape, std::size_t dim, std::vector<int>& result);
    ValPtr process_slot(std::shared_ptr<InitValArrayAST> ast, std::vector<std::size_t>& shape, std::size_t dim, ValPtrList& result);
    ValPtr process_init_val(std::shared_ptr<InitValArrayAST> ast, std::vector<std::size_t>& shape, std::size_t dim, std::vector<int>& result);
    std::size_t error_num() const {return _error_num;}
private:
    std::size_t _error_num;
    ValPtr LogError(std::string_view message);
    xstl::Guard NewEnvironment();
    xstl::Guard NewLoopEnv();
    //The symbol Table inside a block;
    xstl::Guard NewSymTable();

    xstl::Guard NewConstVars();
    
    //Continuously insert labesl into _now_func, which could be later translated easilly.
    FuncDefPtr _now_func;
    std::unordered_map<std::string_view, FuncDefPtr> _funcs;
    std::unordered_map<std::string_view, FuncDefPtr> _lib_funcs;
    xstl::NestedMapPtr<std::string, ValPtr> _vars;
    xstl::NestedMapPtr<std::string, ValPtr> _loop_labels;

    //Add a new symbol table.
    //This should also be nested!
    xstl::NestedMapPtr<std::string, STEPtr> _symbol_table;
    //The function table don't have to be nested because we don't have nested functions
    std::unordered_map<std::string, std::unordered_map<std::string, FTEPtr> > _func_table;

    //This map is used to store the values of const variables and arrays.
    xstl::NestedMapPtr<std::string, ConVarPTR > _const_vars;
};
#endif
