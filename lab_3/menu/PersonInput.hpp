#pragma once
#include "Menu.hpp"
#include "../Person.hpp"

Person InputPerson(const string& prompt) {
    PersonID id;
    id.series = InputNumber("Введите серию паспорта");
    id.number = InputNumber("Введите номер паспорта");
    
    string name = InputString("Введите имя");
    string surname = InputString("Введите фамилию");
    string patronymic = InputString("Введите отчество");
    int day = InputNumber("Введите день рождения (1-31)");
    int month = InputNumber("Введите месяц рождения (1-12)");
    int year = InputNumber("Введите год рождения");
    
    struct tm birth_tm = {0};
    birth_tm.tm_mday = day;
    birth_tm.tm_mon = month - 1;
    birth_tm.tm_year = year - 1900;
    
    time_t birth_date = mktime(&birth_tm);
    
    return Person(id, name, surname, patronymic, birth_date);
}

string PersonToString(const Person& p) {
    return p.GetFullName();
}