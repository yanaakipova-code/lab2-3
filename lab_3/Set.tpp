#include "Set.hpp"

template<typename T, template<typename> class Container>
Set<T, Container>::Set(): m_data = new Container<T>(){}

template<typename T, template<typename> class Container>
Set<T, Container>::Set(Container<T>& other): Set(){
    for(size_t i = 0; i < other.GetLength(); i++){
        m_data->Append(i);
    }
}

template<typename T, template<typename> class Container>
Set<T, Container>::Set(Set<T, Container>& other):Set(){
    for(size_t i = 0; i < other.GetSize(); i++){
        m_data.Append(other.GetData(i));
    }
}

template<typename T, template<typename> class Container>
Set<T, Container>::~Set(){
    delete m_data;
}

template<typename T, template<typename> class Container>
unsigned int Set<T, Container>::GetSize(){
    return m_data->GetLength();
}

template<typename T, template<typename> class Container>
T Set<T, Container>::GetData(unsigned int index){
    return m_data->Get(index);
}