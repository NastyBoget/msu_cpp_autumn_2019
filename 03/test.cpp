#include <iostream>
#include <cassert>
#include "matrix.h"

int main() {
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);
    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);
    double x = m[4][1];
    assert(x == 0);
    m[1][2] = 5; // строка 1, колонка 2
    m *= 3; // умножение на число
    assert(m[1][2] == 15);
    Matrix m1(rows, cols);
    Matrix m2(rows, cols);
    assert(m1 != m);
    assert(m1 == m2);
    const Matrix m3(rows, cols);
    x = m3[1][1];
	//m3[0][0] = 9;
    std::cout << "done" << std::endl;
    return 0;
}
