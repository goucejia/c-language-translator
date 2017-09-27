/*******************************************************************************
 * Name            : Matrix.cc
 * Project         : fcal
 * Module          : Matrix Class Implementatioon
 * Description     : This file provides implementation for matrix class
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Son Nguyen
 * Modifications by: Son Nguyen, Yu Fang
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "../include/Matrix.h"

matrix::matrix(int i, int j) {
    rows = i;
    cols = j;
    data = new float[i*j];
}

matrix::matrix(const matrix& m) {
    rows = m.n_rows();
    cols = m.n_cols();
    data = new float[cols * rows];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i*cols + j] = *m.access(i, j);
        }
    }
}

int matrix::n_rows(void) const {
    return rows;
}

int matrix::n_cols(void) const {
    return cols;
}

float* matrix::access(const int i, const int j) const {
    if (i >= rows || j >= cols) {
        printf("Index out of bound %d, %d, %d\n", i, j, cols);
        exit(1);
    }
    return &data[i*cols + j];
}

void matrix::modify(int i, int j, float value) {
    if (i >= rows || j >= cols) {
        printf("Index out of bound MM %d, %d\n", i, j);
        exit(1);
    }
    data[i*cols + j] = value;
}

std::ostream& operator<<(std::ostream &os, matrix &m) {
    os << m.n_rows() << " " << m.n_cols() <<"\n";
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            os << *m.access(i, j) << "  ";
        }
        os << "\n";
    }
    return os;
}

matrix matrix::operator*(matrix m) {
    if (cols != m.rows) {
        perror("Invalid matrix dimesion");
        exit(1);
    }

    matrix result = matrix(rows, m.n_cols());
    int sum;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < m.n_cols(); j++) {
            sum = 0;
            for (int k = 0; k < cols; k++) {
                sum += data[i * cols + k]*(*m.access(k, j));
            }
            *(result.access(i, j)) = sum;
        }
    }
    return result;
}

void matrix::operator=(matrix m) {
    if (data != m.access(0, 0)) {
        if (data != 0)
            delete[] data;
        rows = m.n_rows();
        cols = m.n_cols();
        data = new float[rows * cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i*cols + j] = *m.access(i, j);
            }
        }
    }
}

matrix matrix::matrix_read(std::string filename) {
    std::ifstream t(filename.c_str());
    std::string content((std::istreambuf_iterator<char>(t)),
                       (std::istreambuf_iterator<char>()));
    int row = 1;
    int col = 1;
    if (content.length() == 0) {
        return matrix(0, 0);
    }

    std::string tem;
    int index = 0;
    while (content[index] != '\n') {
      if (content[index] == ' ' && content[index+1] != ' ') {
        row = strtof(tem.c_str(), NULL);
        tem = "";
      } else {
        tem += content[index];
      }
      index++;
    }
    col = strtof(tem.c_str(), NULL);
    index++;
    tem ="";

    matrix result = matrix(row, col);
    int r = 0;
    int c = 0;
    float a;
    for (int i = index; i < content.length(); i++) {
        if (content[i] == ' ' && content[i+1] != ' ') {
            a = strtof(tem.c_str(), NULL);
            *(result.access(r, c)) = a;
            c++;
            tem = "";
        } else {}
        if (content[i] == '\n' && content[i+1] != '\n') {
            a = strtof(tem.c_str(), NULL);
            *(result.access(r, c)) = a;
            r++;
            c = 0;
            tem ="";
        } else {
            tem += content[i];
        }
    }
    return result;
}

matrix::~matrix() {
    delete[] data;
}

/*int main(){
    matrix m = matrix(2, 2);
    m.modify(0,0, 1);
    m.modify(0,1, 2);
    m.modify(1,0, 3);
    m.modify(1,1, 4);
    std::cout << m.n_cols() << "  " << m.n_rows() << "\n";
    std::cout << *m.access(0,1) << "  " << *m.access(1,1) <<"\n";
    std::cout << m;
    matrix n = m*m;
    std::cout << n;
}*/
