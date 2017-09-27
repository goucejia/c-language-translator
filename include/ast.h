/*******************************************************************************
 * Name            : ast.h
 * Project         : fcal
 * Module          : ast
 * Description     : Header file for AST
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell, Yu Fang, Son Nguyen
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_AST_H_
#define PROJECT_INCLUDE_AST_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include <typeinfo>
#include "./scanner.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace ast {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/*!
 * Node (Abstract)
 * The interface of all ast classes. All inheriting classes have to implement
 * UnParse method.
 */
class Node {
 public:
  virtual std::string UnParse(void) { return " This should be pure virtual "; }
  virtual std::string CppCode(void) { return " This should be pure virtual"; }
  virtual ~Node(void) {}
};

/*!
 * Expr (Abstract)
 * This class is the abstract class of all Expr type classes.
 */
class Expr : public Node {
 public:
    virtual std::string UnParse(void) {return " This should be pure virtual ";}
};

/*!
 * Expr ::= varName
 * This class is the representation of variable name expression.
 */
class VarExpr : public Expr {
 public:
    explicit VarExpr(std::string s) { name_ = s; }
    std::string name() { return name_; }
    void set_name(std::string s) { name_ = s; }
    std::string UnParse(void) { return name_; }
    std::string CppCode(void) { return name_; }

 private:
    std::string name_;
};

/*!
 * Expr ::= integerConst
 * This class is the representation of integer constant expression.
 */
class IntConstExpr : public Expr {
 public:
    explicit IntConstExpr(std::string s) { value_ = s; }
    std::string value() { return value_ ;}
    void set_value(std::string s) { value_ = s; }
    std::string UnParse(void) { return value_; }
    std::string CppCode(void) { return value_; }

 private:
    std::string value_;
};

/*!
 * Expr ::= floatConst
 * This class is the representation of float constant expression.
 */
class FloatConstExpr : public Expr {
 public:
    explicit FloatConstExpr(std::string s) { value_ = s; }
    std::string value() { return value_; }
    void set_value(std::string s) { value_ = s; }
    std::string UnParse(void) { return value_; }
    std::string CppCode(void) { return value_; }

 private:
    std::string value_;
};

/*!
 * Expr ::= stringConst
 * This class is the representation of string constant expression.
 */
class StringConstExpr : public Expr {
 public:
    explicit StringConstExpr(std::string s) { value_ = s; }
    std::string value() { return value_; }
    void set_value(std::string s) { value_ = s; }
    std::string UnParse(void) { return value_; }
    std::string CppCode(void) { return value_; }

 private:
    std::string value_;
};

/*!
 * Expr ::= 'True'
 * This class is the representation of True expression.
 */
class TrueExpr : public Expr {
 public:
    TrueExpr() {}
    std::string UnParse() { return "True"; }
    std::string CppCode(void) { return "true"; }
};

/*!
 * Expr ::= 'False'
 * This class is the representation of False expression.
 */
class FalseExpr : public Expr {
 public:
    FalseExpr() {}
    std::string UnParse() { return "False"; }
    std::string CppCode(void) { return "false"; }
};

/*!
 * Expr ::= Expr '*' Expr
 * This class is the representation of multiplication expression.
 */
class MulExpr : public Expr {
 public:
    MulExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " * " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return "(" + expr_left_->CppCode() + " * " \
        + expr_right_->CppCode() + ")"; }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '/' Expr
 * This class is the representation of division expression.
 */
class DivExpr : public Expr {
 public:
    DivExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " / " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return "(" + expr_left_->CppCode() + " / " \
        + expr_right_->CppCode() + ")"; }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '+' Expr
 * This class is the representation of addition expression.
 */
class PlusExpr : public Expr {
 public:
    PlusExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " + " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return "(" + expr_left_->CppCode() + " + " \
        + expr_right_->CppCode() + ")"; }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '-' Expr
 * This class is the representation of subtraction expression.
 */
class MinusExpr : public Expr {
 public:
    MinusExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " - " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return "(" + expr_left_->CppCode() + " - " \
        + expr_right_->CppCode() + ")"; }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '>' Expr
 * This class is the representation of greater expression.
 */
class GreaterExpr : public Expr {
 public:
    GreaterExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " > " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return "(" + expr_left_->CppCode() + " > " \
        + expr_right_->CppCode() + ")"; }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '>=' Expr
 * This class is the representation of greater or equal expression.
 */
