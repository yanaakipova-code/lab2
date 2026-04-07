#include "ImmutableArraySequence.hpp"
#include "Error.hpp"
#include <memory>

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(T* items, size_t count)
    : ArraySequence<T>(items, count) {}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence()
    : ArraySequence<T>() {}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& other)
    : ArraySequence<T>(other) {}

template<class T>
void ImmutableArraySequence<T>::Append(T temp) {
    throw ChangeImmutableException("Ошибка: нельзя изменять неизменяемую последовательность (Append запрещен)");
}

template<class T>
void ImmutableArraySequence<T>::Prepend(T temp) {
    throw ChangeImmutableException("Ошибка: нельзя изменять неизменяемую последовательность (Prepend запрещен)");
}

template<class T>
void ImmutableArraySequence<T>::InsertAt(T temp, size_t index) {
    throw ChangeImmutableException("Ошибка: нельзя изменять неизменяемую последовательность (InsertAt запрещен)");
}

template<class T>
std::unique_ptr<ImmutableArraySequence<T>> ImmutableArraySequence<T>::WithAppend(T item) const {
    size_t old_size = this->GetLength();
    auto result = std::make_unique<ImmutableArraySequence<T>>(old_size + 1);
    
    for (size_t i = 0; i < old_size; i++) {
        result->Set(i, this->Get(i));
    }
    result->Set(old_size, item);
    
    return result;
}

template<class T>
std::unique_ptr<ImmutableArraySequence<T>> ImmutableArraySequence<T>::WithInsertAt(T item, size_t index) const {
    if (index > this->GetLength()) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    
    size_t old_size = this->GetLength();
    auto result = std::make_unique<ImmutableArraySequence<T>>(old_size + 1);
    
    for (size_t i = 0; i < index; i++) {
        result->Set(i, this->Get(i));
    }
    
    result->Set(index, item);
    
    for (size_t i = index; i < old_size; i++) {
        result->Set(i + 1, this->Get(i));
    }
    
    return result;
}

template<class T>
std::unique_ptr<ImmutableArraySequence<T>> ImmutableArraySequence<T>::WithPrepend(T item) const {
    return WithInsertAt(item, 0);
}

template<class T>
std::unique_ptr<Sequence<T>> ImmutableArraySequence<T>::Concat(Sequence<T>* other) const {
    size_t this_size = this->GetLength();
    size_t other_size = other->GetLength();
    size_t new_size = this_size + other_size;
    
    auto result = std::make_unique<ImmutableArraySequence<T>>(new_size);
    
    for (size_t i = 0; i < this_size; i++) {
        result->Set(i, this->Get(i));
    }
    
    for (size_t i = 0; i < other_size; i++) {
        result->Set(this_size + i, other->Get(i));
    }
    
    return result;
}

template<class T>
std::unique_ptr<ArraySequence<T>> ImmutableArraySequence<T>::ToMutable() const {
    size_t size = this->GetLength();
    auto result = std::make_unique<ArraySequence<T>>();
    
    for (size_t i = 0; i < size; i++) {
        result->Append(this->Get(i));
    }
    
    return result;
}

template<class T>
std::unique_ptr<ImmutableArraySequence<T>> ImmutableArraySequence<T>::WithPrepend(T item) const {
    return WithInsertAt(item, 0);
}



template<class T>
Iterator<T> ImmutableArraySequence<T>::begin() {
    return ArraySequence<T>::begin();
}

template<class T>
Iterator<T> ImmutableArraySequence<T>::end() {
    return ArraySequence<T>::end();
}

//явный константный итератор
template<class T>
ConstIterator<T> ImmutableArraySequence<T>::cbegin() const {
    return ArraySequence<T>::cbegin();
}

template<class T>
ConstIterator<T> ImmutableArraySequence<T>::cend() const {
    return ArraySequence<T>::cend();
}