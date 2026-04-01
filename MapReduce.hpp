#pragma once
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include <algorithm>
#include <stdexcept>

template<class T, class U>
Sequence<U>* MapWithIndex(Sequence<T>& seq, U (*func)(const T&,size_t)){
    size_t len = seq.GetLength();
    ArraySequence<U>* result = new ArraySequence<U>();
    size_t i = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it, ++i){
        result->Append(func(*it, i));
    }
    return result;
}

template<class T>
Sequence<T>* Skip(Sequence<T>& seq, size_t n){
    size_t len = seq.GetLength();
    if (n >= len) {
        return new ArraySequence<T>();
    }
    ArraySequence<T>* result = new ArraySequence<T>();

    auto it = seq.begin();
    for(size_t i = 0; i < n; ++i){
        ++it;
    }
    for(; it != seq.end(); ++it){
        result->Append(*it);
    }
    return result;
}

template<class T>
Sequence<T>* Take(Sequence<T>& seq, size_t n){
    size_t len = seq.GetLength();
    if (n == 0) {
        return new ArraySequence<T>();
    }
    if (n >= len){
        n = len;
    }
    ArraySequence<T>* result = new ArraySequence<T>();
    size_t count = 0;
    for(auto it = seq.begin(); it != seq.end() && count < n; ++it, ++count){
        result->Append(*it);
    }
    return result;
}

template<class T, class U>
Sequence<std::pair<T,U>>* Zip(Sequence<T>& seq1, Sequence<U>& seq2){
    size_t min_len = std::min(seq1.GetLength(), seq2.GetLength());
    ArraySequence<std::pair<T,U>>* result = new ArraySequence<std::pair<T,U>>();

    auto it1 = seq1.begin();
    auto it2 = seq2.begin();

    for (size_t i = 0; i < min_len; ++i, ++it1, ++it2) {
        result->Append({*it1, *it2});
    }

    return result;
}

template<class T, class U>
Sequence<U>* FlatMap(Sequence<T>& seq, Sequence<U>* (*func)(const T&)) {
    auto* result = new ArraySequence<U>();
    
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        auto* mapped = func(*it);
        for (auto mit = mapped->begin(); mit != mapped->end(); ++mit) {
            result->Append(*mit);
        }
        delete mapped;
    }
    
    return result;
}

template<class T>
Sequence<T>* Range(T start, T end, T step = 1){
    if (step == 0){
        throw std::invalid_argument("Range: step cannot be zero");
    } 
    ArraySequence<T>* result = new ArraySequence<T>();
    T current = start;
    while ((step > 0 && current < end) || (step < 0 && current > end)) {
        result->Append(current);
        current += step;
    }
    return result;
}