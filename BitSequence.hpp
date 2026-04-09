#pragma once
#include <memory>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include "ArraySequence.hpp" 
#include "Sequence.hpp"
#include "DynamicArray.hpp"
#include "Bit.hpp"
#include "Option.hpp"
#include "Iterator.hpp"

template <std::integral T>
class BitSequence : public Sequence<Bit> {
private:
    DynamicArray<T>* m_data;
    size_t m_bit_count;
    
    static constexpr size_t BITS_PER_CELL = sizeof(T) * 8;
    
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
        size_t lastBits = m_bit_count % BITS_PER_CELL;
        
        if (lastBits != 0) {
            T mask = (static_cast<T>(1) << lastBits) - 1;
            T last_val = m_data->Get(cells - 1);
            m_data->Set(cells - 1, last_val & mask);
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

    std::unique_ptr<BitSequence<T>> And(const BitSequence<T>& other) const;
    std::unique_ptr<BitSequence<T>> Or(const BitSequence<T>& other) const;
    std::unique_ptr<BitSequence<T>> Xor(const BitSequence<T>& other) const;
    std::unique_ptr<BitSequence<T>> Not() const;
    
    std::unique_ptr<ArraySequence<Bit>> ToMutable() const;
    
    BitSequence<T> operator&(const BitSequence<T>& other) const;
    BitSequence<T> operator|(const BitSequence<T>& other) const;
    BitSequence<T> operator^(const BitSequence<T>& other) const;
    BitSequence<T> operator~() const;
    
    Bit& operator[](size_t index);
    const Bit& operator[](size_t index) const;
    std::unique_ptr<Iterator<Bit>> begin() override;
    std::unique_ptr<Iterator<Bit>> end() override;
    std::unique_ptr<ConstIterator<Bit>> begin() const override;
    std::unique_ptr<ConstIterator<Bit>> end() const override;
    std::unique_ptr<ConstIterator<Bit>> cbegin() const override;
    std::unique_ptr<ConstIterator<Bit>> cend() const override;
};

#include "BitSequence.tpp"