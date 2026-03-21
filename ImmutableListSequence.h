#pragma once
#include "ListSequence.h"
#include <stdexcept>

template<class T>
class ImmutableListSequence: public ListSequence<T>{
public:
    ImmutableListSequence(T* items, size_t count);
    ImmutableListSequence();
    ImmutableListSequence(const ImmutableListSequence<T>& other);

    void Append(T temp) override;
    void Prepend(T temp) override;
    void InsertAt(T temp, size_t index) override;

    ImmutableListSequence<T>* WithAppend(T item) const;
    ImmutableListSequence<T>* WithPrepend(T item) const;
    ImmutableListSequence<T>* WithInsertAt(T item, size_t index) const;

    Sequence<T>* Concat(Sequence<T>* other) const override;
    ListSequence<T>* ToMutable() const;
};
#include "ImmutableListSequence.tpp"
