#include "ArraySequence.h"
#include <stdexcept>

template<class T>
ArraySequence<T>::ArraySequence(){
    m_items = new DynamicArray<T>(0);
}

template<class T>
ArraySequence<T>::ArraySequence(T* temp, size_t count){
    m_items = new DynamicArray<T>(items, count);
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& array_sequence){
    m_items = new DynamicArray<T>(*other.m_items);
}

template<class T>
ArraySequence<T>::~ArraySequence(){
    delete m_items;
}