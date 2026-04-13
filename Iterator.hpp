#pragma once
#include <iterator>

template<class T, template<typename> class Derived>
class Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    reference operator*() {
        return derived().operator*();
    }
    
    pointer operator->() {
        return derived().operator->();
    }
    
    Iterator& operator++() {
        derived().operator++();
        return *this;
    }
    
    bool operator==(const Iterator& other) const {
        return derived().operator==(other.derived());
    }
    
    bool operator!=(const Iterator& other) const {
        return derived().operator!=(other.derived());
    }
    
private:
    Derived<T>& derived() {
        return static_cast<Derived<T>&>(*this);
    }
    
    const Derived<T>& derived() const {
        return static_cast<const Derived<T>&>(*this);
    }
};

template<class T, template<typename> class Derived>
class ConstIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    reference operator*() const {
        return derived().operator*();
    }
    
    pointer operator->() const {
        return derived().operator->();
    }
    
    ConstIterator& operator++() {
        derived().operator++();
        return *this;
    }
    
    bool operator==(const ConstIterator& other) const {
        return derived().operator==(other.derived());
    }
    
    bool operator!=(const ConstIterator& other) const {
        return derived().operator!=(other.derived());
    }
    
private:
    const Derived<T>& derived() const {
        return static_cast<const Derived<T>&>(*this);
    }
    
    Derived<T>& derived() {
        return static_cast<Derived<T>&>(*this);
    }
};