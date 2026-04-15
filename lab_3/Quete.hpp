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

    void Enqueue(const T value);
    void Dequeue();
    bool IsEmpty();

    int GetSize() const;
    T GetData(const size_t index) const;

    T Peek();

    template<typename U>
    Quate<U, Container> Map(U (*func)(const T&)) const;
    Quate<T, Container> Where(bool (*predicate)(const T&)) const;

    T Reduce(T (*func)(const T&, const T&)) const;
    Quate<T, Container> Concat(Quate<T, Container>& other) const;
    void Clutch(Quate<T, Container>& other);
};

#include "Quete.tpp"