class GreaterEqualExpr : public Expr {
 public:
    GreaterEqualExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " >= " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return "(" + expr_left_->CppCode() + " >= " \
        + expr_right_->CppCode() + ")"; }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '<' Expr
 * This class is the representation of less expression.
 */
class LessExpr : public Expr {
 public:
    LessExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " < " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return "( " + expr_left_->CppCode() + " < " \
        + expr_right_->CppCode() + " )"; }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '<=' Expr
 * This class is the representation of less than or equal expression.
 */
class LessEqualExpr : public Expr {
 public:
    LessEqualExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " <= " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return "(" + expr_left_->CppCode() + " <= " \
        + expr_right_->CppCode() + ")"; }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '==' Expr
 * This class is the representation of equal equal expression.
 */
class EqualEqualExpr : public Expr {
 public:
    EqualEqualExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " == " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return expr_left_->CppCode() + " == " \
        + expr_right_->CppCode(); }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '!=' Expr
 * This class is the representation of not equal expression.
 */
class NotEqualExpr : public Expr {
 public:
    NotEqualExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " != " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return expr_left_->CppCode() + " != " \
        + expr_right_->CppCode(); }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '&&' Expr
 * This class is the representation of and expression.
 */
class AndExpr : public Expr {
 public:
    AndExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " && " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return expr_left_->CppCode() + " && " \
        + expr_right_->CppCode(); }
 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= Expr '||' Expr
 * This class is the representation of or expression.
 */
class OrExpr : public Expr {
 public:
    OrExpr(Expr* l, Expr* r) { expr_left_ = l; expr_right_ = r; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_right_ = r; }
    std::string UnParse() { return expr_left_->UnParse() + " || " \
        + expr_right_->UnParse(); }
    std::string CppCode() { return expr_left_->CppCode() + " || " \
        + expr_right_->CppCode(); }

 private:
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= varName '[' Expr ':' Expr ']'
 * This class is the representation of matrix reference expression.
 */
class MatrixRefExpr : public Expr {
 public:
    MatrixRefExpr(std::string n, Expr* l, Expr* r) {
        name_ = n;
        expr_left_ = l;
        expr_right_ = r;
    }
    std::string name() { return name_; }
    void set_name(std::string n) { name_ = n; }
    Expr* expr_left() { return expr_left_; }
    void set_expr_left(Expr* l) { expr_left_ = l; }
    Expr* expr_right() { return expr_right_; }
    void set_expr_right(Expr* r) { expr_left_ = r; }
    std::string UnParse() {
        return name_ + " [" + expr_left_->UnParse() + ": " \
            + expr_right_->UnParse() + "]"; }

    std::string CppCode(void) {
      return "*(" + name_ + ".access(" + expr_left_->CppCode() + ", " +\
        expr_right_->CppCode() + "))";
    }

 private:
    std::string name_;
    Expr* expr_left_;
    Expr* expr_right_;
};

/*!
 * Expr ::= varName '(' Expr ')'
 * This class is the representation of function call expression.
 */
class FuncCallExpr : public Expr {
 public:
    FuncCallExpr(std::string n, Expr* e) { name_ = n; expr_ = e; }
    std::string name() { return name_; }
    void set_name(std::string n) { name_ = n; }
    Expr* expr() { return expr_; }
    void set_expr(Expr* e) { expr_ = e; }
    std::string UnParse() { return name_ + "(" + expr_->UnParse() + ")"; }
    // std::string CppCode() { return name_ + "(" + expr_->UnParse() + ")"; }
    std::string CppCode() {
      if (name_.compare("n_rows") == 0 || name_.compare("n_cols") == 0) {
        return expr_->CppCode() + "." + name_ + "()";
      } else if (name_.compare("matrix_read") == 0) {
        return "matrix::" + name_ + "(" + expr_->CppCode() + ")";
      } else {
        return name_ + "(" + expr_->CppCode() + ")";
      }
    }

 private:
    std::string name_;
    Expr* expr_;
};

/*!
 * Expr ::= '(' Expr ')'
 * This class is the representation of parenthesized expression.
 */
class GroupExpr : public Expr {
 public:
    explicit GroupExpr(Expr* e) { expr_ = e; }
    Expr* expr() { return expr_; }
    void set_expr(Expr* e) { expr_ = e; }
    std::string UnParse() { return "(" + expr_->UnParse() + ")"; }
    std::string CppCode() { return "(" + expr_->CppCode() + ")"; }

