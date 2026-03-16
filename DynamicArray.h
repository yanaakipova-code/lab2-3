#pragma once
#include <stdexcept>
#include <cstddef>
template<class T>
class DynamicArray{
private:
    size_t m_size;
    size_t m_capacity;
    T* m_data;
public:
    DynamicArray(size_t size);
    DynamicArray(T* items, size_t count);
    DynamicArray(const DynamicArray<T> &dynamicArray);
};

#include "DynamicArray.tpp"
