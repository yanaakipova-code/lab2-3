#pragma once
#include <iterator>
template<class T>
class Iterator{
private:
    T* m_ptr;
public:
    // типы для итератора
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Iterator(T* ptr): m_ptr(ptr){}// список инициализаций

    reference operator*() const {
        return *m_ptr;
    }

    pointer operator->(){
        return m_ptr;
    }

    Iterator& operator++(){
        ++m_ptr;
        return *this;
    }

    Iterator operator++(int){
        Iterator old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const Iterator& other) const{
        return m_ptr == other.m_ptr;
    }
    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }
};

template<class T>
class ConstIterator{
private:
    const T* m_ptr;
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    ConstIterator(const T* ptr) : m_ptr(ptr) {}
    
    reference operator*() const{
        return *m_ptr;
    }

    pointer operator->() const{
        return m_ptr;
    }

    ConstIterator& operator++() {
        ++m_ptr;
        return *this;
    }
    
    ConstIterator operator++(int) {
        ConstIterator tmp = *this;
        ++(*this);
        return tmp;
    }

     bool operator==(const ConstIterator& other) const { 
        return m_ptr == other.m_ptr; 
    }

    bool operator!=(const ConstIterator& other) const {
        return !(*this == other);
    }
};