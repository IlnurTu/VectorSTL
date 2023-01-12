#ifndef LAB4_MYCONTIGUOUSITERATOR_H
#define LAB4_MYCONTIGUOUSITERATOR_H

#include <iostream>

#define ContiguousIterator MyConstContiguousIterator

template<bool B, typename U, typename V>
struct conditional {
    using type = V;
};

template<typename U, typename V>
struct conditional<true, U, V> {
    using type = U;
};

template<bool B, typename U, typename V>
using conditional_t = typename conditional<B, U, V>::type;

template<typename T, bool isConst>
class ContiguousIterator {
private:
    conditional_t<isConst,const T*,T*> ptr;
public:
    ContiguousIterator(T *ptr) : ptr(ptr) {}

    ContiguousIterator() : ptr(nullptr) {}

    ContiguousIterator &operator++() {
        ++ptr;
        return *this;
    }

    ContiguousIterator operator++(int) {
        ContiguousIterator res(ptr);
        ++ptr;
        return res;
    }

    ContiguousIterator &operator--() {
        --ptr;
        return *this;
    }

    ContiguousIterator operator--(int) {
        ContiguousIterator res(ptr);
        --ptr;
        return res;
    }

    ContiguousIterator &operator+=(int r) {
        ptr += r;
        return *this;
    }

    ContiguousIterator operator-=(int r) {
        ptr -= r;
        return *this;
    }

    ContiguousIterator operator+(int r) {
        auto copy = *this;
        copy += r;
        return copy;
    }

    ContiguousIterator operator-(int r) {
        auto copy = *this;
        copy -= r;
        return copy;
    }

    ContiguousIterator operator+(const ContiguousIterator &r) {
        auto copy = *this;
        copy.ptr = copy.ptr + r.ptr;
        return copy;
    }

    ContiguousIterator operator-(const ContiguousIterator &r) {
        auto copy = *this;
        copy.ptr = copy.ptr - r.ptr;
        return copy;
    }

    std::strong_ordering operator<=>(const ContiguousIterator &r) const {
        return ptr <=> r.ptr;
    }

    T &operator*() {
        return *ptr;
    }

    T *operator->() {
        return ptr;
    }

//    bool operator !=(ContiguousIterator& r) const{
//        return !(*this == r);
//    }

    bool operator ==(ContiguousIterator& r) const{
        return this->ptr == r.ptr;
    }

    T* get(){
        return ptr;
    }



};

#endif
