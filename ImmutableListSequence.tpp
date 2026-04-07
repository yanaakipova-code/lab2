#include "ImmutableListSequence.hpp"
#include "Error.hpp"
#include <memory>


template<class T>
ImmutableListSequence<T>::ImmutableListSequence(T* items, size_t count)
    :ListSequence<T>(items, count) {}

template<class T>
ImmutableListSequence<T>::ImmutableListSequence()
    :ListSequence<T>() {}

template<class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T>& other)
    :ListSequence<T>(other) {}

template<class T>
void ImmutableListSequence<T>::Append(T temp) {
    throw ChangeImmutableException("Нельзя изменять неизменяемую последовательность");
}

template<class T>
void ImmutableListSequence<T>::Prepend(T temp) {
    throw ChangeImmutableException("Нельзя изменять неизменяемую последовательность");
}

template<class T>
void ImmutableListSequence<T>::InsertAt(T temp, size_t index) {
    throw ChangeImmutableException("Нельзя изменять неизменяемую последовательность");
}

template<class T>
std::unique_ptr<ImmutableListSequence<T>> ImmutableListSequence<T>::WithAppend(T item) const {
    auto copy = std::make_unique<ImmutableListSequence<T>>(*this);
    copy->ListSequence<T>::Append(item);
    return copy;
}


template<class T>
std::unique_ptr<Sequence<T>> ImmutableListSequence<T>::Concat(Sequence<T>* other) const {
    auto result = std::make_unique<ImmutableListSequence<T>>(*this);
    for (size_t i = 0; i < other->GetLength(); i++) {
        result->ListSequence<T>::Append(other->Get(i));
    }
    return result;
}

template<class T>
std::unique_ptr<ImmutableListSequence<T>> ImmutableListSequence<T>::WithAppend(T item) const {
    auto result = std::make_unique<ImmutableListSequence<T>>(*this);
    result->ListSequence<T>::Append(item);
    return result;
}

template<class T>
std::unique_ptr<ImmutableListSequence<T>> ImmutableListSequence<T>::WithPrepend(T item) const {
    auto result = std::make_unique<ImmutableListSequence<T>>(*this);
    result->ListSequence<T>::Prepend(item);
    return result;
}

template<class T>
std::unique_ptr<ImmutableListSequence<T>> ImmutableListSequence<T>::WithInsertAt(T item, size_t index) const {
    if (index > this->GetLength()) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    auto result = std::make_unique<ImmutableListSequence<T>>(*this);
    result->ListSequence<T>::InsertAt(item, index);
    return result;
}

template<class T>
std::unique_ptr<Sequence<T>> ImmutableListSequence<T>::Concat(Sequence<T>* other) const {
    auto result = std::make_unique<ImmutableListSequence<T>>(*this);
    for (size_t i = 0; i < other->GetLength(); i++) {
        result->ListSequence<T>::Append(other->Get(i));
    }
    return result;
}

template<class T>
std::unique_ptr<ListSequence<T>> ImmutableListSequence<T>::ToMutable() const {
    size_t size = this->GetLength();
    auto result = std::make_unique<ListSequence<T>>();
    
    for (size_t i = 0; i < size; i++) {
        result->Append(this->Get(i));
    }
    
    return result;
}

template<class T>
Iterator<T> ImmutableListSequence<T>::begin() {
    return ListSequence<T>::begin();
}

template<class T>
Iterator<T> ImmutableListSequence<T>::end() {
    return ListSequence<T>::end();
}

template<class T>
ConstIterator<T> ImmutableListSequence<T>::begin() const {
    return ListSequence<T>::begin();
}

template<class T>
ConstIterator<T> ImmutableListSequence<T>::end() const {
    return ListSequence<T>::end();
}

template<class T>
ConstIterator<T> ImmutableListSequence<T>::cbegin() const {
    return ListSequence<T>::cbegin();
}

template<class T>
ConstIterator<T> ImmutableListSequence<T>::cend() const {
    return ListSequence<T>::cend();
}