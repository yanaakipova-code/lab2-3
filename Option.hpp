#pragma once
#include <stdexcept>
#include <functional>

template<class T>
class Option{
private:
    T m_value;
    bool m_hasValue;

public:
    Option(): m_hasValue(false){}
    Option(const T& value):
        m_value(value), m_hasValue(true){}

    bool HasValue() const { 
        return m_hasValue; 
    }

    T GetValue() const {
        if (!m_hasValue) {
            throw std::runtime_error("Option  не имеет значения");
        }
        return m_value;
    }

    static Option<T> Some(const T& value){
        return Option<T>(value);
    }

    static Option<T> None(){
        return Option<T>();
    }


    template<typename U>
    Option<U> Map(std::function<U(T)> func) const{
        if (m_hasValue){
            return Option<U>::Some(func(m_value));
        }
        return Option<U>:: None();
    }

    template<typename U>
    Option<U> FlatMap(std::function<Option<U>(T)> func) const{
        if (m_hasValue){
            return func(m_value);
        }
        return Option<U>::None();
    }

    template<typename U>
    T OrElse(const T& default_value) const {
        if (m_hasValue) {
            return m_value;
        } else {
            return default_value;
        }
    }


};