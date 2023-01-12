#ifndef LAB4_MYVECTOR_H
#define LAB4_MYVECTOR_H

#include <iostream>
#include "MyContiguousIterator.h"


template<typename T, typename Allocator = std::allocator<T>>
class Vector {
private:
    T *arr;
    size_t sz;
    size_t cap;
    Allocator allocator;
    using AllocTraits = std::allocator_traits<Allocator>;
    using const_iterator = MyConstContiguousIterator<T, true>;
    using iterator = MyConstContiguousIterator<T, false>;
public:
    void reserve(size_t n) {
        if (n <= cap) return;

        T *newarr = AllocTraits::allocate(allocator, n);

        int i;
        try {
            for (i = 0; i < sz; i++)
                AllocTraits::construct(allocator, newarr + i, std::move_if_noexcept(arr[i]));
        } catch (...) {
            for (int j = 0; j < i; j++)
                AllocTraits::destroy(allocator, newarr + j);
            AllocTraits::deallocate(allocator, newarr, n);
            throw;
        }
        for (i = 0; i < sz; i++)
            AllocTraits::destroy(allocator, arr + i);
        AllocTraits::deallocate(allocator, arr, cap);

        arr = newarr;
        cap = n;
    }

    void push_back(const T &value) {
        if (sz == cap) reserve(2 * sz);
        AllocTraits::construct(allocator, arr + sz, value);
        ++sz;
    }

    void push_back(T &&value) {
        if (sz == cap) reserve(2 * sz);
        AllocTraits::construct(allocator, arr + sz, std::move(value));
        ++sz;
    }

    template<typename ... Args>
    void emplace_back(Args &&... args) {
        if (sz == cap) reserve(2 * sz);
        AllocTraits::construct(allocator, arr + sz, std::forward<Args>(args)...);
        ++sz;
    }

    Vector(const Vector<T, Allocator> &e) : allocator(e.allocator) {
        reserve(e.cap);
        for (int i = 0; i < e.sz; i++)
            AllocTraits::construct(allocator, arr + i, e.arr[i]);
        sz = e.sz;
        cap = e.cap;
    }

    Vector(Vector<T, Allocator> &&e) : allocator(e.allocator), arr(e.arr), sz(e.sz), cap(e.cap) {
        e.arr = nullptr;
    }

    Vector() : cap(0), sz(0), arr(nullptr) {
        reserve(1);
    }


    const_iterator cbegin() const {
        return const_iterator(arr);
    }

    const_iterator cend() const {
        return const_iterator(arr + sz);
    }

    iterator begin() {
        return iterator(arr);
    }

    iterator end() {
        return iterator(arr + sz);
    }

    iterator erase(iterator pos) {
        AllocTraits::destroy(allocator,pos.get());
        size_t len = this->end().get() - pos.get() - 1;
        std::memmove(pos.get(), (pos + 1).get(), len * sizeof(*pos));
        --sz;
        return pos;
    }

    ~Vector() {
        for (int i = 0; i < sz; i++) {
            AllocTraits ::destroy(allocator,arr+i);
        }
        AllocTraits::deallocate(allocator,arr,cap);
    }
};

#endif
