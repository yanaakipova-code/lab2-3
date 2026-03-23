#pragma once
#include <stdexcept>
#include <cstddef>

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
};

