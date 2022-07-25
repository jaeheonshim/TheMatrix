#include "Matrix.h"

#include <algorithm>

Matrix::Matrix(int rows, int cols, MatType** data) : rows(rows), cols(cols) {
    this->data = new Matrix::MatType*[rows];
    for(int i{ 0 }; i < rows; ++i) {
        this->data[i] = new Matrix::MatType[cols];
        for(int j{ 0 }; j < cols; ++j) {
            this->data[i][j] = data[i][j];
        }
    }
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    this->data = new Matrix::MatType*[rows];
    for(int i{ 0 }; i < rows; ++i) {
        this->data[i] = new Matrix::MatType[cols];
        std::fill(this->data[i], this->data[i] + cols, 0);
    }
}

Matrix::~Matrix() {
    for(int i{ 0 }; i < rows; ++i) {
        delete this->data[i];
    }

    delete this->data;
}

std::ostream& operator << (std::ostream& o, const Matrix& mat) {
    o << "[";
    for(int i{ 0 }; i < mat.rows; ++i) {
        if(i > 0) std::cout << ' ';
        for(int j{ 0 }; j < mat.cols; ++j) {
            o << mat.data[i][j];
            if(j + 1 != mat.cols) std::cout << " ";
        }
        if(i + 1 != mat.rows) std::cout << '\n';
    }
    o << "]";
    return o;
}

std::istream& operator >> (std::istream& in, Matrix& mat) {
    for(int i{ 0 }; i < mat.rows; ++i) {
        for(int j{ 0 }; j < mat.cols; ++j) {
            in >> mat[i][j];
        }
    }

    return in;
}