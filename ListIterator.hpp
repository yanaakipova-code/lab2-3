#pragma once
#include <iterator>
#include <cstddef>

template<class T>
class LinkedList;

template<class T>
class ListIterator {
private:
    typename LinkedList<T>::Node* m_ptr;
    
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    
    ListIterator(typename LinkedList<T>::Node* ptr = nullptr) : m_ptr(ptr) {}
    
    reference operator*() const {
        return m_ptr->data;
    }
    
    pointer operator->() {
        return &(m_ptr->data);
    }
    
    ListIterator& operator++() {
        m_ptr = m_ptr->next;
        return *this;
    }
    
    ListIterator operator++(int) {
        ListIterator old = *this;
        m_ptr = m_ptr->next;
        return old;
    }
    
    bool operator==(const ListIterator& other) const {
        return m_ptr == other.m_ptr;
    }
    
    bool operator!=(const ListIterator& other) const {
        return !(*this == other);
    }
};

template<class T>
class ConstListIterator {
private:
    const typename LinkedList<T>::Node* m_ptr;
    
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    
    ConstListIterator(const typename LinkedList<T>::Node* ptr = nullptr) : m_ptr(ptr) {}
    
    reference operator*() const {
        return m_ptr->data;
    }
    
    pointer operator->() const {
        return &(m_ptr->data);
    }
    
    ConstListIterator& operator++() {
        m_ptr = m_ptr->next;
        return *this;
    }
    
    ConstListIterator operator++(int) {
        ConstListIterator old = *this;
        m_ptr = m_ptr->next;
        return old;
    }
    
    bool operator==(const ConstListIterator& other) const {
        return m_ptr == other.m_ptr;
    }
    
    bool operator!=(const ConstListIterator& other) const {
        return !(*this == other);
    }
};