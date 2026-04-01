#include "ArraySequence.hpp"
#include "Iterator.hpp"
#include "Option.hpp"
#include "Bit.hpp"
#include <stdexcept>
#include <cstddef>
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
Iterator<T> ArraySequence<T>::begin() {
    return Iterator<T>(m_items->GetData());
}

template<class T>
Iterator<T> ArraySequence<T>::end() {
    return Iterator<T>(m_items->GetData() + m_items->GetSize());
}

template<class T>
ConstIterator<T> ArraySequence<T>::begin() const {
    return ConstIterator<T>(m_items->GetData());
}

template<class T>
ConstIterator<T> ArraySequence<T>::end() const {
    return ConstIterator<T>(m_items->GetData() + m_items->GetSize());
}

template<class T>
ConstIterator<T> ArraySequence<T>::cbegin() const {
    return ConstIterator<T>(m_items->GetData());
}

template<class T>
ConstIterator<T> ArraySequence<T>::cend() const {
    return ConstIterator<T>(m_items->GetData() + m_items->GetSize());
}

template<class T>
T ArraySequence<T>::GetFirst() const{
    if (m_items->GetSize() == 0) {
        throw std::out_of_range("ArraySequence пуст");
    }
    return m_items->Get(0);
}

template<class T>
T ArraySequence<T>::GetLast() const {
    int size = m_items->GetSize();
    if (size == 0) {
        throw std::out_of_range("ArraySequence пуст");
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
    if (start_index < 0 || end_index >= GetLength() || start_index > end_index) {
        throw std::out_of_range("Недопустимые индексы для ArraySequence");
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
    int old_size = m_items->GetSize();
    
    if (index < 0 || index > old_size) {
        throw std::out_of_range("Индекс за массивом");
    }
    
    m_items->Resize(old_size + 1);
    
    for (int i = old_size; i > index; i--) {
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
        throw std::invalid_argument("Нулквой указатель");
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
    for (auto it = begin(); it != end(); ++it) {
        result->Append(func(*it));
    }
    return result;
}

template<class T>
Sequence<T>* ArraySequence<T>::Where(bool (*predicate)(T)) {
    ArraySequence<T>* result = new ArraySequence<T>();
    for (auto it = begin(); it != end(); ++it) {
        T elem = *it;
        if (predicate(elem)) {
            result->Append(elem);
        }
    }
    return result;
}

template<class T>
T ArraySequence<T>::Reduce(T (*func)(T, T), T initial) {
    T result = initial;
    for (auto it = begin(); it != end(); ++it) {
        result = func(result, *it);
    }
    return result;
}

template<class T>
Option<T> ArraySequence<T>::TryGetFirst(bool (*predicate)(T)) const {
    for (auto it = begin(); it != end(); ++it) {
        T elem = *it;
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

// для доп баллов
template<class T>
T& ArraySequence<T>::operator[](size_t index) {
    return m_items->GetRef(index);
}

template<class T>
const T& ArraySequence<T>::operator[](size_t index) const {
    return m_items->GetRef(index);
}