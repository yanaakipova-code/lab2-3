#include "Matrix.hpp"
#include <stdexcept>
#include "../Error.h"

using namespace std;

template<typename T, template<typename> class Container>
SquareMatrix<T, Container>::SquareMatrix(): m_size(0){
    m_data = new Container<Container<T>>();
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container>::SquareMatrix(size_t size): SquareMatrix(){
    m_size = size;
    for (size_t i = 0; i < size; i++){
        Container<T> row;
        for (size_t j = 0; j < size; j++){
            row.Append(T());
        }
        m_data->Append(row);
    }
}

template<typename T, template<typename> class Container>
SquareMatrix<T,Container>::SquareMatrix(initializer_list<initializer_list<T>> matrix): SquareMatrix(){
    size_t size = matrix.size();

    m_data = new Container<Container<T>>();
    for (auto& row_matrix: matrix){
        if(row_matrix.size() != size){
            throw MatrixSquereException("Maтрица может быть только квадратной");
        }

        Container<T> row;
        for (auto value: row_matrix){
            row.Append(value);
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
T SquareMatrix<T, Container>::Get(size_t row, size_t col) const{
    if (row >= m_size || col >= m_size){
        throw OutOfRangeException("Индексы выходят за размеры масива");
    }
    return m_data->Get(row).Get(col);
}

template<typename T, template<typename> class Container>
size_t SquareMatrix<T, Container>::GetSize() const{
    return m_size;
}

template<typename T, template<typename> class Container>
void SquareMatrix<T, Container>::Set(size_t row, size_t col, T value) {
    if(row >= m_size || col >= m_size){
        throw OutOfRangeException("Нельзя добавить элемент за матрицу");
    }

    Container<T> row_container = m_data->Get(row);
    row_container.Set(col, value);
    m_data->Set(row, row_container)
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquereMatrix<T, Container>::Sum(const SquereMatrix<T, Container>& other) const{
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
            T multi = Get(i,j)*value;
            result.Set(i,j,multi);
        }
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquereMatrix<T, Container>::MultiplyRow(size_t row_number,T value) const{
    if(row_number >= m_size){
        throw OutOfRangeException("Индекс не может быть больше размера матрицы");
    }
    SquareMatrix<T, Container> result(*this);

    Container<T> row = m_data->Get(row_number);
    for (size_t i = 0; i < m_size; i++){
        T multi_row = row.Get(i)*value;
        result.Set(row_number, i, multi_row);
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::MultiplyCol(size_t col_number,T value) const{
    if (col_number >= m_size){
        throw OutOfRangeException("Индекс не может быть больше размера матрицы");
    }

    SquareMatrix<T, Container> result(*this);

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
    SquareMatrix<T, Container> result(*this);
    
    Container<T> row1 = m_data->Get(row_n1);
    Container<T> row2 = m_data->Get(row_n2);
    for(size_t i = 0; i < m_size; i++){
        T sum_row = row1.Get(i)+row2.Get(i) * value;
        result.Set(row_n1,i,sum_row);
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::SumCol(size_t col_n1, size_t col_n2, T value) const{
    if (col_n1 >= m_size || col_n2 >= m_size){
        throw OutOfRangeException("Таких столбцов нет");
    }

    SquareMatrix<T, Container> result(*this);
    for( size_t i = 0; i < m_size; i++){
        T sum_col = Get(i, col_n1) + Get(i,col_n2) * value;
        result.Set(i,col_n1,sum_col);
    }
    return result;
}

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::SwapRow(size_t row_n1, size_t row_n2) const{
    if(row_n1 >= m_size || row_n2 >= m_size){
        throw OutOfRangeException("Таких строк нет");
    }
    SquareMatrix<T, Container> result(*this);

    for (size_t i = 0; i < m_size; i++) {
            T temp = result.Get(row_n1, i);
            result.Set(row_n1, i, result.Get(row_n2, i));
            result.Set(row_n2, i, temp);
        }
    return result;
}   

template<typename T, template<typename> class Container>
SquareMatrix<T, Container> SquareMatrix<T, Container>::SwapCal(size_t col_n1, size_t col_n2) const{
    if(col_n1 >= m_size || col_n2 >= m_size){
        throw OutOfRangeException("Таких столбцов нет");
    }

    SquareMatrix<T, Container> result(*this);

    for (size_t i = 0; i < m_size; i++){
        T temp = result.Get(i, col_n1);
        result.Set(i, col_n1, result.Get(i,col_n2));
        result,Set(i, col_n2, temp);
    }
    return result;
}

template<typename T, template<typename> class Container>
T SquareMatrix<T, Container>:: MatrixNorm() const{
    T max_value = 0;
    for ( size_t i = 0; i < m_size; i++){
        for(size_t j = 0; j < m_size; i++){
            T value = abs(Get(i,j));
            if(value > max_value){
                max_value = value;
            }
        }
    }
    return max_value;
}