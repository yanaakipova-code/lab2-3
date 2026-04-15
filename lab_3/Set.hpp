#pragma once
#include "../Error.hpp"

template<typename T, template<typename> class Container>
class Set{
private:
    Container<T>* m_data;
public:
    Set();
    Set(Container<T>& other);
    Set(Set<T, Container>& other);
    ~Set();

    unsigned int GetSize() const;
    T GetData(unsigned int index) const;

    void Add(const T& value);
    void Remove(int index);
    void Remove(const T& vaiue);
    bool Contains(const T& value) const;

    template<typename U>
    Set<U, Container> Map(U (*func)(const T&));
    Set<T, Container> Where(bool (*predicate)(const T&));

    Set<T, Container> Unification(const Set<T, Container>& other) const;
    Set<T, Container> Intersection(const Set<T, Container>& other) const;
    Set<T, Container> Subtraction(const Set<T, Container>& other) const;
};

#include "Set.tpp"