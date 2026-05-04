#include "Set.hpp"

template<typename T, template<typename> class Container>
Set<T, Container>::Set(): m_data(new Container<T>()){}

template<typename T, template<typename> class Container>
Set<T, Container>::Set(const Container<T>& other): Set{}{
    for(const auto& i : other){
        Add(i);
    }
}

template<typename T, template<typename> class Container>
Set<T, Container>::Set(const Set<T, Container>& other):Set{}{
    for(const auto& i : other){
        m_data->Append(i);
    }
}

template<typename T, template<typename> class Container>
Set<T, Container>::~Set(){
    delete m_data;
}

template<typename T, template<typename> class Container>
size_t Set<T, Container>::GetSize() const{
    return m_data->GetLength();
}

template<typename T, template<typename> class Container>
T Set<T, Container>::GetData(size_t index) const{
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
void Set<T, Container>::RemoveByIndex(size_t index){
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
void Set<T, Container>::RemoveByValue(const T& value){
    int index = -1;
    for(int i = 0; i < GetSize(); i++){
        if(GetData(i) == value){
            index = i;
            break;
        }
    }
    if(index == -1){
        throw NotSetElemException("нет такого элемента");
    }
    RemoveByIndex(index);
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
            result.Add(GetData(i));
        }
    }
    return result;
}

template<typename T, template<typename> class Container>
Set<T, Container> Set<T, Container>::Unification(const Set<T, Container>& other) const{
    Set<T, Container> new_set (*this);

    for(const auto& i : other){
        new_set.Add(i);
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
            new_set.RemoveByValue(GetData(i));
        }
    }
    return new_set;
}

template<typename T, template<typename> class Container>
bool Set<T, Container>::CheckSubset(const Set<T, Container>& other) const {
    for (const auto& i : other) {
        if (!Contains(i)) {
            return false;
        }
    }
    return true;
}

template<typename T, template<typename> class Container>
bool Set<T, Container>::Сomparison(const Set<T, Container>& other) const{
    if(GetSize() == other.GetSize() && CheckSubset(other)){
        return true;
    }
    return false;
}

template<typename T, template<typename> class Container>
auto Set<T, Container>::begin(){
    return m_data->begin();
}

template<typename T, template<typename> class Container>
auto Set<T, Container>::end(){
    return m_data->end();
}

template<typename T, template<typename> class Container>
auto Set<T, Container>::cbegin() const{
    return m_data->cbegin();
}

template<typename T, template<typename> class Container>
auto Set<T, Container>::cend() const{
    return m_data->cend();
}

template<typename T, template<typename> class Container>
auto Set<T, Container>::begin() const {
    return m_data->cbegin();
}

template<typename T, template<typename> class Container>
auto Set<T, Container>::end() const {
    return m_data->cend();
}