#include "ListSequence.hpp"
#include <stdexcept>

template<class T>
ListSequence<T>::ListSequence() {
    m_list = new LinkedList<T>();
}

template<class T>
ListSequence<T>::ListSequence(T* items, size_t count){
    if (items == nullptr && count > 0) {
        throw std::invalid_argument("у списка нулевой указатель");
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
        throw std::out_of_range("Sequence пуст");
    }
    return m_list->GetFirst();
}

template<class T>
T ListSequence<T>::GetLast() const {
    if (m_list->GetLength() == 0) {
        throw std::out_of_range("Sequence пуст");
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
        throw std::out_of_range("Неверные индексы");
    }

    LinkedList<T>* subList = m_list->GetSubList(start_index, end_index);
   
    T* tempData = new T[subList->GetLength()];
    for (int i = 0; i < subList->GetLength(); i++) {
        tempData[i] = subList->Get(i);
    }
    
    ListSequence<T>* result = new ListSequence<T>(tempData, subList->GetLength());

    delete[] tempData;
    delete subList;
    
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
        throw std::out_of_range("Индекс за передлами массива");
    }
    
    m_list->InsertAt(temp, index);
}

template<class T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* other) const {
    if (other == nullptr) {
        throw std::invalid_argument("у списка нулевой указатель");
    }
    
    ListSequence<T>* result = new ListSequence<T>(*this);
    
    for (int i = 0; i < other->GetLength(); i++) {
        result->Append(other->Get(i));
    }
    
    return result;
}

template<class T>
Sequence<T>* ListSequence<T>::Map(T (*func)(T)){
    T* result = new T[GetLength()];
    for (size_t i = 0; i < GetLength(); i++) {
        result[i] = func(Get(i));
    }
    ListSequence<T>* new_seq = new ListSequence<T>(result, GetLength());
    delete[] result;
    return new_seq;
}

template<class T>
Sequence<T>* ListSequence<T>::Where(bool (*predicate)(T)) {
    DynamicArray<T> temp;
    for (size_t i = 0; i < GetLength(); i++) {
        T elem = Get(i);
        if (predicate(elem)) {
            temp.Append(elem);
        }
    }
    return new ListSequence<T>(temp.GetData(), temp.GetSize());
}


template<class T>
T ListSequence<T>::Reduce(T (*func)(T, T), T initial) {
    T result = initial;
    for (size_t i = 0; i < GetLength(); i++) {
        result = func(result, Get(i));
    }
    return result;
}