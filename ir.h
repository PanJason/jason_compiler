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

// Base class of all instructions
class InstBase{
public:
    virtual ~InstBase() = default;
    //dump intermediate representation of Eeyore
    virtual void Dump_Eeyore() const;
};
using InstPtr = std::shared_ptr<InstBase>;
using InstPtrList = std::vector<InstPtr>;

// Base class of all values
class ValueBase {
public:
    virtual ~ValueBase() = default;
    virtual void Dump_Eeyore() const = 0;
};
using ValPtr = std::shared_ptr<ValueBase>;
using ValPtrList = std::vector<ValPtr>;

class FunctionDef{
public:

const std::string &func_name() const {return _func_name;}
std::size_t num_args() const {return _num_args;}

private:
std::string _func_name;
std::size_t _num_args;
InstPtrList _insts;
};
using FuncDefPtr = std::shared_ptr<FunctionDef>;

#endif