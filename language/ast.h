// =====
// Language abstract syntax tree
// =====
#ifndef __LANGUAGE_AST_H
#define __LANGUAGE_AST_H

#include "lexer.h"
#include <memory>
#include <vector>

namespace language
{

class ExprAST
{
public:
  ExprAST() = default;
  virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST 
{
public:
  NumberExprAST( const double val ) : val(val) {}
private:
  double val;
};

class VariableExprAST : public ExprAST
{
public:
  VariableExprAST( const std::string& name ) : name(name) {}
private:
  std::string name;
};

class BinaryExprAST : public ExprAST
{
public:
  BinaryExprAST( Operator op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs)
    : op(op), lhs( std::move(lhs) ), rhs( std::move(rhs) ) {}
private:
  Operator op;
  std::unique_ptr<ExprAST> lhs;
  std::unique_ptr<ExprAST> rhs;
};

class CallExprAST : public ExprAST
{
public:
  CallExprAST( const std::string& callee, std::vector<std::unique_ptr<ExprAST>> args)
    : callee(callee), args(std::move(args)) {}
private:
   std::string callee;
   std::vector<std::unique_ptr<ExprAST>> args;
};

class PrototypeAST
{
public:
  PrototypeAST( const std::string& name, std::vector< std::string > args )
    : name(name), args(args) {}

  const std::string& getName() const 
  {
    return name;
  }

  ~PrototypeAST() = default;

private:
  std::string name;
  std::vector< std::string > args;
};

class FunctionAST {
public:
  FunctionAST( std::unique_ptr< PrototypeAST > proto, std::unique_ptr< ExprAST > body)
    : proto(std::move(proto)), body(std::move(body)) {}

  ~FunctionAST() = default;

private:
  std::unique_ptr< PrototypeAST > proto;
  std::unique_ptr< ExprAST > body;

};

};

#endif