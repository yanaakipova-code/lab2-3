#include "BitSequence.hpp"
#include <memory>
#include <cstddef> 
#include <stdexcept>

BitSequence::BitSequence(bool* bits, size_t count) {
    Bit* bitItems = new Bit[count];
    for (size_t i = 0; i < count; i++) {
        bitItems[i] = Bit(bits[i]);
    }
    m_bits = new ArraySequence<Bit>(bitItems, count);
    delete[] bitItems;
}

BitSequence::BitSequence(size_t size) {
    Bit* bitItems = new Bit[size];
    for (size_t i = 0; i < size; i++) {
        bitItems[i] = Bit(false);
    }
    m_bits = new ArraySequence<Bit>(bitItems, size);
    delete[] bitItems;
}

BitSequence::BitSequence(const BitSequence& other) {
    m_bits = new ArraySequence<Bit>(*other.m_bits);
}

BitSequence::~BitSequence() {
    delete m_bits;
}

Bit BitSequence::GetFirst() const { 
    return m_bits->GetFirst(); 
}
Bit BitSequence::GetLast() const { 
    return m_bits->GetLast();
}
Bit BitSequence::Get(size_t index) const {
     return m_bits->Get(index); 
}
size_t BitSequence::GetLength() const { 
    return m_bits->GetLength(); 
}

Sequence<Bit>* BitSequence::GetSubsequence(size_t start_index, size_t end_index) const {
    return m_bits->GetSubsequence(start_index, end_index);
}

void BitSequence::Append(Bit temp) {
     m_bits->Append(temp); 
}
void BitSequence::Prepend(Bit temp) {
     m_bits->Prepend(temp); 
}
void BitSequence::InsertAt(Bit temp, size_t index) {
     m_bits->InsertAt(temp, index); 
}

Sequence<Bit>* BitSequence::Concat(Sequence<Bit>* other) const {
    return m_bits->Concat(other);
}

std::unique_ptr<BitSequence> BitSequence::And(const BitSequence& other) const {
    if (GetLength() != other.GetLength()) {
        throw std::invalid_argument("BitSequence::And: длины не совпадают");
    }
    
    bool* resultBits = new bool[GetLength()];
    for (size_t i = 0; i < GetLength(); i++) {
        resultBits[i] = Get(i).GetValue() & other.Get(i).GetValue();
    }
    
    auto result = std::make_unique<BitSequence>(resultBits, GetLength());
    delete[] resultBits;
    return result;
}

std::unique_ptr<BitSequence> BitSequence::Or(const BitSequence& other) const {
    if (GetLength() != other.GetLength()) {
        throw std::invalid_argument("BitSequence::Or: длины не совпадают");
    }
    
    bool* resultBits = new bool[GetLength()];
    for (size_t i = 0; i < GetLength(); i++) {
        resultBits[i] = Get(i).GetValue() | other.Get(i).GetValue();
    }
    
    auto result = std::make_unique<BitSequence>(resultBits, GetLength());
    delete[] resultBits;
    return result;
}

std::unique_ptr<BitSequence> BitSequence::Xor(const BitSequence& other) const {
    if (GetLength() != other.GetLength()) {
        throw std::invalid_argument("BitSequence::Xor: длины не совпадают");
    }
    
    bool* resultBits = new bool[GetLength()];
    for (size_t i = 0; i < GetLength(); i++) {
        resultBits[i] = Get(i).GetValue() ^ other.Get(i).GetValue();
    }
    
    auto result = std::make_unique<BitSequence>(resultBits, GetLength());
    delete[] resultBits;
    return result;
}

std::unique_ptr<BitSequence> BitSequence::Not() const {
    bool* resultBits = new bool[GetLength()];
    for (size_t i = 0; i < GetLength(); i++) {
        resultBits[i] = !Get(i).GetValue();
    }
    
    auto result = std::make_unique<BitSequence>(resultBits, GetLength());
    delete[] resultBits;
    return result;
}

void BitSequence::SetBit(size_t index, bool value) {
    m_bits->Set(index, Bit(value));
}

bool BitSequence::GetBit(size_t index) const {
    return Get(index).GetValue();
}

std::unique_ptr<ArraySequence<Bit>> BitSequence::ToMutable() const {
    return std::make_unique<ArraySequence<Bit>>(*m_bits);
}