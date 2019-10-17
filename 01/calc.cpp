#include <iostream>
#include <stdexcept>
using std::cout;
using std::string;
using std::invalid_argument;
// __LINE__
/* recursive descent grammar
 * X->B[+|-B]
 * B->C[*|/C]
 * C->-T|T
 * T->0-9
*/
char get_char(const char *&str)
{
    while (*++str == ' ') {}
    if (*str != '\0') {
        return *str;
    } else {
        return '\0';
    }
}
int get_number(const char *& str) // T
{
    int arg = 0;
    if ((*str >= '9') || (*str <= '0')) {
        string err("error on character ");
        throw invalid_argument(err + *str);
    }
    while((*str <= '9') && (*str >= '0')) {
        arg = arg * 10 + (*str - '0');
        get_char(str);
    }
    if ((*str != '+') && (*str != '\0') && (*str != '-') &&\
            (*str != '*') && (*str != '/')) {
        string err("error on character ");
        throw invalid_argument(err + *str);
    }
    return arg;
}
int get_sign(const char *& str) // C
{
    if (*str == '-') {
        get_char(str);
        int arg = get_number(str);
        return -arg;
    }
    else {
        return get_number(str);
    }
}
int get_multiply(const char *& str) // B
{
    int arg = get_sign(str);
    if ((*str != '+') && (*str != '\0') && (*str != '-') &&\
            (*str != '*') && (*str != '/')) {
        string err("error on character ");
        throw invalid_argument(err + *str);
    }
    while (*str == '*' || *str == '/') {
        if (*str == '*') {
            get_char(str);
            arg *= get_sign(str);
        } else if (*str == '/') {
            get_char(str);
            int arg2 = get_sign(str);
            if (arg2 != 0) {
                arg /= arg2;
            } else {
                string err("error on character ");
                throw invalid_argument(err + *str);
            }
        }
    }
    return arg;
}
int calc(const char *& str) // X
{
    int arg = get_multiply(str);
    if ((*str != '+') && (*str != '\0') && (*str != '-')) {
        string err("error on character ");
        throw invalid_argument(err + *str);
    }
    while (*str == '+' || *str == '-') {
        if (*str == '+') {
            get_char(str);
            arg += get_multiply(str);
        } else if (*str == '-') {
            get_char(str);
            arg -= get_multiply(str);
        }
    }
    if (*str != '\0') {
        string err("error on character ");
        throw invalid_argument(err + *str);
    }
    return arg;
}
int main(int argc, char **argv)
{
    const int err = 1;
    if (argc != 2) {
        cout << "wrong number of parameters" << std::endl;
        return err;
    }
    // string for parsing in argv[1]
    const char *str = argv[1];
    try {
        int res = calc(str);
        cout << res << std::endl;
        return 0;
    } catch (std::exception& e) {
        cout << e.what() << std::endl;
        return err;
    }
}