 private:
    Expr* expr_;
};


/*!
 * Expr ::= 'if' Expr 'then' Expr 'else' Expr
 * This class is the representation of if expression.
 */
class IfExpr : public Expr {
 public:
    IfExpr(Expr* e, Expr* et, Expr* ee) {
        expr_test_ = e;
        expr_then_ = et;
        expr_else_ = ee;
    }
    Expr* expr_test() { return expr_test_; }
    void set_expr_test(Expr* e) { expr_test_ = e; }
    Expr* expr_then() { return expr_then_; }
    void set_expr_then(Expr* e) { expr_then_ = e; }
    Expr* expr_else() { return expr_else_; }
    void set_expr_else(Expr* e) { expr_else_ = e; }
    std::string UnParse() {
        return "if " + expr_test_->UnParse() + " then " + \
        expr_then_->UnParse() + " else " + expr_else_->UnParse();
    }
    std::string CppCode() {
      return "( " + expr_test_->CppCode() + " ? " + expr_then_->CppCode() +\
        + " : " + expr_else_->CppCode() + ")\n";
    }

 private:
    Expr* expr_test_;
    Expr* expr_then_;
    Expr* expr_else_;
};

/*!
 * Expr ::= '!' Expr
 * This class is the representation of negation expression.
 */
class NotExpr : public Expr {
 public:
    explicit NotExpr(Expr* e) { expr_ = e; }
    Expr* expr() { return expr_; }
    void set_expr(Expr* e) { expr_ = e; }
    std::string UnParse() { return "!" + expr_->UnParse(); }
    std::string CppCode() { return "!" + expr_->UnParse(); }

 private:
    Expr* expr_;
};

/*!
 * Decl (Abstract)
 * This is the abstract class for all Decl type classes.
 */
class Decl : public Node {
 public:
  virtual std::string UnParse(void) { return "This should be pure virtual"; }
};

/*!
 * Decl ::= 'int' varName ';'
 * This class is the representation of integer variable decleration.
 */
class IntDecl : public Decl {
 public:
  explicit IntDecl(std::string s) { name_ = s; }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  std::string UnParse(void) { return "int " + name_ + ";\n"; }
  std::string CppCode(void) { return "int " + name_ + ";\n"; }

 private:
  std::string name_;
};

/*!
 * Decl ::= 'float' varName ';'
 * This class is the representation of float variable decleration.
 */
class FloatDecl : public Decl {
 public:
  explicit FloatDecl(std::string s) { name_ = s; }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  std::string UnParse(void) { return "float " + name_ + ";\n"; }
  std::string CppCode(void) { return "float " + name_ + ";\n"; }

 private:
  std::string name_;
};

/*!
 * Decl ::= 'string' varName ';'
 * This class is the representation of string variable decleration.
 */
class StringDecl : public Decl {
 public:
  explicit StringDecl(std::string s) { name_ = s; }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  std::string UnParse(void) { return "string " + name_ + ";\n"; }
  std::string CppCode(void) { return "string " + name_ + ";\n"; }

 private:
  std::string name_;
};

/*!
 * Decl ::= 'boolean' varName ';'
 * This class is the representation of boolean variable decleration.
 */
class BooleanDecl : public Decl {
 public:
  explicit BooleanDecl(std::string s) { name_ = s; }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  std::string UnParse(void) { return "boolean " + name_ + ";\n"; }
  std::string CppCode(void) { return "boolean " + name_ + ";\n"; }

 private:
  std::string name_;
};

/*!
 * Decl ::= 'matrix' varName '=' Expr ';'
 * This class is the representation of matrix variable decleration.
 */
class ShortMatrixDecl : public Decl {
 public:
  ShortMatrixDecl(std::string s, Expr* expr) { name_ = s; expr_ = expr; }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  Expr* expr(void) { return expr_; }
  void set_expr(Expr* e) { expr_ = e; }
  std::string UnParse(void) { return "matrix " + name_ + " = " + \
                                expr_->UnParse() + ";\n"; }
  std::string CppCode(void) {
  //   FuncCallExpr* call;
  //   MulExpr* mul;
  //   if ((typeid(call) == typeid(expr_))) {
  //     // calling matrx::matrxread()
  //     return "matrix " + name_ + " = matrix::" + expr_->CppCode() + ";\n";
  //   } else {
  //     return "matrix " + name_ + " = " + expr_->CppCode() + ";\n";
  //   }
    return "matrix " + name_ + " = " + expr_->CppCode() + ";\n";
  }

