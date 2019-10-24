#include <stdexcept>
#include "matrix.h"

bool Matrix::operator==(const Matrix &other) const
{
    if (this == &other)
        return true;
    if ((this->columns != other.columns) || (this->rows != other.rows)) {
        return false;
    }
    for (size_t i = 0; i < other.rows * other.columns; ++i)
        if (this->data[i] != other.data[i])
            return false;
    return true;
}

bool Matrix::operator!=(const Matrix &other) const
{
    return !(*this == other);
}

size_t Matrix::getRows()
{
    return rows;
}

size_t Matrix::getColumns()
{
    return columns;
}

Matrix::Matrix(size_t rows, size_t columns)
{
    this->rows = rows;
    this->columns = columns;
    data = new int[rows * columns];
    for (size_t i = 0; i < rows * columns; ++i) {
        data[i] = 0;
    }
}

Matrix::~Matrix()
{
    delete[] data;
}

const Matrix &Matrix::operator*=(int arg)
{
    for (size_t i = 0; i < rows * columns; ++i)
        data[i] *= arg;
    return *this;
}

Matrix::proxy Matrix::operator[](size_t i) const {
    if (i >= rows) {
        throw std::out_of_range("");
    }
    return proxy(*this, i);
}
