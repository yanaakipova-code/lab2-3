#pragma once
#include <stdexcept>
#include <cstddef>
#include <memory>
#include <initializer_list>
#include "Sequence.hpp"
#include "ListIterator.hpp"
#include "LinkedList.hpp"
#include "Option.hpp"
#include "Iterator.hpp"

template<class T>
class ListSequence : public Sequence<T>{
private:
    LinkedList<T>* m_list;
    
public:
    ListSequence(T* items, size_t count);
    ListSequence();
    ListSequence(const ListSequence<T>& other);
    ListSequence(std::initializer_list<T> list);
    
    ~ListSequence() override;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(size_t index) const override;
    size_t GetLength() const override;
    Sequence<T>* GetSubsequence(size_t start_index, size_t end_index) const override;
    void Set(size_t index, T value);

    const T& GetRef(size_t index) const;
    T& GetRef(size_t index);

    void Append(T temp) override;
    void Prepend(T temp) override;
    void InsertAt(T temp, size_t index) override;
    Sequence<T>* Concat(Sequence<T>* other) const override;

    Sequence<T>* Map(T (*func)(T)) override;
    Sequence<T>* Where(bool (*predicate)(T)) override;
    T Reduce(T (*func)(T, T), T initial) override;

    Option<T> TryGetFirst(bool (*predicate)(T) = nullptr) const override;
    Option<T> TryGetLast(bool (*predicate)(T) = nullptr) const override;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    ListIterator<T> begin();
    ListIterator<T> end();
    ConstListIterator<T> begin() const;
    ConstListIterator<T> end() const;
    ConstListIterator<T> cbegin() const;
    ConstListIterator<T> cend() const;
};

#include "ListSequence.tpp"