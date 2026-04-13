#include "BitSequence.hpp"
#include "ArraySequence.hpp"
#include "Error.hpp"
#include <memory>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

template <std::integral T>
BitSequence<T>::BitSequence(bool* bits, size_t count) 
    : m_bit_count(count) {
    size_t cells = GetCellsCount();
    m_data = new DynamicArray<T>(cells);
    
    for (size_t i = 0; i < cells; i++) {
        m_data->Set(i, 0);
    }
    
    for (size_t i = 0; i < count; i++) {
        if (bits[i]) {
            SetBit(i, true);
        }
    }
}

template <std::integral T>
BitSequence<T>::BitSequence(size_t size) 
    : m_bit_count(size) {
    size_t cells = GetCellsCount();
    m_data = new DynamicArray<T>(cells);
    
    for (size_t i = 0; i < cells; i++) {
        m_data->Set(i, 0);
    }
}

template <std::integral T>
BitSequence<T>::BitSequence(const BitSequence<T>& other) 
    : m_bit_count(other.m_bit_count) {
    size_t cells = GetCellsCount();
    m_data = new DynamicArray<T>(cells);
    
    for (size_t i = 0; i < cells; i++) {
        m_data->Set(i, other.m_data->Get(i));
    }
}

template <std::integral T>
BitSequence<T>::~BitSequence() {
    delete m_data;
}

template <std::integral T>
Bit<T> BitSequence<T>::GetFirst() const {
    if (m_bit_count == 0) {
        throw EmptySequenceException("BitSequence пуст");
    }
    return Get(0);
}

template <std::integral T>
Bit<T> BitSequence<T>::GetLast() const {
    if (m_bit_count == 0) {
        throw EmptySequenceException("BitSequence пуст");
    }
    return Get(m_bit_count - 1);
}

template <std::integral T>
Bit<T> BitSequence<T>::Get(size_t index) const {
    return Bit<T>(GetBit(index));
}

template <std::integral T>
size_t BitSequence<T>::GetLength() const {
    return m_bit_count;
}

template <std::integral T>
Sequence<Bit<T>>* BitSequence<T>::GetSubsequence(size_t start_index, size_t end_index) const {
    if (start_index > end_index || end_index >= m_bit_count) {
        throw OutOfRangeException("BitSequence::GetSubsequence: неверные индексы");
    }
    
    size_t new_size = end_index - start_index + 1;
    BitSequence<T>* result = new BitSequence<T>(new_size);
    
    for (size_t i = 0; i < new_size; i++) {
        bool bit_value = GetBit(start_index + i);
        result->SetBit(i, bit_value);
    }
    
    return result;
}

template <std::integral T>
void BitSequence<T>::Append(Bit<T> temp) {
    size_t new_size = m_bit_count + 1;
    size_t old_cells = GetCellsCount();
    m_bit_count = new_size;
    size_t new_cells = GetCellsCount();
    
    if (new_cells > old_cells) {
        m_data->Resize(new_cells);
        m_data->Set(new_cells - 1, 0);
    }
    
    SetBit(m_bit_count - 1, temp.GetBit(0));
}

template <std::integral T>
void BitSequence<T>::Prepend(Bit<T> temp) {
    InsertAt(temp, 0);
}

template <std::integral T>
void BitSequence<T>::InsertAt(Bit<T> temp, size_t index) {
    if (index > m_bit_count) {
        throw OutOfRangeException("BitSequence::InsertAt: индекс вне диапазона");
    }
    
    size_t new_size = m_bit_count + 1;
    size_t old_cells = GetCellsCount();
    m_bit_count = new_size;
    size_t new_cells = GetCellsCount();
    
    if (new_cells > old_cells) {
        m_data->Resize(new_cells);
        m_data->Set(new_cells - 1, 0);
    }
    
    for (size_t i = m_bit_count - 1; i > index; i--) {
        bool bit = GetBit(i - 1);
        SetBit(i, bit);
    }
    
    SetBit(index, temp.GetBit(0));
}

