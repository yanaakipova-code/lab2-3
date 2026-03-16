#include <LinkedList.h>
#include <cstddef>
#include <stdexcept> 

template<class T>
LinkedList<T>::LinkedList()
    : m_head(nullptr), m_tail(nullptr), m_size(0){}

template<class T>
LinkedList<T>::LinkedList (T* items, size_t count)
    : LinkedList()
    {
        if (items = nullptr){
            throw std::invalid_argument("Нулевое значение аргумента");
        }

        for (size_t i = 0; i < count; ++i) {
            Node* new_node = new Node(items[i]);
            if (m_size == 0) {
                m_head = new_node;
                m_tail = new_node;
            } else {
                m_tail->next = new_node;
                new_node->prev = m_tail;
                m_tail = new_node;
            }
            ++m_size;
        }
}

template<class T>
LinkedList<T>::LinkedList (const LinkedList<T>& linked_list)
    : LinkedList(){
    Node* current = linked_list.m_head;
    while (current != nullptr) {
        Node* new_node = new Node(current->data);
        if (m_size == 0) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        ++m_size;
        current = current->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node* current = m_head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template<class T>
T LinkedList<T>::GetFirst(){
    if(m_size = 0){
        throw std::out_of_range("Список пуст");
    }
    return m_head->data;
}

template<class T>
T LinkedList<T>::GetLast(){
    if(m_size = 0){
        throw std::out_of_range("Список пуст");
    }
    return m_teil->data;
}
template<class T>
LinkedList<T>::Node* LinkedList<T>::GetNode(size_t index){
    if (index >= m_size) {
        throw std::out_of_range("Индекс за списком");
    }
    Node* current;
    if (index < m_size / 2) {
        current = m_head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = m_tail;
        for (size_t i = m_size - 1; i > index; --i) {
            current = current->prev;
        }
    }
    return current;
}

template<class T>
T LinkedList<T>::Get(size_t index){
    return GetNode(index)->data;
}

template<class T>
void LinkedList<T>::Append(T temp) {
    Node* new_node = new Node(temp);
    
    if (m_size == 0) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        m_tail->next = new_node;
        new_node->prev = m_tail;
        m_tail = new_node;
    }
    
    ++m_size;
}

template<class T>
LinkedList<T>*::GetSubList(size_t start_index, int end_index){
    if(start_index > end_index || end_index >= size_t){
        throw std::out_of_range("Индекс за размером списка");
    }

    LinkedList<T>* sub_list = new LinkedList<T>();
    Node* current = GetNode(start_index);
    
    for (size_t i = start_index; i <= end_index; ++i) {
        subList->Append(current->data);
        current = current->next;
    }
    return subList;
}

template<class T>
size_t LinkedList<T>::GetLength(){
    return m_size;
}

template<class T>
void LinkedList<T>::Prepend(T temp){
    Node* new_node = new Node(temp);

    if(m_size == 0){
        m_head = new_node;
        m_tail = new_node;
    }else{
        new_node->next = m_head;
        m_head->prev = new_node;
        m_head = new_node;
    }
    ++m_size;
}