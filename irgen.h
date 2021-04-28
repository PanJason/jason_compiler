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
#include "ir.h"
#include "global.h"
#include "guard.h"
#include "nested.h"

class IRGen{
    public:
    IRGen() : _error_num(0){
        //register the lib functions
        //To do
    }

    //dump eeyore representations
    void Dump_Eeyore() const;

    //vistor methods here
    ValPtr GenerateOn(const CompUnitAST& ast);
    ValPtr GenerateOn(const ConstDeclAST& ast);
    ValPtr GenerateOn(const ConstDefAST& ast);
    ValPtr GenerateOn(const ConstDefListAST& ast);
    ValPtr GenerateOn(const ConstInitValArrayAST& ast);
    ValPtr GenerateOn(const ConstInitValAST& ast);
    ValPtr GenerateOn(const VarDeclAST& ast);
    ValPtr GenerateOn(const VarDefListAST& ast);
    ValPtr GenerateOn(const VarDefAST& ast);
    ValPtr GenerateOn(const InitValArrayAST& ast);
    ValPtr GenerateOn(const InitValAST& ast);
    ValPtr GenerateOn(const FuncDefAST& ast);
    ValPtr GenerateOn(const FuncFParamsAST& ast);
    ValPtr GenerateOn(const FuncFParamVarAST& ast);
    ValPtr GenerateOn(const FuncFParamArrayAST& ast);
    ValPtr GenerateOn(const DimensionAST& ast);
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
    ValPtr GenerateOn(const FuncRParamsAST& ast);
    ValPtr GenerateOn(const IntAST& ast);
    ValPtr GenerateOn(const IdAST& ast);
    ValPtr GenerateOn(const ArrayAST& ast);

    std::optional<int> EvalOn(const IdAST& ast);
    std::optional<int> EvalOn(const IntAST& ast);
    std::optional<int> EvalOn(const ArrayAST& ast);
    std::optional<int> EvalOn(const UnaryAST& ast);
    std::optional<int> EvalOn(const BinaryAST& ast);

    std::size_t error_num() const {return _error_num;}
private:
    std::size_t _error_num;
    ValPtr LogError(std::string_view message);
    xstl::Guard NewEnvironment();
    xstl::Guard NewLoopEnv();
    //The symbol Table inside a block;
    xstl::Guard NewSymTable();
    
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
    std::unordered_map<std::string, std::vector<int> > _const_vars;
};
#endif
