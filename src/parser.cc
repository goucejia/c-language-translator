/*******************************************************************************
 * Name            : parser.h
 * Project         : fcal
 * Module          : parser
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Erik Van Wyk
 * Modifications by: Dan Challou, John Harwell, Son Nguyen, Yu Fang
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "../include/parser.h"
#include <assert.h>
#include <stdio.h>
#include <sstream>
#include "../include/ext_token.h"
#include "../include/scanner.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace parser {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Parser::~Parser() {
  if (scanner_) delete scanner_;

  scanner::ExtToken *to_delete1;
  curr_token_ = tokens_;
  while (curr_token_) {
    to_delete1 = curr_token_;
    curr_token_ = curr_token_->next();
    delete to_delete1;
  } /* while() */

  scanner::Token *curr_scanner_token = stokens_;
  scanner::Token *to_delete2;
  while (curr_scanner_token) {
    to_delete2 = curr_scanner_token;
    curr_scanner_token = curr_scanner_token->next();
    delete to_delete2;
  } /* while() */
} /* Parser::~Parser() */

ParseResult Parser::Parse(const char *text) {
  assert(text != NULL);

  ParseResult pr;
  try {
    scanner_ = new scanner::Scanner();
    stokens_ = scanner_->Scan(text);
    tokens_ = tokens_->ExtendTokenList(this, stokens_);

    assert(tokens_ != NULL);
    curr_token_ = tokens_;
    pr = ParseProgram();
  }
  catch (std::string errMsg) {
      pr.ok(false);
      pr.errors(errMsg);
      pr.ast(NULL);
  }
  return pr;
} /* Parser::parse() */

/*
 * parse methods for non-terminal symbols
 * --------------------------------------
 */

/*!
 *  ParseProgram() will parse the root node of a function and return a
 * ParseResult object with its inner ast field being an Program* object.
 */
// Program
ParseResult Parser::ParseProgram() {
  ParseResult pr;
  // root
  // Program ::= varName '(' ')' '{' Stmts '}'
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  match(scanner::kLeftParen);
  match(scanner::kRightParen);
  match(scanner::kLeftCurly);
  ParseResult pr_stmts = parse_stmts();
  ast::Stmts* ss = (ast::Stmts*) pr_stmts.ast();
  match(scanner::kRightCurly);
  match(scanner::kEndOfFile);
  ast::Program* result_ast = new ast::Program(name, ss);
  pr.ast(result_ast);
  return pr;
} /* Parser::ParseProgram() */

/*!
 *  The parse_matrix_decl() will parser the declaration of matrix object and
 * specifies the two kind of declaration by setting the inner ast feild of
 * returned ParseResult as LongMatrixDecl* or ShortMatrixDecl*.
 */
// MatrixDecl
// identical purpose of parse_decl, handles special matrix syntax.
ParseResult Parser::parse_matrix_decl() {
  ParseResult pr;
  match(scanner::kMatrixKwd);
  match(scanner::kVariableName);
  std::string var_name = prev_token_->lexeme();

  // Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '='
  // Expr ';'
  if (attempt_match(scanner::kLeftSquare)) {
    ParseResult temp = parse_expr(0);
    ast::Expr* left = (ast::Expr*) temp.ast();
    match(scanner::kColon);
    temp = parse_expr(0);
    ast::Expr* right = (ast::Expr*) temp.ast();
    match(scanner::kRightSquare);
    ast::VarExpr* temp_s = (ast::VarExpr*) parse_variable_name().ast();
    std::string l_name = temp_s->name();
    match(scanner::kColon);
    temp_s = (ast::VarExpr*) parse_variable_name().ast();
    std::string r_name =  temp_s->name();
    match(scanner::kAssign);
    temp = parse_expr(0);
    ast::Expr* expr = (ast::Expr*) temp.ast();
    ast::LongMatrixDecl* result_ast = new
          ast::LongMatrixDecl(var_name, left, right, l_name, r_name, expr);
    pr.ast(result_ast);
  } else if (attempt_match(scanner::kAssign)) {
    // Decl ::= 'matrix' varName '=' Expr ';'
    ParseResult temp = parse_expr(0);
    ast::Expr* expr = (ast::Expr*) temp.ast();
    ast::ShortMatrixDecl* result_ast = new ast::ShortMatrixDecl(var_name, expr);
    pr.ast(result_ast);
  } else {
    throw((std::string) "Bad Syntax of Matrix Decl in in parseMatrixDecl");
  }
  match(scanner::kSemiColon);
  return pr;
}

