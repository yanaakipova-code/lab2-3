#pragma once

class Bit {
private:
    bool m_value;
public:
    Bit(bool value = false) : m_value(value) {}

    bool GetValue() const {
        return m_value; 
    }
    void SetValue(bool value) {
         m_value = value; 
    }

    Bit operator&(const Bit& other) const { 
        return Bit(m_value & other.m_value); 
    }
    
    Bit operator|(const Bit& other) const { 
        return Bit(m_value | other.m_value); 
    }
    
    Bit operator^(const Bit& other) const { 
        return Bit(m_value ^ other.m_value); 
    }
    
    Bit operator!() const { 
        return Bit(!m_value); 
    }
    operator bool() const { 
        return m_value; 
    }
};