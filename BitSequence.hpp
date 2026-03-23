#pragma once
#include <memory>
#include <cstddef> 
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "Bit.hpp"
class BitSequence: public Sequence<Bit>{
private:
    ArraySequence<Bit>* m_bits;

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

    std::unique_ptr<BitSequence> And(const BitSequence& other) const;
    std::unique_ptr<BitSequence> Or(const BitSequence& other) const;
    std::unique_ptr<BitSequence> Xor(const BitSequence& other) const;  
    std::unique_ptr<BitSequence> Not() const;                          

    void SetBit(size_t index, bool value);
    bool GetBit(size_t index) const;
    
    std::unique_ptr<ArraySequence<Bit>> ToMutable() const;
};