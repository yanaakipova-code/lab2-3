#pragma once

template<typename T, template<typename> class Container>
class Quate;

template<typename T, template<typename> class Container>
struct SplitInfo{
    Quate<T, Container> Que_1;
    Quate<T, Container> Que_2;
};

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
    bool IsEmpty() const;

    int GetSize() const;
    T GetData(const int index) const;

    T Peek() const;

    template<typename U>
    Quate<U, Container> Map(U (*func)(const T&)) const;
    Quate<T, Container> Where(bool (*predicate)(const T&)) const;

    T Reduce(T (*func)(const T&, const T&)) const;
    Quate<T, Container> Concat(Quate<T, Container>& other) const;
    void Clutch(Quate<T, Container>& other);

    Quate<T, Container> Extraction(int begin, int end) const;
    bool Check(Quate<T, Container>& other) const;
    SplitInfo<T, Container> Split(bool (*func)(const T&)) const;

    auto begin();
    auto end();
    auto begin() const;
    auto end() const;
    auto cbegin() const;
    auto cend() const;
};

#include "Quete.tpp"