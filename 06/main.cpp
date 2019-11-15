#include <iostream>
#include <cassert>
#include <stdexcept>
#include <sstream>
#include <vector>
using std::string;

class Format {
    std::stringstream arg;
    std::vector<string> args;
    size_t cnt_args;
    string str;
public:
    Format(const char *str) : cnt_args(0), str(str)
    {}
    size_t get_num(string::iterator& it, const string::iterator& end)
    {
        size_t num = 0;
        if (!std::isdigit(*it)) {
            string error("invalid string in symbol ");
            throw std::runtime_error(error + *it);
        }
        while((it != end) && (std::isdigit(*it))) {
            num = num * 10 + (*it - '0');
            ++it;
        }
        if (*it != '}') {
            string error("invalid string in symbol ");
            throw std::runtime_error(error + *it);
        }
        return num;
    }
    template<typename T>
    void add_args(T arg)
    {
        ++cnt_args;
        this->arg << arg; // проверяем, можно ли записать в поток
        this->args.push_back(this->arg.str());
        this->arg.str(string()); // очищаем поток
    }
    template<typename T, typename... Args>
    void add_args(T arg, Args... args)
    {
        ++cnt_args;
        this->arg << arg;
        this->args.push_back(this->arg.str());
        this->arg.str(string());
        add_args(args...);
    }
    string get_res()
    {
        string res;
        for (auto it = str.begin(); it != str.end(); ++it) {
            if (*it == '{') {
                ++it;
                size_t num = get_num(it, str.end());
                if (num >= cnt_args) {
                    throw std::runtime_error("invalid string: argument number too large");
                }
                res += args[num];
            } else if (*it == '}') {
                throw std::runtime_error("invalid string in symbol }");
            } else {
                res += *it;
            }
        }
        return res;
    }
};

template<typename... Args>
string format(const char *str, Args... args)
{
    Format f(str);
    f.add_args(args...);
    return f.get_res();
}

string format(const char *str)
{
    Format f(str);
    return f.get_res();
}

int main() {
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    text = format("I love {1} and {0}", "c++", "python");
    assert(text == "I love python and c++");
    text = format("{0}+{1} = 1", "zero", "one", "two");
    assert(text == "zero+one = 1");
    text = format("only string");
    assert(text == "only string");
    try {
        text = format("{}");
    } catch (std::runtime_error& e) {
        string err = e.what();
        assert(err == "invalid string in symbol }");
    }
    try {
        text = format("{0}+{1}+{3} = 4", "zero", "one", "three");
    } catch (std::runtime_error& e) {
        string err = e.what();
        assert(err == "invalid string: argument number too large");
    }
    try {
        text = format("invalid {string}", "arg");
    } catch (std::runtime_error& e) {
        string err = e.what();
        assert(err == "invalid string in symbol s");
    }
    try {
        text = format("bad}str");
    } catch (std::runtime_error& e) {
        string err = e.what();
        assert(err == "invalid string in symbol }");
    }
    try {
        text = format("bad{}str");
    } catch (std::runtime_error& e) {
        string err = e.what();
        assert(err == "invalid string in symbol }");
    }
    // std::vector<int> v; // нельзя записать в поток
    // text = format("some string {0}", v); // не скомпилируется
    std::cout << "done" << std::endl;
    return 0;
}
