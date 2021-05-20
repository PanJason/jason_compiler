// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "source.tab.hpp"


// Unqualified %code blocks.
#line 29 "source.y"

    #include "driver.h"
    #define DEBUG

#line 50 "source.tab.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 141 "source.tab.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 42: // program
      case 43: // CompUnit
      case 44: // Decl
      case 45: // ConstDecl
      case 46: // ConstDefList
      case 47: // ConstDef
      case 48: // Dimension
      case 49: // ConstInitVal
      case 50: // ConstInitValArray
      case 52: // ConstInitValList
      case 53: // VarDecl
      case 54: // VarDefList
      case 55: // VarDef
      case 56: // InitVal
      case 57: // InitValArray
      case 58: // InitValList
      case 59: // FuncDef
      case 60: // FuncFParams
      case 61: // FuncFParam
      case 62: // FuncFParamVar
      case 63: // FuncFParamArray
      case 64: // Block
      case 65: // BlockItems
      case 66: // BlockItem
      case 67: // Stmt
      case 68: // Assign_stmt
      case 69: // Exp_stmt
      case 70: // If_stmt
      case 71: // While_stmt
      case 72: // Cond_stmt
      case 73: // Return_stmt
      case 74: // Exp
      case 75: // Cond
      case 76: // LVal
      case 77: // PrimaryExp
      case 78: // UnaryExp
      case 79: // FuncCallExp
      case 80: // FuncRParams
      case 81: // MulExp
      case 82: // AddExp
      case 83: // RelExp
      case 84: // EqExp
      case 85: // LAndExp
      case 86: // LOrExp
      case 87: // IDENT
        value.YY_MOVE_OR_COPY< ASTPtr > (YY_MOVE (that.value));
        break;

      case 37: // OCT_NUM
      case 38: // DEC_NUM
      case 39: // HEX_NUM
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 40: // ID
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 42: // program
      case 43: // CompUnit
      case 44: // Decl
      case 45: // ConstDecl
      case 46: // ConstDefList
      case 47: // ConstDef
      case 48: // Dimension
      case 49: // ConstInitVal
      case 50: // ConstInitValArray
      case 52: // ConstInitValList
      case 53: // VarDecl
      case 54: // VarDefList
      case 55: // VarDef
      case 56: // InitVal
      case 57: // InitValArray
      case 58: // InitValList
      case 59: // FuncDef
      case 60: // FuncFParams
      case 61: // FuncFParam
      case 62: // FuncFParamVar
      case 63: // FuncFParamArray
      case 64: // Block
      case 65: // BlockItems
      case 66: // BlockItem
      case 67: // Stmt
      case 68: // Assign_stmt
      case 69: // Exp_stmt
      case 70: // If_stmt
      case 71: // While_stmt
      case 72: // Cond_stmt
      case 73: // Return_stmt
      case 74: // Exp
      case 75: // Cond
      case 76: // LVal
      case 77: // PrimaryExp
      case 78: // UnaryExp
      case 79: // FuncCallExp
      case 80: // FuncRParams
      case 81: // MulExp
      case 82: // AddExp
      case 83: // RelExp
      case 84: // EqExp
      case 85: // LAndExp
      case 86: // LOrExp
      case 87: // IDENT
        value.move< ASTPtr > (YY_MOVE (that.value));
        break;

      case 37: // OCT_NUM
      case 38: // DEC_NUM
      case 39: // HEX_NUM
        value.move< int > (YY_MOVE (that.value));
        break;

      case 40: // ID
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 42: // program
      case 43: // CompUnit
      case 44: // Decl
      case 45: // ConstDecl
      case 46: // ConstDefList
      case 47: // ConstDef
      case 48: // Dimension
      case 49: // ConstInitVal
      case 50: // ConstInitValArray
      case 52: // ConstInitValList
      case 53: // VarDecl
      case 54: // VarDefList
      case 55: // VarDef
      case 56: // InitVal
      case 57: // InitValArray
      case 58: // InitValList
      case 59: // FuncDef
      case 60: // FuncFParams
      case 61: // FuncFParam
      case 62: // FuncFParamVar
      case 63: // FuncFParamArray
      case 64: // Block
      case 65: // BlockItems
      case 66: // BlockItem
      case 67: // Stmt
      case 68: // Assign_stmt
      case 69: // Exp_stmt
      case 70: // If_stmt
      case 71: // While_stmt
      case 72: // Cond_stmt
      case 73: // Return_stmt
      case 74: // Exp
      case 75: // Cond
      case 76: // LVal
      case 77: // PrimaryExp
      case 78: // UnaryExp
      case 79: // FuncCallExp
      case 80: // FuncRParams
      case 81: // MulExp
      case 82: // AddExp
      case 83: // RelExp
      case 84: // EqExp
      case 85: // LAndExp
      case 86: // LOrExp
      case 87: // IDENT
        value.copy< ASTPtr > (that.value);
        break;

      case 37: // OCT_NUM
      case 38: // DEC_NUM
      case 39: // HEX_NUM
        value.copy< int > (that.value);
        break;

      case 40: // ID
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 42: // program
      case 43: // CompUnit
      case 44: // Decl
      case 45: // ConstDecl
      case 46: // ConstDefList
      case 47: // ConstDef
      case 48: // Dimension
      case 49: // ConstInitVal
      case 50: // ConstInitValArray
      case 52: // ConstInitValList
      case 53: // VarDecl
      case 54: // VarDefList
      case 55: // VarDef
      case 56: // InitVal
      case 57: // InitValArray
      case 58: // InitValList
      case 59: // FuncDef
      case 60: // FuncFParams
      case 61: // FuncFParam
      case 62: // FuncFParamVar
      case 63: // FuncFParamArray
      case 64: // Block
      case 65: // BlockItems
      case 66: // BlockItem
      case 67: // Stmt
      case 68: // Assign_stmt
      case 69: // Exp_stmt
      case 70: // If_stmt
      case 71: // While_stmt
      case 72: // Cond_stmt
      case 73: // Return_stmt
      case 74: // Exp
      case 75: // Cond
      case 76: // LVal
      case 77: // PrimaryExp
      case 78: // UnaryExp
      case 79: // FuncCallExp
      case 80: // FuncRParams
      case 81: // MulExp
      case 82: // AddExp
      case 83: // RelExp
      case 84: // EqExp
      case 85: // LAndExp
      case 86: // LOrExp
      case 87: // IDENT
        value.move< ASTPtr > (that.value);
        break;

      case 37: // OCT_NUM
      case 38: // DEC_NUM
      case 39: // HEX_NUM
        value.move< int > (that.value);
        break;

      case 40: // ID
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 42: // program
      case 43: // CompUnit
      case 44: // Decl
      case 45: // ConstDecl
      case 46: // ConstDefList
      case 47: // ConstDef
      case 48: // Dimension
      case 49: // ConstInitVal
      case 50: // ConstInitValArray
      case 52: // ConstInitValList
      case 53: // VarDecl
      case 54: // VarDefList
      case 55: // VarDef
      case 56: // InitVal
      case 57: // InitValArray
      case 58: // InitValList
      case 59: // FuncDef
      case 60: // FuncFParams
      case 61: // FuncFParam
      case 62: // FuncFParamVar
      case 63: // FuncFParamArray
      case 64: // Block
      case 65: // BlockItems
      case 66: // BlockItem
      case 67: // Stmt
      case 68: // Assign_stmt
      case 69: // Exp_stmt
      case 70: // If_stmt
      case 71: // While_stmt
      case 72: // Cond_stmt
      case 73: // Return_stmt
      case 74: // Exp
      case 75: // Cond
      case 76: // LVal
      case 77: // PrimaryExp
      case 78: // UnaryExp
      case 79: // FuncCallExp
      case 80: // FuncRParams
      case 81: // MulExp
      case 82: // AddExp
      case 83: // RelExp
      case 84: // EqExp
      case 85: // LAndExp
      case 86: // LOrExp
      case 87: // IDENT
        yylhs.value.emplace< ASTPtr > ();
        break;

      case 37: // OCT_NUM
      case 38: // DEC_NUM
      case 39: // HEX_NUM
        yylhs.value.emplace< int > ();
        break;

      case 40: // ID
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 55 "source.y"
                       {drv.root = std::move(yystack_[0].value.as < ASTPtr > ()); }