/*!
 *  The parse_standard_decl() function will parse the standard declaration of
 * object, such as IntDecl*, FloatDecl*, StringDecl* and BooleanDecl*,
 * recognizing by the erminal of input tokens.
 */
// standardDecl
// Decl ::= integerKwd varName | floatKwd varName | stringKwd varName
ParseResult Parser::parse_standard_decl() {
  ParseResult pr;

  if (attempt_match(scanner::kIntKwd)) {
    // Type ::= intKwd
    match(scanner::kVariableName);
    std::string temp = prev_token_->lexeme();
    ast::IntDecl* result_ast = new ast::IntDecl(temp);
    match(scanner::kSemiColon);
    pr.ast(result_ast);
  } else if (attempt_match(scanner::kFloatKwd)) {
    // Type ::= floatKwd
    match(scanner::kVariableName);
    std::string temp = prev_token_->lexeme();
    ast::FloatDecl* result_ast = new ast::FloatDecl(temp);
    match(scanner::kSemiColon);
    pr.ast(result_ast);
  } else if (attempt_match(scanner::kStringKwd)) {
    // Type ::= stringKwd
    match(scanner::kVariableName);
    std::string temp = prev_token_->lexeme();
    ast::StringDecl* result_ast = new ast::StringDecl(temp);
    match(scanner::kSemiColon);
    pr.ast(result_ast);
  } else if (attempt_match(scanner::kBoolKwd)) {
    // Type ::= boolKwd
    match(scanner::kVariableName);
    std::string temp = prev_token_->lexeme();
    ast::BooleanDecl* result_ast = new ast::BooleanDecl(temp);
    match(scanner::kSemiColon);
    pr.ast(result_ast);
  }
  return pr;
}

/*!
 *  The parse_decl() is an function acting as a dispatcher for declaration
 * syntax, to either parse_matrix_decl() or parse_standard_decl().
 */
// Decl
ParseResult Parser::parse_decl() {
  ParseResult pr;
  // Decl :: matrix variableName ....
  if (next_is(scanner::kMatrixKwd)) {
    pr = parse_matrix_decl();
  } else {
    // Decl ::= Type variableName semiColon
    pr = parse_standard_decl();
  }
  return pr;
}

/*!
 *  The parse_stmts() method parse a sequence of Stmt, branckes out the first
 * stmt and the rests, and the rests will recursively be brancked out by further
 * calls to this function.
 */
// Stmts
ParseResult Parser::parse_stmts() {
  ParseResult pr;
  if (!next_is(scanner::kRightCurly) && !next_is(scanner::kInKwd)) {
    // Stmts ::= Stmt Stmts
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt* s = (ast::Stmt*) pr_stmt.ast();
    ParseResult pr_stmts = parse_stmts();
    ast::Stmts* ss = (ast::Stmts*) pr_stmts.ast();
    ast::MultiStmts* result_ast = new ast::MultiStmts(s, ss);
    pr.ast(result_ast);
  } else {
    // Stmts ::=
    // nothing to match.k
    ast::EmptyStmts* result_ast = new ast::EmptyStmts();
    pr.ast(result_ast);
  }
  return pr;
}

/*!
 *  The parse_stmt() function will parse the stmt syntax and recognize the type
 * of stmt, the ast feild of returned ParseResult may be DeclStmt*, BlockStmt*,
 * IfElseStmt*, IfStmt*, MatrixAssignStmt*, AssignStmt*, PrintStmt*, WhileStmt*,
 * RepeatStmt*, EmptyStmt* or error depending on the input structure.
 */
