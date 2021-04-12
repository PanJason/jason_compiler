/****************************************************/
/*File: jason.l                                     */
/*Lexical Analysis for Jason Compiler               */
/*Yueyang (Jason) Pan                               */
/****************************************************/

%{
    #include "global.hpp"
%}
dec_digit       [0-9]
oct_digit       [0-7]
hex_digit       [0-9a-fA-F]
nonzero_digit   [1-9]
oct_num         0{oct_digit}*
hex_num         0x{hex_digit}+
dec_num         {nonzero_digit}{dec_digit}*
identifier_nondigit [a-zA-Z_]
identifier_all  [a-zA-Z0-9_]
identifier      {identifier_nondigit}{identifier_all}*
whitespace      [ \t]+
newline         \n


%%
"if"            {return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"while"         {return WHILE;}
"break"         {return BREAK;}
"continue"      {return CONTINUE;}
"return"        {return RETURN;}
"const"         {return CONST;}
"int"           {return INT;}
"void"          {return VOID;}
"="             {return ASSIGN;}
";"             {return SEMI;}
","             {return COMMA;}
"{"             {return LLPAREN;}
"}"             {return LRPAREN;}
"["             {return MLPAREN;}
"]"             {return MRPAREN;}
"("             {return SLPAREN;}
")"             {return SRPAREN;}
"!"             {return NOT;}
"=="            {return EQ;}
"!="            {return NEQ;}
"<"             {return LT;}
">"             {return GT;}
"<="            {return LTE;}
">="            {return GTE;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"%"             {return MOD;}
"&&"            {return AND;}
"||"            {return OR;}
{whitespace}    { /*Do Nothing*/ }
{newline}       { lineno++; }
{oct_num}       {return OCT_NUM;}
{dec_num}       {return DEC_NUM;}
{hex_num}       {return HEX_NUM;}
{identifier}    {return ID;}
"//"            {char c;
                do { 
                    c=input(); 
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                } while (c != '\n');
                }
"/*"            {char c; bool outside = 0;
                do {
                    c=input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                    while (c == '*'){ 
                        c = input();
                        if (c == EOF) break;
                        if (c == '\n') lineno++;
                        if (c == '/') { outside = 1; break;}
                    }
                } while ( c!= EOF && !outside);
                }
.               {return ERROR;}

%%