#include "BitSequence.hpp"
#include "ArraySequence.hpp" 
#include <memory>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

BitSequence::BitSequence(bool* bits, size_t count) 
    : m_bit_count(count)
{
    size_t cells = GetCellsCount();
    m_data = new DynamicArray<uint32_t>(cells);
    // каждая ячейка 0
    for (size_t i = 0; i < cells; i++) {
        m_data->Set(i, 0);
    }
    //каждую ячейку заполняем значением
    for (size_t i = 0; i < count; i++) {
        if (bits[i]) {
            SetBit(i, true);
        }
    }
}

BitSequence::BitSequence(size_t size) 
    : m_bit_count(size)
{
    size_t cells = GetCellsCount();
    m_data = new DynamicArray<uint32_t>(cells);
    
    for (size_t i = 0; i < cells; i++) {
        m_data->Set(i, 0);
    }
}

BitSequence::BitSequence(const BitSequence& other) 
    : m_bit_count(other.m_bit_count)
{
    size_t cells = GetCellsCount();
    m_data = new DynamicArray<uint32_t>(cells);
    
    for (size_t i = 0; i < cells; i++) {
        m_data->Set(i, other.m_data->Get(i));
    }
}

BitSequence::~BitSequence() {
    delete m_data;
}


Bit BitSequence::GetFirst() const {
    if (m_bit_count == 0) {
        throw std::out_of_range("BitSequence пуст");
    }
    return Get(0);
}

Bit BitSequence::GetLast() const {
    if (m_bit_count == 0) {
        throw std::out_of_range("BitSequence пуст");
    }
    return Get(m_bit_count - 1);
}

Bit BitSequence::Get(size_t index) const {
    return Bit(GetBit(index));
}

size_t BitSequence::GetLength() const {
    return m_bit_count;
}

Sequence<Bit>* BitSequence::GetSubsequence(size_t start_index, size_t end_index) const {
    if (start_index > end_index || end_index >= m_bit_count) {
        throw std::out_of_range("BitSequence::GetSubsequence: неверные индексы");
    }
    
    size_t new_size = end_index - start_index + 1;
    bool* temp_bits = new bool[new_size];
    
    for (size_t i = 0; i < new_size; i++) {
        temp_bits[i] = GetBit(start_index + i);
    }
    
    BitSequence* result = new BitSequence(temp_bits, new_size);
    delete[] temp_bits;
    
    return result;
}

void BitSequence::Append(Bit temp) {
    size_t new_size = m_bit_count + 1;
    size_t old_cells = GetCellsCount();
    m_bit_count = new_size;
    size_t new_cells = GetCellsCount();
    
    if (new_cells > old_cells) {
        m_data->Resize(new_cells);
        m_data->Set(new_cells - 1, 0);
    }
    
    SetBit(m_bit_count - 1, temp.GetValue());
}

void BitSequence::Prepend(Bit temp) {
    InsertAt(temp, 0);
}

void BitSequence::InsertAt(Bit temp, size_t index) {
    if (index > m_bit_count) {
        throw std::out_of_range("BitSequence::InsertAt: индекс вне диапазона");
    }
    
    size_t new_size = m_bit_count + 1;
    size_t old_cells = GetCellsCount();
    m_bit_count = new_size;
    size_t new_cells = GetCellsCount();
    
    if (new_cells > old_cells) {
        m_data->Resize(new_cells);//расширяем массив
        m_data->Set(new_cells - 1, 0);
    }
    
    for (size_t i = m_bit_count - 1; i > index; i--) {
        bool bit = GetBit(i - 1);
        SetBit(i, bit);
    }
    
    SetBit(index, temp.GetValue());
}

Sequence<Bit>* BitSequence::Concat(Sequence<Bit>* other) const {
    if (other == nullptr) {
        throw std::invalid_argument("BitSequence::Concat: нулевой указатель");
    }
    
    size_t total_size = m_bit_count + other->GetLength();
    bool* temp_bits = new bool[total_size];
    
    for (size_t i = 0; i < m_bit_count; i++) {
        temp_bits[i] = GetBit(i);
    }
    
    for (size_t i = 0; i < other->GetLength(); i++) {
        temp_bits[m_bit_count + i] = other->Get(i).GetValue();
    }
    
    BitSequence* result = new BitSequence(temp_bits, total_size);
    delete[] temp_bits;
    
    return result;
}

Sequence<Bit>* BitSequence::Map(Bit (*func)(Bit)) {
    BitSequence* result = new BitSequence(m_bit_count);
    
    for (size_t i = 0; i < m_bit_count; i++) {
        Bit transformed = func(Get(i));
        result->SetBit(i, transformed.GetValue());
    }
    
    return result;
}

Sequence<Bit>* BitSequence::Where(bool (*predicate)(Bit)) {
    size_t count = 0;
    for (size_t i = 0; i < m_bit_count; i++) {
        if (predicate(Get(i))) {
            count++;
        }
    }
    
    bool* temp_bits = new bool[count];
    size_t index = 0;
    
    for (size_t i = 0; i < m_bit_count; i++) {
        if (predicate(Get(i))) {
            temp_bits[index++] = GetBit(i);
        }
    }
    
    BitSequence* result = new BitSequence(temp_bits, count);
    delete[] temp_bits;
    
    return result;
}

Bit BitSequence::Reduce(Bit (*func)(Bit, Bit), Bit initial) {
    Bit result = initial;
    
    for (size_t i = 0; i < m_bit_count; i++) {
        result = func(result, Get(i));
    }
    
    return result;
}

