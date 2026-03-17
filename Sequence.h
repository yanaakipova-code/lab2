#pragma once
#include <stdexcept>
#include <cstddef>

template<class T>
class Sequence{
public:
    virtual ~Sequence() = default;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;
    virtual Sequence<T>* GetSubsequence(int start_index, int end_index) const = 0;

    virtual void Append(T temp) = 0;
    virtual void Prepend(T temp) = 0;
    virtual void InsertAt(T temp, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* sequence) const = 0;
};

