// =====
// Language lexer
// =====
#ifndef __LANGUAGE_LEXER_H
#define __LANGUAGE_LEXER_H

#include "token.h"

namespace language
{

class lexer
{
public:
  lexer() = default;

  token getToken() 
  {
    static int LastChar = ' ';
    token tok;

    // Skip any whitespace.
    while (std::isspace(LastChar)) {
      LastChar = getchar();
    }
    
    // identifier: [a-zA-Z][a-zA-Z0-9]*
    if (std::isalpha(LastChar)) 
    { 
      std::string identifier(1, LastChar);
      while (std::isalnum((LastChar = std::getchar()))) {
          identifier += LastChar;
      }
      tok.value = std::move(identifier);

      if (std::get<std::string>(tok.value) == "def")
        tok.type = TokenId::DEF;
      else if (std::get<std::string>(tok.value) == "extern")
        tok.type = TokenId::EXTERN;
      else 
        tok.type = TokenId::IDENTIFIER;
    } else if (std::isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+   
      std::string NumStr;
      do {
        NumStr += LastChar;
        LastChar = std::getchar();
      } while (std::isdigit(LastChar) || LastChar == '.');

      tok.value = strtod(NumStr.c_str(), 0);
      tok.type = TokenId::NUMBER;
    } else if (LastChar == '#') { // Comment until end of line.
      do {
        LastChar = getchar();
      } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
      
      // try grabbing the next token if it's not EOF
      if (LastChar != EOF)
        return getToken();
    } else if (isOperator( LastChar ) ) {
      tok.type = TokenId::OPERATOR;
      tok.value = std::to_string(LastChar);
    } else if (LastChar == EOF) {
      tok.type = TokenId::END_OF_FILE;
    }

    return tok;
  }
};

}

#endif