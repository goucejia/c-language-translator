/*******************************************************************************
 * Name            : scanner.cc
 * Project         : fcal
 * Module          : scanner
 * Description     : This file provides the scan method for scanner
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Son Nguyen
 * Modifications by: Son Nguyen, Yu Fang
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <iostream>
#include "../include/regex.h"
#include "../include/scanner.h"
// #include "../include/token.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Functions
 ******************************************************************************/
  int string_not_equal(const char* l, const char* s, int count) {
    if (count != strlen(s))
        return 1;
    for (int i = 0; i < count; i++) {
        if (l[i] != s[i])
            return 1;
    }
    return 0;
  }

  int consume_whitespace_and_comments(regex_t *line_comment,
                                    regex_t *white_space,
                                    regex_t *block_comment,
                                    const char *text) {
    int num_matched_chars = 0;
    int total_num_matched_chars = 0;
    int still_consuming_white_space;

    do {
      still_consuming_white_space = 0;  //  exit loop if not reset by a match

      //  Try to match white space
      num_matched_chars = match_regex(white_space, text);
      total_num_matched_chars += num_matched_chars;
      if (num_matched_chars > 0) {
        text = text + num_matched_chars;
        still_consuming_white_space = 1;
      }

      //  Try to match block comments
      num_matched_chars = match_regex(block_comment, text);
      total_num_matched_chars += num_matched_chars;
      if (num_matched_chars > 0) {
        text = text + num_matched_chars;
        still_consuming_white_space = 1;
      }

      //  Try to match line comments
      num_matched_chars = match_regex(line_comment, text);
      total_num_matched_chars += num_matched_chars;
      if (num_matched_chars > 0) {
        text = text + num_matched_chars;
        still_consuming_white_space = 1;
      }
    } while (still_consuming_white_space);

    return total_num_matched_chars;
} /* consume_whitespace_and_comments() */


/*extract firts count chars of text*/
char * substring(const char* text, int count) {
    char *result = reinterpret_cast<char*>(malloc(strlen(text) + 1));
    if (count > strlen(text)) {
        result[0] = '\0';
        return result;
    }
    for (int i = 0; i < count; i++) {
        result[i] = text[i];
    }
    result[count] = '\0';
    return result;
}/*substring*/

