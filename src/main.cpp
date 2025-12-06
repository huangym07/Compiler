#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

//===----------------------------------------===//
// Lexer                                        //
//===----------------------------------------===//

// The lexer returns [0, 255] if it is unknown character, otherwise one of these
// for known things.
enum Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5
};

static std::string IdentifierStr; // Filled in if tok_identifier
static double NumVal;             // Filled in if tok_number

// gettok - Return the next token from standard input.
static int gettok() {
  static int LastChar = ' ';

  // Skip any whitespace
  while (std::isspace(LastChar))
    LastChar = std::getchar();

  if (std::isalpha(LastChar)) { // identifier: [a-zA-z][a-zA-Z0-9]+
    IdentifierStr = LastChar;
    while (std::isalnum(LastChar = std::getchar()))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  if (std::isdigit(LastChar) ||
      LastChar == '.') { // number: ([0-9]+(\.[0-9]*)?) | (\.[0-9]+)
    std::string Number{};

    if (std::isdigit(LastChar)) {
      Number += LastChar;
      while (std::isdigit(LastChar = std::getchar()))
        Number += LastChar;
    }
    if (LastChar == '.') {
      Number += LastChar;
      while (std::isdigit(LastChar = std::getchar()))
        Number += LastChar;
    }

    // Single "." is regarded as an unknown character.
    if (Number == ".")
      return '.';

    NumVal = std::strtod(Number.c_str(), 0);
    return tok_number;
  }

  if (LastChar == '#') {
    do
      LastChar = std::getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return gettok();
  }

  if (LastChar == EOF)
    return tok_eof;

  int ThisChar = LastChar;
  LastChar = std::getchar();
  return ThisChar;
}

static std::string toktostr(int tok) {
  switch (tok) {
  case tok_eof:
    return "EOF";

  // commands
  case tok_def:
    return "def";
  case tok_extern:
    return "extern";

  // primary
  case tok_identifier:
    return "identifier";
  case tok_number:
    return "number";

  default:
    return std::string{static_cast<char>(tok)};
  }
}

int main() {
  std::cout << "hello" << std::endl;

  int tok;
  do {
    tok = gettok();
    std::cout << toktostr(tok);
    if (tok == tok_identifier || tok == tok_def || tok == tok_extern) {
      std::cout << ": " << IdentifierStr;
    } else if (tok == tok_number) {
      std::cout << ": " << NumVal;
    }
    std::cout << std::endl;
  } while (tok != EOF);

  return 0;
}