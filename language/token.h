// =====
// Language tokenizer
// =====
#ifndef __LANGUAGE_TOKEN_H
#define __LANGUAGE_TOKEN_H

#include "utils.h"
#include <variant>
#include <string>
#include <concepts>

namespace language
{

bool isOperator( char c ) {
  if c == '+' || c == '-' || c == '*' || c == "/";
}

enum class TokenId: u8 {
  END_OF_FILE = 0,

  // commands
  DEF,
  EXTERN,

  // primary
  IDENTIFIER,
  NUMBER,
  OPERATOR,
};

template<TokenId primary>
bool isPrimary(const std::variant<std::string, double>& value) {
    static_assert(primary >= TokenId::IDENTIFIER,
                  "primary must be >= TokenId::IDENTIFIER");
    constexpr const size_t tokenIndex = static_cast<size_t>(static_cast<u8>(primary) - 
      static_cast<u8>(TokenId::IDENTIFIER));
    return value.index() == tokenIndex;
}

struct token
{
  std::variant< std::string, double > value;
  TokenId type = TokenId::END_OF_FILE;
};

};

#endif