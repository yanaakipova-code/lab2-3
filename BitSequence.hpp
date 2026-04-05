#pragma once
#include <memory>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include "Sequence.hpp"
#include "DynamicArray.hpp"
#include "Bit.hpp"
#include "Option.hpp"
#include "Iterator.hpp"
#define BITS_PER_CELL 32

class BitSequence : public Sequence<Bit> {
private:
    DynamicArray<uint32_t>* m_data;
    size_t m_bit_count;
    
    size_t GetCellIndex(size_t bit_index) const {
        return bit_index / BITS_PER_CELL;
    }
    
    size_t GetBitOffset(size_t bit_index) const {
        return bit_index % BITS_PER_CELL;
    }
    
    size_t GetCellsCount() const {
        return (m_bit_count + BITS_PER_CELL - 1) / BITS_PER_CELL;
    }
    
    void ClearUnusedBits() {
        if (m_bit_count == 0) return;
        
        size_t cells = GetCellsCount();
        size_t lastBits = GetBitOffset(m_bit_count);
        
        if (lastBits != 0) {
            uint32_t mask = (1u << lastBits) - 1;
            uint32_t lastVal = m_data->Get(cells - 1);
            m_data->Set(cells - 1, lastVal & mask);
        }
    }

public:    
    BitSequence(bool* bits, size_t count);
    BitSequence(size_t size);
    BitSequence(const BitSequence& other);
    ~BitSequence() override;

    Bit GetFirst() const override;
    Bit GetLast() const override;
    Bit Get(size_t index) const override;
    size_t GetLength() const override;
    Sequence<Bit>* GetSubsequence(size_t start_index, size_t end_index) const override;

    void Append(Bit temp) override;
    void Prepend(Bit temp) override;
    void InsertAt(Bit temp, size_t index) override;
    Sequence<Bit>* Concat(Sequence<Bit>* other) const override;

    Sequence<Bit>* Map(Bit (*func)(Bit)) override;
    Sequence<Bit>* Where(bool (*predicate)(Bit)) override;
    Bit Reduce(Bit (*func)(Bit, Bit), Bit initial) override;

    Option<Bit> TryGetFirst(bool (*predicate)(Bit) = nullptr) const override;
    Option<Bit> TryGetLast(bool (*predicate)(Bit) = nullptr) const override;

    void SetBit(size_t index, bool value);
    bool GetBit(size_t index) const;

    std::unique_ptr<BitSequence> And(const BitSequence& other) const;
    std::unique_ptr<BitSequence> Or(const BitSequence& other) const;
    std::unique_ptr<BitSequence> Xor(const BitSequence& other) const;
    std::unique_ptr<BitSequence> Not() const;
    
    std::unique_ptr<ArraySequence<Bit>> ToMutable() const;
    
    BitSequence operator&(const BitSequence& other) const;
    BitSequence operator|(const BitSequence& other) const;
    BitSequence operator^(const BitSequence& other) const;
    BitSequence operator~() const;
    
    Bit& operator[](size_t index);
    const Bit& operator[](size_t index) const;

    Iterator<Bit> begin() override;
    Iterator<Bit> end() override;
    ConstIterator<Bit> begin() const override;
    ConstIterator<Bit> end() const override;
    ConstIterator<Bit> cbegin() const override;
    ConstIterator<Bit> cend() const override;
};