// Stmt
ParseResult Parser::parse_stmt() {
  ParseResult pr;

  // Stmt ::= Decl
  if (next_is(scanner::kIntKwd) || next_is(scanner::kFloatKwd) ||
      next_is(scanner::kMatrixKwd) || next_is(scanner::kStringKwd) ||
      next_is(scanner::kBoolKwd)) {
    ast::Decl* temp = (ast::Decl*) parse_decl().ast();
    ast::DeclStmt* result_ast = new ast::DeclStmt(temp);
    pr.ast(result_ast);

  } else if (attempt_match(scanner::kLeftCurly)) {
    // Stmt ::= '{' Stmts '}'
    ast::Stmts* temp = (ast::Stmts*) parse_stmts().ast();
    ast::BlockStmt* result_ast = new ast::BlockStmt(temp);
    match(scanner::kRightCurly);
    pr.ast(result_ast);

  } else if (attempt_match(scanner::kIfKwd)) {
    // Stmt ::= 'if' '(' Expr ')' Stmt
    // Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    match(scanner::kLeftParen);
    ast::Expr* expr = (ast::Expr*) parse_expr(0).ast();
    match(scanner::kRightParen);
    ast::Stmt* temp_l = (ast::Stmt*) parse_stmt().ast();

    if (attempt_match(scanner::kElseKwd)) {
      ast::Stmt* temp_r = (ast::Stmt*) parse_stmt().ast();
      ast::IfElseStmt* result_ast = new ast::IfElseStmt(expr, temp_l, temp_r);
      pr.ast(result_ast);
    } else {
      ast::IfStmt* result_ast = new ast::IfStmt(expr, temp_l);
      pr.ast(result_ast);
    }

  } else if (attempt_match(scanner::kVariableName)) {
    /*
     * Stmt ::= varName '=' Expr ';'  | varName '[' Expr ':' Expr ']'
     * '=' Expr ';'
     */
    bool matrix = false;
    std::string var_name = prev_token_->lexeme();
    if (attempt_match(scanner::kLeftSquare)) {
      ast::Expr* le = (ast::Expr*) parse_expr(0).ast();
      match(scanner::kColon);
      ast::Expr* re = (ast::Expr*) parse_expr(0).ast();
      match(scanner::kRightSquare);
      match(scanner::kAssign);
      ast::Expr* ex = (ast::Expr*) parse_expr(0).ast();
      match(scanner::kSemiColon);
      ast::MatrixAssignStmt* result_ast = new
                              ast::MatrixAssignStmt(var_name, le, re, ex);
      pr.ast(result_ast);
  } else {
      match(scanner::kAssign);
      ast::Expr* ex = (ast::Expr*) parse_expr(0).ast();
      ast::AssignStmt* result_ast = new ast::AssignStmt(var_name, ex);
      match(scanner::kSemiColon);
      pr.ast(result_ast);
  }

  } else if (attempt_match(scanner::kPrintKwd)) {
    // Stmt ::= 'print' '(' Expr ')' ';'
    match(scanner::kLeftParen);
    ast::Expr* ex = (ast::Expr*) parse_expr(0).ast();
    match(scanner::kRightParen);
    match(scanner::kSemiColon);
    ast::PrintStmt* result_ast = new ast::PrintStmt(ex);
    pr.ast(result_ast);

  } else if (attempt_match(scanner::kRepeatKwd)) {
    // Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
    match(scanner::kLeftParen);
    match(scanner::kVariableName);
    std::string var_name = prev_token_->lexeme();
    match(scanner::kAssign);
    ast::Expr* le = (ast::Expr*) parse_expr(0).ast();
    match(scanner::kToKwd);
    ast::Expr* ue = (ast::Expr*) parse_expr(0).ast();
    match(scanner::kRightParen);
    ast::Stmt* ss = (ast::Stmt*) parse_stmt().ast();
    ast::RepeatStmt* result_ast = new ast::RepeatStmt(var_name, le, ue, ss);
    pr.ast(result_ast);

  } else if (attempt_match(scanner::kWhileKwd)) {
    // Stmt ::= 'while' '(' Expr ')' Stmt
    match(scanner::kLeftParen);
    ast::Expr* ex = (ast::Expr*) parse_expr(0).ast();
    match(scanner::kRightParen);
    ast::Stmt* ss = (ast::Stmt*) parse_stmt().ast();
    ast::WhileStmt* result_ast = new ast::WhileStmt(ex, ss);
    pr.ast(result_ast);

  } else if (attempt_match(scanner::kSemiColon)) {
    // Stmt ::= ';
    // parsed a skip
    ast::EmptyStmt* result_ast = new ast::EmptyStmt();
    pr.ast(result_ast);

  } else {
    throw(make_error_msg(curr_token_->terminal()) +
          " while parsing a statement");
  }
  // Stmt ::= variableName assign Expr semiColon
  return pr;
}

// Expr
ParseResult Parser::parse_expr(int rbp) {
  /* Examine current token, without consuming it, to call its
     associated parse methods.  The ExtToken objects have 'nud' and
     'led' methods that are dispatchers that call the appropriate
     parse methods.*/
  ParseResult left = curr_token_->nud();

  while (rbp < curr_token_->lbp()) {
    left = curr_token_->led(left);
  }

  return left;
}

/*
 * parse methods for Expr productions
 * ----------------------------------
 */

 /*!
  *  The parse_true_kwd() function will parse the "true" keyword and return a
  * ParseResult object with its ast feild being TrueExpr*.
  */