template <std::integral T>
Sequence<Bit<T>>* BitSequence<T>::Concat(Sequence<Bit<T>>* other) const {
    if (other == nullptr) {
        throw NullPointerException("BitSequence::Concat: нулевой указатель");
    }
    
    size_t total_size = m_bit_count + other->GetLength();
    BitSequence<T>* result = new BitSequence<T>(total_size);
    
    for (size_t i = 0; i < m_bit_count; i++) {
        result->SetBit(i, GetBit(i));
    }
    
    for (size_t i = 0; i < other->GetLength(); i++) {
        Bit<T> bit = other->Get(i);
        result->SetBit(m_bit_count + i, bit.GetBit(0));
    }
    
    return result;
}

template <std::integral T>
Sequence<Bit<T>>* BitSequence<T>::Map(Bit<T> (*func)(Bit<T>)) {
    BitSequence<T>* result = new BitSequence<T>(m_bit_count);
    
    for (size_t i = 0; i < m_bit_count; i++) {
        Bit<T> transformed = func(Get(i));
        result->SetBit(i, transformed.GetBit(0));
    }
    
    return result;
}

template <std::integral T>
Sequence<Bit<T>>* BitSequence<T>::Where(bool (*predicate)(Bit<T>)) {
    size_t count = 0;
    for (size_t i = 0; i < m_bit_count; i++) {
        if (predicate(Get(i))) {
            count++;
        }
    }
    
    BitSequence<T>* result = new BitSequence<T>(count);
    size_t result_index = 0;
    
    for (size_t i = 0; i < m_bit_count; i++) {
        if (predicate(Get(i))) {
            result->SetBit(result_index++, GetBit(i));
        }
    }
    
    return result;
}

template <std::integral T>
Bit<T> BitSequence<T>::Reduce(Bit<T> (*func)(Bit<T>, Bit<T>), Bit<T> initial) {
    Bit<T> result = initial;
    
    for (size_t i = 0; i < m_bit_count; i++) {
        result = func(result, Get(i));
    }
    
    return result;
}

template <std::integral T>
Option<Bit<T>> BitSequence<T>::TryGetFirst(bool (*predicate)(Bit<T>)) const {
    for (size_t i = 0; i < m_bit_count; i++) {
        Bit<T> elem = Get(i);
        if (predicate == nullptr || predicate(elem)) {
            return Option<Bit<T>>::Some(elem);
        }
    }
    return Option<Bit<T>>::None();
}

template <std::integral T>
Option<Bit<T>> BitSequence<T>::TryGetLast(bool (*predicate)(Bit<T>)) const {
    for (size_t i = m_bit_count; i > 0; i--) {
        Bit<T> elem = Get(i - 1);
        if (predicate == nullptr || predicate(elem)) {
            return Option<Bit<T>>::Some(elem);
        }
    }
    return Option<Bit<T>>::None();
}

template <std::integral T>
void BitSequence<T>::SetBit(size_t index, bool value) {
    if (index >= m_bit_count) {
        throw OutOfRangeException("BitSequence::SetBit: индекс вне диапазона");
    }
    
    size_t cell = GetCellIndex(index);
    size_t offset = GetBitOffset(index);
    T word = m_data->Get(cell);
    
    if (value) {
        word |= (static_cast<T>(1) << offset);
    } else {
        word &= ~(static_cast<T>(1) << offset);
    }
    
    m_data->Set(cell, word);
}

template <std::integral T>
bool BitSequence<T>::GetBit(size_t index) const {
    if (index >= m_bit_count) {
        throw OutOfRangeException("BitSequence::GetBit: индекс вне диапазона");
    }
    
    size_t cell = GetCellIndex(index);
    size_t offset = GetBitOffset(index);
    T word = m_data->Get(cell);
    
    return (word >> offset) & 1;
}

