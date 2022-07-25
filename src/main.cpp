#include <iostream>
#include <cstdlib>
#include <vector>

#include "Matrix.h"
#include "Algorithms.h"

Matrix readFromStdin();

int main() {
    Matrix matrix{ readFromStdin() };

    Algorithms::rref(matrix);
    std::cout << "In reduced row echelon form:\n";
    std::cout << matrix << '\n';

    return 0;
}

Matrix readFromStdin() {
    int rows{};
    int cols{};

    std::cin >> rows;
    std::cin >> cols;

    Matrix m(rows, cols);
    std::cin >> m;

    return m;
}