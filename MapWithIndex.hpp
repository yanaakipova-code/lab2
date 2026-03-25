#pragma once
#include "Sequence.hpp"
#include "ArraySequence.hpp"

template<class T, class U>
Sequence<U>* MapWithIndex(Sequence<T>* seq, U (*func)(T,size_t)){
    if(seq == nullptr){
        throw std::invalid_argument("MapWithIndex: аргумент не передан");
    }
    size_t len = seq->GetLength();
    U* result = new U[len];

    for (size_t i = 0; i < len; i++){
        result[i] = func(seq->Get(i), i);
    }
    auto* new_seq = new ArraySequence<U>(result, len);
    delete[] result;
    return new_seq;
}