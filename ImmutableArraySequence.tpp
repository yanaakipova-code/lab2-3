#include "ImmutableArraySequence.h"

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(T* items, size_t count)
    : ArraySequence<T>(items, count) {}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence()
    : ArraySequence<T>() {}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& other)
    : ArraySequence<T>(other) {}

template<class T>
void ImmutableArraySequence<T>::Append(T temp) {
    throw std::runtime_error("Ошибка: нельзя изменять неизменяемую последовательность (Append запрещен)");
}

template<class T>
void ImmutableArraySequence<T>::Prepend(T temp) {
    throw std::runtime_error("Ошибка: нельзя изменять неизменяемую последовательность (Prepend запрещен)");
}

template<class T>
void ImmutableArraySequence<T>::InsertAt(T temp, size_t index) {
    throw std::runtime_error("Ошибка: нельзя изменять неизменяемую последовательность (InsertAt запрещен)");
}

template<class T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::WithAppend(T item) const {
    size_t old_size = this->GetLength();
    T* new_data = new T[old_size + 1];

    for(size_t i = 0; i < old_size; i++){
        new_data = this->Get(i);
    }

    new_data[old_size] = item; 
    ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(new_data, old_size + 1); 

    delete [] new_data;
    return result;
}

template<class T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::WithInsertAt(T item, size_t index) const {
    size_t old_size = this->GetLength();
    T* new_data = new T[old_size + 1]; 

    for (size_t i = 0; i < index; i++) {
        new_data[i] = this->Get(i);
    }
    
    new_data[index] = item;
    
    for (size_t i = index; i < old_size; i++) {
        new_data[i + 1] = this->Get(i); 
    }
    
    ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(new_data, old_size + 1);
    
    delete[] new_data;
    return result;
}

template<class T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::WithPrepend(T item) const {
    return WithInsertAt(item, 0);
}

template<class T>
Sequence<T>* ImmutableArraySequence<T>::Concat(Sequence<T>* other) const {
    size_t this_size = this->GetLength();
    size_t other_size = other->GetLength();
    size_t new_size = this_size + other_size;

    T* new_data = new T[new_size];
    
    for (size_t i = 0; i < this_size; i++) {
        new_data[i] = this->Get(i);
    }
    
    for (size_t i = 0; i < other_size; i++) {
        new_data[this_size + i] = other->Get(i);
    }
    
    ImmutableArraySequence<T>* result = 
        new ImmutableArraySequence<T>(new_data, new_size);
    
    delete[] new_data;
    
    return result;
}