Option<Bit> BitSequence::TryGetFirst(bool (*predicate)(Bit)) const {
    for (size_t i = 0; i < m_bit_count; i++) {
        Bit elem = Get(i);
        if (predicate == nullptr || predicate(elem)) {
            return Option<Bit>::Some(elem);
        }
    }
    return Option<Bit>::None();
}

Option<Bit> BitSequence::TryGetLast(bool (*predicate)(Bit)) const {
    for (size_t i = m_bit_count; i > 0; i--) {
        Bit elem = Get(i - 1);
        if (predicate == nullptr || predicate(elem)) {
            return Option<Bit>::Some(elem);
        }
    }
    return Option<Bit>::None();
}

void BitSequence::SetBit(size_t index, bool value) {
    if (index >= m_bit_count) {
        throw std::out_of_range("BitSequence::SetBit: индекс вне диапазона");
    }
    
    size_t cell = GetCellIndex(index);
    size_t offset = GetBitOffset(index);
    uint32_t word = m_data->Get(cell);
    
    if (value) {
        word |= (1u << offset);
    } else {
        word &= ~(1u << offset);
    }
    
    m_data->Set(cell, word);
}

bool BitSequence::GetBit(size_t index) const {
    if (index >= m_bit_count) {
        throw std::out_of_range("BitSequence::GetBit: индекс вне диапазона");
    }
    
    size_t cell = GetCellIndex(index);
    size_t offset = GetBitOffset(index);
    uint32_t word = m_data->Get(cell);
    
    return (word >> offset) & 1;
}

std::unique_ptr<BitSequence> BitSequence::And(const BitSequence& other) const {
    if (m_bit_count != other.m_bit_count) {
        throw std::invalid_argument("BitSequence::And: длины не совпадают");
    }
    
    auto result = std::make_unique<BitSequence>(m_bit_count);
    size_t cells = GetCellsCount();
    
    for (size_t i = 0; i < cells; i++) {
        uint32_t val = m_data->Get(i) & other.m_data->Get(i);
        result->m_data->Set(i, val);
    }
    
    result->ClearUnusedBits();
    return result;
}

std::unique_ptr<BitSequence> BitSequence::Or(const BitSequence& other) const {
    if (m_bit_count != other.m_bit_count) {
        throw std::invalid_argument("BitSequence::Or: длины не совпадают");
    }
    
    auto result = std::make_unique<BitSequence>(m_bit_count);
    size_t cells = GetCellsCount();
    
    for (size_t i = 0; i < cells; i++) {
        uint32_t val = m_data->Get(i) | other.m_data->Get(i);
        result->m_data->Set(i, val);
    }
    
    result->ClearUnusedBits();
    return result;
}

std::unique_ptr<BitSequence> BitSequence::Xor(const BitSequence& other) const {
    if (m_bit_count != other.m_bit_count) {
        throw std::invalid_argument("BitSequence::Xor: длины не совпадают");
    }
    
    auto result = std::make_unique<BitSequence>(m_bit_count);
    size_t cells = GetCellsCount();
    
    for (size_t i = 0; i < cells; i++) {
        uint32_t val = m_data->Get(i) ^ other.m_data->Get(i);
        result->m_data->Set(i, val);
    }
    
    result->ClearUnusedBits();
    return result;
}

std::unique_ptr<BitSequence> BitSequence::Not() const {
    auto result = std::make_unique<BitSequence>(m_bit_count);
    size_t cells = GetCellsCount();
    
    for (size_t i = 0; i < cells; i++) {
        uint32_t val = ~(m_data->Get(i));
        result->m_data->Set(i, val);
    }
    
    result->ClearUnusedBits();
    return result;
}

std::unique_ptr<ArraySequence<Bit>> BitSequence::ToMutable() const {
    auto result = std::make_unique<ArraySequence<Bit>>();
    
    for (size_t i = 0; i < m_bit_count; i++) {
        result->Append(Bit(GetBit(i)));
    }
    
    return result;
}

BitSequence BitSequence::operator&(const BitSequence& other) const {
    auto result = And(other);
    return *result;
}

BitSequence BitSequence::operator|(const BitSequence& other) const {
    auto result = Or(other);
    return *result;
}

BitSequence BitSequence::operator^(const BitSequence& other) const {
    auto result = Xor(other);
    return *result;
}

BitSequence BitSequence::operator~() const {
    auto result = Not();
    return *result;
}

Bit& BitSequence::operator[](size_t index) {
    throw std::runtime_error("BitSequence::operator[]: используйте SetBit/GetBit");
}

const Bit& BitSequence::operator[](size_t index) const {
    throw std::runtime_error("BitSequence::operator[]: используйте GetBit");
}

Iterator<Bit> BitSequence::begin() {
    throw std::runtime_error("BitSequence::begin(): итераторы требуют временного массива");
}

Iterator<Bit> BitSequence::end() {
    throw std::runtime_error("BitSequence::end(): итераторы требуют временного массива");
}

ConstIterator<Bit> BitSequence::begin() const {
    throw std::runtime_error("BitSequence::begin() const: итераторы требуют временного массива");
}

ConstIterator<Bit> BitSequence::end() const {
    throw std::runtime_error("BitSequence::end() const: итераторы требуют временного массива");
}
ConstIterator<Bit> BitSequence::cbegin() const {
    throw std::runtime_error("BitSequence::cbegin(): итераторы требуют временного массива");
}

ConstIterator<Bit> BitSequence::cend() const {
    throw std::runtime_error("BitSequence::cend(): итераторы требуют временного массива");
}
