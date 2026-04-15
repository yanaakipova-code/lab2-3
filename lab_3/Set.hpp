#pragma once

template<typename T, template<typename> class Container>
class Set{
private:
    Container<T>* m_data;
public:
    Set();
    Set(Container<T>& other);
    Set(Set<T, Container>& other);
    ~Set();

    unsigned int GetSize();
    T GetData(unsigned int index);
};

#include "Set.tpp"