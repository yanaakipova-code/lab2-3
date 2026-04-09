#pragma once
#include <memory>
#include <iterator>

template<class T>
class Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    virtual ~Iterator() = default;
    
    virtual reference operator*() = 0;
    virtual pointer operator->() = 0;
    virtual Iterator& operator++() = 0;
    virtual bool operator==(const Iterator& other) const = 0;
    virtual bool operator!=(const Iterator& other) const = 0;
    virtual std::unique_ptr<Iterator<T>> clone() const = 0;
};

template<class T>
class ConstIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    virtual ~ConstIterator() = default;
    
    virtual reference operator*() const = 0;
    virtual pointer operator->() const = 0;
    virtual ConstIterator& operator++() = 0;
    virtual bool operator==(const ConstIterator& other) const = 0;
    virtual bool operator!=(const ConstIterator& other) const = 0;
    virtual std::unique_ptr<ConstIterator<T>> clone() const = 0;
};