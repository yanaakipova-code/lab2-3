#pragma once
#include <stdexcept>
#include <cstddef>

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
    LinkedList (T* items, size_t count);
    LinkedList ();
    LinkedList (const LinkedList<T>& linked_list);
    
    ~LinkedList();
 
    T GetFirst();
    T GetLast();

    Node* GetNode(size_t index);
    T Get(size_t index);
    LinkedList<T>* GetSubList(size_t start_index, int end_index);
    size_t GetLength(); 

    void Append(T temp);
    void Prepend(T temp);

};

#include "LinkedList.tpp"