/*Scan - return a list of Token */
Token *Scanner :: Scan(const char * text) {
    // init_regex();

    regex_t *white_space = new regex_t;
    white_space = make_regex("^[\n\t\r ]+");
    regex_t *block_comment = new regex_t;
    block_comment = make_regex("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
    regex_t *line_comment = new regex_t;
    line_comment = make_regex("^//[^\n]*\n");
    text += consume_whitespace_and_comments(line_comment,
                             white_space, block_comment, text);

    Token* result = new Token();
    Token* ptr = result;

    Result tem;
    while (strlen(text)) {
    Token *a = new Token();
        tem = find_TokenType(text);
        if (tem.type == kEndOfFile && strlen(text)) {
            ptr->set_terminal(kLexicalError);
            ptr->set_lexeme(substring(text, 1));
            ptr->set_next(a);
            text += 1;
            text += consume_whitespace_and_comments(line_comment, white_space,
                block_comment, text);
            ptr = ptr->next();
        } else {
            ptr->set_terminal(tem.type);
            ptr->set_lexeme(substring(text, tem.length));
            ptr->set_next(a);
            text = text + tem.length;
            text += consume_whitespace_and_comments(line_comment, white_space,
                block_comment, text);
            ptr = ptr->next();
        }
    }

    return result;
}/*Scan*/

/*find_TokenType - helper function for Scan - takes in a string text and return
a struct Result which has the length of the element and TokenType.
It will search until a match is found, if there is no match, return kEndOfFile.
It will not return kLexicalError, this error will be spotted in Scan */
Result Scanner :: find_TokenType(const char * text) {
    // init_regex();
    Result result;

    // Variable name
    if (match_regex(regexes[kVariableName], text)) {
        int count = match_regex(regexes[kVariableName], text);
        if (string_not_equal(text, "int", count) &&
            string_not_equal(text, "float", count) &&
            string_not_equal(text, "string", count) &&
            string_not_equal(text, "matrix", count) &&
            string_not_equal(text, "boolean", count) &&
            string_not_equal(text, "True", count) &&
            string_not_equal(text, "False", count) &&
            string_not_equal(text, "let", count) &&
            string_not_equal(text, "in", count) &&
            string_not_equal(text, "end", count) &&
            string_not_equal(text, "if", count) &&
            string_not_equal(text, "then", count) &&
            string_not_equal(text, "else", count) &&
            string_not_equal(text, "repeat", count) &&
            string_not_equal(text, "while", count) &&
            string_not_equal(text, "print", count) &&
            string_not_equal(text, "to", count) ) {
                result.length = match_regex(regexes[kVariableName], text);
                result.type = kVariableName;
                return result;
            }
    }

    // Keywords
    if (match_regex(regexes[kWhileKwd], text)) {
        result.length = match_regex(regexes[kWhileKwd], text);
        result.type = kWhileKwd;
        return result;
    }
    if (match_regex(regexes[kBoolKwd], text)) {
        result.length = match_regex(regexes[kBoolKwd], text);
        result.type = kBoolKwd;
        return result;
    }
    if (match_regex(regexes[kTrueKwd], text)) {
        result.length = match_regex(regexes[kTrueKwd], text);
        result.type = kTrueKwd;
        return result;
    }
    if (match_regex(regexes[kFalseKwd], text)) {
        result.length = match_regex(regexes[kFalseKwd], text);
        result.type = kFalseKwd;
        return result;
    }
    if (match_regex(regexes[kIntKwd], text)) {
        result.length = match_regex(regexes[kIntKwd], text);
        result.type = kIntKwd;
        return result;
    }
    if (match_regex(regexes[kFloatKwd], text)) {
        result.length = match_regex(regexes[kFloatKwd], text);
        result.type = kFloatKwd;
        return result;
    }
    if (match_regex(regexes[kStringKwd], text)) {
        result.length = match_regex(regexes[kStringKwd], text);
        result.type = kStringKwd;
        return result;
    }
    if (match_regex(regexes[kMatrixKwd], text)) {
        result.length = match_regex(regexes[kMatrixKwd], text);
        result.type = kMatrixKwd;
        return result;
    }
    if (match_regex(regexes[kLetKwd], text)) {
        result.length = match_regex(regexes[kLetKwd], text);
        result.type = kLetKwd;
        return result;
    }
    if (match_regex(regexes[kInKwd], text)) {
        result.length = match_regex(regexes[kInKwd], text);
        result.type = kInKwd;
        return result;
    }
    if (match_regex(regexes[kEndKwd], text)) {
        result.length = match_regex(regexes[kEndKwd], text);
        result.type = kEndKwd;
        return result;
    }
    if (match_regex(regexes[kIfKwd], text)) {
        result.length = match_regex(regexes[kIfKwd], text);
        result.type = kIfKwd;
        return result;
    }
    if (match_regex(regexes[kThenKwd], text)) {
        result.length = (match_regex(regexes[kThenKwd], text));
        result.type = kThenKwd;
        return result;
    }
    if (match_regex(regexes[kElseKwd], text)) {
        result.length = match_regex(regexes[kElseKwd], text);
        result.type = kElseKwd;
        return result;
    }
    if (match_regex(regexes[kRepeatKwd], text)) {
        result.length = match_regex(regexes[kRepeatKwd], text);
        result.type = kRepeatKwd;
        return result;
    }
    if (match_regex(regexes[kPrintKwd], text)) {
        result.length = match_regex(regexes[kPrintKwd], text);
        result.type = kPrintKwd;
        return result;
    }
    if (match_regex(regexes[kToKwd], text)) {
        result.length = match_regex(regexes[kToKwd], text);
        result.type = kToKwd;
        return result;
    }

    // Constants
    if (match_regex(regexes[kFloatConst], text)) {
        result.length = match_regex(regexes[kFloatConst], text);
        result.type = kFloatConst;
        return result;
    }
    if (match_regex(regexes[kIntConst], text)) {
        result.length = match_regex(regexes[kIntConst], text);
        result.type = kIntConst;
        return result;
    }
    if (match_regex(regexes[kStringConst], text)) {
        result.length = match_regex(regexes[kStringConst], text);
        result.type = kStringConst;
        return result;
    }
    // kDash needs to be here
    if (match_regex(regexes[kDash], text)) {
        result.length = match_regex(regexes[kDash], text);
        result.type = kDash;
        return result;
    }

    // Punctuation
    if (match_regex(regexes[kLeftParen], text)) {
        result.length = match_regex(regexes[kLeftParen], text);
        result.type = kLeftParen;
        return result;
    }
    if (match_regex(regexes[kRightParen], text)) {
        result.length = match_regex(regexes[kRightParen], text);
        result.type = kRightParen;
        return result;
    }
    if (match_regex(regexes[kLeftCurly], text)) {
        result.length = match_regex(regexes[kLeftCurly], text);
        result.type = kLeftCurly;
        return result;
    }
    if (match_regex(regexes[kRightCurly], text)) {
        result.length = match_regex(regexes[kRightCurly], text);
        result.type = kRightCurly;
        return result;
    }
    if (match_regex(regexes[kLeftSquare], text)) {
        result.length = match_regex(regexes[kLeftSquare], text);
        result.type = kLeftSquare;
        return result;
    }
    if (match_regex(regexes[kRightSquare], text)) {
        result.length = match_regex(regexes[kRightSquare], text);
        result.type = kRightSquare;
        return result;
    }

    if (match_regex(regexes[kSemiColon], text)) {
        result.length = match_regex(regexes[kSemiColon], text);
        result.type = kSemiColon;
        return result;
    }
    if (match_regex(regexes[kColon], text)) {
        result.length = match_regex(regexes[kColon], text);
        result.type = kColon;
        return result;
    }

    // Operations
  if (match_regex(regexes[kEqualsEquals], text)) {
        result.length = match_regex(regexes[kEqualsEquals], text);
        result.type = kEqualsEquals;
        return result;
    }
    if (match_regex(regexes[kAssign], text)) {
        result.length = match_regex(regexes[kAssign], text);
        result.type = kAssign;
        return result;
    }
    if (match_regex(regexes[kPlusSign], text)) {
        result.length = match_regex(regexes[kPlusSign], text);
        result.type = kPlusSign;
        return result;
    }
    if (match_regex(regexes[kStar], text)) {
        result.length = match_regex(regexes[kStar], text);
        result.type = kStar;
        return result;
    }
    if (match_regex(regexes[kForwardSlash], text)) {
        result.length = match_regex(regexes[kForwardSlash], text);
        result.type = kForwardSlash;
        return result;
    }
    if (match_regex(regexes[kLessThanEqual], text)) {
        result.length = match_regex(regexes[kLessThanEqual], text);
        result.type = kLessThanEqual;
        return result;
    }
    if (match_regex(regexes[kLessThan], text)) {
        result.length = match_regex(regexes[kLessThan], text);
        result.type = kLessThan;
        return result;
    }
    if (match_regex(regexes[kGreaterThanEqual], text)) {
        result.length = match_regex(regexes[kGreaterThanEqual], text);
        result.type = kGreaterThanEqual;
        return result;
    }
    if (match_regex(regexes[kGreaterThan], text)) {
        result.length = match_regex(regexes[kGreaterThan], text);
        result.type = kGreaterThan;
        return result;
    }
    if (match_regex(regexes[kNotEquals], text)) {
        result.length = match_regex(regexes[kNotEquals], text);
        result.type = kNotEquals;
        return result;
    }
    if (match_regex(regexes[kAndOp], text)) {
        result.length = match_regex(regexes[kAndOp], text);
        result.type = kAndOp;
        return result;
    }
    if (match_regex(regexes[kOrOp], text)) {
        result.length = match_regex(regexes[kOrOp], text);
        result.type = kOrOp;
        return result;
    }
    if (match_regex(regexes[kNotOp], text)) {
        result.length = match_regex(regexes[kNotOp], text);
        result.type = kNotOp;
        return result;
    }

    result.length = 0;
    result.type = kEndOfFile;
    return result;
} /*find_TokenType*/

/*Initialize all the needed regexes*/
void Scanner :: init_regex() {
    // Keywords
    Scanner::regexes[kIntKwd] = make_regex("^int");
    Scanner::regexes[kFloatKwd] = make_regex("^float");
    Scanner::regexes[kStringKwd] = make_regex("^string");
    Scanner::regexes[kMatrixKwd] = make_regex("^matrix");
    Scanner::regexes[kLetKwd] = make_regex("^let");
    Scanner::regexes[kInKwd] = make_regex("^in");
    Scanner::regexes[kEndKwd] = make_regex("^end");
    Scanner::regexes[kIfKwd] = make_regex("^if");
    Scanner::regexes[kThenKwd] = make_regex("^then");
    Scanner::regexes[kElseKwd] = make_regex("^else");
    Scanner::regexes[kRepeatKwd] = make_regex("^repeat");
    Scanner::regexes[kPrintKwd] = make_regex("^print");
    Scanner::regexes[kToKwd] = make_regex("^to");
    Scanner::regexes[kWhileKwd] = make_regex("^while");
    Scanner::regexes[kBoolKwd] = make_regex("^boolean");
    Scanner::regexes[kTrueKwd] = make_regex("^True");
    Scanner::regexes[kFalseKwd] = make_regex("^False");

    // Constants
    Scanner::regexes[kIntConst] = make_regex("^[0-9]+");
    Scanner::regexes[kFloatConst] = make_regex("^[0-9]*\\.[0-9]+");
    Scanner::regexes[kStringConst] = make_regex("^\"[^\"]*\"");

    // Variable Name
    Scanner::regexes[kVariableName] = make_regex("^_*[a-zA-Z]+[_a-zA-Z0-9-]*");

    // Punctuation
    Scanner::regexes[kLeftParen] = make_regex("^\\(");
    Scanner::regexes[kRightParen] = make_regex("^\\)");
    Scanner::regexes[kLeftCurly] = make_regex("^\\{");
    Scanner::regexes[kRightCurly] = make_regex("^\\}");
    Scanner::regexes[kLeftSquare] = make_regex("^\\[");
    Scanner::regexes[kRightSquare] = make_regex("^\\]");
    Scanner::regexes[kSemiColon] = make_regex("^;");
    Scanner::regexes[kColon] = make_regex("^:");

    // Operations
    Scanner::regexes[kAssign] = make_regex("^=");
    Scanner::regexes[kPlusSign] = make_regex("^\\+");
    Scanner::regexes[kStar] = make_regex("^\\*");
    Scanner::regexes[kDash] = make_regex("^-");
    Scanner::regexes[kForwardSlash] = make_regex("^/");
    Scanner::regexes[kLessThan] = make_regex("^<");
    Scanner::regexes[kLessThanEqual] = make_regex("^<=");
    Scanner::regexes[kGreaterThan] = make_regex("^>");
    Scanner::regexes[kGreaterThanEqual] = make_regex("^>=");
    Scanner::regexes[kEqualsEquals] = make_regex("^==");
    Scanner::regexes[kNotEquals] = make_regex("^!=");
    Scanner::regexes[kAndOp] = make_regex("^&&");
    Scanner::regexes[kOrOp] = make_regex("^\\|\\|");
    Scanner::regexes[kNotOp] = make_regex("^!");
}/*init_regex*/

} /* namespace scanner */
} /* namespace fcal */

 /*int main(){
  using namespace std;
  fcal::scanner::Scanner* s = new fcal::scanner::Scanner();
  fcal::scanner::Result result;

  const char* text= "{int a; @ float b; if (a <= b) # $}";
  fcal::scanner::Token* token = new fcal::scanner::Token(fcal::scanner::kEndKwd,text,NULL);
  token = s->Scan(text);
  while (token->terminal()!= fcal::scanner::kEndOfFile){
      cout<<token->lexeme()<<"   "<<token->terminal()<<"\n";
    token = token->next();
  }
  exit(1);
}*/
