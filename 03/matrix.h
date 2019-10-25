#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>

class Matrix
{
public:
    Matrix(size_t rows, size_t columns);
    size_t getRows() const;
    size_t getColumns() const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    const Matrix& operator*=(int arg);
    ~Matrix();
    class proxy {
    public:
        proxy(const Matrix &m, size_t i)
        {
            columns = m.columns;
            data = m.data + i * columns;
        }
        int& operator[](size_t j)
        {
            if (j >= columns) {
                throw std::out_of_range("");
            }
            return data[j];
        }
    private:
        size_t columns;
        int *data;
    };
    proxy operator[](size_t i);
private:
    size_t rows;
    size_t columns;
    int *data;
};

#endif
