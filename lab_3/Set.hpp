#pragma once
#include "../Error.hpp"

template<typename T, template<typename> class Container>
class Set{
private:
    Container<T>* m_data;
public:
    Set();
    Set(const Container<T>& other);
    Set(const Set<T, Container>& other);
    ~Set();

    size_t GetSize() const;
    T GetData(size_t index) const;

    void Add(const T& value);
    void RemoveByIndex(size_t index);
    void Dequeue();
    void RemoveByValue(const T& vaiue);
    bool Contains(const T& value) const;

    template<typename U>
    Set<U, Container> Map(U (*func)(const T&));
    Set<T, Container> Where(bool (*predicate)(const T&));

    Set<T, Container> Unification(const Set<T, Container>& other) const;
    Set<T, Container> Intersection(const Set<T, Container>& other) const;
    Set<T, Container> Subtraction(const Set<T, Container>& other) const;

    bool CheckSubset(const Set<T, Container>& other) const;
    bool Comparison(const Set<T, Container>& other) const;
    bool IsEmpty() const;

    T& operator[](size_t index);

    auto begin();
    auto end();
    auto cbegin() const;
    auto cend() const;
    auto begin() const;
    auto end() const;

};

#include "Set.tpp"