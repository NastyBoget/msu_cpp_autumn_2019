#include <iostream>
#include <cassert>
#include "thread_pool.h"

int foo(int x) {
    return x;
}

struct A
{
    int data;
};

struct B
{
    int data;
    B() : data(0) {}
    int bar(int x) {
        return data + x;
    }
    static int foo(int x) {
        return x;
    }
};

int bar(const A& a) {
    return a.data;
}

int main() {

    ThreadPool pool(6);
    A a;
    auto task0 = pool.exec(bar, a);
    assert(task0.get() == 0);
    auto task1 = pool.exec([]() { return 1; });
    assert(task1.get() == 1);
    auto task2 = pool.exec(foo, 2);
    assert(task2.get() == 2);
    auto task3 = pool.exec(&B::foo, 3);
    assert(task3.get() == 3);
    B b;
    auto f = std::bind(&B::bar, &b, std::placeholders::_1);
    auto task4 = pool.exec(f, 4);
    assert(task4.get() == 4);
    std::cout << "done" << std::endl;
    return 0;
}