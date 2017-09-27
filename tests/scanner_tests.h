/* Copyright [2017] <Son Nguyen> <Yu Fang> */

#ifndef PROJECT_TESTS_SCANNER_TESTS_H_
#define PROJECT_TESTS_SCANNER_TESTS_H_

#include <cxxtest/TestSuite.h>

#include <stdio.h>
#include "include/read_input.h"
#include "include/scanner.h"

// using namespace std;
namespace scanner = fcal::scanner;
class ScannerTestSuite : public CxxTest::TestSuite {
 public:
    /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
     */
    scanner::Scanner *s;
    void test_setup_code() {
      s = new scanner::Scanner();
      s->init_regex();
    }


    // Tests for components and functions used by "scan"
    // --------------------------------------------------

    /* You should test the regular expressions you use to make and match
       regular expressions,and the functions used by makeRegex and
       matchRegex regex_tests.h.
       However, You will likely need to write several tests to
       adequately test  the functions that are called from "scan".
       Once you are confident that the components used by "scan"
       work properly, then you can run tests on the "scan" method itself.
    */

    /* testing the init_regex() */
    void test_intKwd_regex() {
        regex_t *re = s->regexes[scanner::kIntKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "int 123");
        TS_ASSERT_EQUALS(num_matched_chars, 3);
        }
    void test_floatKwd_regex() {
        regex_t *re = s->regexes[scanner::kFloatKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "float 123.0");
        TS_ASSERT_EQUALS(num_matched_chars, 5);
        }
    void test_stringKwd_regex() {
        regex_t *re = s->regexes[scanner::kStringKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "string abc");
        TS_ASSERT_EQUALS(num_matched_chars, 6);
        }
    void test_matrixKwd_regex() {
        regex_t *re = s->regexes[scanner::kMatrixKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "matrix [1 2]");
        TS_ASSERT_EQUALS(num_matched_chars, 6);
        }
    void test_letKwd_regex() {
        regex_t *re = s->regexes[scanner::kLetKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "let a = b");
        TS_ASSERT_EQUALS(num_matched_chars, 3);
        }
    void test_inKwd_regex() {
        regex_t *re = s->regexes[scanner::kInKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "in (blabla)");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_endKwd_regex() {
        regex_t *re = s->regexes[scanner::kEndKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "end //comment");
        TS_ASSERT_EQUALS(num_matched_chars, 3);
        }
    void test_ifKwd_regex() {
        regex_t *re = s->regexes[scanner::kIfKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "if (a = 6)");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_thenKwd_regex() {
        regex_t *re = s->regexes[scanner::kThenKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "then codeBody");
        TS_ASSERT_EQUALS(num_matched_chars, 4);
        }
    void test_elseKwd_regex() {
        regex_t *re = s->regexes[scanner::kElseKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "else codeBody");
        TS_ASSERT_EQUALS(num_matched_chars, 4);
        }
    void test_repeatKwd_regex() {
        regex_t *re = s->regexes[scanner::kRepeatKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "repeat; ");
        TS_ASSERT_EQUALS(num_matched_chars, 6);
        }
    void test_printKwd_regex() {
        regex_t *re = s->regexes[scanner::kPrintKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "print(i)");
        TS_ASSERT_EQUALS(num_matched_chars, 5);
        }
    void test_toKwd_regex() {
        regex_t *re = s->regexes[scanner::kToKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "to b");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_trueKwd_regex() {
        regex_t *re = s->regexes[scanner::kTrueKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "True ");
        TS_ASSERT_EQUALS(num_matched_chars, 4);
        }
    void test_falseKwd_regex() {
        regex_t *re = s->regexes[scanner::kFalseKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "False ");
        TS_ASSERT_EQUALS(num_matched_chars, 5);
        }
    void test_whileKwd_regex() {
        regex_t *re = s->regexes[scanner::kWhileKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "while (a < b)");
        TS_ASSERT_EQUALS(num_matched_chars, 5);
        }
    void test_boolKwd_regex() {
        regex_t *re = s->regexes[scanner::kBoolKwd];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "boolean check");
        TS_ASSERT_EQUALS(num_matched_chars, 7);
        }

    // const
    void test_intConst_regex() {
        regex_t *re = s->regexes[scanner::kIntConst];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "123456");
        TS_ASSERT_EQUALS(num_matched_chars, 6);
        }
    void test_floatConst_regex() {
        regex_t *re = s->regexes[scanner::kFloatConst];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "123.456");
        TS_ASSERT_EQUALS(num_matched_chars, 7);
        }
    void test_stringConst_regex() {
        regex_t *re = s->regexes[scanner::kStringConst];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "\"aaa\"");
        TS_ASSERT_EQUALS(num_matched_chars, 5);
        }
    void test_varName_regex() {
        regex_t *re = s->regexes[scanner::kVariableName];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "tempVar_");
        TS_ASSERT_EQUALS(num_matched_chars, 8);
        }

    // punctuation
    void test_leftParen_regex() {
        regex_t *re = s->regexes[scanner::kLeftParen];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "(int a)");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_rightParen_regex() {
        regex_t *re = s->regexes[scanner::kRightParen];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, ") ");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_leftCur_regex() {
        regex_t *re = s->regexes[scanner::kLeftCurly];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "{func(i)}");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_rightCur_regex() {
        regex_t *re = s->regexes[scanner::kRightCurly];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "} ");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_leftSquar_regex() {
        regex_t *re = s->regexes[scanner::kLeftSquare];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "[a-z]");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_rightSquar_regex() {
        regex_t *re = s->regexes[scanner::kRightSquare];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "] ");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_semiCol_regex() {
        regex_t *re = s->regexes[scanner::kSemiColon];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "; ");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_colon_regex() {
        regex_t *re = s->regexes[scanner::kColon];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, ": ");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }

    // operation
    void test_assign_regex() {
        regex_t *re = s->regexes[scanner::kAssign];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "= b");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_plus_regex() {
        regex_t *re = s->regexes[scanner::kPlusSign];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "+= b");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_star_regex() {
        regex_t *re = s->regexes[scanner::kStar];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "* b");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_forwarsSlash_regex() {
        regex_t *re = s->regexes[scanner::kForwardSlash];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "// comment");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_lessThan_regex() {
        regex_t *re = s->regexes[scanner::kLessThan];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "< index");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_lessThanEqual_regex() {
        regex_t *re = s->regexes[scanner::kLessThanEqual];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "<= index");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_greaterThan_regex() {
        regex_t *re = s->regexes[scanner::kGreaterThan];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "> index");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }
    void test_greaterThanEqual_regex() {
        regex_t *re = s->regexes[scanner::kGreaterThanEqual];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, ">= index");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_equalEquals_regex() {
        regex_t *re = s->regexes[scanner::kEqualsEquals];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "== index");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_notEquals_regex() {
        regex_t *re = s->regexes[scanner::kNotEquals];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "!= index");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_andOp_regex() {
        regex_t *re = s->regexes[scanner::kAndOp];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "&& cond");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_orOp_regex() {
        regex_t *re = s->regexes[scanner::kOrOp];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "|| cond");
        TS_ASSERT_EQUALS(num_matched_chars, 2);
        }
    void test_notOp_regex() {
        regex_t *re = s->regexes[scanner::kNotOp];
        TS_ASSERT(re);
        int num_matched_chars = fcal::scanner::match_regex(re, "! cond");
        TS_ASSERT_EQUALS(num_matched_chars, 1);
        }


    // You should place tests for these other functions used by
    // scan below.

    /* testing the find_TokenType*/
    void test_terminal_intKwd() {
        fcal::scanner::Result ret = s->find_TokenType("int 123");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 3);
        TS_ASSERT(ret.type == fcal::scanner::kIntKwd);
        }
    void test_terminal_floatKwd() {
        fcal::scanner::Result ret = s->find_TokenType("float 123.0");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 5);
        TS_ASSERT(ret.type == fcal::scanner::kFloatKwd);
        }
    void test_terminal_stringKwd() {
        fcal::scanner::Result ret = s->find_TokenType("string abc");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 6);
        TS_ASSERT(ret.type == fcal::scanner::kStringKwd);
        }
    void test_terminal_matrixKwd() {
        fcal::scanner::Result ret = s->find_TokenType("matrix [1 2]");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 6);
        TS_ASSERT(ret.type == fcal::scanner::kMatrixKwd);
        }
    void test_terminal_letKwd() {
        fcal::scanner::Result ret = s->find_TokenType("let a = b");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 3);
        TS_ASSERT(ret.type == fcal::scanner::kLetKwd);
        }
    void test_terminal_inKwd() {
        fcal::scanner::Result ret = s->find_TokenType("in (blabla)");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kInKwd);
        }
    void test_terminal_endKwd() {
        fcal::scanner::Result ret = s->find_TokenType("end   // comment");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 3);
        TS_ASSERT(ret.type == fcal::scanner::kEndKwd);
        }
    void test_terminal_ifKwd() {
        fcal::scanner::Result ret = s->find_TokenType("if (a=1)");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kIfKwd);
        }
    void test_terminal_thenKwd() {
        fcal::scanner::Result ret = s->find_TokenType("then codeBody");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 4);
        TS_ASSERT(ret.type == fcal::scanner::kThenKwd);
        }
    void test_terminal_elseKwd() {
        fcal::scanner::Result ret = s->find_TokenType("else codeBody");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 4);
        TS_ASSERT(ret.type == fcal::scanner::kElseKwd);
        }
    void test_terminal_repeatKwd() {
        fcal::scanner::Result ret = s->find_TokenType("repeat; ");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 6);
        TS_ASSERT(ret.type == fcal::scanner::kRepeatKwd);
        }
    void test_terminal_printKwd() {
        fcal::scanner::Result ret = s->find_TokenType("print(i)");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 5);
        TS_ASSERT(ret.type == fcal::scanner::kPrintKwd);
        }
    void test_terminal_toKwd() {
        fcal::scanner::Result ret = s->find_TokenType("to b");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kToKwd);
        }
    void test_terminal_falseKwd() {
        fcal::scanner::Result ret = s->find_TokenType("False ");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 5);
        TS_ASSERT(ret.type == fcal::scanner::kFalseKwd);
        }
    void test_terminal_trueKwd() {
        fcal::scanner::Result ret = s->find_TokenType("True ");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 4);
        TS_ASSERT(ret.type == fcal::scanner::kTrueKwd);
        }
    void test_terminal_whileKwd() {
        fcal::scanner::Result ret = s->find_TokenType("while (a < b)");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 5);
        TS_ASSERT(ret.type == fcal::scanner::kWhileKwd);
        }
    void test_terminal_booleanKwd() {
        fcal::scanner::Result ret = s->find_TokenType("boolean check;");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 7);
        TS_ASSERT(ret.type == fcal::scanner::kBoolKwd);
        }

    // const
    void test_terminal_intConst() {
        fcal::scanner::Result ret = s->find_TokenType("123456");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 6);
        printf ("%d\n", ret.type);
        TS_ASSERT(ret.type == fcal::scanner::kIntConst);
        }
    void test_terminal_floatConst() {
        fcal::scanner::Result ret = s->find_TokenType("123.456");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 7);
        TS_ASSERT(ret.type == fcal::scanner::kFloatConst);
        }
    void test_terminal_stringConst() {
        fcal::scanner::Result ret = s->find_TokenType("\"aaa\"");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 5);
        TS_ASSERT(ret.type == fcal::scanner::kStringConst);
        }
    void test_terminal_varName() {
        fcal::scanner::Result ret = s->find_TokenType("tempVar_");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 8);
        TS_ASSERT(ret.type == fcal::scanner::kVariableName);
        }

    // punctuation
    void test_terminal_leftParen() {
        fcal::scanner::Result ret = s->find_TokenType("(int a)");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kLeftParen);
        }
    void test_terminal_rightParen() {
        fcal::scanner::Result ret = s->find_TokenType(") ");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kRightParen);
        }
    void test_terminal_leftCur() {
        fcal::scanner::Result ret = s->find_TokenType("{ expressions }");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kLeftCurly);
        }
    void test_terminal_rightCur() {
        fcal::scanner::Result ret = s->find_TokenType("} ");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kRightCurly);
        }
    void test_terminal_leftSquar() {
        fcal::scanner::Result ret = s->find_TokenType("[ exp ]");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kLeftSquare);
        }
    void test_terminal_rightSquar() {
        fcal::scanner::Result ret = s->find_TokenType("] ");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kRightSquare);
        }
    void test_terminal_semiColon() {
        fcal::scanner::Result ret = s->find_TokenType("; ");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kSemiColon);
        }
    void test_terminal_Colon() {
        fcal::scanner::Result ret = s->find_TokenType(": ");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kColon);
        }

    // operation
    void test_terminal_Assign() {
        fcal::scanner::Result ret = s->find_TokenType("= b");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kAssign);
        }
    void test_terminal_Star() {
        fcal::scanner::Result ret = s->find_TokenType("* b");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kStar);
        }
    void test_terminal_Dash() {
        fcal::scanner::Result ret = s->find_TokenType("- b");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kDash);
        }
    void test_terminal_ForwardSlash() {
        fcal::scanner::Result ret = s->find_TokenType("// comment");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kForwardSlash);
        }
    void test_terminal_lessThan() {
        fcal::scanner::Result ret = s->find_TokenType("< index");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kLessThan);
        }
    void test_terminal_lessThanEqual() {
        fcal::scanner::Result ret = s->find_TokenType("<= index");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kLessThanEqual);
        }
    void test_terminal_greaterThan() {
        fcal::scanner::Result ret = s->find_TokenType("> index");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kGreaterThan);
        }
    void test_terminal_greaterThanEqual() {
        fcal::scanner::Result ret = s->find_TokenType(">= index");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kGreaterThanEqual);
        }
    void test_terminal_equalEquals() {
        fcal::scanner::Result ret = s->find_TokenType("== index");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kEqualsEquals);
        }
    void test_terminal_notEquals() {
        fcal::scanner::Result ret = s->find_TokenType("!= index");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kNotEquals);
        }
    void test_find_andOp() {
        fcal::scanner::Result ret = s->find_TokenType("&& cond");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kAndOp);
        }
    void test_terminal_orOp() {
        fcal::scanner::Result ret = s->find_TokenType("|| cond");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 2);
        TS_ASSERT(ret.type == fcal::scanner::kOrOp);
        }
    void test_terminal_NotOp() {
        fcal::scanner::Result ret = s->find_TokenType("!cond");
        int result = ret.length;
        TS_ASSERT_EQUALS(result, 1);
        TS_ASSERT(ret.type == fcal::scanner::kNotOp);
        }


    /* Below is one of the tests for these components in the project
       solution created by your instructor.  It uses a helper
       function function called "tokenMaker_tester", which you have
       not been given.  You are expected to design your own components
       for "scan" and your own mechanisms for easily testing them.

        void xtest_TokenMaker_leftCurly () {
            tokenMaker_tester ("{ ", "^\\{", leftCurly, "{");
        }

        Note that this test is here named "xtest_Token..." The leading
        "x" is so that cxxTest doesn't scan the line above and think
        it is an actual test that isn't commented out.  cxxTest is
        very simple and doesn't even process block comments.
    */


    /* You must have at least one separate test case for each terminal
       symbol.  Thus, you need a test that will pass or fail based
       solely on the regular expression (and its corresponding code)
       for each terminal symbol.

       This requires a test case for each element of the enumerated
       type tokenType.  This may look something like the sample test
       shown in the comment above.
    */

    void token_tester(const char* success, const char* fail,
                        scanner::kTokenEnumType type) {
        scanner::Token *tks_success = s->Scan(success);
        scanner::Token *tks_fail = s->Scan(fail);
        // TS_ASSERT(tks_fail != NULL);
        TS_ASSERT(tks_success->terminal() == type);
        TS_ASSERT(tks_fail->terminal() != type);
        }

    void test_intKwd_token() {
        token_tester("   int b", "float b", fcal::scanner::kIntKwd);
        }
    void test_floatKwd_token() {
        token_tester("  float 123.0", "123.3", fcal::scanner::kFloatKwd);
        }
    void test_stringKwd_token() {
        token_tester(" string* obj", "\"a_string\"", fcal::scanner::kStringKwd);
        }
    void test_matrixKwd_token() {
        token_tester(" matrix* mat;", "mateix", fcal::scanner::kMatrixKwd);
        }
    void test_letKwd_token() {
        token_tester(" let a = b", " (let )", fcal::scanner::kLetKwd);
        }
    void test_inKwd_token() {
        token_tester(" in (range a-b)", "blabla", fcal::scanner::kInKwd);
        }
    void test_endKwd_token() {
        token_tester("  end; ", "} end", fcal::scanner::kEndKwd);
        }
    void test_ifKwd_token() {
        token_tester("  if (i < 10) {}", "else if", fcal::scanner::kIfKwd);
        }
    void test_thenKwd_token() {
        token_tester(" then let a = b", "(then )", fcal::scanner::kThenKwd);
        }
    void test_elseKwd_token() {
        token_tester(" else codeBody", "; else", fcal::scanner::kElseKwd);
        }
    void test_repeatKwd_token() {
        token_tester("   repeat (exp)", "}; repeat", fcal::scanner::kRepeatKwd);
        }
    void test_PrintKwd_token() {
        token_tester(" print(i)", "then print(i)", fcal::scanner::kPrintKwd);
        }
    void test_ToKwd_token() {
        token_tester("  to b", "from a to b", fcal::scanner::kToKwd);
        }
    void test_intConst_token() {
        token_tester("  123456", "123.456", fcal::scanner::kIntConst);
        }
    void test_floatConst_token() {
        token_tester("  123.456", "123456", fcal::scanner::kFloatConst);
        }
    void test_stringConst_token() {
        token_tester("  \"a string__\"", "string", fcal::scanner::kStringConst);
        }
    void test_varName_token() {
        token_tester("  matrix_read()", "  string* var", scanner::kVariableName);
        }
    void test_leftParen_token() {
        token_tester("  (i++)", " for (i++)", fcal::scanner::kLeftParen);
        }
    void test_rightParen_token() {
        token_tester("  )", " ( )", fcal::scanner::kRightParen);
        }
    void test_leftCur_token() {
        token_tester("  { func() }", " main { }", fcal::scanner::kLeftCurly);
        }
    void test_rightCur_token() {
        token_tester("  }", " { }", fcal::scanner::kRightCurly);
        }
    void test_leftSquare_token() {
        token_tester("  [ func() ]", " in [ ]", fcal::scanner::kLeftSquare);
        }
    void test_rightSquare_token() {
        token_tester("  ]", " [ ]", fcal::scanner::kRightSquare);
        }
    void test_semiCol_token() {
        token_tester("  ;", " );", fcal::scanner::kSemiColon);
        }
    void test_colon_token() {
        token_tester("  ::func", " var:", fcal::scanner::kColon);
        }
    void test_assign_token() {
        token_tester(" = b", " == b", fcal::scanner::kAssign);
        }
    void test_plus_token() {
        token_tester(" += b", "\"+\"", fcal::scanner::kPlusSign);
        }
    void test_star_token() {
        token_tester(" *b", "\"*\"", fcal::scanner::kStar);
        }
    void test_dash_token() {
        token_tester(" -= b", "\"-\"", fcal::scanner::kDash);
        }
    void test_forwardSlash_token() {
        token_tester(" // aaa", " \\", fcal::scanner::kForwardSlash);
        }
    void test_lessThan_token() {
        token_tester(" < index", " <= index", fcal::scanner::kLessThan);
        }
    void test_lessThanEqual_token() {
        token_tester(" <= index", " < index", fcal::scanner::kLessThanEqual);
        }
    void test_greaterThan_token() {
        token_tester(" > index", " >= index", fcal::scanner::kGreaterThan);
        }
    void test_greaterThanEqual_token() {
        token_tester(" >= index", " > index", fcal::scanner::kGreaterThanEqual);
        }
    void test_equalEquals_token() {
        token_tester(" == index", " = index", fcal::scanner::kEqualsEquals);
        }
    void test_notEquals_token() {
        token_tester(" != index", " ! index", fcal::scanner::kNotEquals);
        }
    void test_andOp_token() {
        token_tester(" && cond", " & cond", fcal::scanner::kAndOp);
        }
    void test_orOp_token() {
        token_tester(" || cond", " | cond", fcal::scanner::kOrOp);
        }
    void test_notOp_token() {
        token_tester(" ! cond", " != cond", fcal::scanner::kNotOp);
        }

    /* tests for terminal types */
    // testing kEndOfFile
    int count_endOfFile(scanner::Token *tks) {
        int count = 0;
        scanner::Token *curToken = tks;
        while (curToken != NULL) {
            if (curToken->terminal() == scanner::kEndOfFile) {
                count++;
                }
            curToken = curToken->next();
        }
        return count;
    }

    void test_kEndOfFile() {
        const char *exp = "{int a; float b; if (a <= b) then print a;}";
        scanner::Token *tks = s->Scan(exp);
        // TS_ASSERT(tks);
        TS_ASSERT(count_endOfFile(tks) == 1);
        }

    // testing kLexicalError
    int count_lexError(scanner::Token *tks) {
        int count = 0;
        scanner::Token *curToken = tks;
        while (curToken != NULL) {
            if (curToken->terminal() == scanner::kLexicalError) {
                count++;
                }
            curToken = curToken->next();
        }
        return count;
        }

    void test_lexicalError() {
        const char *exp = "{int a; @ float b; if (a <= b) # $}";
        scanner::Token *tks = s->Scan(exp);
        TS_ASSERT(count_lexError(tks) == 3);
        }

    // Tests for "scan"
    // --------------------------------------------------

    /* Below are some helper functions and sample tests for testing the
       "scan" method on Scanner.
    */

    // Test that a list of tokens has no lexicalError tokens.
    bool noLexicalErrors(scanner::Token *tks) {
        scanner::Token *currentToken = tks;
        while (currentToken != NULL) {
          if (currentToken->terminal() == scanner::kLexicalError) {
              printf("problem: %s\n", currentToken->lexeme().c_str());
              fflush(stdout);
                                return false;
            } else {
              currentToken = currentToken->next();
            }
        }
        return true;
    }

    /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned.
    */
    void scanFileNoLexicalErrors(const char* filename) {
        char *text =  scanner::ReadInputFromFile(filename);
        TS_ASSERT(text);
        scanner::Token *tks = s->Scan(text);
        TS_ASSERT(tks != NULL);
        TS_ASSERT(noLexicalErrors(tks));
    }


    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
  bool sameTerminals(scanner::Token *tks, int numTerms,
                     scanner::TokenType *ts) {
        scanner::Token *currentToken = tks;
        int termIndex = 0;
        while (currentToken != NULL && termIndex < numTerms) {
            if (currentToken->terminal() != ts[termIndex]) {
              printf("item at index: %i: terminal: %i should be terminal: %i\n",
                  termIndex, currentToken->terminal(), ts[termIndex]);
              fflush(stdout);
              return false;
            } else {
                ++termIndex;
                currentToken = currentToken->next();
            }
        }
        return true;
    }


    /* Below are the provided test files that your code should also
       pass.

       You may initially want to rename these tests to "xtest_..." so
       that the CxxTest framework does not see it as a test and won't
       run it as one.  This way you can focus on the tests that you'll
       write above for the individual terminal types first. Then focus
       on these tests.

    */

    // The "endOfFile" token is always the last one in the list of tokens.
    void test_scan_empty() {
        scanner::Token *tks = s->Scan("  ");
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
        TS_ASSERT(tks->next() == NULL);
    }

    void test_scan_empty_comment() {
        scanner::Token *tks = s->Scan(" /* a comment */ ");
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
        TS_ASSERT(tks->next() == NULL);
    }

    // When a lexical error occurs, the scanner creates a token with a
    // single-character lexeme and lexicalError as the terminal.
    void test_scan_lexicalErrors() {
        scanner::Token *tks = s->Scan("$&1  ");
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal(), scanner::kLexicalError);
        TS_ASSERT_EQUALS(tks->lexeme(), "$");
        tks = tks->next();
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal(), scanner::kLexicalError);
        TS_ASSERT_EQUALS(tks->lexeme(), "&");
        tks = tks->next();
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal(), scanner::kIntConst);
        TS_ASSERT_EQUALS(tks->lexeme(), "1");
        tks = tks->next();
        TS_ASSERT(tks != NULL);
        TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
        TS_ASSERT(tks->next() == NULL);
    }


    // A test for scanning numbers and a variable.

    void test_scan_nums_vars() {
        scanner::Token *tks = s->Scan(" 123 x 12.34 ");
        TS_ASSERT(tks != NULL);
        scanner::TokenType ts[] = { scanner::kIntConst, scanner::kVariableName,
                                    scanner::kFloatConst, scanner::kEndOfFile };
        TS_ASSERT(sameTerminals(tks, 4, ts));
    }


    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexemes
       are correct.
     */

    void test_scan_bad_syntax_good_tokens() {
        const char *filename = "./samples/bad_syntax_good_tokens.dsl";
        char *text =  scanner::ReadInputFromFile(filename);
        TS_ASSERT(text);
        scanner::Token *tks = NULL;
        tks = s->Scan(text);
        TS_ASSERT(tks != NULL);
        scanner::TokenType ts[] = {
          scanner::kIntConst, scanner::kIntConst,
          scanner::kIntConst, scanner::kIntConst,
          scanner::kStringConst, scanner::kStringConst, scanner::kStringConst,
          scanner::kFloatConst, scanner::kFloatConst, scanner::kFloatConst,
          scanner::kMatrixKwd,
          scanner::kSemiColon, scanner::kColon, scanner::kToKwd,
          scanner::kLeftCurly, scanner::kLeftParen,
          scanner::kRightCurly, scanner::kRightParen,
          scanner::kPlusSign, scanner::kStar, scanner::kDash,
          scanner::kForwardSlash,
          scanner::kEqualsEquals, scanner::kLessThanEqual,
          scanner::kGreaterThanEqual, scanner::kNotEquals,
          scanner::kAssign,
          scanner::kVariableName, scanner::kVariableName,
          scanner::kVariableName, scanner::kVariableName,
          scanner::kVariableName, scanner::kVariableName,
          scanner::kVariableName,
          scanner::kIntKwd, scanner::kFloatKwd, scanner::kStringKwd,
          scanner::kEndOfFile
        };
        int count = 38;
        TS_ASSERT(sameTerminals(tks, count, ts));
    }

    void test_scan_sample_forestLoss() {
        scanFileNoLexicalErrors("./samples/forest_loss_v2.dsl");
    }
};

#endif  // PROJECT_TESTS_SCANNER_TESTS_H_