// Expr ::= trueKwd
ParseResult Parser::parse_true_kwd() {
  ParseResult pr;
  match(scanner::kTrueKwd);
  ast::TrueExpr* resultAst = new ast::TrueExpr();
  pr.ast(resultAst);
  return pr;
}

/*!
 *  The parse_false_kwd() function will parse the "false" keyword and return a
 * ParseResult object with its ast feild being FalseExpr*.
 */
// Expr ::= falseKwd
ParseResult Parser::parse_false_kwd() {
  ParseResult pr;
  match(scanner::kFalseKwd);
  ast::FalseExpr* resultAst = new ast::FalseExpr();
  pr.ast(resultAst);
  return pr;
}

/*!
 *  The parse_int_const() function will parse the intConst keyword and return a
 * ParseResult object with its ast feild being IntConstExpr*.
 */
// Expr ::= intConst
ParseResult Parser::parse_int_const() {
  ParseResult pr;
  match(scanner::kIntConst);
  ast::IntConstExpr* resultAst = new ast::IntConstExpr(prev_token_->lexeme());
  pr.ast(resultAst);
  return pr;
}

/*!
 *  The parse_float_const() function will parse the floatConst keyword and
 * return a ParseResult object with its ast feild being FloatConstExpr*.
 */
// Expr ::= floatConst
ParseResult Parser::parse_float_const() {
  ParseResult pr;
  match(scanner::kFloatConst);
  ast::FloatConstExpr* resultAst = new
               ast::FloatConstExpr(prev_token_->lexeme());
  pr.ast(resultAst);
  return pr;
}

/*!
 *  The parse_string_const() function will parse the stringConst keyword and
 * return a ParseResult object with its ast feild being StringConstExpr*.
 */
// Expr ::= stringConst
ParseResult Parser::parse_string_const() {
  ParseResult pr;
  match(scanner::kStringConst);
  ast::StringConstExpr* resultAst = new
                      ast::StringConstExpr(prev_token_->lexeme());
  pr.ast(resultAst);
  return pr;
}

/*!
 *  The parse_variable_name() function will parse the variableName keyword and
 * return a ParseResult object with its ast feild being either MatrixRefExpr*,
 * VarExpr* or GroupExpr*.
 */
// Expr ::= variableName .....
ParseResult Parser::parse_variable_name() {
  ParseResult pr;
  match(scanner::kVariableName);
  ast::VarExpr* varexpr = new ast::VarExpr(prev_token_->lexeme());
  if (attempt_match(scanner::kLeftSquare)) {
    // Expr ::= varName '[' Expr ':' Expr ']'
    ParseResult tem = parse_expr(0);
    ast::Expr* expr_left = (ast::Expr*) tem.ast();
    match(scanner::kColon);
    tem = parse_expr(0);
    ast::Expr* expr_right = (ast::Expr*) tem.ast();
    match(scanner::kRightSquare);
    ast::MatrixRefExpr* result_ast = new
                ast::MatrixRefExpr(varexpr->UnParse(), expr_left, expr_right);
    pr.ast(result_ast);
  }  else if (attempt_match(scanner::kLeftParen)) {
    // Expr ::= varableName '(' Expr ')'
    ParseResult tem = parse_expr(0);
    match(scanner::kRightParen);
    ast::Expr* expr = (ast::Expr*) tem.ast();
    ast::FuncCallExpr* result_ast =
                   new ast::FuncCallExpr(varexpr->UnParse(), expr);
    pr.ast(result_ast);
    // pr.ast((ast::GroupExpr*) new ast::GroupExpr(expr));
  } else {
    // variable
    pr.ast(varexpr);
  }
  return pr;
}

/*!
 *  The parse_nested_expr() function will parse syntax with structure:
 * Expr ::= leftParen Expr rightParen and return a ParseResult object with its
 * ast field being GroupExpr*.
 */
// Expr ::= leftParen Expr rightParen
ParseResult Parser::parse_nested_expr() {
  ParseResult pr;
  match(scanner::kLeftParen);
  ParseResult tem = parse_expr(0);
  ast::Expr* expr = (ast::Expr*) tem.ast();
  pr.ast((ast::GroupExpr*) new ast::GroupExpr(expr));
  match(scanner::kRightParen);
  return pr;
}

/*!
 *  The parse_if_expr() function will parse syntax with structure:
 * Expr ::= 'if' Expr 'then' Expr 'else' Expr and return a ParseResult object
 * with its ast feild being IfExpr*.
 */
