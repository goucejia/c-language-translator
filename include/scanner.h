/*******************************************************************************
 * Name            : scanner.h
 * Project         : fcal
 * Module          : scanner
 * Description     : Header file for scanner module
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell, Son Nguyen, Yu Fang
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_SCANNER_H_
#define PROJECT_INCLUDE_SCANNER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <regex.h>
#include <string>
#include "./regex.h"
// #include "token.h"



/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

class Scanner;

/* below are the possible terminal types for each token */

enum kTokenEnumType {
    /*0*/kIntKwd,
    kFloatKwd,
    kBoolKwd,
    kTrueKwd,
    kFalseKwd,
    kStringKwd,
    kMatrixKwd,
    kLetKwd,
    kInKwd,
    kEndKwd,
    /*10*/kIfKwd,
    kThenKwd,
    kElseKwd,
    kRepeatKwd,
    kWhileKwd,
    kPrintKwd,
    kToKwd,

    // Constants
    kIntConst,
    kFloatConst,
    kStringConst,

    // Names
    /*20*/kVariableName,

    // Punctuation
    kLeftParen,
    kRightParen,
    kLeftCurly,
    kRightCurly,
    kLeftSquare,
    kRightSquare,
    kSemiColon,
    kColon,

    // Operators
    kAssign,
    /*30*/kPlusSign,
    kStar,
    kDash,
    kForwardSlash,
    kLessThan,
    kLessThanEqual,
    kGreaterThan,
    kGreaterThanEqual,
    kEqualsEquals,
    kNotEquals,
    /*40*/kAndOp,
    kOrOp,
    kNotOp,

    // Special terminal types
    kEndOfFile,
    kLexicalError
};


  typedef enum kTokenEnumType TokenType;

  typedef struct Result {
      int length;
      TokenType type;
  } Result;

/*******************************************************************************
 * Class Definitions
 *
 * You will need to define a Token class (remember, a pointer of type Token *
 * is returned by the scan method of the scanner class.)
 * Also, Classes are typically declared (and sometimes also defined) in
 * their own header files
 *
 * You will also need to define a Scanner class with a scan and other methods
 ******************************************************************************/

class Token {
 public:
    // constructors
    Token() {
        terminal_ = kEndOfFile;
        lexeme_ = "";
        next_ = NULL;
    }
    Token(TokenType tt, std :: string l, Token *t) {
        terminal_ = tt;
        lexeme_ = l;
        next_ = t;
    }
    Token(const char l[1], TokenType tt, Token *t) {
        terminal_ = tt;
        lexeme_ = l;
        next_ = t;
    }

    // getters and setters
    TokenType terminal() {
        return Token :: terminal_;
    }
    void set_terminal(TokenType tt) {
        terminal_ = tt;
    }

    std :: string lexeme() {
        return lexeme_;
    }
    void set_lexeme(std :: string l) {
        lexeme_ = l;
    }

    Token *next() {
        return next_;
    }
    void set_next(Token* t) {
        next_ = t;
    }

 private:
    TokenType terminal_;
    std :: string lexeme_;
    Token *next_;
};

class Scanner {
 public:
        Token *Scan(const char *);
        Result find_TokenType(const char *);
        Scanner() {
            init_regex();
        }
        regex_t *regexes[kLexicalError + 1];

        void init_regex();
};


} /* namespace scanner */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_SCANNER_H_
