#pragma once

template<typename T, template<typename> class Container>
class Quate{
private:
    Container<T>* m_data;
public:
    Quate();
    Quate(const Quate<T, Container>& other);
    Quate(const Container<T>& other);
    ~Quate();
};

#include "Quete.tpp"