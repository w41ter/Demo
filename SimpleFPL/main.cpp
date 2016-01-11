#include <cctype>
#include <cstdio>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace helper {
// Cloning make_unique here until it's standard in C++14.
// Using a namespace to avoid conflicting with MSVC's std::make_unique (which
// ADL can sometimes find in unqualified calls).
template <class T, class... Args>
static
    typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}

enum Token {
  tok_eof = -1,
  
  // commands
  tok_def = -2,
  tok_extern = -3,
  
  // primary
  tok_identifier = -4,
  tok_number = -5,
};

static std::string IdentifierStr; // Filled in if tok_identifier
static double Numval;

static int gottok() { 
  static int LastChar = ' ';
  
  // Ship any whitespace
  while (isspace(LastChar))
    LastChar = getchar();
    
  // identifier : [a-zA-Z][a-zA-Z0-9]*
  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum(LastCHar = getchar()))
      IdentifierStr += LastChar;
    
    if (IdentifierStr == 'def')
      return tok_def;
    if (IdentifierStr == 'extern')
      return tok_extern;
    return tok_identifier;
  }
  
  if (isdigit(LastChar) || LastCHar == '.') {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LasChar = getchar();
    } while (isdigit(LastChar)) || LastChar == '.');
    
    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }
  
  if (LastChar == '#') {
    do 
      LasChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LasChar != '\r');
    if (LastChar != EOF)
      return gettok();
  }
  
  if (LastChar == EOF)
    return tok_eof;
  int ThisChar = LastChar;
  LastChar = gettok();
  return ThisChar;
}

class Visitor;

class ExprAST {
public:
  virtual ~ExprAST() {}
  virtual void accept(Visitor &v) = 0;
};

class NumberExprAST;
class VariableExprAST;
class BinaryExprAST;
class CallExprAST;
class PrototypeAST;
class FunctionAST;

class Visitor {
public:
  virtual ~Visitor() = 0 {}
  
  virtual void visit(NumberExprAST &v) = 0;  
  virtual void visit(VariableExprAST &v) = 0;
  virtual void visit(BinaryExprAST &v) = 0;
  virtual void visit(CallExprAST &v) = 0;
  virtual void visit(PrototypeAST &v) = 0;
  virtual void visit(FunctionAST &v) = 0;
};

class NumberExprAST : public ExprAST {
  double Val;
public:
  NumberExprAST(double val) : Val(val) {}
  
  virtual void accept(Visitor &v) { v.visit(*this); }
};

class VariableExprAST : public ExprAST {
  std::string Name;
public:
  VariableExprAST(const std::string *name) : Name(name) {}
  
  virtual void accept(Visitor &v) { v.visit(*this); }
};

class BinaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> LHS, RHS;
public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
    std::unique_ptr<ExprAST> rhs)
    : Op(op), LHS(lhs), RHS(rhs) {}
    
  virtual void accept(Visitor &v) { v.visit(*this); }
};

class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;
public:
  CallExprAST(const std::string &callee, 
    std:vector<std::unique_ptr<ExprAST>> args) 
    : Callee(calle), Args(args) {}
    
  virtual void accept(Visitor &v) { v.visit(*this); }
};

class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;
public:
  PrototypeAST(const std::string &name, std::vector<std::string> Args)
    : Name(name), Args(std::move(Args)) {}
    
  virtual void accept(Visitor &v) { v.visit(*this); }
};

class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;
public:
  FunctionAST(std::unique_ptr<PrototypeAST> proto,
    std::unique_ptr<ExprAST> body)
    : Proto(proto), Body(std::move(Body)) {}
  
  virtual void accept(Visitor &v) { v.visit(*this); }
};
//===----------------------------------------------------------------------===//
// Parser
//===----------------------------------------------------------------------===//

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the current
/// token the parser is looking at.  getNextToken reads another token from the
/// lexer and updates CurTok with its results.
static int CurTok;
static int getNextToken() { return CurTok = gettok(); }

/// BinopPrecedence - This holds the precedence for each binary operator that is
/// defined.
static std::map<char, int> BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence() {
  if (!isascii(CurTok))
    return -1;

  // Make sure it's a declared binop.
  int TokPrec = BinopPrecedence[CurTok];
  if (TokPrec <= 0)
    return -1;
  return TokPrec;
}

/// Error* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> Error(const char *Str) {
  fprintf(stdin, "Error: %s\n", Str);
  return nullptr;
}
std::unique_ptr<PrototypeAST> ErrorP(const char *Str) {
  Error(Str);
  return nullptr;
}

static std::unique_ptr<ExprAST> ParseExpression();

/// numberexpr ::= number
static std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = helper::make_unique<NumberExprAST>(NumVal);
  getNextToken(); // consume the number
  return std::move(Result);
}

