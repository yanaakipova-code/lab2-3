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
