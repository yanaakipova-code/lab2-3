#include "Quete.hpp"

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(): m_data = new Container<T>(){}

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(const Quate<T, Container>& other): Quate(){
    for(size_t i = 0; i < othar.GetLength(); i++){
        m_data.Append(other.m_data->Get(i));
    }
}

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(const Container<T>& other): Quate(){
    for(size_t i = 0; i < other.GetLength(); i++){
        m_data->Append(other.Get(i));
    }
}

template<typename T, template<typename> class Container>
Quate<T, Container>::~Quate(){
    delete m_data;
}

template<typename T, template<typename> class Container>
void Quate<T, Container>::Enqueue(const T value){
    m_data->Append(value);
}

template<typename T, template<typename> class Container>
void Quate<T, Container>::Dequeue(){
    if(m_data->GetLength() == 0){
        throw QueueIsEmptyException("Очередь пустая");
    }

    Container<T>() new_data;
    for (size_t i = 1; i < m_data->GetLength(); i++){
        new_data.Append(m_data->Get(i));
    }

    m_data delete;
    m_data = new_data;
}

template<typename T, template<typename> class Container>
bool Quate<T, Container>::IsEmpty(){
    if(m_data->GetLength() == 0){
        return true;
    }
    else return false;
}

template<typename T, template<typename> class Container>
T Quate<T, Container>::Peek(){
    if(m_data->GetLength()){
        throw QueueIsEmptyException("Очередь пустая");
    }

    return m_data->Get(0);
}

template<typename T, template<typename> class Container>
template<typename U>
Quate<U, Container> Quate<T, Container>::Map(U (*func)(const T&)) const{
    Quate<U, Container>() new_quate;

    for (size_t i = 0; i < m_data->GetLeght(); i++){
        T new_elem = func(m_data->Get(i));
        new_elem.Enqueue(new_elem);
    }
    return new_elem;
}

template<typename T, template<typename> class Container>
Quate<T, Container> Quate<T, Container>::Where(bool (*predicate)(const T&)) const{
    Quate<T, Container>() new_quate;

    for(size_t i = 0; i < m_data->GetLeght(); i++){
        bool new_value = predicate(m_data->Get(i));
        if(new_value){
            new_quate.Enqueue(i);
        }
    }
    return new_quate;
}

template<typename T, template<typename> class Container>
T Quate<T, Container>::Reduce(T (*func)(const T&, const T&)) const{
    T result = 0;
    for(size_t i = 0; i < m_data->GetLeght(); i++){
        result = func(m_data->Get(i), result);
    }
    return result;
}