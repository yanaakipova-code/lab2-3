#pragma once
#include "Menu.hpp"
#include "../Pair.hpp"

template<typename T, typename U>
Pair<T, U> InputPair(const string& prompt) {
    T first = InputNumber(prompt + " (первый элемент)");
    U second = InputNumber(prompt + " (второй элемент)");
    return Pair<T, U>(first, second);
}

template<typename T, typename U>
string PairToString(const Pair<T, U>& p) {
    return p.ToString();
}