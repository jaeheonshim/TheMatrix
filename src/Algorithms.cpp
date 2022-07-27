#include "Algorithms.h"
#include "Matrix.h"

#include <vector>
#include <random>

namespace Algorithms {
    static std::mt19937 mt{ std::random_device{}() };
    static std::uniform_int_distribution<> range100{ 1, 100 };

    void random_int32(Matrix& mat) {
        for(int i{ 0 }; i < mat.rows; ++i) {
            for(int j{ 0 }; j < mat.cols; ++j) {
                mat[i][j] = range100(mt);
            }
        }
    }

    void ref(Matrix& mat) {
        int row{ 0 };
        int col{};
        // row,col of current pivot

        while(row < mat.rows) {
            // Find leftmost nonzero column 
            for(col = 0; col < mat.cols; ++col) {
                int i{};
                for(i = row; i < mat.rows; ++i) {
                    if(mat[i][col] != 0) break;
                }

                if(i != mat.rows) break;
            }

            // Put a 1 in the topmost position using elementary row operations
            if(mat[row][col] != 1) {
                if(mat[row][col] != 0) {
                    // the top matrix needs to be scaled down, such that the first column is a 1
                    Matrix::MatType scalar{ mat[row][col] };
                    for(int i{ row }; i < mat.cols; ++i) {
                        mat[row][i] /= scalar;
                    }
                }
            }

            // clear out the bottom rows
            for(int i{ row + 1 }; i < mat.rows; ++i) {
                if(mat[i][col] != 0) {
                    Matrix::MatType scalar{ mat[i][col] };
                    for(int j{ 0 }; j < mat.cols; ++j) {
                        mat[i][j] += mat[row][j] * -scalar;
                    }
                }
            }

            ++row;
        }
    }

    void rref(Matrix& mat) {
        ref(mat);
        std::vector<int> pivotColumns; // let's just store the pivot columns in a vector for simplicity

        // first, identify all of the pivot columns
        int row{ 0 };
        int j{ 0 };
        while(row < mat.rows) {
            while(mat[row][j] == 0 && j < mat.cols) ++j;
            ++row;

            if(j < mat.cols) pivotColumns.push_back(j);
            else {
                --row;
                break;
            } // zero row!
        }

        row -= 1;

        // starting with rightmost
        for(std::vector<int>::const_reverse_iterator iter{ pivotColumns.rbegin() }; iter != pivotColumns.rend(); ++iter) {
            int col{ *iter };
            // clear upper rows
            for(int i{ row - 1 }; i >= 0; --i) {
                Matrix::MatType x{ mat[i][col] }; // the value of the column we are trying to clear
                Matrix::MatType scalar{ -x };
                for(int j{ col }; j < mat.cols; ++j) {
                    mat[i][j] += mat[row][j] * scalar;
                }
            }

            --row;
        }
    }
}