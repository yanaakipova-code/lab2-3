#include "Set.hpp"

template<typename T, template<typename> class Container>
Set<T, Container>::Set(): m_data(new Container<T>())(){}

template<typename T, template<typename> class Container>
Set<T, Container>::Set(Container<T>& other): Set(){
    for(size_t i = 0; i < other.GetLength(); i++){
        m_data->Append(other.Get(i));
    }
}

template<typename T, template<typename> class Container>
Set<T, Container>::Set(Set<T, Container>& other):Set(){
    for(size_t i = 0; i < other.GetSize(); i++){
        m_data->Append(other.GetData(i));
    }
}

template<typename T, template<typename> class Container>
Set<T, Container>::~Set(){
    delete m_data;
}

template<typename T, template<typename> class Container>
unsigned int Set<T, Container>::GetSize() const{
    return m_data->GetLength();
}

template<typename T, template<typename> class Container>
T Set<T, Container>::GetData(unsigned int index) const{
    return m_data->Get(index);
}

template<typename T, template<typename> class Container>
void Set<T, Container>::Add(const T& value){
    for (size_t i = 0; i < GetSize(); i++){
        if(value == GetData(i)) return;
    }
    m_data->Append(value);
}

template<typename T, template<typename> class Container>
void Set<T, Container>::Remove(int index){
    if(index >= GetSize()){
        throw OutOfRangeException("Индекс за пределами множества");
    }
    Container<T>* new_set = new Container<T>();
    for(size_t i = 0; i < index; i++){
        new_set->Append(GetData(i));
    }
    for(size_t i = index + 1; i < GetSize(); i++){
        new_set->Append(GetData(i));
    }
    delete m_data;
    m_data = new_set;
}

template<typename T, template<typename> class Container>
void Set<T, Container>::Remove(const T& value){
    int index = -1;
    for(size_t i = 0; i < GetSize(); i++){
        if(GetData(i) == value){
            index = i;
        }
    }
    if(index == -1){
        throw NotSetElemException("нет такого элемента");
    }
    Remove(index);
}

template<typename T, template<typename> class Container>
bool Set<T, Container>::Contains(const T& value) const{
    for(size_t i = 0; i < GetSize(); i++){
        if(value == GetData(i)){
            return true;
            break;
        }
    }
    return false;
}

template<typename T, template<typename> class Container>
template<typename U>
Set<U, Container> Set<T, Container>::Map(U(*func)(const T&)){
    Set<U, Container> result;
    for(size_t i = 0; i < GetSize(); i++){
        result.Add(func(GetData(i)));
    }
    return result;
}


template<typename T, template<typename> class Container>
Set<T, Container> Set<T, Container>::Where(bool (*predicate)(const T&)){
    Set<T, Container> result;
    for(size_t i = 0; i < GetSize(); i++){
        if(predicate(GetData(i))){
            result.Add(i)
        }
    }
    return result;
}

template<typename T, template<typename> class Container>
Set<T, Container> Set<T, Container>::Unification(const Set<T, Container>& other) const{
    Set<T, Container> new_set (*this);

    for(size_t i = 0; i < other.GetSize(); i++){
        new_set.Add(other.GetData(i));
    }
    return new_set;
}

// template<typename T, template<typename> class Container>
// Set<T, Container> Set<T, Container>::Intersection(const Set<T, Container>& other) const{
//     Set<T, Container> new_set;
//     for(size_t i = 0; i < GetSize(); i++){
//         for(size_t j = 0; j < other.GetSize(); j++){
//             if(GetData(i) == other.GetData(j)){
//                 new_set.Add(GetData(i));
//                 break;
//             }
//         }
//     } 
//     return new_set; 
// }


template<typename T, template<typename> class Container>
Set<T, Container> Set<T, Container>::Intersection(const Set<T, Container>& other) const{
    Set<T, Container> new_set;

    for(size_t i = 0; i < GetSize(); i++){
        if(other.Contains(GetData(i))){
            new_set.Add(GetData(i));
        }
    }
    return new_set;
}

template<typename T, template<typename> class Container>
Set<T, Container> Set<T, Container>::Subtraction(const Set<T, Container>& other) const{
    Set<T, Container> new_set = *this;

    for(size_t i = 0; i < GetSize(); i++){
        if(other.Contains(GetData(i))){
            new_set.Remove(GetData(i));
        }
    }
    return new_set;
}


