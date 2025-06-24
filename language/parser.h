// =====
// Language parser
// =====
#ifndef __LANGUAGE_PARSER_H
#define __LANGUAGE_PARSER_H

#include "lexer.h"
#include "ast.h"
#include <iostream>

namespace language
{

template< typename T >
std::unique_ptr< T > logError( const std::string& errorMessage ) 
{
  std::cerr << "Error: " << errorMessage << std::endl;
  return nullptr;
}

class parser
{
public:
  parser() = default;
private:
  std::unique_ptr< ExprAST > parseNumberExpr() {
    auto res = std::make_unique< NumberExprAST >( 
      std::get<double>(mLex.getToken().value) );
    mLex.getNextToken();
    return res;
  }

  std::unique_ptr< ExprAST > parseParenExpr() {
    mLex.getNextToken();
    auto expr = parseExpression();
    if(!expr){
      return nullptr;
    }

    // TODO we want an "expect" function that will wrap "consumption" with an error report
    if(mLex.getToken().type != TokenId::RPAREN){
      logError<ExprAST>("expected ')'");
    }
    mLex.getNextToken();

    return expr;
  }

  std::unique_ptr< ExprAST > parseIdentifierExpr() {
    std::string id = std::get<std::string>( mLex.getToken().value );
    mLex.getNextToken();

    if(mLex.getToken().type != TokenId::LPAREN) {
      return std::make_unique< VariableExprAST >(id); // simple
    }

    // call a function
    mLex.getNextToken();
    std::vector<std::unique_ptr<ExprAST>> args;
    if(mLex.getToken().type != TokenId::RPAREN) {
      // parse a list of arguments
      // please fix this so the control flow is easier to understand
      while(true) {
        if(auto arg = parseExpression())
          args.push_back(std::move(arg));
        else
          return nullptr;
        if(mLex.getToken().type == TokenId::RPAREN)
        if(mLex.getToken().type != TokenId::COMMA) {
          return logError<CallExprAST>("Expected ')' or ',' in argument list");
        }
        mLex.getNextToken();
      }
    }
    mLex.getNextToken(); // consume the RPAREN

    return std::make_unique<CallExprAST>(id, std::move(args));
  }

  std::unique_ptr<ExprAST> parsePrimary() {
    std::unique_ptr<ExprAST> expr;
    switch(mLex.getToken().type)
    {
      case TokenId::IDENTIFIER: 
      {
        expr = parseIdentifierExpr();
      } break;
      case TokenId::NUMBER:
      {
        expr = parseNumberExpr();
      } break;
      case TokenId::RPAREN:
      {
        expr = parseParenExpr();
      } break;
      default:
      {
        expr = logError<ExprAST>("unknown token when expecting an expression");;
      } break;
    }

    return expr;
  }

  std::unique_ptr<ExprAST> parseExpression() {
    // TODO
    return nullptr; 
  }

private:
  lexer mLex; // feel free to rename it :)
};

};

#endif