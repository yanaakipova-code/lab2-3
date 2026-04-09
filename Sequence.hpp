#pragma once
#include <stdexcept>
#include <cstddef>
#include "Option.hpp"
#include "Iterator.hpp" 

template<class T>
class Sequence{
public:
    virtual ~Sequence() = default;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(size_t index) const = 0;
    virtual size_t GetLength() const = 0;
    virtual Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) const = 0;

    virtual void Append(T temp) = 0;
    virtual void Prepend(T temp) = 0;
    virtual void InsertAt(T temp, size_t index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* sequence) const = 0;

    virtual Sequence<T>* Map(T (*func)(T)) = 0;
    virtual Sequence<T>* Where(bool (*predicate)(T)) = 0;
    virtual T Reduce(T (*func)(T, T), T initial) = 0;

    virtual Option<T> TryGetFirst(bool (*predicate)(T) = nullptr) const = 0;
    virtual Option<T> TryGetLast(bool (*predicate)(T) = nullptr) const = 0;

    virtual std::unique_ptr<Iterator<T>> begin() = 0;
    virtual std::unique_ptr<Iterator<T>> end() = 0;
    virtual std::unique_ptr<ConstIterator<T>> begin() const = 0;
    virtual std::unique_ptr<ConstIterator<T>> end() const = 0;
    virtual std::unique_ptr<ConstIterator<T>> cbegin() const = 0;
    virtual std::unique_ptr<ConstIterator<T>> cend() const = 0;
};

