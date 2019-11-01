#include "bigint.h"
#include <algorithm>
#include <iostream>
BigInt::BigInt(int n)
{
    sign = n >= 0;
    if (!sign) {
        n = -n;
    }
    data = new char[block_size];
    size = 0;
    buf_size = block_size;
    // перевод числа в строку
    do {
        if (size == buf_size) {
            buf_size += block_size;
            char *tmp = new char[buf_size];
            std::copy(data, data + size, tmp);
            delete[] data;
            data = tmp;
        }
        data[size++] = char(n % 10 + '0');
        n /= 10;
    } while (n != 0);
    std::reverse(data, data + size);
}

BigInt::BigInt(const BigInt &other)
{
    buf_size = other.buf_size;
    size = other.size;
    data = new char[buf_size];
    sign = other.sign;
    std::copy(other.data, other.data + size, data);
}

BigInt &BigInt::operator=(const BigInt &other) {
    if (this == &other) {
        return *this;
    }
    buf_size = other.buf_size;
    size = other.size;
    sign = other.sign;
    auto ptr = new char[buf_size];
    delete[] data;
    data = ptr;
    std::copy(other.data, other.data + size, data);
    return *this;
}

BigInt::BigInt(BigInt &&other) {
    size = other.size;
    data = other.data;
    sign = other.sign;
    buf_size = other.buf_size;
    other.data = nullptr;
    other.size = other.buf_size = 0;
}

BigInt &BigInt::operator=(BigInt &&other) {
    if (this == &other) {
        return *this;
    }
    buf_size = other.buf_size;
    size = other.size;
    sign = other.sign;
    delete[] data;
    data = other.data;
    other.data = nullptr;
    other.size = other.buf_size = 0;
    return *this;
}

BigInt::~BigInt() {
    delete[] data;
}

std::ostream& operator<<(std::ostream &os, const BigInt& obj) {
    if (!obj.sign) { // число отрицательное
        os << '-';
    }
    for (size_t i = 0; i < obj.size; ++i) {
        os << obj.data[i];
    }
    return os;
}

BigInt BigInt::operator-() const{
    BigInt res = *this;
    res.sign = !sign;
    return res;
}

BigInt::BigInt(size_t size, char *data,  bool sign, size_t buf_size) {
    this->size = size;
    this->data = data;
    this->sign = sign;
    this->buf_size = buf_size;
    this->data = new char[buf_size];
    std::copy(data, data + size, this->data);
}

BigInt BigInt::add(const BigInt &obj1, const BigInt &obj2) const {
    size_t min_size = std::min(obj1.size, obj2.size);
    size_t max_size = std::max(obj1.size, obj2.size);
    const char* max_data = size == max_size ? obj1.data : obj2.data; // число наибольшей длины
    unsigned n = 0; // дополнительный разряд
    size_t new_buf_size = std::max(obj1.buf_size, obj2.buf_size); // buf_size для результата
    char *res = new char[new_buf_size]; // число-результат
    for (size_t i = 0; i < min_size; ++i) {
        //складываем с конца
        unsigned sum = obj1.data[obj1.size - 1 -i] - '0' + obj2.data[obj2.size - 1 - i] - '0';
        res[max_size - 1 - i] = char(sum % 10 + n + '0');
        n = sum / 10;
    }
    for (size_t i = min_size; i < max_size; ++i) { // если одно число длиннее другого
        if (max_data[max_size - 1 - i] == '9' && n == 1) { // если есть доп разряд и встретили 9 (99 + 1)
            res[max_size - 1 - i] = '0';
        } else {
            res[max_size - 1 - i] = max_data[max_size - 1 - i] + n;
            n = 0;
        }
    }
    if (n > 0) { // размер числа-суммы увеличился
        if (max_size == new_buf_size) { // не хватает размера текущего буфера
            new_buf_size += block_size;
            char *tmp = new char[new_buf_size];
            std::copy(res, res + max_size, tmp + 1);
            delete[] res;
            res = tmp;
        } else {
            std::copy(res, res + max_size, res + 1);
        }
        res[0] = '1';
        ++max_size;
    }
    auto sum = BigInt(max_size, res, obj1.sign, new_buf_size);
    delete[] res;
    return sum;
}

