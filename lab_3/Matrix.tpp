#include "Matrix.hpp"
#include <stdexcept>
#include <cstdlib> 
#include <cmath>
#include "../Error.hpp"

using namespace std;

template<typename T, template<typename> class Container>
SquareMatrix<T, Container>::SquareMatrix() : m_size{0} {
    m_data = new Container<Container<T>>();
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container>::SquareMatrix(size_t size) : m_size{size} {
    m_data = new Container<Container<T>>();
    
    Container<T> empty_row;
    for (size_t j = 0; j < size; j++){
        empty_row.Append(T{});
    }
 
    for (size_t i = 0; i < size; i++){
        m_data->Append(empty_row);
    }
}


template<typename T, template<typename> class Container>
SquareMatrix<T,Container>::SquareMatrix(initializer_list<initializer_list<T>> matrix) {
    size_t size = matrix.size();
    m_size = size;
    m_data = new Container<Container<T>>();
    
    for (auto& row_matrix : matrix){
        if(row_matrix.size() != size){
            throw MatrixSquereException("Матрица может быть только квадратной");
        }
        Container<T> row;
        for (auto value : row_matrix){
            row.Append(value);
        }
        m_data->Append(row);
    }
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container>::SquareMatrix(const SquareMatrix<T, Container>& other) 
    : m_size(other.m_size) {
    m_data = new Container<Container<T>>();
    for (size_t i = 0; i < m_size; i++) {
        Container<T> row;
        for (size_t j = 0; j < m_size; j++) {
            row.Append(other.Get(i, j));
        }
        m_data->Append(row);
    }
}


template<typename T, template<typename> class Container>
SquareMatrix<T, Container>::~SquareMatrix(){
    delete m_data;  
    m_data = nullptr;
    m_size = 0;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container>& SquareMatrix<T, Container>::operator=(const SquareMatrix<T, Container>& other) {
    if (this != &other) {
        delete m_data;
        m_size = other.m_size;
        m_data = new Container<Container<T>>();
        for (size_t i = 0; i < m_size; i++) {
            Container<T> row;
            for (size_t j = 0; j < m_size; j++) {
                row.Append(other.Get(i, j));
            }
            m_data->Append(row);
        }
    }
    return *this;
}

template<typename T, template<typename> class Container>
void SquareMatrix<T, Container>::Set(size_t row, size_t col, T value) {
    if(row >= m_size || col >= m_size){
        throw OutOfRangeException("Нельзя добавить элемент за матрицу");
    }
    Container<T>& row_container = m_data->GetRef(row);
    row_container.Set(col, value);
}

template<typename T, template<typename> class Container>
T SquareMatrix<T, Container>::Get(size_t row, size_t col) const{
    if (row >= m_size || col >= m_size){
        throw OutOfRangeException("Индексы выходят за размеры масива");
    }
    Container<T> row_container = m_data->Get(row);
    return row_container.Get(col);
}

template<typename T, template<typename> class Container>
size_t SquareMatrix<T, Container>::GetSize() const{
    return m_size;
}


template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::Sum(const SquareMatrix<T, Container>& other) const{
    if(m_size != other.m_size){
        throw MatrixSquereSizeException("Размеры должны совпадать");
    }

    SquareMatrix<T, Container> result(m_size);
    
    for(size_t i = 0; i < m_size; i++){
        for(size_t j = 0; j < m_size; j++){
            T sum = Get(i,j) + other.Get(i,j);
            result.Set(i,j,sum);
        }
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::Multiply(T value) const {
    SquareMatrix<T, Container> result(m_size);
    for (size_t i = 0; i < m_size; i++){
        for (size_t j = 0; j < m_size; j++){
            T multi = Get(i,j) * value;
            result.Set(i,j,multi);
        }
    }
    return result;
}
template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::MultiplyRow(size_t row_number, T value) const{
    if(row_number >= m_size){
        throw OutOfRangeException("Индекс не может быть больше размера матрицы");
    }
    SquareMatrix<T, Container> result = *this;
    
    for (size_t i = 0; i < m_size; i++){
        T multi_row = Get(row_number, i) * value;
        result.Set(row_number, i, multi_row);
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::MultiplyCol(size_t col_number, T value) const{
    if (col_number >= m_size){
        throw OutOfRangeException("Индекс не может быть больше размера матрицы");
    }

    SquareMatrix<T, Container> result = *this;

    for (size_t i = 0; i < m_size; i++) {
        T col_value = Get(i, col_number) * value;
        result.Set(i, col_number, col_value);
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::SumRow(size_t row_n1, size_t row_n2, T value) const{
    if(row_n1 >= m_size || row_n2 >= m_size){
        throw OutOfRangeException("Таких строк нет");
    }
    SquareMatrix<T, Container> result = *this;
    
    for(size_t i = 0; i < m_size; i++){
        T sum_row = Get(row_n1, i) + Get(row_n2, i) * value;
        result.Set(row_n1, i, sum_row);
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::SumCol(size_t col_n1, size_t col_n2, T value) const{
    if (col_n1 >= m_size || col_n2 >= m_size){
        throw OutOfRangeException("Таких столбцов нет");
    }

    SquareMatrix<T, Container> result = *this;
    for( size_t i = 0; i < m_size; i++){
        T sum_col = Get(i, col_n1) + Get(i, col_n2) * value;
        result.Set(i, col_n1, sum_col);
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::SwapRow(size_t row_n1, size_t row_n2) const{
    if(row_n1 >= m_size || row_n2 >= m_size){
        throw OutOfRangeException("Таких строк нет");
    }
    SquareMatrix<T, Container> result = *this;

    for (size_t i = 0; i < m_size; i++) {
        T temp = result.Get(row_n1, i);
        result.Set(row_n1, i, result.Get(row_n2, i));
        result.Set(row_n2, i, temp);
    }
    return result;
}   

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::SwapCol(size_t col_n1, size_t col_n2) const{
    if(col_n1 >= m_size || col_n2 >= m_size){
        throw OutOfRangeException("Таких столбцов нет");
    }

    SquareMatrix<T, Container> result = *this;

    for (size_t i = 0; i < m_size; i++){
        T temp = result.Get(i, col_n1);
        result.Set(i, col_n1, result.Get(i, col_n2));
        result.Set(i, col_n2, temp);
    }
    return result;
}

template<typename U>
class Complex;

template<typename T, template<typename> class Container>
T SquareMatrix<T, Container>::MatrixNorm() const{
    if constexpr (std::is_same_v<T, Complex<double>>) {
        double max_value = 0;
        for (size_t i = 0; i < m_size; i++){
            for(size_t j = 0; j < m_size; j++){
                double value = Get(i, j).Abs();
                if(value > max_value){
                    max_value = value;
                }
            }
        }
        return Complex<double>(max_value, 0);
    } else {
        T max_value = 0;
        for (size_t i = 0; i < m_size; i++){
            for(size_t j = 0; j < m_size; j++){
                T value = std::abs(Get(i, j));
                if(value > max_value){
                    max_value = value;
                }
            }
        }
        return max_value;
    }
}

template<typename T, template<typename> class Container>
bool SquareMatrix<T, Container>::operator==(const SquareMatrix<T, Container>& other) const{
    if (other.GetSize() != GetSize()){
        return false;
    }

    for(size_t i = 0; i < GetSize(); i++){
        for(size_t j = 0; j < GetSize(); j++){
            if (Get(i,j) != other.Get(i,j)){
                return false;
            }
        }
    }
    return true;
}

template<typename T, template<typename> class Container>
T& SquareMatrix<T, Container>::operator()(size_t row, size_t col) {
    if (row >= m_size || col >= m_size) {
        throw OutOfRangeException("Индексы выходят за пределы матрицы");
    }
    Container<T>& row_container = m_data->GetRef(row);
    return row_container.GetRef(col);
}

template<typename T, template<typename> class Container>
bool SquareMatrix<T, Container>::operator!=(const SquareMatrix<T, Container>& other) const{
    return !(*this == other);
}

template<typename T, template<typename> class Container>
auto SquareMatrix<T, Container>::begin(){
    return m_data->begin();
}

template<typename T, template<typename> class Container>
auto SquareMatrix<T, Container>::end(){
    return m_data->end();
}

template<typename T, template<typename> class Container>
auto SquareMatrix<T, Container>::cbegin() const{
    return m_data->cbegin();
}

template<typename T, template<typename> class Container>
auto SquareMatrix<T, Container>::cend() const{
    return m_data->cend();
}