#line 858 "source.tab.cpp"
    break;

  case 3:
#line 57 "source.y"
                   { 
    ASTPtrList units;
    units.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<CompUnitAST>(std::move(units));  }
#line 867 "source.tab.cpp"
    break;

  case 4:
#line 61 "source.y"
                      {
    ASTPtrList units;
    units.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<CompUnitAST>(std::move(units));  }
#line 876 "source.tab.cpp"
    break;

  case 5:
#line 65 "source.y"
                            {
    auto p_CompUnitAST = std::dynamic_pointer_cast<CompUnitAST>(yystack_[1].value.as < ASTPtr > ());
    p_CompUnitAST->_units.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_CompUnitAST;
            }
#line 886 "source.tab.cpp"
    break;

  case 6:
#line 70 "source.y"
                               {
    auto p_CompUnitAST = std::dynamic_pointer_cast<CompUnitAST>(yystack_[1].value.as < ASTPtr > ());
    p_CompUnitAST->_units.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_CompUnitAST;
            }
#line 896 "source.tab.cpp"
    break;

  case 7:
#line 77 "source.y"
                        {yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > ();}
#line 902 "source.tab.cpp"
    break;

  case 8:
#line 78 "source.y"
                      {yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > ();}
#line 908 "source.tab.cpp"
    break;

  case 9:
#line 81 "source.y"
                                          { 
    yylhs.value.as < ASTPtr > () =  std::make_shared<ConstDeclAST>(token::TOK_INT, std::move(yystack_[1].value.as < ASTPtr > ()));}
#line 915 "source.tab.cpp"
    break;

  case 10:
#line 85 "source.y"
                        {
    ASTPtrList const_defs;
    const_defs.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<ConstDefListAST>(std::move(const_defs));
}
#line 925 "source.tab.cpp"
    break;

  case 11:
#line 90 "source.y"
                                          {
    auto p_ConstDefListAST = std::dynamic_pointer_cast<ConstDefListAST>(yystack_[2].value.as < ASTPtr > ());
    p_ConstDefListAST->const_defs().push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_ConstDefListAST;
}
#line 935 "source.tab.cpp"
    break;

  case 12:
#line 97 "source.y"
                                    {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[2].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<ConstDefAST>(p_IdAST->id(), nullptr, std::move(yystack_[0].value.as < ASTPtr > ()), 0);
}
#line 944 "source.tab.cpp"
    break;

  case 13:
#line 101 "source.y"
                                              {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<ConstDefAST>(p_IdAST->id(), std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()), 1);
}
#line 953 "source.tab.cpp"
    break;

  case 14:
#line 107 "source.y"
                                  {
    ASTPtrList const_exprs;
    const_exprs.push_back(std::move(yystack_[1].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<DimensionAST>(std::move(const_exprs));
}
#line 963 "source.tab.cpp"
    break;

  case 15:
#line 112 "source.y"
                                             {
    auto p_DimensionAST = std::dynamic_pointer_cast<DimensionAST>(yystack_[3].value.as < ASTPtr > ());
    p_DimensionAST->dims().push_back(std::move(yystack_[1].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_DimensionAST;            
}
#line 973 "source.tab.cpp"
    break;

  case 16:
#line 119 "source.y"
                  { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 979 "source.tab.cpp"
    break;

  case 17:
#line 120 "source.y"
                                { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 985 "source.tab.cpp"
    break;

  case 18:
#line 123 "source.y"
                          {
    yylhs.value.as < ASTPtr > () = std::make_shared<ConstInitValArrayAST>(nullptr);
}
#line 993 "source.tab.cpp"
    break;

  case 19:
#line 126 "source.y"
                                               {
    yylhs.value.as < ASTPtr > () = std::make_shared<ConstInitValArrayAST>(std::move(yystack_[1].value.as < ASTPtr > ()));
}
#line 1001 "source.tab.cpp"
    break;

  case 21:
#line 134 "source.y"
                                {
    ASTPtrList const_exprs;
    const_exprs.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<ConstInitValAST>(std::move(const_exprs));
}
#line 1011 "source.tab.cpp"
    break;

  case 22:
#line 139 "source.y"
                                                  {
    auto p_ConstInitValList = std::dynamic_pointer_cast<ConstInitValAST>(yystack_[2].value.as < ASTPtr > ());
    p_ConstInitValList->const_exprs().push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_ConstInitValList;
}
#line 1021 "source.tab.cpp"
    break;

  case 23:
#line 146 "source.y"
                                  {
    yylhs.value.as < ASTPtr > () =  std::make_shared<VarDeclAST>(token::TOK_INT, std::move(yystack_[1].value.as < ASTPtr > ()));
}
#line 1029 "source.tab.cpp"
    break;

  case 24:
#line 151 "source.y"
                     {
    ASTPtrList var_defs;
    var_defs.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<VarDefListAST>(std::move(var_defs));
}
#line 1039 "source.tab.cpp"
    break;

  case 25:
#line 156 "source.y"
                                      {
    auto p_VarDefList = std::dynamic_pointer_cast<VarDefListAST>(yystack_[2].value.as < ASTPtr > ());
    p_VarDefList->var_defs().push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_VarDefList;
}
#line 1049 "source.tab.cpp"
    break;

  case 26:
#line 163 "source.y"
                    {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[0].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<VarDefAST>(p_IdAST->id(), nullptr, nullptr, 0);
}
#line 1058 "source.tab.cpp"
    break;

  case 27:
#line 167 "source.y"
                               {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[2].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<VarDefAST>(p_IdAST->id(), nullptr, std::move(yystack_[0].value.as < ASTPtr > ()), 0);
}
#line 1067 "source.tab.cpp"
    break;

  case 28:
#line 171 "source.y"
                              {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[1].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<VarDefAST>(p_IdAST->id(), std::move(yystack_[0].value.as < ASTPtr > ()), nullptr, 1);
}
#line 1076 "source.tab.cpp"
    break;

  case 29:
#line 175 "source.y"
                                         {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<VarDefAST>(p_IdAST->id(), std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()), 1);
}
#line 1085 "source.tab.cpp"
    break;

  case 30:
#line 181 "source.y"
                  { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1091 "source.tab.cpp"
    break;

  case 31:
#line 182 "source.y"
                           { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1097 "source.tab.cpp"
    break;

  case 32:
#line 185 "source.y"
                     {
    yylhs.value.as < ASTPtr > () = std::make_shared<InitValArrayAST>(nullptr);
}
#line 1105 "source.tab.cpp"
    break;

  case 33:
#line 188 "source.y"
                                          {
    yylhs.value.as < ASTPtr > () = std::make_shared<InitValArrayAST>(std::move(yystack_[1].value.as < ASTPtr > ()));
}
#line 1113 "source.tab.cpp"
    break;

  case 34:
#line 193 "source.y"
                      {
    ASTPtrList exprs;
    exprs.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<InitValAST>(std::move(exprs));
}
#line 1123 "source.tab.cpp"
    break;

  case 35:
#line 198 "source.y"
                                        {
    auto p_InitValList = std::dynamic_pointer_cast<InitValAST>(yystack_[2].value.as < ASTPtr > ());
    p_InitValList->exprs().push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_InitValList;
}
#line 1133 "source.tab.cpp"
    break;

  case 36:
#line 205 "source.y"
                                               {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncDefAST>(token::TOK_VOID, p_IdAST->id(), nullptr, std::move(yystack_[0].value.as < ASTPtr > ()));
}
#line 1142 "source.tab.cpp"
    break;

  case 37:
#line 209 "source.y"
                                                           {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[4].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncDefAST>(token::TOK_VOID, p_IdAST->id(), std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
}
#line 1151 "source.tab.cpp"
    break;

  case 38:
#line 213 "source.y"
                                              {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncDefAST>(token::TOK_INT, p_IdAST->id(), nullptr, std::move(yystack_[0].value.as < ASTPtr > ()));
}
#line 1160 "source.tab.cpp"
    break;

  case 39:
#line 217 "source.y"
                                                          {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[4].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncDefAST>(token::TOK_INT, p_IdAST->id(), std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
}
#line 1169 "source.tab.cpp"
    break;

  case 40:
#line 223 "source.y"
                         {
    ASTPtrList param_list;
    param_list.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncFParamsAST>(std::move(param_list));
}
#line 1179 "source.tab.cpp"
    break;

  case 41:
#line 228 "source.y"
                                           {
    auto p_FuncFParams = std::dynamic_pointer_cast<FuncFParamsAST>(yystack_[2].value.as < ASTPtr > ());
    p_FuncFParams->param_list().push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_FuncFParams;
}
#line 1189 "source.tab.cpp"
    break;

  case 42:
#line 236 "source.y"
                            { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1195 "source.tab.cpp"
    break;

  case 43:
#line 237 "source.y"
                              { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1201 "source.tab.cpp"
    break;

  case 44:
#line 240 "source.y"
                          {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[0].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncFParamVarAST>(token::TOK_INT, p_IdAST->id());
}
#line 1210 "source.tab.cpp"
    break;

  case 45:
#line 246 "source.y"
                                            {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[2].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncFParamArrayAST>(token::TOK_INT, p_IdAST->id(), nullptr);
}
#line 1219 "source.tab.cpp"
    break;

  case 46:
#line 250 "source.y"
                                                  {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value.as < ASTPtr > ());
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncFParamArrayAST>(token::TOK_INT, p_IdAST->id(), std::move(yystack_[0].value.as < ASTPtr > ()));
}
#line 1228 "source.tab.cpp"
    break;

  case 47:
#line 256 "source.y"
                    {
    yylhs.value.as < ASTPtr > () = std::make_shared<BlockAST>(nullptr);
}
#line 1236 "source.tab.cpp"
    break;

  case 48:
#line 259 "source.y"
                                         {
    yylhs.value.as < ASTPtr > () = std::make_shared<BlockAST>(std::move(yystack_[1].value.as < ASTPtr > ()));
}
#line 1244 "source.tab.cpp"
    break;

  case 49:
#line 264 "source.y"
                        {
    ASTPtrList items;
    items.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<BlockItemsAST>(std::move(items));
}
#line 1254 "source.tab.cpp"
    break;

  case 50:
#line 269 "source.y"
                                   {
    auto p_BlockItems = std::dynamic_pointer_cast<BlockItemsAST>(yystack_[1].value.as < ASTPtr > ());
    p_BlockItems->items().push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_BlockItems;
}
#line 1264 "source.tab.cpp"
    break;

  case 51:
#line 276 "source.y"
                   {
    yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > ();
}
#line 1272 "source.tab.cpp"
    break;

  case 52:
#line 279 "source.y"
                   {
    yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > ();
}
#line 1280 "source.tab.cpp"
    break;

  case 53:
#line 284 "source.y"
                    { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1286 "source.tab.cpp"
    break;

  case 54:
#line 285 "source.y"
                          { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1292 "source.tab.cpp"
    break;

  case 55:
#line 286 "source.y"
                       { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1298 "source.tab.cpp"
    break;

  case 56:
#line 287 "source.y"
                      { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1304 "source.tab.cpp"
    break;

  case 57:
#line 288 "source.y"
                         { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1310 "source.tab.cpp"
    break;

  case 58:
#line 289 "source.y"
                        { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1316 "source.tab.cpp"
    break;

  case 59:
#line 290 "source.y"
                          { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1322 "source.tab.cpp"
    break;

  case 60:
#line 293 "source.y"
                               {
    yylhs.value.as < ASTPtr > () = std::make_shared<AssignAST>(std::move(yystack_[3].value.as < ASTPtr > ()), std::move(yystack_[1].value.as < ASTPtr > ()));
}
#line 1330 "source.tab.cpp"
    break;

  case 61:
#line 298 "source.y"
                   {
    yylhs.value.as < ASTPtr > () = std::make_shared<ExpAST>(nullptr);
}
#line 1338 "source.tab.cpp"
    break;

  case 62:
#line 301 "source.y"
                       {
    yylhs.value.as < ASTPtr > () = std::make_shared<ExpAST>(std::move(yystack_[1].value.as < ASTPtr > ()));
}
#line 1346 "source.tab.cpp"
    break;

  case 63:
#line 306 "source.y"
                                           {
    yylhs.value.as < ASTPtr > () = std::make_shared<IfAST>(std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()), nullptr);
}
#line 1354 "source.tab.cpp"
    break;

  case 64:
#line 309 "source.y"
                                                     {
    yylhs.value.as < ASTPtr > () = std::make_shared<IfAST>(std::move(yystack_[4].value.as < ASTPtr > ()), std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
}
#line 1362 "source.tab.cpp"
    break;

  case 65:
#line 314 "source.y"
                                              {
    yylhs.value.as < ASTPtr > () = std::make_shared<WhileAST>(std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
}
#line 1370 "source.tab.cpp"
    break;

  case 66:
#line 319 "source.y"
                         {
    yylhs.value.as < ASTPtr > () = std::make_shared<CondAST>(token::TOK_BREAK);
}
#line 1378 "source.tab.cpp"
    break;

  case 67:
#line 322 "source.y"
                            {
    yylhs.value.as < ASTPtr > () = std::make_shared<CondAST>(token::TOK_CONTINUE);
}
#line 1386 "source.tab.cpp"
    break;

  case 68:
#line 327 "source.y"
                          {
    yylhs.value.as < ASTPtr > () = std::make_shared<ReturnAST>(nullptr);
}
#line 1394 "source.tab.cpp"
    break;

  case 69:
#line 330 "source.y"
                              {
    yylhs.value.as < ASTPtr > () = std::make_shared<ReturnAST>(std::move(yystack_[1].value.as < ASTPtr > ()));
}
#line 1402 "source.tab.cpp"
    break;

  case 70:
#line 335 "source.y"
                     { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1408 "source.tab.cpp"
    break;

  case 71:
#line 338 "source.y"
                     { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1414 "source.tab.cpp"
    break;

  case 72:
#line 341 "source.y"
                    { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1420 "source.tab.cpp"
    break;

  case 73:
#line 342 "source.y"
                              {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[1].value.as < ASTPtr > ()); 
                yylhs.value.as < ASTPtr > () = std::make_shared<ArrayAST>(p_IdAST->id(), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1429 "source.tab.cpp"
    break;

  case 74:
#line 348 "source.y"
                                  { yylhs.value.as < ASTPtr > () = yystack_[1].value.as < ASTPtr > (); }
#line 1435 "source.tab.cpp"
    break;

  case 75:
#line 349 "source.y"
                   { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1441 "source.tab.cpp"
    break;

  case 76:
#line 350 "source.y"
                      {
                yylhs.value.as < ASTPtr > () = std::make_shared<IntAST>(yystack_[0].value.as < int > ());
                #ifdef DEBUG
                    printf("%d\n", yystack_[0].value.as < int > ());
                #endif 
            }
#line 1452 "source.tab.cpp"
    break;

  case 77:
#line 356 "source.y"
                      {
                yylhs.value.as < ASTPtr > () = std::make_shared<IntAST>(yystack_[0].value.as < int > ());
                #ifdef DEBUG
                    printf("%d\n", yystack_[0].value.as < int > ());
                #endif
            }
#line 1463 "source.tab.cpp"
    break;

  case 78:
#line 362 "source.y"
                      {
                yylhs.value.as < ASTPtr > () = std::make_shared<IntAST>(yystack_[0].value.as < int > ());
                #ifdef DEBUG
                    printf("%d\n", yystack_[0].value.as < int > ());
                #endif
            }
#line 1474 "source.tab.cpp"
    break;

  case 79:
#line 370 "source.y"
                         { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1480 "source.tab.cpp"
    break;

  case 80:
#line 371 "source.y"
                          { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1486 "source.tab.cpp"
    break;

  case 81:
#line 372 "source.y"
                            {
                yylhs.value.as < ASTPtr > () = std::make_shared<UnaryAST>(token::TOK_PLUS, std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1494 "source.tab.cpp"
    break;

  case 82:
#line 375 "source.y"
                             {
                yylhs.value.as < ASTPtr > () = std::make_shared<UnaryAST>(token::TOK_MINUS, std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1502 "source.tab.cpp"
    break;

  case 83:
#line 378 "source.y"
                           {
                yylhs.value.as < ASTPtr > () = std::make_shared<UnaryAST>(token::TOK_NOT, std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1510 "source.tab.cpp"
    break;

  case 84:
#line 383 "source.y"
                                    {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[2].value.as < ASTPtr > ());
                yylhs.value.as < ASTPtr > () = std::make_shared<FuncCallAST>(p_IdAST->id(), nullptr); 
            }
#line 1519 "source.tab.cpp"
    break;

  case 85:
#line 387 "source.y"
                                                {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value.as < ASTPtr > ());
                yylhs.value.as < ASTPtr > () = std::make_shared<FuncCallAST>(p_IdAST->id(), std::move(yystack_[1].value.as < ASTPtr > ())); 
            }
#line 1528 "source.tab.cpp"
    break;

  case 86:
#line 393 "source.y"
                  {
    ASTPtrList exprs;
    exprs.push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = std::make_shared<FuncRParamsAST>(std::move(exprs));
}
#line 1538 "source.tab.cpp"
    break;

  case 87:
#line 398 "source.y"
                                    {
    auto p_FuncRParams = std::dynamic_pointer_cast<FuncRParamsAST>(yystack_[2].value.as < ASTPtr > ());
    p_FuncRParams->exprs().push_back(std::move(yystack_[0].value.as < ASTPtr > ()));
    yylhs.value.as < ASTPtr > () = p_FuncRParams;
}
#line 1548 "source.tab.cpp"
    break;

  case 88:
#line 406 "source.y"
                       { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1554 "source.tab.cpp"
    break;

  case 89:
#line 407 "source.y"
                                    {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_TIMES,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1563 "source.tab.cpp"
    break;

  case 90:
#line 411 "source.y"
                                   {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_OVER,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1572 "source.tab.cpp"
    break;

  case 91:
#line 415 "source.y"
                                  {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_MOD,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1581 "source.tab.cpp"
    break;

  case 92:
#line 421 "source.y"
                     { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1587 "source.tab.cpp"
    break;

  case 93:
#line 422 "source.y"
                                 {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_PLUS,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1596 "source.tab.cpp"
    break;

  case 94:
#line 426 "source.y"
                                  {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_MINUS,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1605 "source.tab.cpp"
    break;

  case 95:
#line 432 "source.y"
                     { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1611 "source.tab.cpp"
    break;

  case 96:
#line 433 "source.y"
                               {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_LT,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1620 "source.tab.cpp"
    break;

  case 97:
#line 437 "source.y"
                               {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_GT,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1629 "source.tab.cpp"
    break;

  case 98:
#line 441 "source.y"
                                {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_LTE,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1638 "source.tab.cpp"
    break;

  case 99:
#line 445 "source.y"
                                {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_GTE,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1647 "source.tab.cpp"
    break;

  case 100:
#line 451 "source.y"
                     { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1653 "source.tab.cpp"
    break;

  case 101:
#line 452 "source.y"
                              {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_EQ,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1662 "source.tab.cpp"
    break;

  case 102:
#line 456 "source.y"
                               {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_NEQ,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1671 "source.tab.cpp"
    break;

  case 103:
#line 462 "source.y"
                    { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1677 "source.tab.cpp"
    break;

  case 104:
#line 463 "source.y"
                                {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_AND,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1686 "source.tab.cpp"
    break;

  case 105:
#line 468 "source.y"
                      { yylhs.value.as < ASTPtr > () = yystack_[0].value.as < ASTPtr > (); }
#line 1692 "source.tab.cpp"
    break;

  case 106:
#line 469 "source.y"
                                {
                yylhs.value.as < ASTPtr > () = std::make_shared<BinaryAST>(token::TOK_OR,
                std::move(yystack_[2].value.as < ASTPtr > ()), std::move(yystack_[0].value.as < ASTPtr > ()));
            }
#line 1701 "source.tab.cpp"
    break;

  case 107:
#line 474 "source.y"
                {
    yylhs.value.as < ASTPtr > () = std::make_unique<IdAST>(yystack_[0].value.as < std::string > ());
}
#line 1709 "source.tab.cpp"
    break;


#line 1713 "source.tab.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short parser::yypact_ninf_ = -150;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     142,    -7,   -10,   -10,    16,   142,  -150,  -150,  -150,  -150,
     -10,  -150,    60,  -150,    86,    21,  -150,  -150,  -150,   125,
    -150,    37,  -150,   -10,    57,     6,   250,    49,    14,  -150,
     -10,   275,    93,  -150,    99,    57,    57,    57,    57,  -150,
    -150,  -150,     4,  -150,  -150,  -150,  -150,   124,    22,    63,
     -10,    50,    13,  -150,  -150,  -150,   220,  -150,  -150,  -150,
    -150,    57,   250,    50,    25,  -150,   245,  -150,  -150,  -150,
    -150,   275,    38,  -150,  -150,  -150,  -150,    57,    57,    57,
      57,    57,   190,    67,    75,   121,  -150,  -150,    69,    50,
    -150,  -150,    88,    94,  -150,  -150,    50,  -150,   106,  -150,
    -150,  -150,  -150,  -150,   124,   124,  -150,  -150,    35,   117,
      87,   105,   128,   157,   195,   -10,  -150,  -150,  -150,   159,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,   158,   151,
    -150,  -150,   250,  -150,  -150,  -150,   275,  -150,    57,  -150,
     162,    57,    57,  -150,  -150,  -150,   168,  -150,  -150,  -150,
      57,  -150,  -150,  -150,    67,   163,    22,   119,   110,   149,
     150,   165,  -150,   173,    62,    57,    57,    57,    57,    57,
      57,    57,    57,    62,  -150,   185,    22,    22,    22,    22,
     119,   119,   110,   149,  -150,    62,  -150
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     2,     3,     7,     8,     4,
       0,   107,     0,    24,    26,     0,     1,     5,     6,     0,
      10,     0,    23,     0,     0,     0,     0,    28,     0,     9,
       0,     0,     0,    25,    26,     0,     0,     0,     0,    77,
      76,    78,     0,    75,    79,    88,    80,    92,    70,    72,
       0,     0,     0,    40,    42,    43,     0,    32,    27,    31,
      30,     0,     0,     0,     0,    11,     0,    12,    17,    18,
      16,     0,     0,    83,    81,    82,    14,     0,     0,     0,
       0,     0,     0,    73,    44,     0,    47,    38,     0,     0,
      20,    34,     0,     0,    29,    36,     0,    21,     0,    13,
      74,    89,    90,    91,    93,    94,    84,    86,     0,     0,
       0,     0,     0,     0,     0,     0,    61,    51,    53,     0,
      49,    52,    54,    55,    56,    57,    58,    59,     0,    75,
      41,    39,     0,    33,    15,    37,     0,    19,     0,    85,
      45,     0,     0,    66,    67,    68,     0,    48,    50,    62,
       0,    35,    22,    87,    46,     0,    95,   100,   103,   105,
      71,     0,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,    63,    96,    97,    98,    99,
     101,   102,   104,   106,    65,     0,    64
  };

  const short
  parser::yypgoto_[] =
  {
    -150,  -150,  -150,    43,  -150,  -150,   161,   -20,   -63,  -150,
     -17,  -150,  -150,  -150,   169,   -44,  -150,  -150,   188,   166,
     107,  -150,  -150,   -32,  -150,    81,  -149,  -150,  -150,  -150,
    -150,  -150,  -150,   -24,    71,   -75,  -150,   -16,  -150,  -150,
      68,    36,    -6,    45,    42,  -150,     3
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     4,     5,   117,     7,    19,    20,    27,    67,    68,
      86,    98,     8,    12,    13,    58,    59,    92,     9,    52,
      53,    54,    55,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   155,    43,    44,    45,    46,   108,
      47,    48,   157,   158,   159,   160,    49
  };

  const unsigned char
  parser::yytable_[] =
  {
      42,    32,    60,    97,    10,    14,    15,    70,    99,    57,
     129,    72,    91,    21,    69,   175,    16,    50,    94,    87,
      73,    74,    75,    76,   184,    50,    34,    51,    88,    83,
      11,    95,    60,    21,    89,    63,   186,    93,    60,    57,
      88,    28,    70,     6,   129,    57,    96,    70,    17,    69,
     138,    80,    81,    84,    69,    24,   139,   131,   107,   100,
      31,   101,   102,   103,   135,   110,    85,    61,   111,   112,
     113,   114,    62,   152,    22,    23,   116,    35,    85,    36,
      50,    24,    35,    82,    36,    61,    37,    38,   151,   129,
     146,    37,    38,   109,    39,    40,    41,    11,   129,    39,
      40,    41,    11,   132,    24,   133,    25,   141,    60,    26,
     129,    61,    70,   134,   153,    57,    71,    24,    34,    69,
     154,   136,    26,   137,   110,   142,   163,   111,   112,   113,
     114,     1,   115,   169,   170,   116,   140,    85,    90,    29,
      30,    35,   143,    36,   165,   166,   167,   168,   104,   105,
      37,    38,     1,     2,     3,    77,    78,    79,    39,    40,
      41,    11,   110,   180,   181,   111,   112,   113,   114,     1,
     115,   144,   149,   116,   150,    85,   147,   156,   156,    35,
      24,    36,   162,   171,   164,   172,   173,   174,    37,    38,
     185,    65,    33,    18,    64,   130,    39,    40,    41,    11,
     148,   176,   177,   178,   179,   156,   156,   156,   156,   145,
      35,   106,    36,   161,   183,    35,   182,    36,     0,    37,
      38,     0,     0,     0,    37,    38,     0,    39,    40,    41,
      11,     0,    39,    40,    41,    11,    56,    90,     0,     0,
      35,     0,    36,     0,     0,     0,     0,     0,     0,    37,
      38,     0,     0,     0,     0,     0,     0,    39,    40,    41,
      11,    66,    90,     0,     0,    35,    56,    36,     0,     0,
      35,     0,    36,     0,    37,    38,     0,     0,     0,    37,
      38,     0,    39,    40,    41,    11,     0,    39,    40,    41,
      11,    66,     0,     0,     0,    35,     0,    36,     0,     0,
       0,     0,     0,     0,    37,    38,     0,     0,     0,     0,
       0,     0,    39,    40,    41,    11
  };

  const short
  parser::yycheck_[] =
  {
      24,    21,    26,    66,    11,     2,     3,    31,    71,    26,
      85,    35,    56,    10,    31,   164,     0,    11,    62,    51,
      36,    37,    38,    19,   173,    11,    23,    21,    15,    49,
      40,    63,    56,    30,    21,    21,   185,    61,    62,    56,
      15,    20,    66,     0,   119,    62,    21,    71,     5,    66,
      15,    29,    30,    50,    71,    18,    21,    89,    82,    21,
      23,    77,    78,    79,    96,     3,    16,    18,     6,     7,
       8,     9,    23,   136,    14,    15,    14,    20,    16,    22,
      11,    18,    20,    20,    22,    18,    29,    30,   132,   164,
     114,    29,    30,    18,    37,    38,    39,    40,   173,    37,
      38,    39,    40,    15,    18,    17,    20,    20,   132,    23,
     185,    18,   136,    19,   138,   132,    23,    18,   115,   136,
     140,    15,    23,    17,     3,    20,   150,     6,     7,     8,
       9,    10,    11,    23,    24,    14,    19,    16,    17,    14,
      15,    20,    14,    22,    25,    26,    27,    28,    80,    81,
      29,    30,    10,    11,    12,    31,    32,    33,    37,    38,
      39,    40,     3,   169,   170,     6,     7,     8,     9,    10,
      11,    14,    14,    14,    23,    16,    17,   141,   142,    20,
      18,    22,    14,    34,    21,    35,    21,    14,    29,    30,
       5,    30,    23,     5,    28,    88,    37,    38,    39,    40,
     119,   165,   166,   167,   168,   169,   170,   171,   172,    14,
      20,    21,    22,   142,   172,    20,   171,    22,    -1,    29,
      30,    -1,    -1,    -1,    29,    30,    -1,    37,    38,    39,
      40,    -1,    37,    38,    39,    40,    16,    17,    -1,    -1,
      20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    16,    17,    -1,    -1,    20,    16,    22,    -1,    -1,
      20,    -1,    22,    -1,    29,    30,    -1,    -1,    -1,    29,
      30,    -1,    37,    38,    39,    40,    -1,    37,    38,    39,
      40,    16,    -1,    -1,    -1,    20,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40
  };

  const signed char
  parser::yystos_[] =
  {
       0,    10,    11,    12,    42,    43,    44,    45,    53,    59,
      11,    40,    54,    55,    87,    87,     0,    44,    59,    46,
      47,    87,    14,    15,    18,    20,    23,    48,    20,    14,
      15,    23,    48,    55,    87,    20,    22,    29,    30,    37,
      38,    39,    74,    76,    77,    78,    79,    81,    82,    87,
      11,    21,    60,    61,    62,    63,    16,    51,    56,    57,
      74,    18,    23,    21,    60,    47,    16,    49,    50,    51,
      74,    23,    74,    78,    78,    78,    19,    31,    32,    33,
      29,    30,    20,    48,    87,    16,    51,    64,    15,    21,
      17,    56,    58,    74,    56,    64,    21,    49,    52,    49,
      21,    78,    78,    78,    81,    81,    21,    74,    80,    18,
       3,     6,     7,     8,     9,    11,    14,    44,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    76,
      61,    64,    15,    17,    19,    64,    15,    17,    15,    21,
      19,    20,    20,    14,    14,    14,    74,    17,    66,    14,
      23,    56,    49,    74,    48,    75,    82,    83,    84,    85,
      86,    75,    14,    74,    21,    25,    26,    27,    28,    23,
      24,    34,    35,    21,    14,    67,    82,    82,    82,    82,
      83,    83,    84,    85,    67,     5,    67
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    41,    42,    43,    43,    43,    43,    44,    44,    45,
      46,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    52,    52,    53,    54,    54,    55,    55,    55,    55,
      56,    56,    57,    57,    58,    58,    59,    59,    59,    59,
      60,    60,    61,    61,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    67,    67,    67,    67,
      68,    69,    69,    70,    70,    71,    72,    72,    73,    73,
      74,    75,    76,    76,    77,    77,    77,    77,    77,    78,
      78,    78,    78,    78,    79,    79,    80,    80,    81,    81,
      81,    81,    82,    82,    82,    83,    83,    83,    83,    83,
      84,    84,    84,    85,    85,    86,    86,    87
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     2,     2,     1,     1,     4,
       1,     3,     3,     4,     3,     4,     1,     1,     1,     3,
       2,     1,     3,     3,     1,     3,     1,     3,     2,     4,
       1,     1,     1,     3,     1,     3,     5,     6,     5,     6,
       1,     3,     1,     1,     2,     4,     5,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     2,     5,     7,     5,     2,     2,     2,     3,
       1,     1,     1,     2,     3,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     3,     4,     1,     3,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "IF", "THEN", "ELSE", "WHILE",
  "BREAK", "CONTINUE", "RETURN", "CONST", "INT", "VOID", "ASSIGN", "SEMI",
  "COMMA", "LLPAREN", "LRPAREN", "MLPAREN", "MRPAREN", "SLPAREN",
  "SRPAREN", "NOT", "EQ", "NEQ", "LT", "GT", "LTE", "GTE", "PLUS", "MINUS",
  "TIMES", "OVER", "MOD", "AND", "OR", "ERROR", "OCT_NUM", "DEC_NUM",
  "HEX_NUM", "ID", "$accept", "program", "CompUnit", "Decl", "ConstDecl",
  "ConstDefList", "ConstDef", "Dimension", "ConstInitVal",
  "ConstInitValArray", "EMPTY", "ConstInitValList", "VarDecl",
  "VarDefList", "VarDef", "InitVal", "InitValArray", "InitValList",
  "FuncDef", "FuncFParams", "FuncFParam", "FuncFParamVar",
  "FuncFParamArray", "Block", "BlockItems", "BlockItem", "Stmt",
  "Assign_stmt", "Exp_stmt", "If_stmt", "While_stmt", "Cond_stmt",
  "Return_stmt", "Exp", "Cond", "LVal", "PrimaryExp", "UnaryExp",
  "FuncCallExp", "FuncRParams", "MulExp", "AddExp", "RelExp", "EqExp",
  "LAndExp", "LOrExp", "IDENT", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    55,    55,    57,    61,    65,    70,    77,    78,    81,
      85,    90,    97,   101,   107,   112,   119,   120,   123,   126,
     131,   134,   139,   146,   151,   156,   163,   167,   171,   175,
     181,   182,   185,   188,   193,   198,   205,   209,   213,   217,
     223,   228,   236,   237,   240,   246,   250,   256,   259,   264,
     269,   276,   279,   284,   285,   286,   287,   288,   289,   290,
     293,   298,   301,   306,   309,   314,   319,   322,   327,   330,
     335,   338,   341,   342,   348,   349,   350,   356,   362,   370,
     371,   372,   375,   378,   383,   387,   393,   398,   406,   407,
     411,   415,   421,   422,   426,   432,   433,   437,   441,   445,
     451,   452,   456,   462,   463,   468,   469,   474
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2258 "source.tab.cpp"

#line 479 "source.y"


void yy::parser::error(const location_type& l, const std::string &m)
{
    std::cerr << l << ":" <<m <<std::endl;
}
