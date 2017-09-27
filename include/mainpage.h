/* Copyright [2017] <Son Nguyen> <Yu Fang> */

#ifndef PROJECT_INCLUDE_MAINPAGE_H_
#define PROJECT_INCLUDE_MAINPAGE_H_

/*! \mainpage Fcal translator mainpage

\section info_sec Information
  This program is an translator for fcal language, and the output will be a file with
cpp extension. This program currently contain scanner and parser parts.

\subsection scanner Scanner
  Scanner will scan the input dsl file, and output a list of tokens to be passed
on to parser to be parsed. By successfully generating the list of tokens, the input
file is syntatically corret, otherwise it contains syntax errors.

\subsection parser Parser
  Parser will take the input as list of tokens, and generate an abstract syntax tree.
By successfully generating the tree, the input file is grammatically correct, otherwise
it contains grammatically errors and cannot be parsed.

 */

#endif  // PROJECT_INCLUDE_MAINPAGE_H_
