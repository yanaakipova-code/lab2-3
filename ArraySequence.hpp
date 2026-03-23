#pragma once
#include <stdexcept>
#include <cstddef>
#include "Sequence.hpp"
#include "DynamicArray.hpp"

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
};

#include "ArraySequence.tpp"
