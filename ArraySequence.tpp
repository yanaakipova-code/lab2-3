#include "ArraySequence.hpp"
#include "Iterator.hpp"
#include "Option.hpp"
#include "Bit.hpp"
#include "Error.h"
#include <stdexcept>
#include <cstddef>
#include <memory>
#include "Sequence.hpp"

template<class T>
ArraySequence<T>::ArraySequence(){
    m_items = new DynamicArray<T>(0);
}

template<class T>
ArraySequence<T>::ArraySequence(T* temp, size_t count){
    m_items = new DynamicArray<T>(temp, count);
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& array_sequence){
    m_items = new DynamicArray<T>(*array_sequence.m_items);
}

template<class T>
ArraySequence<T>::~ArraySequence(){
    delete m_items;
}

template<class T>
T ArraySequence<T>::GetFirst() const{
    if (m_items->GetSize() == 0) {
        throw OutOfRangeException("ArraySequence пуст");
    }
    return m_items->Get(0);
}

template<class T>
T ArraySequence<T>::GetLast() const {
    int size = m_items->GetSize();
    if (size == 0) {
        throw OutOfRangeException("ArraySequence пуст");
    }
    return m_items->Get(size - 1);
}

template<class T>
T ArraySequence<T>::Get(size_t index) const {
    return m_items->Get(index);
}

template<class T>
size_t ArraySequence<T>::GetLength() const {
    return m_items->GetSize();
}

template<class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(size_t start_index, size_t end_index) const {
    if (start_index > end_index || end_index >= GetLength()) {
        throw InvalidArgumentException("Недопустимые индексы для ArraySequence");
    }
    
    ArraySequence<T>* result = new ArraySequence<T>();
    for (size_t i = start_index; i <= end_index; i++) {
        result->Append(m_items->Get(i));
    }
    return result;
}

template<class T>
void ArraySequence<T>::Append(T temp) {
    int old_size = m_items->GetSize();
    m_items->Resize(old_size + 1);
    m_items->Set(old_size, temp);
}

template<class T>
void ArraySequence<T>::Prepend(T temp) {
    InsertAt(temp, 0);
}

template<class T>
void ArraySequence<T>::InsertAt(T temp, size_t index) {
    size_t old_size = m_items->GetSize();
    
    if (index > old_size) {
        throw OutOfRangeException("Индекс за массивом");
    }
    
    m_items->Resize(old_size + 1);
    
    for (size_t i = old_size; i > index; i--) {
        m_items->Set(i, m_items->Get(i - 1));
    }
    
    m_items->Set(index, temp);
}

template<class T>
void ArraySequence<T>::Set(size_t index, T value) {
    m_items->Set(index, value);
}

template<class T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* other) const {
    if (other == nullptr) {
        throw NullPointerException("Нулевой указатель");
    }
    
    ArraySequence<T>* result = new ArraySequence<T>(*this);
    for (size_t i = 0; i < other->GetLength(); i++) {
        result->Append(other->Get(i));
    }
    return result;
}

template<class T>
Sequence<T>* ArraySequence<T>::Map(T (*func)(T)) {
    ArraySequence<T>* result = new ArraySequence<T>();
    size_t len = GetLength();
    for (size_t i = 0; i < len; i++) {
        result->Append(func(Get(i)));
    }
    return result;
}

template<class T>
Sequence<T>* ArraySequence<T>::Where(bool (*predicate)(T)) {
    ArraySequence<T>* result = new ArraySequence<T>();
    size_t len = GetLength();
    for (size_t i = 0; i < len; i++) {
        T elem = Get(i);
        if (predicate(elem)) {
            result->Append(elem);
        }
    }
    return result;
}

template<class T>
T ArraySequence<T>::Reduce(T (*func)(T, T), T initial) {
    T result = initial;
    size_t len = GetLength();
    for (size_t i = 0; i < len; i++) {
        result = func(result, Get(i));
    }
    return result;
}

template<class T>
Option<T> ArraySequence<T>::TryGetFirst(bool (*predicate)(T)) const {
    size_t len = GetLength();
    for (size_t i = 0; i < len; i++) {
        T elem = Get(i);
        if (predicate == nullptr || predicate(elem)) {
            return Option<T>::Some(elem);
        }
    }
    return Option<T>::None();
}

template<class T>
Option<T> ArraySequence<T>::TryGetLast(bool (*predicate)(T)) const {
    size_t len = GetLength();
    for (size_t i = len; i > 0; i--) {
        T elem = Get(i - 1);
        if (predicate == nullptr || predicate(elem)) {
            return Option<T>::Some(elem);
        }
    }
    return Option<T>::None();
}

template<class T>
T& ArraySequence<T>::operator[](size_t index) {
    return m_items->GetRef(index);
}

template<class T>
const T& ArraySequence<T>::operator[](size_t index) const {
    return m_items->GetRef(index);
}


template<class T>
std::unique_ptr<Iterator<T>> ArraySequence<T>::begin() {
    if (m_items->GetSize() == 0) {
        return std::make_unique<ArrayIterator<T>>(nullptr);
    }
    return std::make_unique<ArrayIterator<T>>(m_items->GetData());
}

template<class T>
std::unique_ptr<Iterator<T>> ArraySequence<T>::end() {
    return std::make_unique<ArrayIterator<T>>(m_items->GetData() + m_items->GetSize());
}

template<class T>
std::unique_ptr<ConstIterator<T>> ArraySequence<T>::begin() const {
    if (m_items->GetSize() == 0) {
        return std::make_unique<ConstArrayIterator<T>>(nullptr);
    }
    return std::make_unique<ConstArrayIterator<T>>(m_items->GetData());
}

template<class T>
std::unique_ptr<ConstIterator<T>> ArraySequence<T>::end() const {
    return std::make_unique<ConstArrayIterator<T>>(m_items->GetData() + m_items->GetSize());
}
template<class T>
std::unique_ptr<ConstIterator<T>> ArraySequence<T>::cbegin() const {
    if (m_items->GetSize() == 0) {
        return std::make_unique<ConstArrayIterator<T>>(nullptr);
    }
    return std::make_unique<ConstArrayIterator<T>>(m_items->GetData());
}

template<class T>
std::unique_ptr<ConstIterator<T>> ArraySequence<T>::cend() const {
    return std::make_unique<ConstArrayIterator<T>>(m_items->GetData() + m_items->GetSize());
}