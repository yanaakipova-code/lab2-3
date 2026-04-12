#pragma once
#include <concepts>

template<std::integral T>
class Bit {
private:
    T m_mask;
    
public:
    Bit() : m_mask(0) {}
    Bit(T value) : m_mask(value) {}
    
    bool GetBit(size_t i) const {
        return ((m_mask >> i) & static_cast<T>(1)) != static_cast<T>(0);
    }
    
    T GetMask() const {
        return m_mask;
    }
    
    Bit<T> operator&(const Bit<T>& other) const {
        return Bit<T>(m_mask & other.m_mask);
    }
    
    Bit<T> operator|(const Bit<T>& other) const {
        return Bit<T>(m_mask | other.m_mask);
    }
    
    Bit<T> operator^(const Bit<T>& other) const {
        return Bit<T>(m_mask ^ other.m_mask);
    }
    
    Bit<T> operator~() const {
        return Bit<T>(~m_mask);
    }
};