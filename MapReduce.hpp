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

template<class T>
Sequence<T>* Skip(Sequence<T>* seq, size_t n){
    if(seq == nullptr){
        throw std::invalid_argument("Skip: аргумент не передан");
    }
    if(n >= seq->GetLength()){
        return new ArraySequence<T>();
    }
    return seq->GetSubsequence(n, seq->GetLength() - 1);
}

template<class T>
Sequence<T>* Take(Sequence<T>* seq, size_t n){
    if(seq == nullptr){
        throw std::invalid_argument("Take: аргумент не передан");
    }
    if (n == 0) {
        return new ArraySequence<T>();
    }
    if (n >= seq->GetLength()){
        n = seq->GetLength();
    }
    return seq->GetSubsequence(0,n-1);
}