BigInt BigInt::sub(const BigInt &obj1, const BigInt &obj2) const {
    // находим наибольшее по модулю число, чтобы из большего вычитать меньшее
    bool new_sign = BigInt(obj1.size, obj1.data, true, obj1.buf_size)\
            > BigInt(obj2.size, obj2.data, true, obj2.buf_size);
    size_t min_size = std::min(obj1.size, obj2.size);
    size_t max_size = std::max(obj1.size, obj2.size);
    const char* max_data = size == max_size ? obj1.data : obj2.data; // число наибольшей длины
    int n = 0; // дополнительный разряд
    size_t new_buf_size = std::max(obj1.buf_size, obj2.buf_size);
    char *res = new char[new_buf_size]; // число-результат
    for (size_t i = 0; i < min_size; ++i) {
        int diff = 0;
        // вычитаем с конца с учетом разряда
        if (new_sign) {
            diff = obj1.data[obj1.size - 1 - i] - obj2.data[obj2.size - 1 - i] - n;
        } else {
            diff = obj2.data[obj2.size - 1 - i] - obj1.data[obj1.size - 1 - i] - n;
        }
        if (diff < 0) { // заняли старший разряд
            diff += 10;
            n = 1;
        } else {
            n = 0;
        }
        res[max_size - 1 - i] = char(diff + '0');
    }
    for (size_t i = min_size; i < max_size; ++i) { // если одно число длиннее другого
        if (max_data[max_size - 1 - i] == '0') { // вычитаем с конца с учетом разряда
            res[max_size - 1 - i] = '9';
            n = 1;
        } else {
            res[max_size - 1 - i] = max_data[max_size - 1 - i] - n;
            n = 0;
        }
    }
    size_t i = 0;
    while(res[i] == '0') { // если начало у чисел совпадает, появляются незначащие нули
        ++i;
        if (i == max_size) {
            break;
        }
    }; // res == "0001"
    max_size -= i;
    if (max_size == 0) { // res == "0000" -> "0"
        max_size = 1;
        new_sign = true;
    } else {
        if (i != 0) {
            for (size_t j = 0; j < max_size; ++j) { // убираем незначащие нули
                res[j] = res[j + i];
            }
        }
        new_sign = (new_sign == obj1.sign);
    }
    auto diff = BigInt(max_size, res, new_sign, new_buf_size);
    delete[] res;
    return diff;
}

BigInt BigInt::operator+(const BigInt &other) const {
    if (sign == other.sign) {
        return add(*this, other);
    } else {
        if (sign) {
            return sub(*this, other);
        } else {
            return sub(other, *this);
        }
    }
    return *this;
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (sign == other.sign) {
        return sub(*this, other);
    } else {
        return add(*this, other);
    }
}

BigInt BigInt::operator+(int n) const {
    return *this + BigInt(n);
}

BigInt BigInt::operator-(int n) const {
    return *this - BigInt(n);
}

bool BigInt::operator==(const BigInt &other) const {
    if (this == &other)
        return true;
    if (sign != other.sign || size != other.size) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt &other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt &other) const {
    if (sign != other.sign) {
        return sign < other.sign;
    }
    if (size != other.size) {
        return size < other.size;
    }
    for (int i = 0; i < size; ++i) {
        if (data[i] > other.data[i]) {
            return false;
        }else if (data[i] < other.data[i]) {
            return true;
        }
    }
    return false;
}

bool BigInt::operator<=(const BigInt &other) const {
    return (*this < other) || (*this == other);
}

bool BigInt::operator>=(const BigInt &other) const {
    return !(*this < other);
}

bool BigInt::operator>(const BigInt &other) const {
    return !(*this < other) && (*this != other);
}

bool BigInt::operator==(int n) const {
    return *this == BigInt(n);
}

bool BigInt::operator!=(int n) const {
    return *this != BigInt(n);
}

bool BigInt::operator<(int n) const {
    return *this < BigInt(n);
}

bool BigInt::operator<=(int n) const {
    return *this <= BigInt(n);
}

bool BigInt::operator>(int n) const {
    return *this > BigInt(n);
}

bool BigInt::operator>=(int n) const {
    return *this >= BigInt(n);
}


