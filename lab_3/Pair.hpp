#pragma once
#include <iostream>
#include <sstream>
#include <format>

template<typename T, typename U>

class Pair{
private:
    T first;
    U second;
public:
    Pair(const T& one, const U& two): first{one}, secon{two}  {}

    T GetFirst() const{
        return first;
    }
    U GetSecond() const{
        return second;
    }

    bool operator==(const Pair& other){
        return (other.first == first && other.second == second);
    }

    bool operator!=(const Pair& other){
        return !(other == *this);
    }

    std::string ToString() const{
        return std::format("({} {})", first, second);
    }
};