// Expr ::= 'if' Expr 'then' Expr 'else' Expr
ParseResult Parser::parse_if_expr() {
  ParseResult pr;

  match(scanner::kIfKwd);
  ParseResult tem = parse_expr(0);
  ast::Expr* ex1 = (ast::Expr*) tem.ast();
  match(scanner::kThenKwd);
  tem = parse_expr(0);
  ast::Expr* ex2 = (ast::Expr*) tem.ast();
  match(scanner::kElseKwd);
  tem = parse_expr(0);
  ast::Expr* ex3 = (ast::Expr*) tem.ast();

  ast::IfExpr* ifex = new ast::IfExpr(ex1, ex2, ex3);
  pr.ast(ifex);

  return pr;
}

/*!
 *  The parse_let_expr() function will parse syntax with structure:
 * Expr ::= 'let' Stmts 'in' Expr 'end' and return a ParseResult object
 * with its ast feild being LetExpr*.
 */
// Expr ::= 'let' Stmts 'in' Expr 'end'
ParseResult Parser::parse_let_expr() {
  ParseResult pr;
  match(scanner::kLetKwd);
  ParseResult tem = parse_stmts();
  ast::Stmts* stmts = (ast::Stmts*) tem.ast();
  match(scanner::kInKwd);
  tem = parse_expr(0);
  ast::Expr* expr = (ast::Expr*) tem.ast();
  match(scanner::kEndKwd);
  ast::LetExpr* letex = new ast::LetExpr(stmts, expr);
  pr.ast(letex);

  return pr;
}

/*!
 *  The parse_not_expr() function will parse syntax with structure:
 * Expr ::= '!' Expr and return a ParseResult object with its ast feild being
 * NotExpr*.
 */
// Expr ::= '!' Expr
ParseResult Parser::parse_not_expr() {
  ParseResult pr;
  match(scanner::kNotOp);
  ParseResult tem = parse_expr(0);
  pr.ast((ast::NotExpr*) tem.ast());
  return pr;
}

/*!
 *  The parse_addition() function will parse syntax with structure:
 * Expr ::= Expr plusSign Expr and return a ParseResult object with its ast
 * feild being PlusExpr*.
 */
// Expr ::= Expr plusSign Expr
ParseResult Parser::parse_addition(ParseResult prLeft) {
  // parser has already matched left expression
  ast::Expr* expr_left = (ast::Expr*) prLeft.ast();
  ParseResult pr;
  match(scanner::kPlusSign);
  ParseResult tem = parse_expr(prev_token_->lbp());
  ast::Expr* expr_right = (ast::Expr*) tem.ast();
  ast::PlusExpr* plusex = new ast::PlusExpr(expr_left, expr_right);
  pr.ast(plusex);
  return pr;
}

/*!
 *  The parse_multiplication() function will parse syntax with structure:
 * Expr ::= Expr star Expr and return a ParseResult object with its ast
 * feild being MulExpr*.
 */
// Expr ::= Expr star Expr
ParseResult Parser::parse_multiplication(ParseResult prLeft) {
  // parser has already matchekD left expression
  ast::Expr* expr_left = (ast::Expr*) prLeft.ast();
  ParseResult pr;
  match(scanner::kStar);
  ParseResult tem = parse_expr(prev_token_->lbp());
  ast::Expr* expr_right = (ast::Expr*) tem.ast();
  ast::MulExpr* mulex = new ast::MulExpr(expr_left, expr_right);
  pr.ast(mulex);
  return pr;
}

/*!
 *  The parse_subtraction() function will parse syntax with structure:
 * Expr ::= Expr dash Expr and return a ParseResult object with its ast
 * feild being MinusExpr*.
 */
// Expr ::= Expr dash Expr
ParseResult Parser::parse_subtraction(ParseResult prLeft) {
  // parser has already matchekD left expression
  ast::Expr* expr_left = (ast::Expr*) prLeft.ast();
  ParseResult pr;
  match(scanner::kDash);
  ParseResult tem = parse_expr(prev_token_->lbp());
  ast::Expr* expr_right = (ast::Expr*) tem.ast();
  ast::MinusExpr* minusex = new ast::MinusExpr(expr_left, expr_right);
  pr.ast(minusex);
  return pr;
}

/*!
 *  The parse_division() function will parse syntax with structure:
 * Expr ::= Expr forwardSlash Expr and return a ParseResult object with its ast
 * feild being DivExpr*.
 */
