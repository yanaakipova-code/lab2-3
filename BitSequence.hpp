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
class BitSequence : public Sequence<Bit<T>> {
private:
    DynamicArray<T>* m_data; //указатель на конкретную ячейку
    size_t m_bit_count;// сколько всего битов 
    
    static constexpr size_t BITS_PER_CELL = sizeof(T) * 8;
    
    //номер ячейки
    size_t GetCellIndex(size_t bit_index) const {
        return bit_index / BITS_PER_CELL;
    }
    
    //позиция внутри ячейки 
    size_t GetBitOffset(size_t bit_index) const {
        return bit_index % BITS_PER_CELL;
    }
    
    //сколько ячеек надо
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

    Bit<T> GetFirst() const override;
    Bit<T> GetLast() const override;
    Bit<T> Get(size_t index) const override;
    size_t GetLength() const override;
    Sequence<Bit<T>>* GetSubsequence(size_t start_index, size_t end_index) const override;

    void Append(Bit<T> temp) override;
    void Prepend(Bit<T> temp) override;
    void InsertAt(Bit<T> temp, size_t index) override;
    Sequence<Bit<T>>* Concat(Sequence<Bit<T>>* other) const override;

    Sequence<Bit<T>>* Map(Bit<T> (*func)(Bit<T>)) override;
    Sequence<Bit<T>>* Where(bool (*predicate)(Bit<T>)) override;
    Bit<T> Reduce(Bit<T> (*func)(Bit<T>, Bit<T>), Bit<T> initial) override;

    Option<Bit<T>> TryGetFirst(bool (*predicate)(Bit<T>) = nullptr) const override;
    Option<Bit<T>> TryGetLast(bool (*predicate)(Bit<T>) = nullptr) const override;

    void SetBit(size_t index, bool value);
    bool GetBit(size_t index) const;

    std::unique_ptr<BitSequence<T>> And(const BitSequence<T>& other) const;
    std::unique_ptr<BitSequence<T>> Or(const BitSequence<T>& other) const;
    std::unique_ptr<BitSequence<T>> Xor(const BitSequence<T>& other) const;
    std::unique_ptr<BitSequence<T>> Not() const;
    
    std::unique_ptr<ArraySequence<Bit<T>>> ToMutable() const;
    
    BitSequence<T> operator&(const BitSequence<T>& other) const;
    BitSequence<T> operator|(const BitSequence<T>& other) const;
    BitSequence<T> operator^(const BitSequence<T>& other) const;
    BitSequence<T> operator~() const;
    
    Bit<T>& operator[](size_t index);
    const Bit<T>& operator[](size_t index) const;
    
    std::unique_ptr<Iterator<Bit<T>>> begin() override;
    std::unique_ptr<Iterator<Bit<T>>> end() override;
    std::unique_ptr<ConstIterator<Bit<T>>> begin() const override;
    std::unique_ptr<ConstIterator<Bit<T>>> end() const override;
    std::unique_ptr<ConstIterator<Bit<T>>> cbegin() const override;
    std::unique_ptr<ConstIterator<Bit<T>>> cend() const override;
};

#include "BitSequence.tpp"