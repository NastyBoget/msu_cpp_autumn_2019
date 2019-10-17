#include "linear_allocator.h"
#include <iostream>

void test_LinearAllocator()
{
    {
        LinearAllocator a(100);
        std::cout << "100 bytes in allocator" << std::endl;
        char *ptr = a.alloc(50);
        if (ptr != nullptr) {
            std::cout << "50 bytes was allocated" << std::endl;
        } else {
            std::cout << "alloc failed" << std::endl;
        }
        ptr = a.alloc(60);
        if (ptr == nullptr) {
            std::cout << "60 bytes was not allocated" << std::endl;
        } else {
            std::cout << "alloc failed" << std::endl;
        }
        ptr = a.alloc(50);
        if (ptr != nullptr) {
            std::cout << "50 bytes was allocated" << std::endl;
        } else {
            std::cout << "alloc failed" << std::endl;
        }
        a.reset();
        std::cout << "reset allocator" << std::endl;
        ptr = a.alloc(50);
        if (ptr != nullptr) {
            std::cout << "50 bytes was allocated" << std::endl;
        } else {
            std::cout << "reset failed" << std::endl;
        }
    }
    {
        LinearAllocator a(0);
        std::cout << "0 bytes in allocator" << std::endl;
        char *ptr = a.alloc(0);
        if (ptr != nullptr) {
            std::cout << "0 bytes was allocated" << std::endl;
        } else {
            std::cout << "alloc failed" << std::endl;
        }
    }
}

int main()
{
    test_LinearAllocator();
    return 0;
}
