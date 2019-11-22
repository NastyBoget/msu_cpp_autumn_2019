#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <limits>
#include <utility>

template <class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

    /* Allocates count * sizeof(T) bytes of uninitialized storage
     * by calling new */
    pointer allocate(size_type count) {
        return static_cast<pointer>(operator new(count * sizeof(T)));
    }
    /* Deallocates the storage referenced by the pointer ptr,
     * which must be a pointer obtained by an earlier call to allocate().
     * The argument count must be equal to the first argument of the call to
     * allocate() that originally produced ptr; otherwise, the behavior is undefined. */
    void deallocate(pointer ptr, size_type count) {
        operator delete(ptr);
    }
    template <typename... Args>
    void construct(pointer ptr, Args&&... args) {
        new(ptr) T(std::forward <Args> (args)...);
    }
    void destroy(pointer ptr) {
        ptr->~T();
    }
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max();
    }
};

#endif