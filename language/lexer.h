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
      tok.value = LastChar;
      while (std::isalnum((LastChar = std::getchar())))
        tok.value += LastChar;

      if (tok.value == "def")
        tok.type = TokenId::DEF;
      else if (tok.value == "extern")
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

      if (LastChar != EOF)
        return gettok();
    } else if (LastChar == EOF) {
      return TokenId::END_OF_FILE;
    } else if (isOperator( lastChar) ) {
      tok.type == TokenId::OPERATOR;
      tok.value = std::to_string(lastChar);
    }

    return tok;
  }
};

}

#endif