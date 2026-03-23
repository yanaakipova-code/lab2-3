#pragma once
#include <memory>
#include "ArraySequence.hpp"
#include <stdexcept>

template<class T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence(T* items, size_t count);
    ImmutableArraySequence();
    ImmutableArraySequence(const ImmutableArraySequence<T>& other);

    void Append(T temp) override;
    void Prepend(T temp) override;
    void InsertAt(T temp, size_t index) override;

    std::unique_ptr<ImmutableArraySequence<T>> WithAppend(T item) const;
    std::unique_ptr<ImmutableArraySequence<T>> WithPrepend(T item) const;
    std::unique_ptr<ImmutableArraySequence<T>> WithInsertAt(T item, size_t index) const;

    std::unique_ptr<Sequence<T>> Concat(Sequence<T>* other) const override;
    std::unique_ptr<ArraySequence<T>> ToMutable() const;
};

#include "ImmutableArraySequence.tpp"