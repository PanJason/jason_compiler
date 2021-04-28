/****************************************************/
/*File: jason.l                                     */
/*Lexical Analysis for Jason Compiler               */
/*Yueyang (Jason) Pan                               */
/****************************************************/

%{
    #include "global.h"
    #include "source.tab.hpp"
    #include "driver.h"
    #include <algorithm>
    #include <stdlib.h>
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
%}
%option debug noinput
/*
%{
    yy::parser::symbol_type
    make_OCT_NUM(const std::string &s, const yy::parser::location_type& loc);
    yy::parser::symbol_type
    make_DEC_NUM(const std::string &s, const yy::parser::location_type& loc);
    yy::parser::symbol_type
    make_HEX_NUM(const std::string &s, const yy::parser::location_type& loc);
%}*/
dec_digit       [0-9]
oct_digit       [0-7]
hex_digit       [0-9a-fA-F]
nonzero_digit   [1-9]
oct_num         0{oct_digit}*
hex_num         0[xX]{hex_digit}+
dec_num         {nonzero_digit}{dec_digit}*
identifier_nondigit [a-zA-Z_]
identifier_all  [a-zA-Z0-9_]
identifier      {identifier_nondigit}{identifier_all}*
whitespace      [ \t\r]+
newline         \n
%{
    #define YY_USER_ACTION loc.columns (yyleng);    
%}

%%
%{
    yy::location& loc = drv.location;
    loc.step ();
%}


"if"            {return yy::parser::make_IF(loc);}
"then"          {return yy::parser::make_THEN(loc);}
"else"          {return yy::parser::make_ELSE(loc);}
"while"         {return yy::parser::make_WHILE(loc);}
"break"         {return yy::parser::make_BREAK(loc);}
"continue"      {return yy::parser::make_CONTINUE(loc);}
"return"        {return yy::parser::make_RETURN(loc);}
"const"         {return yy::parser::make_CONST(loc);}
"int"           {return yy::parser::make_INT(loc);}
"void"          {return yy::parser::make_VOID(loc);}
"="             {return yy::parser::make_ASSIGN(loc);}
";"             {return yy::parser::make_SEMI(loc);}
","             {return yy::parser::make_COMMA(loc);}
"{"             {return yy::parser::make_LLPAREN(loc);}
"}"             {return yy::parser::make_LRPAREN(loc);}
"["             {return yy::parser::make_MLPAREN(loc);}
"]"             {return yy::parser::make_MRPAREN(loc);}
"("             {return yy::parser::make_SLPAREN(loc);}
")"             {return yy::parser::make_SRPAREN(loc);}
"!"             {return yy::parser::make_NOT(loc);}
"=="            {return yy::parser::make_EQ(loc);}
"!="            {return yy::parser::make_NEQ(loc);}
"<"             {return yy::parser::make_LT(loc);}
">"             {return yy::parser::make_GT(loc);}
"<="            {return yy::parser::make_LTE(loc);}
">="            {return yy::parser::make_GTE(loc);}
"+"             {return yy::parser::make_PLUS(loc);}
"-"             {return yy::parser::make_MINUS(loc);}
"*"             {return yy::parser::make_TIMES(loc);}
"/"             {return yy::parser::make_OVER(loc);}
"%"             {return yy::parser::make_MOD(loc);}
"&&"            {return yy::parser::make_AND(loc);}
"||"            {return yy::parser::make_OR(loc);}
{whitespace}    { loc.step (); }
{newline}       { loc.lines (yyleng); loc.step (); }
{oct_num}       {
    errno = 0;
    long n = strtol(yytext, NULL, 8);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: "
                                    + std::string(yytext));
  return yy::parser::make_NUMBER (n, loc);

}
{dec_num}       {
    errno = 0;
    long n = strtol(yytext, NULL, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: "
                                    + std::string(yytext));
  return yy::parser::make_NUMBER (n, loc);
}
{hex_num}       {
    errno = 0;
    long n = strtol(yytext, NULL, 16);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: "
                                    + std::string(yytext));
  return yy::parser::make_NUMBER (n, loc);
}
{identifier}    {
    return yy::parser::make_IDENTIFIER (yytext, loc);
}
"//"            {char c;
                do { 
                    c=input();
                    if (c == EOF) return yy:parser::make_END(loc);
                    if (c == '\n') loc.lines(yyleng);
                } while (c != '\n');
                loc.step();
                }
"/*"            {char c; bool outside = 0;
                do {
                    c=input();
                    if (c == EOF) return yy:parser::make_END(loc);
                    if (c == '\n') loc.lines(yyleng);
                    while (c == '*'){ 
                        c = input();

                        if (c == EOF) return yy:parser::make_END(loc);
                        if (c == '\n') loc.lines(yyleng);
                        if (c == '/') { outside = 1; break;}
                    }
                } while ( c!= EOF && !outside);
                loc.step();
                }
.               {
     throw yy::parser::syntax_error
               (loc, "invalid character: " + std::string(yytext));
}
<<EOF>>     return yy::parser::make_END (loc);
%%

void
driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror(errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void
driver::scan_end ()
{
  fclose (yyin);
}
