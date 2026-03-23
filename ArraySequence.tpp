#include "ArraySequence.hpp"
#include <stdexcept>

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
    
    int newSize = end_index - start_index + 1;
    T* tempData = new T[newSize];

    for (int i = 0; i < newSize; i++) {
        tempData[i] = m_items->Get(start_index + i);
    }
    
    ArraySequence<T>* result = new ArraySequence<T>(tempData, newSize);
    delete[] tempData;
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
    
    int this_size = GetLength();
    int other_size = other->GetLength();
    int new_size = this_size + other_size;
    
    T* temp_data = new T[new_size];

    for (int i = 0; i < this_size; i++) {
        temp_data[i] = Get(i);
    }
    
    for (int i = 0; i < other_size; i++) {
        temp_data[this_size + i] = other->Get(i);
    }

    ArraySequence<T>* result = new ArraySequence<T>(temp_data, new_size);
    delete[] temp_data;
    return result;
}

template<class T>
Sequence<T>* ArraySequence<T>::Map(T (*func)(T)){
    T* result = new T[GetLength()];
    for (size_t i = 0; i < GetLength(); i++){
        result[i] = func(get(i));
    }
    return new ArraySequence<T>(result, GetLength);
}

template<class T>
Sequence<T>* ArraySequence<T>::Where(bool (*predicate)(T)){
    DynamicArray<T> temp;
    for (size_t i = 0; i < GetLength(); i++) {
        T elem = Get(i);
        if (predicate(elem)) {
            temp.Append(elem);
        }
    }
    T* result = new T[temp.GetSize()];
    for (size_t i = 0; i < temp.GetSize(); i++){
        result[i] = temp.Get(i);
    }
    ArraySequence<T>* res = new ArraySequence<T>(result, temp.GetSize());
    delete[] result;
    return res;
}

template<class T>
T ArraySequence<T>::Reduce(T (*func)(T, T), T initial){
    T result = initial;
    for (size_t i = 0; i < GetLength(); i++) {
        result = func(result, Get(i));
    }
    return result;
}