 private:
  std::string name_;
  Expr* expr_;
};

/*!
 * Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':'
 * varName  '=' Expr ';'
 * This class is the representation of long matrix decleration.
 */
class LongMatrixDecl : public Decl {
 public:
  LongMatrixDecl(std::string s, Expr* left, Expr* right, std::string l_name,
                  std::string r_name, Expr* expr) {
                    name_ = s; expr_left_ = left; expr_right_ = right;
                    name_left_ = l_name; name_right_ = r_name; expr_ = expr;
                  }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  Expr* expr_left() { return expr_left_; }
  void set_expr_left(Expr* l) { expr_left_ = l; }
  Expr* expr_right() { return expr_right_; }
  void set_expr_right(Expr* r) { expr_right_ = r; }
  std::string name_left() { return name_left_; }
  void set_name_left(std::string s) { name_left_ = s; }
  std::string name_right() { return name_right_; }
  void set_name_right(std::string s) { name_right_ = s; }
  Expr* expr() { return expr_; }
  void set_expr(Expr* e) { expr_ = e; }

  std::string UnParse(void) { return "matrix " + name_ + " [ " + \
        expr_left_->UnParse() + " : " + expr_right_->UnParse() + " ] " + \
        name_left_ + " : " + name_right_ + " = " + expr_->UnParse() + ";\n";}

  std::string CppCode(void) {
    return "matrix " + name_ + "( " + expr_left_->CppCode() + ", " +\
    expr_right_->CppCode() + " );\nfor (int " + name_left_ + " = 0; " +\
    name_left_ + " < " + expr_left_->CppCode() + "; " +\
    name_left_+" ++) {\n  for (int " + name_right_ + " = 0; "+\
    name_right_+" < " + expr_right_->CppCode() + "; "+ name_right_ +\
    " ++ ) {\n     *(" + name_ + ".access("+name_left_+", "+name_right_+\
    ")) = "+ expr_->CppCode() +";\n  }\n}\n"; }

 private:
  std::string name_;
  Expr* expr_left_;
  Expr* expr_right_;
  std::string name_left_;
  std::string name_right_;
  Expr* expr_;
};

/*!
 * Stmts (Abstract)
 * This is the abstract for all Stmts type classes.
 */
class Stmts : public Node {
 public:
  virtual std::string UnParse(void) { return "This should be pure virtual";}
};

/*!
 * Stmts ::= << empty >>
 * This class is the representation of empty statements.
 */
class EmptyStmts : public Stmts {
 public:
  EmptyStmts(void) {}
  std::string UnParse(void) { return ""; }
  std::string CppCode(void) { return ""; }
};

/*!
 * Stmt (Abstract)
 * This is the abstract for all Stmt type classes.
 */
class Stmt : public Node {
 public:
  virtual std::string UnParse(void) { return "This should be pure virtual";}
};

/*!
 * Stmts ::= Stmt Stmts
 * This class is the representation of multiple statements.
 */
class MultiStmts : public Stmts {
 public:
  MultiStmts(Stmt* s, Stmts* ss) { stmt_ = s, stmts_ = ss; }
  Stmt* stmt() { return stmt_; }
  void set_stmt(Stmt* s) { stmt_ = s; }
  Stmts* stmts() { return stmts_; }
  void set_stmts(Stmts* ss) { stmts_ = ss; }
  std::string UnParse(void) { return stmt_->UnParse() + stmts_->UnParse(); }
  std::string CppCode(void) { return stmt_->CppCode() + stmts_->CppCode(); }

 private:
  Stmt* stmt_;
  Stmts* stmts_;
};


/*!
 * Stmt ::= Decl
 * This class is the representation of decleration statement.
 */
class DeclStmt : public Stmt {
 public:
  explicit DeclStmt(Decl* d) { decl_ = d;}
  Decl* decl() { return decl_; }
  void set_decl(Decl* d) { decl_ = d; }
  std::string UnParse(void) { return decl_->UnParse(); }
  std::string CppCode(void) { return decl_->CppCode(); }

 private:
  Decl* decl_;
};


/*!
 * Stmt ::= '{' Stmts '}'
 * This class is the representation of block statements.
 */
class BlockStmt : public Stmt {
 public:
  explicit BlockStmt(Stmts* s) { stmts_ = s; }
  Stmts* stmts() { return stmts_; }
  void set_stmts(Stmts* s) { stmts_ = s; }
  std::string UnParse(void) { return " {" + stmts_->UnParse() + "} "; }
  std::string CppCode(void) { return " {" + stmts_->CppCode() + "} "; }

