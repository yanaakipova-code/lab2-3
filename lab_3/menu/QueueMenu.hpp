#pragma once
#include "Menu.hpp"
#include "../Quete.hpp"
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
void QueueMenuWithType(const string& typeName) {
    Quate<T, ArraySequence>* queue = new Quate<T, ArraySequence>();

    if constexpr (is_same<T, int>::value) {
        for (int i = 1; i <= 5; i++) {
            queue->Enqueue(i);
        }
    } else if constexpr (is_same<T, double>::value) {
        for (int i = 1; i <= 5; i++) {
            queue->Enqueue(i * 1.5);
        }
    } else if constexpr (is_same<T, Complex<double>>::value) {
        queue->Enqueue(Complex<double>(1, 2));
        queue->Enqueue(Complex<double>(3, 4));
        queue->Enqueue(Complex<double>(5, 6));
    } else if constexpr (is_same<T, Person>::value) {
        PersonID id1 = {1111, 123456};
        PersonID id2 = {2222, 789012};
        PersonID id3 = {3333, 345678};
        struct tm tm1 = {0}; tm1.tm_mday = 15; tm1.tm_mon = 5; tm1.tm_year = 1998 - 1900;
        struct tm tm2 = {0}; tm2.tm_mday = 20; tm2.tm_mon = 2; tm2.tm_year = 2010 - 1900;
        struct tm tm3 = {0}; tm3.tm_mday = 10; tm3.tm_mon = 10; tm3.tm_year = 1960 - 1900;
        queue->Enqueue(Person(id1, "Anna", "Ivanova", "Petrovna", mktime(&tm1)));
        queue->Enqueue(Person(id2, "Boris", "Petrov", "Ivanovich", mktime(&tm2)));
        queue->Enqueue(Person(id3, "Alexey", "Sidorov", "Alexeevich", mktime(&tm3)));
    }
    
    const char* items[] = {
        "Показать очередь",
        "Добавить (Enqueue)",
        "Удалить (Dequeue)",
        "Первый элемент (Peek)",
        "Map",
        "Where",
        "Reduce",
        "Очистить",
        "← Назад"
    };
    int item_count = 9;
    
    while (true) {
        int choice = RunMenu(("ОЧЕРЕДЬ <" + typeName + ">").c_str(), items, item_count);
        
        if (choice == -1 || choice == item_count - 1) {
            delete queue;
            break;
        }
        
        try {
            switch (choice) {
                case 0: {
                    string content;
                    for (int i = 0; i < queue->GetSize(); i++) {
                        if (i > 0) content += ", ";
                        if constexpr (is_same<T, int>::value) {
                            content += to_string(queue->GetData(i));
                        } else if constexpr (is_same<T, double>::value) {
                            content += to_string(queue->GetData(i));
                        } else if constexpr (is_same<T, Complex<double>>::value) {
                            content += ComplexToString(queue->GetData(i));
                        } else if constexpr (is_same<T, Person>::value) {
                            content += PersonToString(queue->GetData(i));
                        }
                    }
                    DisplaySequence("Очередь", queue->GetSize(), content);
                    break;
                }
                case 1: {
                    if constexpr (is_same<T, int>::value) {
                        int val = InputNumber("Введите число");
                        queue->Enqueue(val);
                        ShowMessage("Добавлено: " + to_string(val));
                    } else if constexpr (is_same<T, double>::value) {
                        double val = InputDouble("Введите число");
                        queue->Enqueue(val);
                        ShowMessage("Добавлено: " + to_string(val));
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        double re = InputDouble("Введите действительную часть");
                        double im = InputDouble("Введите мнимую часть");
                        queue->Enqueue(Complex<double>(re, im));
                        ShowMessage("Добавлено комплексное число");
                    } else if constexpr (is_same<T, Person>::value) {
                        queue->Enqueue(InputPerson("Введите данные персоны"));
                        ShowMessage("Добавлена персона");
                    }
                    break;
                }
                case 2: {
                    if (queue->IsEmpty()) {
                        ShowMessage("Очередь пуста!", true);
                    } else {
                        queue->Dequeue();
                        ShowMessage("Удалено");
                    }
                    break;
                }
                case 3: {
                    if (queue->IsEmpty()) {
                        ShowMessage("Очередь пуста!", true);
                    } else {
                        if constexpr (is_same<T, int>::value) {
                            ShowMessage("Первый элемент: " + to_string(queue->Peek()));
                        } else if constexpr (is_same<T, double>::value) {
                            ShowMessage("Первый элемент: " + to_string(queue->Peek()));
                        } else if constexpr (is_same<T, Complex<double>>::value) {
                            ShowMessage("Первый элемент: " + ComplexToString(queue->Peek()));
                        } else if constexpr (is_same<T, Person>::value) {
                            ShowMessage("Первый элемент: " + PersonToString(queue->Peek()));
                        }
                    }
                    break;
                }
                case 4: {
                    if constexpr (is_same<T, int>::value) {
                        Quate<int, ArraySequence> new_queue = queue->template Map<int>(SquareInt);
                        delete queue;
                        queue = new Quate<int, ArraySequence>(new_queue);
                        ShowMessage("Map (возведение в квадрат) выполнен");
                    } else if constexpr (is_same<T, double>::value) {
                        Quate<double, ArraySequence> new_queue = queue->template Map<double>(SquareDouble);
                        delete queue;
                        queue = new Quate<double, ArraySequence>(new_queue);
                        ShowMessage("Map (возведение в квадрат) выполнен");
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        Quate<Complex<double>, ArraySequence> new_queue = queue->template Map<Complex<double>>(SquareComplex);
                        delete queue;
                        queue = new Quate<Complex<double>, ArraySequence>(new_queue);
                        ShowMessage("Map (возведение в квадрат) выполнен");
                    } else if constexpr (is_same<T, Person>::value) {
                        const char* mapItems[] = {
                            "В верхний регистр",
                            "В нижний регистр",
                            "← Назад"
                        };
                        int mapChoice = RunMenu("Выберите Map для Person", mapItems, 3);
                        if (mapChoice == 0) {
                            Quate<Person, ArraySequence> new_queue = queue->template Map<Person>(PersonToUpper);
                            delete queue;
                            queue = new Quate<Person, ArraySequence>(new_queue);
                            ShowMessage("Map (в верхний регистр) выполнен");
                        } else if (mapChoice == 1) {
                            Quate<Person, ArraySequence> new_queue = queue->template Map<Person>(PersonToLower);
                            delete queue;
                            queue = new Quate<Person, ArraySequence>(new_queue);
                            ShowMessage("Map (в нижний регистр) выполнен");
                        }
                    }
                    break;
                }
                case 5: {
                    if constexpr (is_same<T, int>::value) {
                        Quate<int, ArraySequence> new_queue = queue->Where(IsEvenInt);
                        delete queue;
                        queue = new Quate<int, ArraySequence>(new_queue);
                        ShowMessage("Where (чётные числа) выполнен");
                    } else if constexpr (is_same<T, double>::value) {
                        Quate<double, ArraySequence> new_queue = queue->Where(IsEvenDouble);
                        delete queue;
                        queue = new Quate<double, ArraySequence>(new_queue);
                        ShowMessage("Where (чётные числа) выполнен");
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        Quate<Complex<double>, ArraySequence> new_queue = queue->Where(IsRealPositive);
                        delete queue;
                        queue = new Quate<Complex<double>, ArraySequence>(new_queue);
                        ShowMessage("Where (положительная действительная часть) выполнен");
                    } else if constexpr (is_same<T, Person>::value) {
                        const char* whereItems[] = {
                            "Имя начинается с 'А'",
                            "--------------",
                            "Все элементы",
                            "← Назад"
                        };
                        int whereChoice = RunMenu("Выберите Where для Person", whereItems, 4);
                        if (whereChoice == 0) {
                            Quate<Person, ArraySequence> new_queue = queue->Where(PersonNameStartsWithA);
                            delete queue;
                            queue = new Quate<Person, ArraySequence>(new_queue);
                            ShowMessage("Where (имя на 'А') выполнен");
                        } else if (whereChoice == 1) {
                            Quate<Person, ArraySequence> new_queue = queue->Where(PersonIsAdult);
                            delete queue;
                            queue = new Quate<Person, ArraySequence>(new_queue);
                            ShowMessage("-------------------");
                        } else if (whereChoice == 2) {
                            Quate<Person, ArraySequence> new_queue = queue->Where(PersonAlwaysTrue);
                            delete queue;
                            queue = new Quate<Person, ArraySequence>(new_queue);
                            ShowMessage("Where (все элементы) выполнен");
                        }
                    }
                    break;
                }
                case 6: {
    if constexpr (is_same<T, int>::value) {
        if (queue->GetSize() == 0) {
            ShowMessage("Очередь пуста!", true);
        } else {
            int sum = queue->Reduce(SumInt);
            ShowMessage("Сумма элементов: " + to_string(sum));
        }
    } else if constexpr (is_same<T, double>::value) {
        if (queue->GetSize() == 0) {
            ShowMessage("Очередь пуста!", true);
        } else {
            double sum = queue->Reduce(SumDouble);
            ShowMessage("Сумма элементов: " + to_string(sum));
        }
    } else if constexpr (is_same<T, Complex<double>>::value) {
        if (queue->GetSize() == 0) {
            ShowMessage("Очередь пуста!", true);
        } else {
            Complex<double> sum = queue->Reduce(SumComplex);
            ShowMessage("Сумма: " + ComplexToString(sum));
        }
    } else if constexpr (is_same<T, Person>::value) {
        if (queue->GetSize() == 0) {
            ShowMessage("Очередь пуста!", true);
        } else {
            Person result = queue->Reduce(MergePersons);
            ShowMessage("Результат Reduce: " + PersonToString(result));
        }
    }
    break;
}
                case 7: {
                    delete queue;
                    queue = new Quate<T, ArraySequence>();
                    ShowMessage("Очередь очищена");
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