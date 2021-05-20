/****************************************************/
/*File: driver.cpp                                  */
/*The definition of all actions by driver           */ 
/*Exacute all the actions                           */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#include "driver.h"
#include "source.tab.hpp"
#define __DEBUG_DRIVER__

driver::driver (): trace_parsing (false), trace_scanning (false), irgen()
{}

int driver::parse (const std::string &f)
{
  file = f;
  location.initialize (&file);
  scan_begin ();
  yy::parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}

int driver::compile (const std::string &f){
  file = f;
  location.initialize(&file);
  scan_begin();
  #ifdef __DEBUG_DRIVER__
    std::cout<<file<<std::endl;
  #endif
  yy::parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse();
  scan_end ();
  #ifdef __DEBUG_DRIVER__
    std::cout<<"Parse Finished!"<<std::endl;
    auto tmp = std::dynamic_pointer_cast<CompUnitAST>(root);
    std::cout<<tmp->units().size()<<std::endl;
  #endif
  root->GenerateIR(irgen);
  #ifdef __DEBUG_DRIVER__
    std::cout<<"IR Generated!"<<std::endl;
  #endif
  if (irgen.error_num()) return 1;
  return 0;
}

int driver::Dump_Eeyore(std::ostream &os){
  irgen.Dump_Eeyore(os);
  return 0;
}
