#pragma once
#include "../Complex.hpp"
#include "../Person.hpp"
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

int SquareInt(const int& x) {
    return x * x;
}

bool IsEvenInt(const int& x) {
    return x % 2 == 0;
}

int SumInt(const int& a, const int& b) {
    return a + b;
}

double SquareDouble(const double& x) {
    return x * x;
}

bool IsEvenDouble(const double& x) {
    return static_cast<int>(x) % 2 == 0;
}

double SumDouble(const double& a, const double& b) {
    return a + b;
}

Complex<double> SquareComplex(const Complex<double>& c) {
    return c * c;
}

bool IsRealPositive(const Complex<double>& c) {
    return c.GetRe() > 0;
}

Complex<double> SumComplex(const Complex<double>& a, const Complex<double>& b) {
    return a + b;
}

Person PersonToUpper(const Person& p) {
    string name = p.GetName();
    string surname = p.GetSurName();
    string patronymic = p.GetPatronymic();
    
    for (char& c : name) c = toupper(c);
    for (char& c : surname) c = toupper(c);
    for (char& c : patronymic) c = toupper(c);
    
    return Person(p.GetID(), name, surname, patronymic, p.GetDate());
}

Person PersonToLower(const Person& p) {
    string name = p.GetName();
    string surname = p.GetSurName();
    string patronymic = p.GetPatronymic();
    
    for (char& c : name) c = tolower(c);
    for (char& c : surname) c = tolower(c);
    for (char& c : patronymic) c = tolower(c);
    
    return Person(p.GetID(), name, surname, patronymic, p.GetDate());
}

bool PersonNameStartsWithA(const Person& p) {
    if (p.GetName().empty()) return false;
    char first = p.GetName()[0];
    return first == 'A' || first == 'a';
}

bool PersonIsAdult(const Person& p) {
    return p.GetAge() >= 18;
}

bool PersonAlwaysTrue(const Person& p) {
    return true;
}

Person MergePersons(const Person& a, const Person& b) {
    return a;
}

Person CopyPerson(const Person& p) {
    return Person(p.GetID(), p.GetName(), p.GetSurName(), p.GetPatronymic(), p.GetDate());
}