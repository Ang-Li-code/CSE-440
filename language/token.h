// =====
// Language tokenizer
// =====
#ifndef __LANGUAGE_TOKEN_H
#define __LANGUAGE_TOKEN_H

#include "utils.h"

namespace language
{

enum class token: int8 {
  tok_eof = 0,

  // commands
  tok_def,
  tok_extern,
  
  // primary
  tok_identifier,
  tok_number,
};

};

#endif