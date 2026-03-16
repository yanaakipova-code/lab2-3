#include <cstddef>
#include <stdexcept> 
#include "DynamicArray.h"

template<class T>
DynamicArray<T>::DynamicArray(T* items, size_t count){
    m_size = count;
    m_capacity = count*2;
    m_data = new T[m_capacity];
    for(size_t i = 0; i< count; i++){
        m_data[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(size_t size){
    m_size = size;
    if(size == 0){
        m_capacity = 1;
    }else{
        m_capacity = size * 2;
    }
    m_data = new T[m_capacity];

    for(size_t i; i < size; i++){
        m_data[i] = T();
    }
}

template<class T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &dynamic_array){
    m_size = dynamic_array.m_size;
    m_capacity = dynamic_array.m_capacity;
    m_data = new T[m_capacity];

    for (size_t i; i < m_size; i++){
        m_data[i] = dynamic_array.m_data[i];
    }
}

template<class T>
DynamicArray<T>::~DynamicArray(){
    delete[] m_data;
}
