#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>
#include <iterator>

template<typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    explicit Iterator(T* ptr) : ptr_(ptr) {}
    bool operator==(const Iterator<T>& other) const {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const Iterator<T>& other) const {
        return !(*this == other);
    }
    T& operator*() const {
        return *ptr_;
    }
    Iterator& operator++() {
        ++ptr_;
        return *this;
    }
    Iterator& operator--() {
        --ptr_;
        return *this;
    }
    Iterator operator++(int) {
        auto tmp = ptr_;
        ++ptr_;
        return Iterator(tmp);
    }
    Iterator operator--(int) {
        auto tmp = ptr_;
        --ptr_;
        return Iterator(tmp);
    }
    Iterator operator+(size_t n) const {
        return Iterator(ptr_ + n);
    }
    Iterator operator-(size_t n) const {
        return Iterator(ptr_ - n);
    }
    Iterator& operator+=(size_t n) {
        ptr_ += n;
        return *this;
    }
    Iterator& operator-=(size_t n) {
        ptr_ -= n;
        return *this;
    }
    size_t operator-(const Iterator& other) const {
        if (ptr_ < other.ptr_) {
            throw std::invalid_argument("invalid iterators");
        }
        return ptr_ - other.ptr_;
    }
    bool operator>(const Iterator& other) const {
        return ptr_ > other.ptr_;
    }
    bool operator>=(const Iterator& other) const {
        return (*this == other) || (*this > other);
    }
    bool operator<(const Iterator& other) const {
        return !(*this >= other);
    }
    bool operator<=(const Iterator& other) const {
        return !(*this > other);
    }
    T& operator[](size_t n) {
        return *(ptr_ + n);
    }
private:
    T* ptr_;
};


#endif