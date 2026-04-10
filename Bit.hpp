#pragma once

class Bit {
private:
    char m_value : 1;
public:
    Bit (bool value = false){
        m_value = 0;
    }

    char GetValue() const {
        return m_value;
    }

    Bit operator&(const Bit& other) const {
        return Bit((m_value & other.m_value) != 0);
    }

    Bit operator|(const Bit& other) const {
        return Bit((m_value | other.m_value) != 0);
    }

    Bit operator^(const Bit& other) const {
        return Bit((m_value ^ other.m_value) != 0);
    }

    Bit operator!() const {
        return Bit(m_value == 0);
    }

    Bit& operator&=(const Bit& other) {
        m_value &= other.m_value;
        return *this;
    }
};