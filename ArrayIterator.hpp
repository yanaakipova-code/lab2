#pragma once
#include "Iterator.hpp"

template<class T>
class ArrayIterator : public Iterator<T, ArrayIterator> {
private:
    T* m_ptr;
    
public:
    ArrayIterator(T* ptr = nullptr) : m_ptr(ptr) {}
    
    T& operator*() {
        return *m_ptr;
    }
    
    T* operator->() {
        return m_ptr;
    }
    
    ArrayIterator& operator++() {
        ++m_ptr;
        return *this;
    }
    
    bool operator==(const ArrayIterator& other) const {
        return m_ptr == other.m_ptr;
    }
    
    bool operator!=(const ArrayIterator& other) const {
        return !(*this == other);
    }
};

template<class T>
class ConstArrayIterator : public ConstIterator<T, ConstArrayIterator> {
private:
    const T* m_ptr;
    
public:
    ConstArrayIterator(const T* ptr = nullptr) : m_ptr(ptr) {}
    
    const T& operator*() const {
        return *m_ptr;
    }
    
    const T* operator->() const {
        return m_ptr;
    }
    
    ConstArrayIterator& operator++() {
        ++m_ptr;
        return *this;
    }
    
    bool operator==(const ConstArrayIterator& other) const {
        return m_ptr == other.m_ptr;
    }
    
    bool operator!=(const ConstArrayIterator& other) const {
        return !(*this == other);
    }
};