 private:
  Stmts* stmts_;
};

/*!
 * Stmt ::= 'if' '(' Expr ')' Stmt
 * This class is the representation of if statement.
 */
class IfStmt : public Stmt {
 public:
  IfStmt(Expr* e, Stmt* s) { expr_ = e; stmt_ = s; }
  Expr* expr() { return expr_; }
  void set_expr(Expr* e) { expr_ = e; }
  Stmt* stmt() { return stmt_; }
  void set_stmt(Stmt* s) { stmt_ = s; }
  std::string UnParse(void) {
          return "if (" + expr_->UnParse() + ") " + stmt_->UnParse(); }
  std::string CppCode(void) {
    return "if (" + expr_->CppCode() + ") {\n  " + stmt_->CppCode() + "}";
  }

 private:
  Expr* expr_;
  Stmt* stmt_;
};

/*!
 * Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
 * This class is the representation of if-else statement.
 */
class IfElseStmt : public Stmt {
 public:
  IfElseStmt(Expr* e, Stmt* ts, Stmt* es) {
                expr_ = e; then_stmt_ = ts; else_stmt_ = es; }
  Expr* expr() { return expr_; }
  void set_expr(Expr* e) { expr_ = e; }
  Stmt* then_stmt() { return then_stmt_; }
  void set_then_stmt(Stmt* s) { then_stmt_ = s; }
  Stmt* else_stmt() { return else_stmt_; }
  void set_else_stmt(Stmt* s) { else_stmt_ = s; }
  std::string UnParse(void) { return "if (" + expr_->UnParse() + ") " + \
                then_stmt_->UnParse() + " else " + else_stmt_->UnParse(); }

  std::string CppCode() {
    return "if (" + expr_->CppCode() + ") {\n  " + \
      then_stmt_->CppCode() + "} else {\n  " + else_stmt_->CppCode() + "}";
  }

 private:
  Expr* expr_;
  Stmt* then_stmt_;
  Stmt* else_stmt_;
};

/*!
 * Stmt ::= varName '=' Expr ';'
 * This class is the representation of assign statement.
 */
class AssignStmt : public Stmt {
 public:
  AssignStmt(std::string s, Expr* e) { name_ = s; expr_ = e; }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  Expr* expr() { return expr_; }
  void set_expr(Expr* e) { expr_ = e; }
  std::string UnParse(void) { return name_ + " = " + expr_->UnParse() + ";\n"; }
  std::string CppCode(void) { return name_ + " = " + expr_->CppCode() + ";\n"; }
 private:
  std::string name_;
  Expr* expr_;
};

/*!
 * Stmt ::= varName '[' Expr ':' Expr ']' '=' Expr ';'
 * This class is the representation of matrix assignment statement.
 */
class MatrixAssignStmt : public Stmt {
 public:
  MatrixAssignStmt(std::string s, Expr* le, Expr* re, Expr* ee) {
      name_ = s; expr_left_ = le; expr_right_ = re; expr_result_ = ee; }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  Expr* expr_left() { return expr_left_; }
  void set_expr_left(Expr* e) { expr_left_ = e; }
  Expr* expr_right() { return expr_right_; }
  void set_expr_right(Expr* e) { expr_right_ = e; }
  Expr* expr_result() { return expr_result_; }
  void set_expr_result(Expr* e) { expr_result_ = e; }
  std::string UnParse(void) { return name_ + " [" + expr_left_->UnParse() + \
  " : " + expr_right_->UnParse() + "] = " + expr_result_->UnParse()  + ";\n"; }
  std::string CppCode(void) {
    return "*( " + name_ + ".access(" + expr_left_->CppCode() + ", " +\
      expr_right_->CppCode() + ")) = " + expr_result_->CppCode() + ";\n";
  }


 private:
  std::string name_;
  Expr* expr_left_;
  Expr* expr_right_;
  Expr* expr_result_;
};

/*!
 * Stmt ::= 'print' '(' Expr ')' ';'
 * This class is the representation of print statement.
 */
class PrintStmt : public Stmt {
 public:
  explicit PrintStmt(Expr* e) { expr_ = e; }
  Expr* expr() { return expr_; }
  void set_expr(Expr* e) { expr_ = e; }
  std::string UnParse(void) { return "print (" + expr_->UnParse() + ");"; }
  std::string CppCode(void) { return "cout << " + expr_->CppCode() + " ;\n"; }

