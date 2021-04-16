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



// First part of user prologue.
#line 6 "jason.ypp"

    #include "global.h"
    #include <algorithm>
    #include <stdlib.h>
    #define YYSTYPE ASTPtr
    #define DEBUG
    static ASTPtr root;

#line 49 "y.tab.c"




# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace yy {
#line 180 "y.tab.c"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.
    typedef int semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        IF = 258,
        THEN = 259,
        ELSE = 260,
        WHILE = 261,
        BREAK = 262,
        CONTINUE = 263,
        RETURN = 264,
        CONST = 265,
        INT = 266,
        VOID = 267,
        ID = 268,
        DEC_NUM = 269,
        OCT_NUM = 270,
        HEX_NUM = 271,
        ASSIGN = 272,
        SEMI = 273,
        COMMA = 274,
        LLPAREN = 275,
        LRPAREN = 276,
        MLPAREN = 277,
        MRPAREN = 278,
        SLPAREN = 279,
        SRPAREN = 280,
        NOT = 281,
        EQ = 282,
        NEQ = 283,
        LT = 284,
        GT = 285,
        LTE = 286,
        GTE = 287,
        PLUS = 288,
        MINUS = 289,
        TIMES = 290,
        OVER = 291,
        MOD = 292,
        AND = 293,
        OR = 294,
        ERROR = 295
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef signed char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);
      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    YY_RVREF (semantic_type) v);

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {};

    /// Build a parser object.
    parser ();
    virtual ~parser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);



  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    /// In theory \a t should be a token_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static token_number_type yytranslate_ (int t);

    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      std::ptrdiff_t
      ssize () const YY_NOEXCEPT
      {
        return std::ptrdiff_t (size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Some specific tokens.
    static const token_number_type yy_error_token_ = 1;
    static const token_number_type yy_undef_token_ = 2;

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 308,     ///< Last index in yytable_.
      yynnts_ = 47,  ///< Number of nonterminal symbols.
      yyfinal_ = 16, ///< Termination state number.
      yyntokens_ = 41  ///< Number of tokens.
    };


  };


} // yy
#line 714 "y.tab.c"









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
#line 793 "y.tab.c"


  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value (std::move (that.value))
  {}
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


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
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
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

    // User destructor.
    YYUSE (yysym.type_get ());
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
        << ' ' << yytname_[yytype] << " (";
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
            yyla.type = yytranslate_ (yylex (&yyla.value));
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
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 25 "jason.ypp"
                       {root = std::move(yystack_[0].value); }
#line 1230 "y.tab.c"
    break;

  case 3:
#line 27 "jason.ypp"
                   { 
    ASTPtrList units;
    units.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<CompUnitAST>(std::move(units));  }
#line 1239 "y.tab.c"
    break;

  case 4:
#line 31 "jason.ypp"
                      {
    ASTPtrList units;
    units.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<CompUnitAST>(std::move(units));  }
#line 1248 "y.tab.c"
    break;

  case 5:
#line 35 "jason.ypp"
                            {
    auto p_CompUnitAST = std::dynamic_pointer_cast<CompUnitAST>(yystack_[1].value);
    p_CompUnitAST->_units.push_back(std::move(yystack_[0].value));
    yylhs.value = p_CompUnitAST;
            }
#line 1258 "y.tab.c"
    break;

  case 6:
#line 40 "jason.ypp"
                               {
    auto p_CompUnitAST = std::dynamic_pointer_cast<CompUnitAST>(yystack_[1].value);
    p_CompUnitAST->_units.push_back(std::move(yystack_[0].value));
    yylhs.value = p_CompUnitAST;
            }
#line 1268 "y.tab.c"
    break;

  case 7:
#line 47 "jason.ypp"
                        {yylhs.value = yystack_[0].value;}
#line 1274 "y.tab.c"
    break;

  case 8:
#line 48 "jason.ypp"
                      {yylhs.value = yystack_[0].value;}
#line 1280 "y.tab.c"
    break;

  case 9:
#line 51 "jason.ypp"
                                          { 
    yylhs.value =  std::make_shared<ConstDeclAST>(INT, std::move(yystack_[1].value));}
#line 1287 "y.tab.c"
    break;

  case 10:
#line 55 "jason.ypp"
                        {
    ASTPtrList const_defs;
    const_defs.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<ConstDefListAST>(std::move(const_defs));
}
#line 1297 "y.tab.c"
    break;

  case 11:
