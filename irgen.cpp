#include "irgen.h"
#include <iostream>

ValPtr IRGen::LogError(std::string_view message){
    std::cerr<<"Error From IRGen (Jason Compiler): "<< message << std::endl;
    _error_num++;
    return nullptr;
}

xstl::Guard IRGen::NewEnvironment(){
    
}