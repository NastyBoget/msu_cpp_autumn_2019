#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H
#include <cstddef>

class LinearAllocator {
    size_t maxSize;
    char *current_ptr;
    char *begin_ptr;
public:
    explicit LinearAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~LinearAllocator();
};


#endif //UNTITLED3_LINEAR_ALLOCATOR_H
