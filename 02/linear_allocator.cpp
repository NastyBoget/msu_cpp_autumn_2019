#include "linear_allocator.h"
LinearAllocator::LinearAllocator(size_t maxSize) : maxSize(maxSize)
{
    begin_ptr = current_ptr = new char[maxSize];
}

char *LinearAllocator::alloc(size_t size)
{
    if (current_ptr + size <= begin_ptr + maxSize) {
        char *res_ptr = current_ptr;
        current_ptr += size;
        return res_ptr;
    } else {
        return nullptr;
    }
}

void LinearAllocator::reset()
{
    current_ptr = begin_ptr;
}

LinearAllocator::~LinearAllocator()
{
    delete[] begin_ptr;
}
