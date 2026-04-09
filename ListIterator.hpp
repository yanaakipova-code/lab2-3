#pragma once
#include <memory>
#include "Iterator.hpp"

template<class T>
class LinkedList;

template<class T>
class ListIterator : public Iterator<T> {
private:
    typename LinkedList<T>::Node* m_nodePtr;
    
public:
    ListIterator(typename LinkedList<T>::Node* ptr = nullptr) : m_nodePtr(ptr) {}
    
    typename Iterator<T>::reference operator*() override {
        return m_nodePtr->data;
    }
    
    typename Iterator<T>::pointer operator->() override {
        return &(m_nodePtr->data);
    }
    
    Iterator<T>& operator++() override {
        if (m_nodePtr) m_nodePtr = m_nodePtr->next;
        return *this;
    }
    
    bool operator==(const Iterator<T>& other) const override {
        const ListIterator* otherList = dynamic_cast<const ListIterator*>(&other);
        if (!otherList) return false;
        return m_nodePtr == otherList->m_nodePtr;
    }
    
    bool operator!=(const Iterator<T>& other) const override {
        return !(*this == other);
    }
    
    std::unique_ptr<Iterator<T>> clone() const override {
        return std::make_unique<ListIterator<T>>(m_nodePtr);
    }
};

template<class T>
class ConstListIterator : public ConstIterator<T> {
private:
    const typename LinkedList<T>::Node* m_nodePtr;
    
public:
    ConstListIterator(const typename LinkedList<T>::Node* ptr = nullptr) : m_nodePtr(ptr) {}
    
    typename ConstIterator<T>::reference operator*() const override {
        return m_nodePtr->data;
    }
    
    typename ConstIterator<T>::pointer operator->() const override {
        return &(m_nodePtr->data);
    }
    
    ConstIterator<T>& operator++() override {
        if (m_nodePtr) m_nodePtr = m_nodePtr->next;
        return *this;
    }
    
    bool operator==(const ConstIterator<T>& other) const override {
        const ConstListIterator* otherList = dynamic_cast<const ConstListIterator*>(&other);
        if (!otherList) return false;
        return m_nodePtr == otherList->m_nodePtr;
    }
    
    bool operator!=(const ConstIterator<T>& other) const override {
        return !(*this == other);
    }
    
    std::unique_ptr<ConstIterator<T>> clone() const override {
        return std::make_unique<ConstListIterator<T>>(m_nodePtr);
    }
};