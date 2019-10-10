#include <iostream>
#define ERR 1
using std::cout;
// __LINE__
/* recursive descent grammar
 * X->B[+|-B]
 * B->C[*|/C]
 * C->-T|T
 * T->0-9
*/
char gc(char *&str)
{
    while (*++str == ' ') {}
    if (*str != '\0') {
        return *str;
    } else {
        return '\0';
    }
}
int num_f(char *& str) // T
{
    int arg = 0;
    if ((*str >= '9') || (*str <= '0')) {
        throw *str;
    }
    while((*str <= '9') && (*str >= '0')) {
        arg = arg * 10 + (*str - '0');
        gc(str);
    }
    if ((*str != '+') && (*str != '\0') && (*str != '-') &&\
            (*str != '*') && (*str != '/')) {
        throw *str;
    }
    return arg;
}
int sign_f(char *& str) // C
{
    if (*str == '-') {
        gc(str);
        int arg = num_f(str);
        return -arg;
    }
    else {
        return num_f(str);
    }
}
int mult_f(char *& str) // B
{
    int arg = sign_f(str);
    if ((*str != '+') && (*str != '\0') && (*str != '-') &&\
            (*str != '*') && (*str != '/')) {
        throw *str;
    }
    while (*str == '*' || *str == '/') {
        if (*str == '*') {
            gc(str);
            arg *= sign_f(str);
        } else if (*str == '/') {
            gc(str);
            int arg2 = sign_f(str);
            if (arg2 != 0) {
                arg /= arg2;
            } else {
                throw '0';
            }
        }
    }
    return arg;
}
int sum_f(char *& str) // X
{
    int arg = mult_f(str);
    if ((*str != '+') && (*str != '\0') && (*str != '-')) {
        throw *str;
    }
    while (*str == '+' || *str == '-') {
        if (*str == '+') {
            gc(str);
            arg += mult_f(str);
        } else if (*str == '-') {
            gc(str);
            arg -= mult_f(str);
        }
    }
    if (*str != '\0') {
        throw *str;
    }
    return arg;
}
int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "wrong number of parameters" << std::endl;
        return ERR;
    }
    // string for parsing in argv[1]
    char *str = argv[1];
    try {
        int res = sum_f(str);
        cout << res << std::endl;
        return 0;
    } catch (char c) {
        cout << "error on character " << c << std::endl;
        return ERR;
    }
}