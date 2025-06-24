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

enum class Operator: u8 {
  nop = 0,
  plus,
  sub,
  mult,
  div,
};

bool isOperator( char c ) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

enum class TokenId: u8 {
  END_OF_FILE = 0,

  // commands
  DEF,
  EXTERN,

  // secondary
  OPERATOR,
  LPAREN,
  RPAREN,
  COMMA,

  // primary
  IDENTIFIER,
  NUMBER,
};

// Use this function as a wrapper around std::variant::index() for checking what value a token holds.
// Ideally the value of a token is always apart of the token so this is unnecessary, 
// but just in case this will keep the code a little cleaner.
template<TokenId primary>
inline bool isPrimary(const std::variant<std::string, double>& value) {
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