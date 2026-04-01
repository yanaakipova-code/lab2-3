#include "LinkedList.hpp"
#include <cstddef>
#include <stdexcept> 
template<class T>
LinkedList<T>::LinkedList() 
    : m_head(nullptr), m_tail(nullptr), m_size(0){}
template<class T>
LinkedList<T>::LinkedList (T* items, size_t count)
    : LinkedList()
    {
        if (items == nullptr){
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
            m_size++;
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
        m_size++;
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
T LinkedList<T>::GetFirst() const {
    if(m_size == 0){
        throw std::out_of_range("Список пуст");
    }
    return m_head->data;
}

template<class T>
T LinkedList<T>::GetLast() const {
    if(m_size == 0){
        throw std::out_of_range("Список пуст");
    }
    return m_tail->data;

}
template<class T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(size_t index) const {
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
T* LinkedList<T>::GetData() {
    if (m_size == 0) {
        return nullptr;
    }
    
    T* data = new T[m_size];
    Node* current = m_head;
    for (size_t i = 0; i < m_size; i++) {
        data[i] = current->data;
        current = current->next;
    }
    return data;
}

template<class T>
const T* LinkedList<T>::GetData() const {
    if (m_size == 0) {
        return nullptr;
    }
    
    T* data = new T[m_size];
    Node* current = m_head;
    for (size_t i = 0; i < m_size; i++) {
        data[i] = current->data;
        current = current->next;
    }
    return data;
}

template<class T>
T LinkedList<T>::Get(size_t index) const {
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
    
    m_size++;
}

template<class T>
LinkedList<T>* LinkedList<T>::GetSubList(size_t start_index, size_t end_index) const {
    if (start_index > end_index || end_index >= m_size) {
        throw std::out_of_range("Индекс за размером списка");
    }

    LinkedList<T>* sub_list = new LinkedList<T>();
    Node* current = GetNode(start_index);
    
    for (size_t i = start_index; i <= end_index; ++i) {
        sub_list->Append(current->data);
        current = current->next;
    }
    return sub_list;
}

template<class T>
size_t LinkedList<T>::GetLength() const{
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
    m_size++;
}

template<class T>
void LinkedList<T>::InsertAt(T temp,size_t index){
    if (index > m_size){
        throw std::out_of_range("Индекс за массивом");
    }
    if(index == 0){
        Prepend(temp);
    }else if(index == m_size){
        Append(temp);
    }else{
        Node* current = GetNode(index);
        Node* new_node = new Node(temp);

        new_node->prev = current->prev;
        new_node->next = current;
        new_node->prev->next = new_node;
        current->prev = new_node;

        m_size++;
    }

}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T> *list){
    LinkedList<T>* result = new LinkedList<T>(*this);
    
    Node* current = list->m_head;
    while (current != nullptr) {
        result->Append(current->data);
        current = current->next;
    }
    
    return result;
}

template<class T>
void LinkedList<T>::Set(size_t index, T value){
     GetNode(index)->data = value;
}

template<class T>
void LinkedList<T>::RemoveAt(size_t index){
    if (index >= m_size) {
        throw std::out_of_range("Индекс за пределами списка");
    }

    Node* to_delete = GetNode(index);

    if(to_delete->prev){
        to_delete->prev->next = to_delete->next;
    }else{
        m_head = to_delete->next;
    }

    if(to_delete->next){
        to_delete->next->prev = to_delete->prev;
    }else{
        m_tail = to_delete->prev;
    }

    delete to_delete;
    m_size--;
}

template<class T>
bool LinkedList<T>::IsEmpty() const{
    return m_size == 0;
}

template<class T>
void LinkedList<T>::Clear(){
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