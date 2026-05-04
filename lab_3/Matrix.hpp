#pragma once
#include <stdexcept>
#include <initializer_list>

template <typename T, template<typename> class Container>
class SquareMatrix{
private:
    Container<Container<T>>* m_data;
    size_t m_size;
    
public:
    SquareMatrix();
    SquareMatrix(size_t size);
    SquareMatrix(std::initializer_list<std::initializer_list<T>> list);
    SquareMatrix(const SquareMatrix<T, Container>& other);
    ~SquareMatrix();

    SquareMatrix<T, Container>& operator=(const SquareMatrix<T, Container>& other);

    T Get(size_t row, size_t col) const;
    size_t GetSize() const;
    void Set(size_t row, size_t col, T value);
    
    SquareMatrix<T, Container> Sum(const SquareMatrix<T, Container>& other) const;
    SquareMatrix<T, Container> Multiply(T value) const;

    SquareMatrix<T, Container> MultiplyRow(size_t row_number, T value) const;
    SquareMatrix<T, Container> MultiplyCol(size_t col_number, T value) const;

    SquareMatrix<T, Container> SumRow(size_t row_n1, size_t row_n2, T value) const;
    SquareMatrix<T, Container> SumCol(size_t col_n1, size_t col_n2, T value) const;
    
    SquareMatrix<T, Container> SwapRow(size_t row_n1, size_t row_n2) const;
    SquareMatrix<T, Container> SwapCol(size_t col_n1, size_t col_n2) const;

    bool operator==(const SquareMatrix<T, Container>& other) const;
    bool operator!=(const SquareMatrix<T, Container>& other) const;
    T& operator()(size_t row, size_t col);

    T MatrixNorm() const;

    auto begin();
    auto end();
    auto cbegin() const;
    auto cend() const;
};

#include "Matrix.tpp"