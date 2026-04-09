#pragma once
#include <memory>
#include "Iterator.hpp"

template<class T>
class ArrayIterator : public Iterator<T> {
private:
    T* m_ptr;
    
public:
    ArrayIterator(T* ptr = nullptr) : m_ptr(ptr) {}
    
    typename Iterator<T>::reference operator*() override {
        return *m_ptr;
    }
    
    typename Iterator<T>::pointer operator->() override {
        return m_ptr;
    }
    
    Iterator<T>& operator++() override {
        ++m_ptr;
        return *this;
    }
    
    bool operator==(const Iterator<T>& other) const override {
        const ArrayIterator* otherArr = dynamic_cast<const ArrayIterator*>(&other);
        if (!otherArr) return false;
        return m_ptr == otherArr->m_ptr;
    }
    
    bool operator!=(const Iterator<T>& other) const override {
        return !(*this == other);
    }
    
    std::unique_ptr<Iterator<T>> clone() const override {
        return std::make_unique<ArrayIterator<T>>(m_ptr);
    }
};

template<class T>
class ConstArrayIterator : public ConstIterator<T> {
private:
    const T* m_ptr;
    
public:
    ConstArrayIterator(const T* ptr = nullptr) : m_ptr(ptr) {}
    
    typename ConstIterator<T>::reference operator*() const override {
        return *m_ptr;
    }
    
    typename ConstIterator<T>::pointer operator->() const override {
        return m_ptr;
    }
    
    ConstIterator<T>& operator++() override {
        ++m_ptr;
        return *this;
    }
    
    bool operator==(const ConstIterator<T>& other) const override {
        const ConstArrayIterator* otherArr = dynamic_cast<const ConstArrayIterator*>(&other);
        if (!otherArr) return false;
        return m_ptr == otherArr->m_ptr;
    }
    
    bool operator!=(const ConstIterator<T>& other) const override {
        return !(*this == other);
    }
    
    std::unique_ptr<ConstIterator<T>> clone() const override {
        return std::make_unique<ConstArrayIterator<T>>(m_ptr);
    }
};