template <std::integral T>
std::unique_ptr<BitSequence<T>> BitSequence<T>::And(const BitSequence<T>& other) const {
    if (m_bit_count != other.m_bit_count) {
        throw LengthMismatchException("BitSequence::And: длины не совпадают");
    }
    
    auto result = std::make_unique<BitSequence<T>>(m_bit_count);
    size_t cells = GetCellsCount();
    
    for (size_t i = 0; i < cells; i++) {
        T val = m_data->Get(i) & other.m_data->Get(i);
        result->m_data->Set(i, val);
    }
    
    result->ClearUnusedBits();
    return result;
}

template <std::integral T>
std::unique_ptr<BitSequence<T>> BitSequence<T>::Or(const BitSequence<T>& other) const {
    if (m_bit_count != other.m_bit_count) {
        throw LengthMismatchException("BitSequence::Or: длины не совпадают");
    }
    
    auto result = std::make_unique<BitSequence<T>>(m_bit_count);
    size_t cells = GetCellsCount();
    
    for (size_t i = 0; i < cells; i++) {
        T val = m_data->Get(i) | other.m_data->Get(i);
        result->m_data->Set(i, val);
    }
    
    result->ClearUnusedBits();
    return result;
}

template <std::integral T>
std::unique_ptr<BitSequence<T>> BitSequence<T>::Xor(const BitSequence<T>& other) const {
    if (m_bit_count != other.m_bit_count) {
        throw LengthMismatchException("BitSequence::Xor: длины не совпадают");
    }
    
    auto result = std::make_unique<BitSequence<T>>(m_bit_count);
    size_t cells = GetCellsCount();
    
    for (size_t i = 0; i < cells; i++) {
        T val = m_data->Get(i) ^ other.m_data->Get(i);
        result->m_data->Set(i, val);
    }
    
    result->ClearUnusedBits();
    return result;
}

template <std::integral T>
std::unique_ptr<BitSequence<T>> BitSequence<T>::Not() const {
    auto result = std::make_unique<BitSequence<T>>(m_bit_count);
    size_t cells = GetCellsCount();
    
    for (size_t i = 0; i < cells; i++) {
        T val = ~(m_data->Get(i));
        result->m_data->Set(i, val);
    }
    
    result->ClearUnusedBits();
    return result;
}


template <std::integral T>
BitSequence<T> BitSequence<T>::operator&(const BitSequence<T>& other) const {
    auto result = And(other);
    return *result;
}

template <std::integral T>
BitSequence<T> BitSequence<T>::operator|(const BitSequence<T>& other) const {
    auto result = Or(other);
    return *result;
}

template <std::integral T>
BitSequence<T> BitSequence<T>::operator^(const BitSequence<T>& other) const {
    auto result = Xor(other);
    return *result;
}

template <std::integral T>
BitSequence<T> BitSequence<T>::operator~() const {
    auto result = Not();
    return *result;
}

template <std::integral T>
std::unique_ptr<Iterator<Bit<T>>> BitSequence<T>::begin() {
    throw std::runtime_error("BitSequence iterators not implemented");
    return nullptr;
}

template <std::integral T>
std::unique_ptr<Iterator<Bit<T>>> BitSequence<T>::end() {
    throw std::runtime_error("BitSequence iterators not implemented");
    return nullptr;
}

template <std::integral T>
std::unique_ptr<ConstIterator<Bit<T>>> BitSequence<T>::begin() const {
    throw std::runtime_error("BitSequence iterators not implemented");
    return nullptr;
}

template <std::integral T>
std::unique_ptr<ConstIterator<Bit<T>>> BitSequence<T>::end() const {
    throw std::runtime_error("BitSequence iterators not implemented");
    return nullptr;
}

template <std::integral T>
std::unique_ptr<ConstIterator<Bit<T>>> BitSequence<T>::cbegin() const {
    throw std::runtime_error("BitSequence iterators not implemented");
    return nullptr;
}

template <std::integral T>
std::unique_ptr<ConstIterator<Bit<T>>> BitSequence<T>::cend() const {
    throw std::runtime_error("BitSequence iterators not implemented");
    return nullptr;
}
