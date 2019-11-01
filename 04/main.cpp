#include <iostream>
#include "bigint.h"
int main() {
    // конструкторы, операторы сравнения
    const BigInt a1(1000000000);
    std::cout << a1 << std::endl;
    const BigInt a2 = 2000000000;
    std::cout << a1 + a2 << std::endl;
    std::cout << a1 - a2 << std::endl;
    BigInt a3 = a2;
    std::cout << a3 - a2 << std::endl;
    std::cout << (a3 == a2) << std::endl;
    std::cout << (a1 < a2) << std::endl;
    std::cout << (a3 <= a2) << std::endl;
    a3 = a3 + 1000000000;
    std::cout << -a3 << std::endl;
    a3 = a3 + a2 + 2000000000;
    std::cout << a3 << std::endl;
    std::cout << (a3 > 0) << std::endl;
    // проверка на заем разряда
    std::cout << a3 - 10 << std::endl;
    std::cout << BigInt(999) + BigInt(2) << std::endl;
    std::cout << BigInt(999) + BigInt(999) << std::endl;
    std::cout << BigInt(2000) - BigInt(1001) << std::endl;
    std::cout << BigInt(1000) - BigInt(1) << std::endl;
    // проверяем знаки
    std::cout << BigInt(-2) + BigInt(-3) << std::endl;
    std::cout << BigInt(9) + BigInt(-2) << std::endl;
    std::cout << BigInt(9) + BigInt(-20) << std::endl;
    std::cout << BigInt(9) - BigInt(-20) << std::endl;
    std::cout << BigInt(9) - BigInt(-2) << std::endl;
    std::cout << BigInt(-2) - BigInt(9) << std::endl;
    std::cout << BigInt(-2) - BigInt(-9) << std::endl;
    // незначащие нули
    std::cout << BigInt(2020) - BigInt(2000) << std::endl;
    // разные размеры буфера
    a3 = a3 + a3; // a3 = 14000000000
    std::cout << a3 << std::endl;
    a3 = a3 + 999;
    std::cout << a3 << std::endl;
    std::cout << a3 - BigInt(1001) << std::endl;
    return 0;
}