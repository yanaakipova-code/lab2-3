#pragma once
#include <bitset>
class Bit {
private:
    unsigned int m_mask;
public:
    Bit() : m_mask(0) {}
    Bit(unsigned int other): m_mask(other){}

    int GetBit(size_t i) const {
        return (m_mask >> i) & 1;
    }

    unsigned int GetMask() const {
        return m_mask;
    }
};