#line 60 "jason.ypp"
                                          {
    auto p_ConstDefListAST = std::dynamic_pointer_cast<ConstDefListAST>(yystack_[2].value);
    p_ConstDefListAST.const_defs().push_back(std::move(yystack_[0].value));
    yylhs.value = p_ConstDefListAST;
}
#line 1307 "y.tab.c"
    break;

  case 12:
#line 67 "jason.ypp"
                                    {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[2].value);
    yylhs.value = std::make_shared<ConstDefAST>(p_IdAST.id(),nullptr, std::move(yystack_[0].value));
}
#line 1316 "y.tab.c"
    break;

  case 13:
#line 71 "jason.ypp"
                                              {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value);
    yylhs.value = std::make_shared<ConstDefAST>(p_IdAST.id(),std::move(yystack_[2].value), std::move(yystack_[0].value));
}
#line 1325 "y.tab.c"
    break;

  case 14:
#line 77 "jason.ypp"
                                  {
    ASTPtrList const_exprs;
    const_exprs.push_back(std::move(yystack_[1].value));
    yylhs.value = std::make_shared<DimensionAST>(std::move(const_exprs));
}
#line 1335 "y.tab.c"
    break;

  case 15:
#line 82 "jason.ypp"
                                             {
    auto p_DimensionAST = std::dynamic_pointer_cast<DimensionAST>(yystack_[3].value);
    p_DimensionAST.dims().push_back(std::move(yystack_[1].value));
    yylhs.value = p_DimensionAST;            
}
#line 1345 "y.tab.c"
    break;

  case 16:
#line 89 "jason.ypp"
                  { yylhs.value = yystack_[0].value; }
#line 1351 "y.tab.c"
    break;

  case 17:
#line 90 "jason.ypp"
                                { yylhs.value = yystack_[0].value; }
#line 1357 "y.tab.c"
    break;

  case 18:
#line 93 "jason.ypp"
                          {
    yylhs.value = std::make_shared<ConstInitValArrayAST>(nullptr);
}
#line 1365 "y.tab.c"
    break;

  case 19:
#line 96 "jason.ypp"
                                               {
    yylhs.value = std::make_shared<ConstInitValArrayAST>(std::move(yystack_[1].value));
}
#line 1373 "y.tab.c"
    break;

  case 21:
#line 104 "jason.ypp"
                                {
    ASTPtrList const_exprs;
    const_exprs.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<ConstInitValAST>(std::move(const_exprs));
}
#line 1383 "y.tab.c"
    break;

  case 22:
#line 109 "jason.ypp"
                                                  {
    auto p_ConstInitValList = std::dynamic_pointer_cast<ConstInitValAST>(yystack_[2].value);
    p_ConstInitValList.const_exprs().push_back(std::move(yystack_[0].value));
    yylhs.value = p_ConstInitValList;
}
#line 1393 "y.tab.c"
    break;

  case 23:
#line 116 "jason.ypp"
                                  {
    yylhs.value =  std::make_shared<VarDeclAST>(INT, std::move(yystack_[1].value));
}
#line 1401 "y.tab.c"
    break;

  case 24:
#line 121 "jason.ypp"
                     {
    ASTPtrList var_defs;
    var_defs.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<VarDefListAST>(std::move(var_defs));
}
#line 1411 "y.tab.c"
    break;

  case 25:
#line 126 "jason.ypp"
                                      {
    auto p_VarDefList = std::dynamic_pointer_cast<VarDefListAST>(yystack_[2].value);
    p_VarDefList.var_defs().push_back(std::move(yystack_[0].value));
    yylhs.value = p_VarDefList;
}
#line 1421 "y.tab.c"
    break;

  case 26:
#line 133 "jason.ypp"
                    {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[0].value);
    yylhs.value = std::make_shared<VarDefAST>(p_IdAST.id(), nullptr, nullptr);
}
#line 1430 "y.tab.c"
    break;

  case 27:
#line 137 "jason.ypp"
                               {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[2].value);
    yylhs.value = std::make_shared<VarDefAST>(p_IdAST.id(), nullptr, std::move(yystack_[0].value));
}
#line 1439 "y.tab.c"
    break;

  case 28:
#line 141 "jason.ypp"
                              {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[1].value);
    yylhs.value = std::make_shared<VarDefAST>(p_IdAST.id(), std::move(yystack_[0].value), nullptr);
}
#line 1448 "y.tab.c"
    break;

  case 29:
#line 145 "jason.ypp"
                                         {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value);
    yylhs.value = std::make_shared<VarDefAST>(p_IdAST.id(), std::move(yystack_[2].value), std::move(yystack_[0].value));
}
#line 1457 "y.tab.c"
    break;

  case 30:
#line 151 "jason.ypp"
                  { yylhs.value = yystack_[0].value; }
#line 1463 "y.tab.c"
    break;

  case 31:
#line 152 "jason.ypp"
                           { yylhs.value = yystack_[0].value; }
#line 1469 "y.tab.c"
    break;

  case 32:
#line 155 "jason.ypp"
                     {
    yylhs.value = std::make_shared<InitValArrayAST>(nullptr);
}
#line 1477 "y.tab.c"
    break;

  case 33:
#line 158 "jason.ypp"
                                          {
    yylhs.value = std::make_shared<InitValArrayAST>(std::move(yystack_[1].value));
}
#line 1485 "y.tab.c"
    break;

  case 34:
#line 163 "jason.ypp"
                      {
    ASTPtrList exprs;
    exprs.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<InitValAST>(std::move(exprs));
}
#line 1495 "y.tab.c"
    break;

  case 35:
#line 168 "jason.ypp"
                                        {
    auto p_InitValList = std::dynamic_pointer_cast<InitValAST>(yystack_[2].value);
    p_InitValList.exprs().push_back(std::move(yystack_[0].value));
    yylhs.value = p_InitValList;
}
#line 1505 "y.tab.c"
    break;

  case 36:
#line 175 "jason.ypp"
                                               {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value);
    yylhs.value = std::make_shared<FuncDefAST>(VOID, p_IdAST.id(), nullptr, std::move(yystack_[0].value));
}
#line 1514 "y.tab.c"
    break;

  case 37:
#line 179 "jason.ypp"
                                                           {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[4].value);
    yylhs.value = std::make_shared<FuncDefAST>(VOID, p_IdAST.id(), std::move(yystack_[2].value), std::move(yystack_[0].value));
}
#line 1523 "y.tab.c"
    break;

  case 38:
#line 183 "jason.ypp"
                                              {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value);
    yylhs.value = std::make_shared<FuncDefAST>(INT, p_IdAST.id(), nullptr, std::move(yystack_[0].value));
}
#line 1532 "y.tab.c"
    break;

  case 39:
#line 187 "jason.ypp"
                                                          {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[4].value);
    yylhs.value = std::make_shared<FuncDefAST>(INT, p_IdAST.id(), std::move(yystack_[2].value), std::move(yystack_[0].value));
}
#line 1541 "y.tab.c"
    break;

  case 40:
#line 193 "jason.ypp"
                         {
    ASTPtrList param_list;
    param_list.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<FuncFParamsAST>(std::move(param_list));
}
#line 1551 "y.tab.c"
    break;

  case 41:
#line 198 "jason.ypp"
                                           {
    auto p_FuncFParams = std::dynamic_pointer_cast<FuncFParamsAST>(yystack_[2].value);
    p_FuncFParams.param_list().push_back(std::move(yystack_[0].value));
    yylhs.value = p_FuncFParams;
}
#line 1561 "y.tab.c"
    break;

  case 42:
#line 206 "jason.ypp"
                            { yylhs.value = yystack_[0].value; }
#line 1567 "y.tab.c"
    break;

  case 43:
#line 207 "jason.ypp"
                              { yylhs.value = yystack_[0].value; }
#line 1573 "y.tab.c"
    break;

  case 44:
#line 210 "jason.ypp"
                          {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[0].value);
    yylhs.value = std::make_shared<FuncFParamVarAST>(INT, p_IdAST.id());
}
#line 1582 "y.tab.c"
    break;

  case 45:
#line 216 "jason.ypp"
                                            {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[2].value);
    yylhs.value = std::make_shared<FuncFParamArrayAST>(INT, p_IdAST.id(), nullptr);
}
#line 1591 "y.tab.c"
    break;

  case 46:
#line 220 "jason.ypp"
                                                  {
    auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value);
    yylhs.value = std::make_shared<FuncFParamArrayAST>(INT, p_IdAST.id(), std::move(yystack_[0].value));
}
#line 1600 "y.tab.c"
    break;

  case 47:
#line 226 "jason.ypp"
                    {
    yylhs.value = std::make_shared<BlockAST>(nullptr);
}
#line 1608 "y.tab.c"
    break;

  case 48:
#line 229 "jason.ypp"
                                         {
    yylhs.value = std::make_shared<BlockAST>(std::move(yystack_[1].value));
}
#line 1616 "y.tab.c"
    break;

  case 49:
#line 234 "jason.ypp"
                        {
    ASTPtrList items;
    items.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<BlockItemsAST>(std::move(items));
}
#line 1626 "y.tab.c"
    break;

  case 50:
#line 239 "jason.ypp"
                                   {
    auto p_BlockItems = std::dynamic_pointer_cast<BlockItemsAST>(yystack_[1].value);
    p_BlockItems.items().push_back(std::move(yystack_[0].value));
    yylhs.value = p_BlockItems;
}
#line 1636 "y.tab.c"
    break;

  case 51:
#line 246 "jason.ypp"
                   {
    yylhs.value = yystack_[0].value;
}
#line 1644 "y.tab.c"
    break;

  case 52:
#line 249 "jason.ypp"
                   {
    yylhs.value = yystack_[0].value;
}
#line 1652 "y.tab.c"
    break;

  case 53:
#line 254 "jason.ypp"
                    { yylhs.value = yystack_[0].value; }
#line 1658 "y.tab.c"
    break;

  case 54:
#line 255 "jason.ypp"
                          { yylhs.value = yystack_[0].value; }
#line 1664 "y.tab.c"
    break;

  case 55:
#line 256 "jason.ypp"
                       { yylhs.value = yystack_[0].value; }
#line 1670 "y.tab.c"
    break;

  case 56:
#line 257 "jason.ypp"
                      { yylhs.value = yystack_[0].value; }
#line 1676 "y.tab.c"
    break;

  case 57:
#line 258 "jason.ypp"
                         { yylhs.value = yystack_[0].value; }
#line 1682 "y.tab.c"
    break;

  case 58:
#line 259 "jason.ypp"
                        { yylhs.value = yystack_[0].value; }
#line 1688 "y.tab.c"
    break;

  case 59:
#line 260 "jason.ypp"
                          { yylhs.value = yystack_[0].value; }
#line 1694 "y.tab.c"
    break;

  case 60:
#line 263 "jason.ypp"
                               {
    yylhs.value = std::make_shared<AssignAST>(std::move(yystack_[3].value), std::move(yystack_[1].value));
}
#line 1702 "y.tab.c"
    break;

  case 61:
#line 268 "jason.ypp"
                   {
    yylhs.value = std::make_shared<ExpAST>(nullptr);
}
#line 1710 "y.tab.c"
    break;

  case 62:
#line 271 "jason.ypp"
                       {
    yylhs.value = std::make_shared<ExpAST>(std::move(yystack_[1].value));
}
#line 1718 "y.tab.c"
    break;

  case 63:
#line 276 "jason.ypp"
                                           {
    yylhs.value = std::make_shared<IfAST>(std::move(yystack_[2].value), std::move(yystack_[0].value), nullptr);
}
#line 1726 "y.tab.c"
    break;

  case 64:
#line 279 "jason.ypp"
                                                     {
    yylhs.value = std::make_shared<IfAST>(std::move(yystack_[4].value), std::move(yystack_[2].value), std::move(yystack_[0].value));
}
#line 1734 "y.tab.c"
    break;

  case 65:
#line 284 "jason.ypp"
                                              {
    yylhs.value = std::make_shared<WhileAST>(std::move(yystack_[2].value), std::move(yystack_[0].value));
}
#line 1742 "y.tab.c"
    break;

  case 66:
#line 289 "jason.ypp"
                         {
    yylhs.value = std::make_shared<CondAST>(BREAK);
}
#line 1750 "y.tab.c"
    break;

  case 67:
#line 292 "jason.ypp"
                            {
    yylhs.value = std::make_shared<CondAST>(CONTINUE);
}
#line 1758 "y.tab.c"
    break;

  case 68:
#line 297 "jason.ypp"
                          {
    yylhs.value = std::make_shared<ReturnAST>(nullptr);
}
#line 1766 "y.tab.c"
    break;

  case 69:
#line 300 "jason.ypp"
                              {
    yylhs.value = std::make_shared<ReturnAST>(std::move(yystack_[2].value));
}
#line 1774 "y.tab.c"
    break;

  case 70:
#line 305 "jason.ypp"
                     { yylhs.value = yystack_[0].value; }
#line 1780 "y.tab.c"
    break;

  case 71:
#line 308 "jason.ypp"
                     { yylhs.value = yystack_[0].value; }
#line 1786 "y.tab.c"
    break;

  case 72:
#line 311 "jason.ypp"
                    { yylhs.value = yystack_[0].value }
#line 1792 "y.tab.c"
    break;

  case 73:
#line 312 "jason.ypp"
                              {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[1].value); 
                yylhs.value = std::make_shared<ArrayAST>(p_IdAST.id(), std::move(yystack_[0].value));
            }
