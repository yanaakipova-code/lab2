#pragma once
#include <memory>
#include "ListSequence.hpp"
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

    std::unique_ptr<ImmutableListSequence<T>> WithAppend(T item) const;
    std::unique_ptr<ImmutableListSequence<T>> WithPrepend(T item) const;
    std::unique_ptr<ImmutableListSequence<T>> WithInsertAt(T item, size_t index) const;

    std::unique_ptr<Sequence<T>> Concat(Sequence<T>* other) const override;
    std::unique_ptr<ListSequence<T>> ToMutable() const;

    Iterator<T> begin() override;
    Iterator<T> end() override;
    ConstIterator<T> begin() const override;
    ConstIterator<T> end() const override;
    ConstIterator<T> cbegin() const;
    ConstIterator<T> cend() const;
};
#include "ImmutableListSequence.tpp"
