/*******************************************************************************
 * Name            : templates.cc
 * Author          : Son Nguyen and Yu Fang
 * Project         : Labs
 * Module          : Lab04
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Description     : This file has been taken from:
 *                   http://www.cplusplus.com/doc/tutorial/templates/. It is
 *                   largely a vehicle for experimenting with team work using
 *                   git. Spending time to learn the basics of templating may
 *                   save you time on your project.
 * Original Author : Dan Challou
 * Modifications by: John Harwell Son Nguyen, Yu Fang
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


/*******************************************************************************
 * Class Definitions (Note that these are almost ALWAYS in a header file; can
 * only be in .cc file for trivial cases like this. If you try to separate the
 * interface and implementation of a template class, you will most likely run
 * into linker errors)
 ******************************************************************************/
template <class T, int N>
class MySequence {
 public:
  MySequence(void) : memblock_() {}

  void set_member(int x, T value) {
    memblock_[x] = value;
  }

  T get_member(int x) {
    return memblock_[x];
  }

 private:
  T memblock_[N];
};

/*******************************************************************************
 * Functions
 ******************************************************************************/
// comment
int main() {
  MySequence<int, 5> myints;
  MySequence<double, 5> myfloats;
  myints.set_member(0, 100);
  myfloats.set_member(3, 3.1416);
  std::cout << myints.get_member(0) << '\n';
  std::cout << myfloats.get_member(3) << '\n';
  printf("%s", "Son Nguyen");
  printf("Yu Fang");
  return 0;
}
