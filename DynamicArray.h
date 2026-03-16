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
    DynamicArray(T* items, size_t count);
    DynamicArray(size_t size);
    DynamicArray(DynamicArray<T> &dynamic_array);

    ~DynamicArray();
};

#include "DynamicArray.tpp"