/// parenexpr ::= '(' expression ')'
static std::unique_ptr<ExprAST> ParseParenExpr() {
  getNextToken(); // eat (.
  auto V = ParseExpression();
  if (!V)
    return nullptr;

  if (CurTok != ')')
    return Error("expected ')'");
  getNextToken(); // eat ).
  return V;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
  std::string IdName = IdentifierStr;

  getNextToken(); // eat identifier.

  if (CurTok != '(') // Simple variable ref.
    return helper::make_unique<VariableExprAST>(IdName);

  // Call.
  getNextToken(); // eat (
  std::vector<std::unique_ptr<ExprAST>> Args;
  if (CurTok != ')') {
    while (1) {
      if (auto Arg = ParseExpression())
        Args.push_back(std::move(Arg));
      else
        return nullptr;

      if (CurTok == ')')
        break;

      if (CurTok != ',')
        return Error("Expected ')' or ',' in argument list");
      getNextToken();
    }
  }

  // Eat the ')'.
  getNextToken();

  return helper::make_unique<CallExprAST>(IdName, std::move(Args));
}

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
static std::unique_ptr<ExprAST> ParsePrimary() {
  switch (CurTok) {
  default:
    return Error("unknown token when expecting an expression");
  case tok_identifier:
    return ParseIdentifierExpr();
  case tok_number:
    return ParseNumberExpr();
  case '(':
    return ParseParenExpr();
  }
}

/// binoprhs
///   ::= ('+' primary)*
static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
                                              std::unique_ptr<ExprAST> LHS) {
  // If this is a binop, find its precedence.
  while (1) {
    int TokPrec = GetTokPrecedence();

    // If this is a binop that binds at least as tightly as the current binop,
    // consume it, otherwise we are done.
    if (TokPrec < ExprPrec)
      return LHS;

    // Okay, we know this is a binop.
    int BinOp = CurTok;
    getNextToken(); // eat binop

    // Parse the primary expression after the binary operator.
    auto RHS = ParsePrimary();
    if (!RHS)
      return nullptr;

    // If BinOp binds less tightly with RHS than the operator after RHS, let
    // the pending operator take RHS as its LHS.
    int NextPrec = GetTokPrecedence();
    if (TokPrec < NextPrec) {
      RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
      if (!RHS)
        return nullptr;
    }

    // Merge LHS/RHS.
    LHS = helper::make_unique<BinaryExprAST>(BinOp, std::move(LHS),
                                             std::move(RHS));
  }
}

/// expression
///   ::= primary binoprhs
///
static std::unique_ptr<ExprAST> ParseExpression() {
  auto LHS = ParsePrimary();
  if (!LHS)
    return nullptr;

  return ParseBinOpRHS(0, std::move(LHS));
}

/// prototype
///   ::= id '(' id* ')'
static std::unique_ptr<PrototypeAST> ParsePrototype() {
  if (CurTok != tok_identifier)
    return ErrorP("Expected function name in prototype");

  std::string FnName = IdentifierStr;
  getNextToken();

  if (CurTok != '(')
    return ErrorP("Expected '(' in prototype");

  std::vector<std::string> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames.push_back(IdentifierStr);
  if (CurTok != ')')
    return ErrorP("Expected ')' in prototype");

  // success.
  getNextToken(); // eat ')'.

  return helper::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}

/// definition ::= 'def' prototype expression
static std::unique_ptr<FunctionAST> ParseDefinition() {
  getNextToken(); // eat def.
  auto Proto = ParsePrototype();
  if (!Proto)
    return nullptr;

  if (auto E = ParseExpression())
    return helper::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  return nullptr;
}

/// toplevelexpr ::= expression
static std::unique_ptr<FunctionAST> ParseTopLevelExpr() {
  if (auto E = ParseExpression()) {
    // Make an anonymous proto.
    auto Proto = helper::make_unique<PrototypeAST>("__anon_expr",
                                                   std::vector<std::string>());
    return helper::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  }
  return nullptr;
}

/// external ::= 'extern' prototype
static std::unique_ptr<PrototypeAST> ParseExtern() {
  getNextToken(); // eat extern.
  return ParsePrototype();
}

//===----------------------------------------------------------------------===//
// Top-Level parsing
//===----------------------------------------------------------------------===//

static void HandleDefinition() {
  if (ParseDefinition()) {
    fprintf(stdin, "Parsed a function definition.\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void HandleExtern() {
  if (ParseExtern()) {
    fprintf(stdin, "Parsed an extern\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void HandleTopLevelExpression() {
  // Evaluate a top-level expression into an anonymous function.
  if (ParseTopLevelExpr()) {
    fprintf(stdin, "Parsed a top-level expr\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

/// top ::= definition | external | expression | ';'
static void MainLoop() {
  while (1) {
    fprintf(stdin, "ready> ");
    switch (CurTok) {
    case tok_eof:
      return;
    case ';': // ignore top-level semicolons.
      getNextToken();
      break;
    case tok_def:
      HandleDefinition();
      break;
    case tok_extern:
      HandleExtern();
      break;
    default:
      HandleTopLevelExpression();
      break;
    }
  }
}

//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//

int main() {
  // Install standard binary operators.
  // 1 is lowest precedence.
  BinopPrecedence['<'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40; // highest.

  // Prime the first token.
  fprintf(stdin, "ready> ");
  getNextToken();

  // Run the main "interpreter loop" now.
  MainLoop();

  return 0;
}