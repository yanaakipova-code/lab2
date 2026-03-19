#pragma once
#include "ArraySequence.h"
#include <stdexcept>

template<class T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence(T* items, size_t count);
    ImmutableArraySequence();
    ImmutableArraySequence(const ImmutableArraySequence<T>& other);

     void Append(T temp) override;
    void Prepend(T temp) override;
    void InsertAt(T temp, size_t index) override;

    ImmutableArraySequence<T>* WithAppend(T item) const;
    ImmutableArraySequence<T>* WithPrepend(T item) const;
    ImmutableArraySequence<T>* WithInsertAt(T item, size_t index) const;

    Sequence<T>* Concat(Sequence<T>* other) const override;
    ArraySequence<T>* ToMutable() const;
};

#include "ImmutableArraySequence.tpp"