// Expr ::= Expr forwardSlash Expr
ParseResult Parser::parse_division(ParseResult prLeft) {
  // parser has already matchekD left expression
  ast::Expr* expr_left = (ast::Expr*) prLeft.ast();
  ParseResult pr;
  match(scanner::kForwardSlash);
  ParseResult tem = parse_expr(prev_token_->lbp());
  ast::Expr* expr_right = (ast::Expr*) tem.ast();
  ast::DivExpr* divex = new ast::DivExpr(expr_left, expr_right);
  pr.ast(divex);
  return pr;
}

// Expr ::= Expr equalEquals Expr
// Expr ::= Expr lessThanEquals Expr
// Expr ::= Expr greaterThanEquals Expr
// Expr ::= Expr notEquals Expr
// Expr ::= Expr leftAngle Expr
// Expr ::= Expr rightAngle Expr
/* Notice that for relational operators we use just one parse
   function.  This shows another possible means for implementing
   expressions, as opposed to the method used for arithmetic
   expressions in which each operation has its own parse method.  It
   will depend on what we do in iteration 3 in building an abstract
   syntax tree to decide which method is better.
*/
ParseResult Parser::parse_relational_expr(ParseResult prLeft) {
  // parser has already matched left expression
  ast::Expr* expr_left = (ast::Expr*) prLeft.ast();
  ParseResult pr;

  next_token();
  // just advance token, since examining it in parse_expr caused
  // this method being called.
  std::string op = prev_token_->lexeme();

  ParseResult tem = parse_expr(prev_token_->lbp());
  ast::Expr* expr_right = (ast::Expr*) tem.ast();
  ast::Expr* result;
  if (op == "==") {
      result = new ast::EqualEqualExpr(expr_left, expr_right);
  } else if (op == "<=") {
      result = new ast::LessEqualExpr(expr_left, expr_right);
  } else if (op == ">=") {
      result = new ast::GreaterEqualExpr(expr_left, expr_right);
  } else if (op == "!=") {
      result = new ast::NotEqualExpr(expr_left, expr_right);
  } else if (op == "<") {
      result = new ast::LessExpr(expr_left, expr_right);
  } else {
      result = new ast::GreaterExpr(expr_left, expr_right);
  }

  pr.ast(result);
  return pr;
}

// Helper function used by the parser.

void Parser::match(const scanner::TokenType &tt) {
  if (!attempt_match(tt)) {
    throw(make_error_msg_expected(tt));
  }
}

bool Parser::attempt_match(const scanner::TokenType &tt) {
  if (curr_token_->terminal() == tt) {
    next_token();
    return true;
  }
  return false;
}

bool Parser::next_is(const scanner::TokenType &tt) {
  return curr_token_->terminal() == tt;
}

void Parser::next_token() {
  if (curr_token_ == NULL) {
    throw(std::string(
        "Internal Error: should not call nextToken in unitialized state"));
  } else if (curr_token_->terminal() == scanner::kEndOfFile &&
           curr_token_->next() == NULL) {
    prev_token_ = curr_token_;
  } else if (curr_token_->terminal() != scanner::kEndOfFile &&
             curr_token_->next() == NULL) {
    throw(make_error_msg("Error: tokens end with endOfFile"));
  } else {
    prev_token_ = curr_token_;
    curr_token_ = curr_token_->next();
  }
}

std::string Parser::terminal_description(const scanner::TokenType &terminal) {
  scanner::Token *dummy_token = new scanner::Token("", terminal, NULL);
  scanner::ExtToken *dummy_ext_token = new scanner::ExtToken(this, dummy_token);
  dummy_ext_token->ExtendToken(this, dummy_token);
  std::string s = dummy_ext_token->description();
  delete dummy_token;
  delete dummy_ext_token;
  return s;
}

std::string Parser::make_error_msg_expected(
    const scanner::TokenType &terminal) {

    std::ostringstream ss;
    ss << terminal;
    std::string str = ss.str();

  std::string s = (std::string) "Expected " + terminal_description(terminal) +
                   str + " but found " + curr_token_->description();
  return s;
}

std::string Parser::make_error_msg(const scanner::TokenType &terminal) {
    std::ostringstream ss;
    ss << terminal;
    std::string str = ss.str();

  std::string s = "Unexpected symbol " + terminal_description(terminal) + str;
  return s;
}

std::string Parser::make_error_msg(const char *msg) { return msg; }

} /* namespace parser */
} /* namespace fcal */
