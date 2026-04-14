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