#line 1801 "y.tab.c"
    break;

  case 74:
#line 318 "jason.ypp"
                                  { yylhs.value = yystack_[1].value; }
#line 1807 "y.tab.c"
    break;

  case 75:
#line 319 "jason.ypp"
                   { yylhs.value = yystack_[0].value}
#line 1813 "y.tab.c"
    break;

  case 76:
#line 320 "jason.ypp"
                      {
                yylhs.value = std::make_shared<IntAST>(atoi(yytext));
                #ifdef DEBUG
                    printf("%d\n", atoi(yytext));
                #endif 
            }
#line 1824 "y.tab.c"
    break;

  case 77:
#line 326 "jason.ypp"
                      {
                yylhs.value = std::make_shared<IntAST>(strtol(yytext, NULL, 8));
                #ifdef DEBUG
                    printf("%d\n", strtol(yytext, NULL, 8));
                #endif
            }
#line 1835 "y.tab.c"
    break;

  case 78:
#line 332 "jason.ypp"
                      {
                yylhs.value = std::make_shared<IntAST>(strtol(yytext, NULL, 16));
                #ifdef DEBUG
                    printf("%d\n", strtol(yytext, NULL, 16));
                #endif
            }
#line 1846 "y.tab.c"
    break;

  case 79:
#line 340 "jason.ypp"
                         { yylhs.value = yystack_[0].value; }
#line 1852 "y.tab.c"
    break;

  case 80:
#line 341 "jason.ypp"
                          { yylhs.value = yystack_[0].value; }
#line 1858 "y.tab.c"
    break;

  case 81:
#line 342 "jason.ypp"
                            {
                yylhs.value = std::make_shared<UnaryAST>(PLUS, std::move(yystack_[0].value));
            }
#line 1866 "y.tab.c"
    break;

  case 82:
#line 345 "jason.ypp"
                             {
                yylhs.value = std::make_shared<UnaryAST>(MINUS, std::move(yystack_[0].value));
            }
#line 1874 "y.tab.c"
    break;

  case 83:
#line 348 "jason.ypp"
                           {
                yylhs.value = std::make_shared<UnaryAST>(NOT, std::move(yystack_[0].value));
            }
#line 1882 "y.tab.c"
    break;

  case 84:
#line 353 "jason.ypp"
                                    {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[2].value);
                yylhs.value = std::make_shared<FuncCallAST>(p_IdAST.id(), nullptr); 
            }
#line 1891 "y.tab.c"
    break;

  case 85:
#line 357 "jason.ypp"
                                                {
                auto p_IdAST = std::dynamic_pointer_cast<IdAST>(yystack_[3].value);
                yylhs.value = std::make_shared<FuncCallAST>(p_IdAST.id(), std::move(yystack_[1].value)); 
            }
#line 1900 "y.tab.c"
    break;

  case 86:
#line 363 "jason.ypp"
                  {
    ASTPtrList exprs;
    exprs.push_back(std::move(yystack_[0].value));
    yylhs.value = std::make_shared<FuncRParamsAST>(std::move(exprs));
}
#line 1910 "y.tab.c"
    break;

  case 87:
#line 368 "jason.ypp"
                                    {
    auto p_FuncRParams = std::dynamic_pointer_cast<FuncRParamsAST>(yystack_[2].value);
    p_FuncRParams.exprs().push_back(std::move(yystack_[0].value));
    yylhs.value = p_FuncRParams;
}
#line 1920 "y.tab.c"
    break;

  case 88:
#line 376 "jason.ypp"
                       { yylhs.value = yystack_[0].value; }
#line 1926 "y.tab.c"
    break;

  case 89:
