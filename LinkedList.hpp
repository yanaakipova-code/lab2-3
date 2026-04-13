#pragma once
#include <initializer_list>
#include <stdexcept>
#include <cstddef>
#include <memory>

template<class T> class ListIterator;
template<class T> class ConstListIterator;

template<class T>
class LinkedList {
private:
    struct Node{
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        Node(const T& value, Node* next) : data(value), next(next), prev(nullptr) {}
        Node(const T& value, Node* next, Node* prev) : data(value), next(next), prev(prev) {}
    };
    
    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    friend class ListIterator<T>;
    friend class ConstListIterator<T>;

    LinkedList(T* items, size_t count);
    LinkedList();
    LinkedList(const LinkedList<T>& linked_list);
    ~LinkedList();
 
    T GetFirst() const;
    T GetLast() const;
    Node* GetNode(size_t index) const;
    T Get(size_t index) const;
    LinkedList<T>* GetSubList(size_t start_index, size_t end_index) const;
    size_t GetLength() const; 
    T* GetData();
    const T* GetData() const;

    void Append(T temp);
    void Prepend(T temp);
    void InsertAt(T temp, size_t index);

    LinkedList<T>* Concat(const LinkedList<T> *list);

    void Set(size_t index, T value);
    void RemoveAt(size_t index);
    bool IsEmpty() const;
    void Clear();
    
    Node* GetHead() { return m_head; }
    const Node* GetHead() const { return m_head; }

    ListIterator<T> begin();
    ListIterator<T> end();
    ConstListIterator<T> begin() const;
    ConstListIterator<T> end() const;
    ConstListIterator<T> cbegin() const;
    ConstListIterator<T> cend() const;
};

#include "LinkedList.tpp"