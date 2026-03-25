#pragma once
#include <stdexcept>
#include <cstddef>
#include "Sequence.hpp"
#include "DynamicArray.hpp"
#include "Option.hpp"

template<class T>
class ArraySequence: public Sequence<T>{
private:
    DynamicArray<T>* m_items;
public:
    ArraySequence(T* temp, size_t count);
    ArraySequence();
    ArraySequence(const ArraySequence<T>& array_sequence);

    ~ArraySequence() override;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(size_t index) const override;
    size_t GetLength() const override;
    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override;

    void Append(T temp) override;
    void Prepend(T temp) override;
    void InsertAt(T temp, size_t index) override;
    void Set(size_t index, T value);
    Sequence<T>* Concat(Sequence<T>* other) const override;

    Sequence<T>* Map(T (*func)(T)) override;
    Sequence<T>* Where(bool(*predicate)(T)) override;
    T Reduce(T (*func)(T, T), T initial) override;

    Option<T> TryGetFirst(bool (*predicate)(T) = nullptr) const override;
    Option<T> TryGetLast(bool (*predicate)(T) = nullptr) const override;


    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    template<class T>
    class Builder{
    private:
        DynamicArray<T>* m_items;
    public:
        Builder(): m_items(new DynamicArray<T>(0)){}
        ~Builder(){}

        Builder& add(const T& value){
            size_t old_size = m_items->GetSize();
            m_items->Resize(old_size+1);
            m_items->Set(old_size, vaule);
            return *this;
        }

        Builder& addSome(const T* values, size_t count){
            for (size_t i = 0; i < count; i++){
                add(values[i]);
            }
            return *this;
        }

        ArraySequence<T>* build() {
            return new ArraySequence<T>(m_items);
        }
    };
};

#include "ArraySequence.tpp"
