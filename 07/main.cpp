#include <iostream>
#include "vector.h"
#include <algorithm>
#include <cassert>
#include <random>

using std::string;
using std::cout;
using std::endl;
int main() {
    {
        Vector<int> v;
        for (size_t i = 0; i < 5; ++i) {
            v.push_back(std::rand() % 10);
        }
        for (auto it = v.begin(); it < v.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        v.pop_back();
        for (auto it = v.rbegin(); it != v.rend(); ++it) {
            cout << *it  << " ";
        }
        cout << endl;
        assert(!v.empty());
        assert(v.size() == 4);
        std::sort(v.begin(), v.end());
        for (auto it : v) {
            cout << it  << " ";
        }
        cout << endl;
        cout << "v[3]=" << v[3] << endl;
        v.clear();
        assert(v.empty());
    }
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        Vector<string> v(5);
        assert(v.size() == 5);
        v.reserve(100);
        assert(v.capacity() == 100);
        v.resize(3);
        assert(v.size() == 3);
        v.clear();
        v.push_back("one");
        v.push_back("two");
        v.push_back("three");
        for (auto &it: v) {
            cout << it  << " ";
        }
        cout << endl;
        std::shuffle(v.begin(), v.end(), gen);
        for (auto &it: v) {
            cout << it  << " ";
        }
        cout << endl;
        auto it1 = v.begin();
        auto it2 = v.end();
        assert(it1 < it2 && it1 <= it2 && it2 > it1 && it2 >= it1);
        cout << "v[2]=" << it1[2] << endl;
        assert((it2 - it1) == v.size());
        assert((it1 + 2) == (it2 - 1));
        it1 += 2;
        it2 -= 1;
        assert(it1 == it2);
        v.clear();
        assert(v.empty());
    }
    cout << "done" << endl;
    return 0;
}