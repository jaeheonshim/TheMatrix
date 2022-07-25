#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

struct Matrix {
    using MatType = double;
    MatType** data;
    const int rows = 0;
    const int cols = 0;

    Matrix(int rows, int cols, MatType** data);
    Matrix(int rows, int cols);
    ~Matrix();

    MatType* operator [] (int i) {
        return data[i];
    }
};

std::ostream& operator << (std::ostream& o, const Matrix& mat);
std::istream& operator >> (std::istream& in, Matrix& mat);

#endif