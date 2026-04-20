#pragma once
#include "Menu.hpp"
#include "../Set.hpp"
#include "../../ArraySequence.hpp"
#include "../../Error.hpp"
#include "../Complex.hpp"
#include "../Person.hpp"
#include "ComplexInput.hpp"
#include "PersonInput.hpp"
#include "functions.hpp"
#include <type_traits>

using namespace std;

template<typename T>
void SetMenuWithType(const string& typeName) {
    Set<T, ArraySequence>* set = new Set<T, ArraySequence>();
    
    if constexpr (is_same<T, int>::value) {
        for (int i = 1; i <= 5; i++) {
            set->Add(i);
        }
    } else if constexpr (is_same<T, double>::value) {
        for (int i = 1; i <= 5; i++) {
            set->Add(i * 1.5);
        }
    } else if constexpr (is_same<T, Complex<double>>::value) {
        set->Add(Complex<double>(1, 2));
        set->Add(Complex<double>(3, 4));
        set->Add(Complex<double>(5, 6));
    } else if constexpr (is_same<T, Person>::value) {
        PersonID id1 = {1111, 123456};
        PersonID id2 = {2222, 789012};
        PersonID id3 = {3333, 345678};
        struct tm tm1 = {0}; tm1.tm_mday = 15; tm1.tm_mon = 5; tm1.tm_year = 1998 - 1900;
        struct tm tm2 = {0}; tm2.tm_mday = 20; tm2.tm_mon = 2; tm2.tm_year = 2010 - 1900;
        struct tm tm3 = {0}; tm3.tm_mday = 10; tm3.tm_mon = 10; tm3.tm_year = 1960 - 1900;
        set->Add(Person(id1, "Anna", "Ivanova", "Petrovna", mktime(&tm1)));
        set->Add(Person(id2, "Boris", "Petrov", "Ivanovich", mktime(&tm2)));
        set->Add(Person(id3, "Alexey", "Sidorov", "Alexeevich", mktime(&tm3)));
    }
    
    const char* items[] = {
        "Показать множество",
        "Добавить элемент",
        "Удалить элемент",
        "Проверить наличие",
        "Map",
        "Where",
        "Очистить",
        "← Назад"
    };
    int item_count = 8;
    
    while (true) {
        int choice = RunMenu(("МНОЖЕСТВО <" + typeName + ">").c_str(), items, item_count);
        
        if (choice == -1 || choice == item_count - 1) {
            delete set;
            break;
        }
        
        try {
            switch (choice) {
                case 0: {
                    if (set->GetSize() == 0) {
                        ShowMessage("Множество пусто");
                        break;
                    }
                    string content;
                    for (unsigned int i = 0; i < set->GetSize(); i++) {
                        if (i > 0) content += ", ";
                        if constexpr (is_same<T, int>::value) {
                            content += to_string(set->GetData(i));
                        } else if constexpr (is_same<T, double>::value) {
                            content += to_string(set->GetData(i));
                        } else if constexpr (is_same<T, Complex<double>>::value) {
                            content += ComplexToString(set->GetData(i));
                        } else if constexpr (is_same<T, Person>::value) {
                            content += PersonToString(set->GetData(i));
                        }
                    }
                    DisplaySequence("Множество", set->GetSize(), content);
                    break;
                }
                case 1: {
                    if constexpr (is_same<T, int>::value) {
                        int val = InputNumber("Введите число");
                        set->Add(val);
                        ShowMessage("Добавлено: " + to_string(val));
                    } else if constexpr (is_same<T, double>::value) {
                        double val = InputDouble("Введите число");
                        set->Add(val);
                        ShowMessage("Добавлено: " + to_string(val));
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        double re = InputDouble("Введите действительную часть");
                        double im = InputDouble("Введите мнимую часть");
                        set->Add(Complex<double>(re, im));
                        ShowMessage("Добавлено комплексное число");
                    } else if constexpr (is_same<T, Person>::value) {
                        Person p = InputPerson("Введите данные персоны");
                        set->Add(p);
                        ShowMessage("Добавлена персона: " + PersonToString(p));
                    }
                    break;
                }
                case 2: {
                    if constexpr (is_same<T, int>::value) {
                        if (set->GetSize() == 0) {
                            ShowMessage("Множество пусто!", true);
                        } else {
                            int val = InputNumber("Введите число для удаления");
                            set->RemoveByValue(val);
                            ShowMessage("Удалено: " + to_string(val));
                        }
                    } else if constexpr (is_same<T, double>::value) {
                        if (set->GetSize() == 0) {
                            ShowMessage("Множество пусто!", true);
                        } else {
                            double val = InputDouble("Введите число для удаления");
                            set->RemoveByValue(val);
                            ShowMessage("Удалено: " + to_string(val));
                        }
                    } else {
                        ShowMessage("Удаление для этого типа не реализовано", true);
                    }
                    break;
                }
                case 3: {
                    if constexpr (is_same<T, int>::value) {
                        if (set->GetSize() == 0) {
                            ShowMessage("Множество пусто!", true);
                        } else {
                            int val = InputNumber("Введите число");
                            ShowMessage(set->Contains(val) ? "Есть в множестве" : "Нет в множестве");
                        }
                    } else if constexpr (is_same<T, double>::value) {
                        if (set->GetSize() == 0) {
                            ShowMessage("Множество пусто!", true);
                        } else {
                            double val = InputDouble("Введите число");
                            ShowMessage(set->Contains(val) ? "Есть в множестве" : "Нет в множестве");
                        }
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        if (set->GetSize() == 0) {
                            ShowMessage("Множество пусто!", true);
                        } else {
                            double re = InputDouble("Введите действительную часть");
                            double im = InputDouble("Введите мнимую часть");
                            ShowMessage(set->Contains(Complex<double>(re, im)) ? "Есть в множестве" : "Нет в множестве");
                        }
                    } else {
                        ShowMessage("Проверка для этого типа не реализована", true);
                    }
                    break;
                }
                case 4: {
                    if (set->GetSize() == 0) {
                        ShowMessage("Множество пусто! Операция невозможна", true);
                        break;
                    }
                    if constexpr (is_same<T, int>::value) {
                        Set<int, ArraySequence> new_set = set->template Map<int>(SquareInt);
                        delete set;
                        set = new Set<int, ArraySequence>(new_set);
                        ShowMessage("Map (возведение в квадрат) выполнен");
                    } else if constexpr (is_same<T, double>::value) {
                        Set<double, ArraySequence> new_set = set->template Map<double>(SquareDouble);
                        delete set;
                        set = new Set<double, ArraySequence>(new_set);
                        ShowMessage("Map (возведение в квадрат) выполнен");
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        Set<Complex<double>, ArraySequence> new_set = set->template Map<Complex<double>>(SquareComplex);
                        delete set;
                        set = new Set<Complex<double>, ArraySequence>(new_set);
                        ShowMessage("Map (возведение в квадрат) выполнен");
                    } else if constexpr (is_same<T, Person>::value) {
                        const char* mapItems[] = {
                            "В верхний регистр",
                            "В нижний регистр",
                            "⭠Назад"
                        };
                        int mapChoice = RunMenu("Выберите Map для Person", mapItems, 3);
                        if (mapChoice == 0) {
                            Set<Person, ArraySequence> new_set = set->template Map<Person>(PersonToUpper);
                            delete set;
                            set = new Set<Person, ArraySequence>(new_set);
                            ShowMessage("Map (в верхний регистр) выполнен");
                        } else if (mapChoice == 1) {
                            Set<Person, ArraySequence> new_set = set->template Map<Person>(PersonToLower);
                            delete set;
                            set = new Set<Person, ArraySequence>(new_set);
                            ShowMessage("Map (в нижний регистр) выполнен");
                        }
                    }
                    break;
                }
                case 5: {
                    if (set->GetSize() == 0) {
                        ShowMessage("Множество пусто! Операция невозможна", true);
                        break;
                    }
                    if constexpr (is_same<T, int>::value) {
                        Set<int, ArraySequence> new_set = set->Where(IsEvenInt);
                        delete set;
                        set = new Set<int, ArraySequence>(new_set);
                        ShowMessage("Where (чётные числа) выполнен");
                    } else if constexpr (is_same<T, double>::value) {
                        Set<double, ArraySequence> new_set = set->Where(IsEvenDouble);
                        delete set;
                        set = new Set<double, ArraySequence>(new_set);
                        ShowMessage("Where (чётные числа) выполнен");
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        Set<Complex<double>, ArraySequence> new_set = set->Where(IsRealPositive);
                        delete set;
                        set = new Set<Complex<double>, ArraySequence>(new_set);
                        ShowMessage("Where (положительная действительная часть) выполнен");
                    } else if constexpr (is_same<T, Person>::value) {
                        const char* whereItems[] = {
                            "Имя начинается с 'А'",
                            "Старше 18 лет",
                            "Все элементы",
                            "← Назад"
                        };
                        int whereChoice = RunMenu("Выберите Where для Person", whereItems, 4);
                        if (whereChoice == 0) {
                            Set<Person, ArraySequence> new_set = set->Where(PersonNameStartsWithA);
                            delete set;
                            set = new Set<Person, ArraySequence>(new_set);
                            ShowMessage("Where (имя на 'А') выполнен");
                        } else if (whereChoice == 1) {
                            Set<Person, ArraySequence> new_set = set->Where(PersonIsAdult);
                            delete set;
                            set = new Set<Person, ArraySequence>(new_set);
                            ShowMessage("------------------------");
                        } else if (whereChoice == 2) {
                            Set<Person, ArraySequence> new_set = set->Where(PersonAlwaysTrue);
                            delete set;
                            set = new Set<Person, ArraySequence>(new_set);
                            ShowMessage("Where (все элементы) выполнен");
                        }
                    }
                    break;
                }
                case 6: {
                    delete set;
                    set = new Set<T, ArraySequence>();
                    ShowMessage("Множество очищено");
                    break;
                }
            }
        } catch (const Exception& e) {
            ShowMessage(string("Ошибка: ") + e.what(), true);
        } catch (const std::exception& e) {
            ShowMessage(string("STL Ошибка: ") + e.what(), true);
        } catch (...) {
            ShowMessage("Неизвестная ошибка!", true);
        }
    }
}