 private:
  Expr* expr_;
};

/*!
 * Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
 * This class is the representation of repeat statement.
 */
class RepeatStmt : public Stmt {
 public:
  RepeatStmt(std::string name, Expr* le, Expr* ue, Stmt* s) {
     name_ = name; expr_lower_ = le; expr_upper_ = ue; stmt_ = s; }
  Expr* expr_lower() { return expr_lower_; }
  void set_expr_lower(Expr* e) { expr_lower_ = e; }
  Expr* expr_upper() { return expr_upper_; }
  void set_expr_upper(Expr* e) { expr_upper_ = e; }
  Stmt* stmt() { return stmt_; }
  void set_stmt(Stmt* s) { stmt_ = s; }

  std::string UnParse(void) {
     return "repeat (" + name_ + " = " + expr_lower_->UnParse() + " to " + \
         expr_upper_->UnParse() + ")" + stmt_->UnParse();
  }

  std::string CppCode(void) {
    return "for (" + name_ + " = " + expr_lower_->CppCode() + "; " + name_ + \
      " <= " + expr_upper_->CppCode() + "; " + name_ + " ++ )  \n" + \
      + "  " + stmt_->CppCode() + "\n";
  }

 private:
  std::string name_;
  Expr* expr_lower_;
  Expr* expr_upper_;
  Stmt* stmt_;
};

/*!
 * Stmt ::= 'while' '(' Expr ')' Stmt
 * This class is the representation of while statement.
 */
class WhileStmt : public Stmt {
 public:
  explicit WhileStmt(Expr* e, Stmt* s) { expr_ = e; stmt_ = s; }
  Expr* expr() { return expr_; }
  void set_expr(Expr* e) { expr_ = e; }
  Stmt* stmt() { return stmt_; }
  void set_stmt(Stmt* e) { stmt_ = e; }
  std::string UnParse(void) {
           return "while (" + expr_->UnParse() + ") " + stmt_->UnParse(); }
  std::string CppCode() {
    return "while (" + expr_->CppCode() + ") {\n" + stmt_->CppCode() + "}\n";
  }

 private:
  Expr* expr_;
  Stmt* stmt_;
};

/*!
 * Stmt ::= ';'
 * This class is the representation of empty statement.
 */
class EmptyStmt : public Stmt {
 public:
  EmptyStmt(void) {}
  std::string UnParse(void) { return ";\n"; }
  std::string CppCode(void) { return ";\n"; }
};

/*!
 * Expr ::= 'let' Stmts 'in' Expr 'end'
 * This class is the representation of let expression.
 */
class LetExpr : public Expr {
 public:
    LetExpr(Stmts* s, Expr* e) { stmts_ = s; expr_ = e; }
    Stmts* stmts() { return stmts_; }
    void set_stmts(Stmts* s) { stmts_ = s; }
    Expr* expr() { return expr_; }
    void set_expr(Expr* e) { expr_ = e; }
    std::string UnParse() { return "let " + stmts_->UnParse() \
        + "in " + expr_->UnParse() + " end"; }
    std::string CppCode() {
      return "({ " + stmts_->CppCode() + "\n  " + expr_->CppCode() + "; })";
    }

 private:
    Stmts* stmts_;
    Expr* expr_;
};


/*!
 * Program ::= varName '(' ')' '{' Stmts '}'
 * This class is the representation of Program which inherits directly
 * from Node.
 */
class Program : public Node {
 public:
  Program(std::string s, Stmts* stmts) { name_ = s; stmts_ = stmts; }
  std::string name() { return name_; }
  void set_name(std::string s) { name_ = s; }
  Stmts* stmts() { return stmts_; }
  void set_stmts(Stmts* ss) { stmts_ = ss; }
  std::string UnParse() {return name_ + "() {\n" + stmts_->UnParse() + "}";}
  std::string CppCode() {
    std::string headers;
    // headers.append("#include <iostream>\n");
    headers += "#include <iostream>\n#include \"../include/Matrix.h\"\n";
    headers += "#include <math.h>\nusing namespace std;\nint ";
    return headers + name_ + "() {\n" + stmts_->CppCode() + "}";
  }

 private:
  std::string name_;
  Stmts* stmts_;
};

} /* namespace ast */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_AST_H_
