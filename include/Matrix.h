/*******************************************************************************
 * Name            : Matrix.h
 * Project         : fcal
 * Module          : ast
 * Description     : Header file for matrix
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell, Yu Fang, Son Nguyen
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

class matrix {
 public:
    matrix(int i, int j);
    matrix(const matrix& m);

    int n_rows() const;
    int n_cols() const;

    float *access(const int i, const int j) const;
    void modify(int i, int j, float value);
    friend std::ostream& operator<<(std::ostream &os, matrix &m);
    matrix operator*(matrix m);
    void operator=(matrix m);

    static matrix matrix_read(std::string filename);

    ~matrix();

 private:
    matrix() {}
    int rows;
    int cols;

    /* Your implementation of "data" may vary.  There are ways in
       which data can be an array of arrays and thus simplify the
       access method, at the cost of complicating the process of
       allocating space for data.  The choice is entirely up to
       you. */
    float *data;
};

#endif  // PROJECT_INCLUDE_MATRIX_H_
