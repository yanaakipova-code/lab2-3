#pragma once
#include "../Error.hpp"
#include <iostream>
#include <cmath>
#include <string> 
#include <format>

using namespace std;

template<typename U>
class Complex{
private:
    U m_re;
    U m_im;
public:
    Complex() : m_re{0}, m_im{0} {}
    
    Complex(U re, U im) : m_re{re}, m_im{im} {}
    
    Complex(const Complex& other) : m_re{other.m_re}, m_im{other.m_im} {}
    
    ~Complex() {}

    U GetRe() const { return m_re; }
    U GetIm() const { return m_im; }
    void SetRe(U re) { m_re = re; }
    void SetIm(U im) { m_im = im; }

    U Abs() const {
        return sqrt((m_re * m_re) + (m_im * m_im));
    }

    Complex operator+(const Complex& other) const {
        return Complex(m_re + other.m_re, m_im + other.m_im);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(m_re - other.m_re, m_im - other.m_im);
    }
    
    Complex operator*(const Complex& other) const {
        U re = (m_re * other.m_re) - (m_im * other.m_im);
        U im = (m_re * other.m_im) + (m_im * other.m_re); 
        return Complex(re, im);
    }
    
    Complex operator/(const Complex& other) const {
        U del = (other.m_re * other.m_re) + (other.m_im * other.m_im); 
        if (del == 0){
            throw DivisionByZeroException("Деление на ноль");
        }
        U re = ((m_re * other.m_re) + (m_im * other.m_im)) / del;
        U im = ((m_im * other.m_re) - (m_re * other.m_im)) / del;
        return Complex(re, im);
    }
    
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            m_re = other.m_re;
            m_im = other.m_im;
        }
        return *this;
    }
    
    Complex& operator=(int value) {
        m_re = value;
        m_im = 0;
        return *this;
    }
    
    bool operator>(const Complex& other) const {
        return Abs() > other.Abs();
    }

    bool operator==(const Complex& other) const {
        return m_re == other.m_re && m_im == other.m_im;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    friend U abs(const Complex& z) {
        return z.Abs();
    }

    string ToString() const {
        if (m_re == 0 && m_im == 0) {
        return "0";
    }
    if (m_re == 0) {
        return std::format("{}i", m_im);
    }
    if (m_im == 0) {
        return std::format("{}", m_re);
    }
    if (m_im > 0) {
        return std::format("{}+{}i", m_re, m_im);
    }
    return std::format("{}{}i", m_re, m_im);
    }
};