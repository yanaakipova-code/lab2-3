#pragma once
#include "Menu.hpp"
#include "../Complex.hpp"

Complex<double> InputComplex(const string& prompt) {
    double re = InputDouble(prompt + " (действительная часть)");
    double im = InputDouble(prompt + " (мнимая часть)");
    return Complex<double>(re, im);
}

string ComplexToString(const Complex<double>& c) {
    return c.ToString();
}