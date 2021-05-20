/****************************************************/
/*File: driver.cpp                                  */
/*The definition of all actions by driver           */ 
/*Exacute all the actions                           */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#include "driver.h"
#include "source.tab.hpp"

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
  yy::parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse();
  scan_end ();
  root->GenerateIR(irgen);
  if (irgen.error_num()) return 1;
  return 0;
}

int driver::Dump_Eeyore(std::ostream &os){
  irgen.Dump_Eeyore(os);
  return 0;
}
