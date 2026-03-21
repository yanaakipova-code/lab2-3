#include "ImmutableListSequence.h"

template<class T>
ImmutableListSequence<T>::ImmutableListSequence(T* items, size_t count)
    :ListSequence<T>(items, count) {}

template<class T>
ImmutableListSequence<T>::ImmutableListSequence()
    :ListSequence<T>() {}

template<class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T>& other)
    :ListSequence<T>(other) {}

template<class T>
void ImmutableListSequence<T>::Append(T temp) {
    throw std::runtime_error("Нельзя изменять неизменяемую последовательность");
}

template<class T>
void ImmutableListSequence<T>::Prepend(T temp) {
    throw std::runtime_error("Нельзя изменять неизменяемую последовательность");
}

template<class T>
void ImmutableListSequence<T>::InsertAt(T temp, size_t index) {
    throw std::runtime_error("Нельзя изменять неизменяемую последовательность");
}

template<class T>
ImmutableListSequence<T>* ImmutableListSequence<T>::WithAppend(T item) const {
    ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
    copy->ListSequence<T>::Append(item);
    return copy;
}

template<class T>
ImmutableListSequence<T>* ImmutableListSequence<T>::WithPrepend(T item) const {
    ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
    copy->ListSequence<T>::Prepend(item);
    return copy;
}

template<class T>
ImmutableListSequence<T>* ImmutableListSequence<T>::WithInsertAt(T item, size_t index) const {
    if (index < 0 || index > this->GetLength()) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
    copy->ListSequence<T>::InsertAt(item, index);
    return copy;
}

template<class T>
Sequence<T>* ImmutableListSequence<T>::Concat(Sequence<T>* other) const {
    ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);
    for (size_t i = 0; i < other->GetLength(); i++) {
        result->ListSequence<T>::Append(other->Get(i));
    }
    return result;
}

template<class T>
ListSequence<T>* ImmutableListSequence<T>::ToMutable() const {
    size_t size = this->GetLength();
    T* dataCopy = new T[size];
    for (size_t i = 0; i < size; i++) {
        dataCopy[i] = this->Get(i);
    }
    ListSequence<T>* result = new ListSequence<T>(dataCopy, size);
    delete[] dataCopy;
    return result;
}