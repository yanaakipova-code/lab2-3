#pragma once
#include <stdexcept>
#include <cstddef>
template<class T>
class DynamicArray{
private:
    size_t m_size;
    T* m_data;
public:
    DynamicArray(); 
    DynamicArray(T* items, size_t count);
    DynamicArray(size_t size);
    DynamicArray(DynamicArray<T> &dynamic_array);

    ~DynamicArray();

    T Get(size_t index);
    size_t GetSize();
    void Set(size_t index, T value);
    void Resize(size_t new_size);

    T& GetRef(size_t index);
    const T& GetRef(size_t index) const;

    T* GetData();
    const T* GetData() const;
};

#include "DynamicArray.tpp"
