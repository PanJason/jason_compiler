#ifndef __DRIVER_H
#define __DRIVER_H
#include <string>
#include <map>
#include "source.tab.hpp"
#include "global.h" 

// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yy::parser::symbol_type yylex (driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of Calc++.
class driver
{
public:
  driver ();

  std::map<std::string, int> variables;

  int result;
  ASTPtr root;

  int parse (const std::string& f);
  std::string file;
  bool trace_parsing;
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
  yy::location location;
};
#endif 