#line 377 "jason.ypp"
                                    {
                yylhs.value = std::make_shared<BinaryAST>(TIMES,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 1935 "y.tab.c"
    break;

  case 90:
#line 381 "jason.ypp"
                                   {
                yylhs.value = std::make_shared<BinaryAST>(OVER,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 1944 "y.tab.c"
    break;

  case 91:
#line 385 "jason.ypp"
                                  {
                yylhs.value = std::make_shared<BinaryAST>(MOD,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 1953 "y.tab.c"
    break;

  case 92:
#line 391 "jason.ypp"
                     { yylhs.value = yystack_[0].value }
#line 1959 "y.tab.c"
    break;

  case 93:
#line 392 "jason.ypp"
                                 {
                yylhs.value = std::make_shared<BinaryAST>(PLUS,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 1968 "y.tab.c"
    break;

  case 94:
#line 396 "jason.ypp"
                                  {
                yylhs.value = std::make_shared<BinaryAST>(MINUS,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 1977 "y.tab.c"
    break;

  case 95:
#line 402 "jason.ypp"
                     { yylhs.value = yystack_[0].value; }
#line 1983 "y.tab.c"
    break;

  case 96:
#line 403 "jason.ypp"
                               {
                yylhs.value = std::make_shared<BinaryAST>(LT,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 1992 "y.tab.c"
    break;

  case 97:
#line 407 "jason.ypp"
                               {
                yylhs.value = std::make_shared<BinaryAST>(GT,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 2001 "y.tab.c"
    break;

  case 98:
#line 411 "jason.ypp"
                                {
                yylhs.value = std::make_shared<BinaryAST>(LTE,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 2010 "y.tab.c"
    break;

  case 99:
#line 415 "jason.ypp"
                                {
                yylhs.value = std::make_shared<BinaryAST>(GTE,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 2019 "y.tab.c"
    break;

  case 100:
#line 421 "jason.ypp"
                     { yylhs.value = yystack_[0].value; }
#line 2025 "y.tab.c"
    break;

  case 101:
#line 422 "jason.ypp"
                              {
                yylhs.value = std::make_shared<BinaryAST>(EQ,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 2034 "y.tab.c"
    break;

  case 102:
#line 426 "jason.ypp"
                               {
                yylhs.value = std::make_shared<BinaryAST>(NEQ,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 2043 "y.tab.c"
    break;

  case 103:
#line 432 "jason.ypp"
                    { yylhs.value = yystack_[0].value; }
#line 2049 "y.tab.c"
    break;

  case 104:
#line 433 "jason.ypp"
                                {
                yylhs.value = std::make_shared<BinaryAST>(AND,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 2058 "y.tab.c"
    break;

  case 105:
#line 438 "jason.ypp"
                      { yylhs.value = yystack_[0].value; }
#line 2064 "y.tab.c"
    break;

  case 106:
#line 439 "jason.ypp"
                                {
                yylhs.value = std::make_shared<BinaryAST>(OR,
                std::move(yystack_[2].value), std::move(yystack_[0].value));
            }
#line 2073 "y.tab.c"
    break;

  case 107:
#line 444 "jason.ypp"
                {
    yylhs.value = std::make_unique<IdAST>(yytext);
}
#line 2081 "y.tab.c"
    break;


#line 2085 "y.tab.c"

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
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


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

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


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
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const short parser::yypact_ninf_ = -140;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      81,     9,    23,    23,    49,    81,  -140,  -140,  -140,  -140,
      23,  -140,    47,  -140,    53,    62,  -140,  -140,  -140,    64,
    -140,    -1,  -140,    23,   274,    -2,   217,    30,     5,  -140,
      23,   232,    37,  -140,    54,  -140,  -140,  -140,   274,   274,
     274,   274,    90,  -140,  -140,  -140,  -140,    67,    76,    -5,
      23,    97,     3,  -140,  -140,  -140,   187,  -140,  -140,  -140,
    -140,   274,   217,    97,    14,  -140,   202,  -140,  -140,  -140,
    -140,   232,    98,  -140,  -140,  -140,  -140,   274,   274,   274,
     274,   274,   246,   103,   111,   121,  -140,  -140,   127,    97,
    -140,  -140,    68,   117,  -140,  -140,    97,  -140,    86,  -140,
    -140,  -140,  -140,  -140,    67,    67,  -140,  -140,    29,   120,
     122,   124,   126,   131,   260,    23,  -140,  -140,  -140,   150,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,   132,   125,
    -140,  -140,   217,  -140,  -140,  -140,   232,  -140,   274,  -140,
     129,   274,   274,  -140,  -140,  -140,   144,  -140,  -140,  -140,
     274,  -140,  -140,  -140,   103,   142,    76,    66,    28,   134,
     130,   148,  -140,   159,   172,   274,   274,   274,   274,   274,
     274,   274,   274,   172,  -140,   177,    76,    76,    76,    76,
      66,    66,    28,   134,  -140,   172,  -140
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     2,     3,     7,     8,     4,
       0,   107,     0,    24,    26,     0,     1,     5,     6,     0,
      10,     0,    23,     0,     0,     0,     0,    28,     0,     9,
       0,     0,     0,    25,    26,    76,    77,    78,     0,     0,
       0,     0,     0,    75,    79,    88,    80,    92,    70,    72,
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
    -140,  -140,  -140,    79,  -140,  -140,   161,   -20,   -58,  -140,
     -21,  -140,  -140,  -140,   166,   -44,  -140,  -140,   188,   167,
     106,  -140,  -140,   -36,  -140,    78,  -139,  -140,  -140,  -140,
    -140,  -140,  -140,   -24,    57,   -79,  -140,    22,  -140,  -140,
      38,   -98,   -48,    33,    40,  -140,     1
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
      42,    32,    60,    14,    15,    57,   129,    70,    97,    50,
      69,    21,    91,    99,    72,    87,    50,    24,    94,    82,
      10,    24,    88,    51,    34,   175,    31,    95,    89,    83,
      63,    21,    60,    88,   184,    57,    11,    93,    60,    96,
     129,    57,    70,   156,   156,    69,   186,    70,   138,    16,
      69,    84,    61,   131,   139,   169,   170,    62,   107,    61,
     135,    73,    74,    75,    71,    22,    23,   176,   177,   178,
     179,   156,   156,   156,   156,    24,    24,    25,   152,     6,
      26,    26,    29,    30,    17,   129,    28,   132,   151,   133,
     146,     1,     2,     3,   129,   165,   166,   167,   168,   101,
     102,   103,    77,    78,    79,   136,   129,   137,    60,    80,
      81,    57,    70,    76,   153,    69,    34,    85,   104,   105,
     154,   180,   181,   100,   110,    61,   163,   111,   112,   113,
     114,     1,   115,   109,    11,    35,    36,    37,    50,   116,
     134,    85,    90,   140,   143,    38,   141,    39,   142,   144,
     149,    24,   150,   110,    40,    41,   111,   112,   113,   114,
       1,   115,   162,    11,    35,    36,    37,   164,   116,   172,
      85,   147,   171,   173,    38,   110,    39,   174,   111,   112,
     113,   114,   185,    40,    41,    11,    35,    36,    37,    33,
     116,    65,    85,    18,   130,    64,    38,   148,    39,   161,
      11,    35,    36,    37,   182,    40,    41,    56,    90,     0,
       0,    38,   183,    39,     0,    11,    35,    36,    37,     0,
      40,    41,    66,    90,     0,     0,    38,     0,    39,     0,
      11,    35,    36,    37,     0,    40,    41,    56,     0,     0,
       0,    38,     0,    39,     0,    11,    35,    36,    37,     0,
      40,    41,    66,     0,     0,     0,    38,     0,    39,    11,
      35,    36,    37,     0,     0,    40,    41,     0,     0,     0,
      38,   106,    39,    11,    35,    36,    37,     0,   145,    40,
      41,     0,     0,     0,    38,     0,    39,    11,    35,    36,
      37,     0,     0,    40,    41,     0,     0,     0,    38,     0,
      39,     0,     0,     0,     0,     0,     0,    40,    41
  };

  const short
  parser::yycheck_[] =
  {
      24,    21,    26,     2,     3,    26,    85,    31,    66,    11,
      31,    10,    56,    71,    38,    51,    11,    22,    62,    24,
      11,    22,    19,    25,    23,   164,    27,    63,    25,    49,
      25,    30,    56,    19,   173,    56,    13,    61,    62,    25,
     119,    62,    66,   141,   142,    66,   185,    71,    19,     0,
      71,    50,    22,    89,    25,    27,    28,    27,    82,    22,
      96,    39,    40,    41,    27,    18,    19,   165,   166,   167,
     168,   169,   170,   171,   172,    22,    22,    24,   136,     0,
      27,    27,    18,    19,     5,   164,    24,    19,   132,    21,
     114,    10,    11,    12,   173,    29,    30,    31,    32,    77,
      78,    79,    35,    36,    37,    19,   185,    21,   132,    33,
      34,   132,   136,    23,   138,   136,   115,    20,    80,    81,
     140,   169,   170,    25,     3,    22,   150,     6,     7,     8,
       9,    10,    11,    22,    13,    14,    15,    16,    11,    18,
      23,    20,    21,    23,    18,    24,    24,    26,    24,    18,
      18,    22,    27,     3,    33,    34,     6,     7,     8,     9,
      10,    11,    18,    13,    14,    15,    16,    25,    18,    39,
      20,    21,    38,    25,    24,     3,    26,    18,     6,     7,
       8,     9,     5,    33,    34,    13,    14,    15,    16,    23,
      18,    30,    20,     5,    88,    28,    24,   119,    26,   142,
      13,    14,    15,    16,   171,    33,    34,    20,    21,    -1,
      -1,    24,   172,    26,    -1,    13,    14,    15,    16,    -1,
      33,    34,    20,    21,    -1,    -1,    24,    -1,    26,    -1,
      13,    14,    15,    16,    -1,    33,    34,    20,    -1,    -1,
      -1,    24,    -1,    26,    -1,    13,    14,    15,    16,    -1,
      33,    34,    20,    -1,    -1,    -1,    24,    -1,    26,    13,
      14,    15,    16,    -1,    -1,    33,    34,    -1,    -1,    -1,
      24,    25,    26,    13,    14,    15,    16,    -1,    18,    33,
      34,    -1,    -1,    -1,    24,    -1,    26,    13,    14,    15,
      16,    -1,    -1,    33,    34,    -1,    -1,    -1,    24,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34
  };

  const signed char
  parser::yystos_[] =
  {
       0,    10,    11,    12,    42,    43,    44,    45,    53,    59,
      11,    13,    54,    55,    87,    87,     0,    44,    59,    46,
      47,    87,    18,    19,    22,    24,    27,    48,    24,    18,
      19,    27,    48,    55,    87,    14,    15,    16,    24,    26,
      33,    34,    74,    76,    77,    78,    79,    81,    82,    87,
      11,    25,    60,    61,    62,    63,    20,    51,    56,    57,
      74,    22,    27,    25,    60,    47,    20,    49,    50,    51,
      74,    27,    74,    78,    78,    78,    23,    35,    36,    37,
      33,    34,    24,    48,    87,    20,    51,    64,    19,    25,
      21,    56,    58,    74,    56,    64,    25,    49,    52,    49,
      25,    78,    78,    78,    81,    81,    25,    74,    80,    22,
       3,     6,     7,     8,     9,    11,    18,    44,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    76,
      61,    64,    19,    21,    23,    64,    19,    21,    19,    25,
      23,    24,    24,    18,    18,    18,    74,    21,    66,    18,
      27,    56,    49,    74,    48,    75,    82,    83,    84,    85,
      86,    75,    18,    74,    25,    29,    30,    31,    32,    27,
      28,    38,    39,    25,    18,    67,    82,    82,    82,    82,
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


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "IF", "THEN", "ELSE", "WHILE", "BREAK",
  "CONTINUE", "RETURN", "CONST", "INT", "VOID", "ID", "DEC_NUM", "OCT_NUM",
  "HEX_NUM", "ASSIGN", "SEMI", "COMMA", "LLPAREN", "LRPAREN", "MLPAREN",
  "MRPAREN", "SLPAREN", "SRPAREN", "NOT", "EQ", "NEQ", "LT", "GT", "LTE",
  "GTE", "PLUS", "MINUS", "TIMES", "OVER", "MOD", "AND", "OR", "ERROR",
  "$accept", "program", "CompUnit", "Decl", "ConstDecl", "ConstDefList",
  "ConstDef", "Dimension", "ConstInitVal", "ConstInitValArray", "EMPTY",
  "ConstInitValList", "VarDecl", "VarDefList", "VarDef", "InitVal",
  "InitValArray", "InitValList", "FuncDef", "FuncFParams", "FuncFParam",
  "FuncFParamVar", "FuncFParamArray", "Block", "BlockItems", "BlockItem",
  "Stmt", "Assign_stmt", "Exp_stmt", "If_stmt", "While_stmt", "Cond_stmt",
  "Return_stmt", "Exp", "Cond", "LVal", "PrimaryExp", "UnaryExp",
  "FuncCallExp", "FuncRParams", "MulExp", "AddExp", "RelExp", "EqExp",
  "LAndExp", "LOrExp", "IDENT", YY_NULLPTR
  };


  const short
  parser::yyrline_[] =
  {
       0,    25,    25,    27,    31,    35,    40,    47,    48,    51,
      55,    60,    67,    71,    77,    82,    89,    90,    93,    96,
     101,   104,   109,   116,   121,   126,   133,   137,   141,   145,
     151,   152,   155,   158,   163,   168,   175,   179,   183,   187,
     193,   198,   206,   207,   210,   216,   220,   226,   229,   234,
     239,   246,   249,   254,   255,   256,   257,   258,   259,   260,
     263,   268,   271,   276,   279,   284,   289,   292,   297,   300,
     305,   308,   311,   312,   318,   319,   320,   326,   332,   340,
     341,   342,   345,   348,   353,   357,   363,   368,   376,   377,
     381,   385,   391,   392,   396,   402,   403,   407,   411,   415,
     421,   422,   426,   432,   433,   438,   439,   444
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

  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
    };
    const int user_token_number_max_ = 295;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

} // yy
#line 2582 "y.tab.c"

#line 449 "jason.ypp"

