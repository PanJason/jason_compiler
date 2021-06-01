/****************************************************/
/*File: driver.h                                    */
/*Driver Class for the compiller                    */
/*This driver classs will contain all information & */ 
/*Exacute all the actions                           */
/*Yueyang (Jason) Pan                               */
/****************************************************/
#ifndef __DRIVER_H
#define __DRIVER_H
#include <string>
#include <map>
#include "source.tab.hpp"
#include "global.h" 
#include "irgen.h"

// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yy::parser::symbol_type yylex (driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing
class driver
{
public:
  driver();

  std::map<std::string, int> variables;

  int result;
  ASTPtr root;
  IRGen irgen;

  int parse (const std::string& f);
  int compile (const std::string& f);
  int Dump_Eeyore(std::ostream &os);
  int Dump_Tigger(std::ostream &os);
  int Dump_RISC_V(std::ostream &os);
  std::string file;
  bool trace_parsing;
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
  yy::location location;
};
#endif 