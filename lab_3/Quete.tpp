#include "Quete.hpp"
#include "../Error.hpp"

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(): m_data(new Container<T>()) {}

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(const Quate<T, Container>& other): Quate{}{
    for(const auto& i : other){
        m_data->Append(i);
    }
}

template<typename T, template<typename> class Container>
Quate<T, Container>::Quate(const Container<T>& other): Quate{}{
    for(const auto& i : other){
        m_data->Append(i);
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
void Quate<T, Container>::Add(const T& value){
    Enqueue(value);
}

template<typename T, template<typename> class Container>
void Quate<T, Container>::Dequeue(){
    if(m_data->GetLength() == 0){
        throw QueueIsEmptyException("Очередь пустая");
    }

    Container<T>* new_data = new Container<T>();
    for (size_t i = 1; i < m_data->GetLength(); i++){
        new_data->Append(m_data->Get(i));
    }

    delete m_data ;
    m_data = new_data;
}

template<typename T, template<typename> class Container>
bool Quate<T, Container>::IsEmpty() const{
    if(m_data->GetLength() == 0){
        return true;
    }
    else return false;
}

template<typename T, template<typename> class Container>
T Quate<T, Container>::Peek() const{
    if(m_data->GetLength() == 0){
        throw QueueIsEmptyException("Очередь пустая");
    }

    return m_data->Get(0);
}

template<typename T, template<typename> class Container>
int Quate<T, Container>::GetSize() const{
    return m_data->GetLength();
}

template<typename T, template<typename> class Container>
T Quate<T, Container>::GetData(const size_t index) const{
    return m_data->Get(index);
}

template<typename T, template<typename> class Container>
template<typename U>
Quate<U, Container> Quate<T, Container>::Map(U (*func)(const T&)) const{
    Quate<U, Container> new_quate;

    for (size_t i = 0; i < m_data->GetLength(); i++){
        T new_elem = func(m_data->Get(i));
        new_quate.Enqueue(new_elem);
    }
    return new_quate;
}

template<typename T, template<typename> class Container>
Quate<T, Container> Quate<T, Container>::Where(bool (*predicate)(const T&)) const{
    Quate<T, Container> new_quate;

    for(size_t i = 0; i < m_data->GetLength(); i++){
        bool new_value = predicate(m_data->Get(i));
        if(new_value){
            new_quate.Enqueue(m_data->Get(i));
        }
    }
    return new_quate;
}

template<typename T, template<typename> class Container>
T Quate<T, Container>::Reduce(T (*func)(const T&, const T&)) const{
    T result = m_data->Get(0);
    for(size_t i = 1; i < m_data->GetLength(); i++){
        result = func(m_data->Get(i), result);
    }
    return result;
}

template<typename T, template<typename> class Container>
Quate<T, Container> Quate<T,Container>::Concat(Quate<T, Container>& other) const{
    Quate<T, Container> result = *this;
    for(int i = 0; i < other.GetSize(); i++){
        result.Enqueue(other.GetData(i));
    }
    return result;
}

template<typename T, template<typename> class Container>
void Quate<T, Container>::Clutch(Quate<T, Container>& other){
    for(const auto& i : other){
        Enqueue(i);
    }
}

template<typename T, template<typename> class Container>
Quate<T, Container> Quate<T, Container>::Extraction(size_t begin, size_t end) const{
    if (begin < 0 || end < 0 || begin > end || begin >= GetSize() || end >= GetSize()){
        throw OutOfRangeException("индексы выходят за перделы очереди");
    }
    Quate<T, Container> result;

    for(int i = begin; i <= end; i++){
        result.Enqueue(GetData(i));
    }
    return result;
}

template<typename T, template<typename> class Container>
bool Quate<T, Container>::Check(Quate<T, Container>& other) const {
    if(other.GetSize() == 0) return true;
    if(other.GetSize() > GetSize()) return false;
    
    for(int i = 0; i < other.GetSize(); i++){
        bool found = false;
        for(int j = 0; j < GetSize(); j++){
            if(other.GetData(i) == GetData(j)){
                found = true;
                break;
            }
        }
        if(!found) return false;
    }
    return true;
}

template<typename T, template<typename> class Container>
SplitInfo<T, Container> Quate<T, Container>::Split(bool (*func)(const T&)) const {
    SplitInfo<T, Container> result;
    for(int i = 0; i < GetSize(); i++){
        if(func(GetData(i))){
            result.Que_1.Enqueue(GetData(i));
        } else {
            result.Que_2.Enqueue(GetData(i));
        }
    }
    return result;
}

template<typename T, template<typename> class Container>
T& Quate<T, Container>::operator[](size_t index) {
    if (index >= static_cast<size_t>(GetSize())) {
        throw OutOfRangeException("Индекс выходит за пределы очереди");
    }
    return m_data->GetRef(index);
}

template<typename T, template<typename> class Container>
auto Quate<T, Container>::begin(){
    return m_data->begin();
}

template<typename T, template<typename> class Container>
auto Quate<T, Container>::end(){
    return m_data->end();
}

template<typename T, template<typename> class Container>
auto Quate<T, Container>::cbegin() const{
    return m_data->cbegin();
}

template<typename T, template<typename> class Container>
auto Quate<T, Container>::cend() const{
    return m_data->cend();
}

template<typename T, template<typename> class Container>
auto Quate<T, Container>::begin() const {
    return m_data->cbegin();
}

template<typename T, template<typename> class Container>
auto Quate<T, Container>::end() const {
    return m_data->cend();
}