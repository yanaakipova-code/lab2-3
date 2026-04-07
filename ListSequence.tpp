#include "ListSequence.hpp"
#include "ListIterator.hpp"
#include "LinkedList.hpp"
#include <stdexcept>
#include "Error.hpp"
template<class T>
ListSequence<T>::ListSequence() {
    m_list = new LinkedList<T>();
}

template<class T>
ListSequence<T>::ListSequence(T* items, size_t count){
    if (items == nullptr && count > 0) {
        throw NullPointerException("у списка нулевой указатель");
    }
    m_list = new LinkedList<T>(items, count);
}

template<class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) {
    m_list = new LinkedList<T>(*other.m_list);
}

template<class T>
ListSequence<T>::~ListSequence() {
    delete m_list;
}

template<class T>
T ListSequence<T>::GetFirst() const {
    if (m_list->GetLength() == 0) {
        throw OutOfRangeException("Sequence пуст");
    }
    return m_list->GetFirst();
}

template<class T>
T ListSequence<T>::GetLast() const {
    if (m_list->GetLength() == 0) {
        throw EmptySequenceException("Sequence пуст");
    }
    return m_list->GetLast();
}

template<class T>
T ListSequence<T>::Get(size_t index) const {
    return m_list->Get(index);
}

template<class T>
size_t ListSequence<T>::GetLength() const {
    return m_list->GetLength();
}

template<class T>
Sequence<T>* ListSequence<T>::GetSubsequence(size_t start_index, size_t end_index) const {
    if (start_index < 0 || end_index >= GetLength() || start_index > end_index) {
        throw OutOfRangeException("Неверные индексы");
    }

    ListSequence<T>* result = new ListSequence<T>();
    for (size_t i = start_index; i <= end_index; i++) {
        result->Append(Get(i));
    }
    return result;
}

template<class T>
void ListSequence<T>::Append(T temp) {
    m_list->Append(temp);
}

template<class T>
void ListSequence<T>::Prepend(T temp) {
    m_list->Prepend(temp);
}

template<class T>
void ListSequence<T>::InsertAt(T temp, size_t index) {
    if (index < 0 || index > GetLength()) {
        throw OutOfRangeException("Индекс за передлами массива");
    }
    
    m_list->InsertAt(temp, index);
}

template<class T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* other) const {
    if (other == nullptr) {
        throw NullPointerException("у списка нулевой указатель");
    }
    
    ListSequence<T>* result = new ListSequence<T>(*this);
    
    for (size_t i = 0; i < other->GetLength(); i++) {
        result->Append(other->Get(i));
    }
    
    return result;
}

template<class T>
Sequence<T>* ListSequence<T>::Map(T (*func)(T)) {
    ListSequence<T>* result = new ListSequence<T>();
    for (auto it = begin(); it != end(); ++it) {
        result->Append(func(*it));
    }
    return result;
}

template<class T>
Sequence<T>* ListSequence<T>::Where(bool (*predicate)(T)) {
    ListSequence<T>* result = new ListSequence<T>();
    for (auto it = begin(); it != end(); ++it) {
        T elem = *it;
        if (predicate(elem)) {
            result->Append(elem);
        }
    }
    return result;
}

template<class T>
T ListSequence<T>::Reduce(T (*func)(T, T), T initial) {
    T result = initial;
    for (auto it = begin(); it != end(); ++it) {
        result = func(result, *it);
    }
    return result;
}

template<class T>
Option<T> ListSequence<T>::TryGetFirst(bool (*predicate)(T)) const {
    for (auto it = begin(); it != end(); ++it) {
        T elem = *it;
        if (predicate == nullptr || predicate(elem)) {
            return Option<T>::Some(elem);
        }
    }
    return Option<T>::None();
}

template<class T>
Option<T> ListSequence<T>::TryGetLast(bool (*predicate)(T)) const {
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
T& ListSequence<T>::operator[](size_t index) {
    if (index >= GetLength()) {
        throw OutOfRangeException("Индекс за выходит за пределы");
    }
    
    auto it = begin();
    for (size_t i = 0; i < index; ++i) {
        ++it;
    }
    return *it;
}

template<class T>
const T& ListSequence<T>::operator[](size_t index) const {
    if (index >= GetLength()) {
        throw OutOfRangeException("Индекс за выходит за пределы");
    }
    
    auto it = begin();
    for (size_t i = 0; i < index; ++i) {
        ++it;
    }
    return *it;
}

template<class T>
ListIterator<T> ListSequence<T>::begin() {
    return m_list->begin();
}

template<class T>
ListIterator<T> ListSequence<T>::end() {
    return m_list->end();
}

template<class T>
ConstListIterator<T> ListSequence<T>::begin() const {
    return m_list->begin();
}

template<class T>
ConstListIterator<T> ListSequence<T>::end() const {
    return m_list->end();
}

template<class T>
ConstListIterator<T> ListSequence<T>::cbegin() const {
    return m_list->cbegin();
}

template<class T>
ConstListIterator<T> ListSequence<T>::cend() const {
    return m_list->cend();
}
