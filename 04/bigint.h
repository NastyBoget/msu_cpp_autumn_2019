#ifndef BIGINT_H
#define BIGINT_H

#include <cstddef>
#include <algorithm>
#include <iosfwd>

class BigInt {
public:
    BigInt(int n);
    BigInt(const BigInt& other);
    BigInt& operator=(const BigInt& other);
    BigInt(BigInt&& other);
    BigInt& operator=(BigInt&& other);
    ~BigInt();
    friend std::ostream& operator<<(std::ostream& os, const BigInt& d);
    BigInt operator-() const;
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator+(int n) const;
    BigInt operator-(int n) const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    bool operator==(int n) const;
    bool operator!=(int n) const;
    bool operator<(int n) const;
    bool operator<=(int n) const;
    bool operator>(int n) const;
    bool operator>=(int n) const;
private:
    size_t size;
    char *data;
    bool sign; // + true, - false
    size_t block_size = 10; // размер блока для увеличения буфера
    size_t buf_size;
    BigInt(size_t size, char* data, bool sign, size_t buf_size);
    BigInt add(const BigInt& obj1, const BigInt& obj2) const; // выполняет сложение в столбик
    BigInt sub(const BigInt& obj1, const BigInt& obj2) const; // выполняет вычитание в столбик
};


#endif
