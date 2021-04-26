#include "irgen.h"
#include <iostream>

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