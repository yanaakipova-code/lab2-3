#pragma once
#include <stdexcept>
#include <cstddef>
#include "Sequence.h"
#include "LinkedList.h"

template<class T>
class ListSequence : public Sequence<T>{
private:
    LinkedList<T>* m_list;
public:

    ListSequence(T* items, size_t count);
    ListSequence();
    ListSequence(const ListSequence<T>& other);

    ~ListSequence() override;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(size_t index) const override;
    size_t GetLength() const override;
    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override;

    void Append(T temp) override;
    void Prepend(T temp) override;
    void InsertAt(T temp, size_t index) override;
    Sequence<T>* Concat(Sequence<T>* other) const override;
};

#include "ListSequence.tpp"