#pragma once
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include <algorithm>
#include <stdexcept>

template<class T, class U>
Sequence<U>* MapWithIndex(ArraySequence<T>& seq, U (*func)(const T&,size_t)){
    size_t len = seq.GetLength();
    ArraySequence<U>* result = new ArraySequence<U>();
    size_t i = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it, ++i){
        result->Append(func(*it, i));
    }
    return result;
}

template<class T, class U>
Sequence<U>* MapWithIndex(ListSequence<T>& seq, U (*func)(const T&,size_t)){
    size_t len = seq.GetLength();
    ListSequence<U>* result = new ListSequence<U>();
    size_t i = 0;
    for (auto it = seq.begin(); it != seq.end(); ++it, ++i){
        result->Append(func(*it, i));
    }
    return result;
}


template<class T>
Sequence<T>* Skip(ArraySequence<T>& seq, size_t n){
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
Sequence<T>* Skip(ListSequence<T>& seq, size_t n){
    size_t len = seq.GetLength();
    if (n >= len) {
        return new ListSequence<T>();
    }
    ListSequence<T>* result = new ListSequence<T>();

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
Sequence<T>* Take(ArraySequence<T>& seq, size_t n){
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

template<class T>
Sequence<T>* Take(ListSequence<T>& seq, size_t n){
    size_t len = seq.GetLength();
    if (n == 0) {
        return new ListSequence<T>();
    }
    if (n >= len){
        n = len;
    }
    ListSequence<T>* result = new ListSequence<T>();
    size_t count = 0;
    for(auto it = seq.begin(); it != seq.end() && count < n; ++it, ++count){
        result->Append(*it);
    }
    return result;
}

template<class T, class U>
Sequence<std::pair<T,U>>* Zip(ArraySequence<T>& seq1, ArraySequence<U>& seq2){
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
Sequence<std::pair<T,U>>* Zip(ListSequence<T>& seq1, ListSequence<U>& seq2){
    size_t min_len = std::min(seq1.GetLength(), seq2.GetLength());
    ListSequence<std::pair<T,U>>* result = new ListSequence<std::pair<T,U>>();

    auto it1 = seq1.begin();
    auto it2 = seq2.begin();

    for (size_t i = 0; i < min_len; ++i, ++it1, ++it2) {
        result->Append({*it1, *it2});
    }

    return result;
}

template<class T, class U>
Sequence<U>* FlatMap(ArraySequence<T>& seq, ArraySequence<U>* (*func)(const T&)) {
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

template<class T, class U>
Sequence<U>* FlatMap(ListSequence<T>& seq, ListSequence<U>* (*func)(const T&)) {
    auto* result = new ListSequence<U>();
    
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
        throw ZeroStepException("Range: шаг не может быть 0");
    } 
    ArraySequence<T>* result = new ArraySequence<T>();
    T current = start;
    while ((step > 0 && current < end) || (step < 0 && current > end)) {
        result->Append(current);
        current += step;
    }
    return result;
}