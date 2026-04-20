#pragma once
#include "Menu.hpp"
#include "../Matrix.hpp"
#include "../../ListSequence.hpp"
#include "../../Error.hpp"
#include <type_traits>
#include <functional>

using namespace std;

template<typename T>
void MatrixMenuWithType(const string& typeName) {
    SquareMatrix<T, ListSequence>* matrix = new SquareMatrix<T, ListSequence>(3);
    
    if constexpr (is_same<T, int>::value) {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                matrix->Set(i, j, i * 3 + j + 1);
            }
        }
    } else if constexpr (is_same<T, double>::value) {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                matrix->Set(i, j, (i * 3 + j + 1) * 1.5);
            }
        }
    }
    
    const char* items[] = {
        "Показать матрицу",
        "Получить элемент",
        "Установить элемент",
        "Сложение матриц",
        "Умножение на скаляр",
        "Норма матрицы",
        "Очистить",
        "← Назад"
    };
    int itemCount = 8;
    
    while (true) {
        int choice = RunMenu(("МАТРИЦА <" + typeName + ">").c_str(), items, itemCount);
        
        if (choice == -1 || choice == itemCount - 1) {
            delete matrix;
            break;
        }
        
        try {
            switch (choice) {
                case 0: {
                    std::function<T(size_t, size_t)> getter = [matrix](size_t i, size_t j) -> T {
                        return matrix->Get(i, j);
                    };
                    DisplayMatrixGeneric<T>("Матрица", matrix->GetSize(), getter);
                    break;
                }
                case 1: {
                    int row = InputNumber("Введите строку (0-based)");
                    int col = InputNumber("Введите столбец (0-based)");
                    T val = matrix->Get(row, col);
                    ShowMessage("Элемент [" + to_string(row) + "][" + to_string(col) + "] = " + to_string(val));
                    break;
                }
                case 2: {
                    int row = InputNumber("Введите строку");
                    int col = InputNumber("Введите столбец");
                    T val;
                    if constexpr (is_same<T, int>::value) {
                        val = InputNumber("Введите значение");
                    } else if constexpr (is_same<T, double>::value) {
                        val = InputDouble("Введите значение");
                    }
                    matrix->Set(row, col, val);
                    ShowMessage("Установлено");
                    break;
                }
                case 3: {
                    ShowMessage("Создайте матрицу 3x3 для сложения:");
                    SquareMatrix<T, ListSequence> other(3);
                    for (size_t i = 0; i < 3; i++) {
                        for (size_t j = 0; j < 3; j++) {
                            T val;
                            if constexpr (is_same<T, int>::value) {
                                val = InputNumber("Элемент [" + to_string(i) + "][" + to_string(j) + "]");
                            } else if constexpr (is_same<T, double>::value) {
                                val = InputDouble("Элемент [" + to_string(i) + "][" + to_string(j) + "]");
                            }
                            other.Set(i, j, val);
                        }
                    }
                    auto result = matrix->Sum(other);
                    *matrix = result;
                    ShowMessage("Сложение выполнено");
                    break;
                }
                case 4: {
                    T scalar;
                    if constexpr (is_same<T, int>::value) {
                        scalar = InputNumber("Введите скаляр");
                    } else if constexpr (is_same<T, double>::value) {
                        scalar = InputDouble("Введите скаляр");
                    }
                    auto result = matrix->Multiply(scalar);
                    *matrix = result;
                    ShowMessage("Умножено на " + to_string(scalar));
                    break;
                }
                case 5: {
                    T norm = matrix->MatrixNorm();
                    ShowMessage("Норма матрицы: " + to_string(norm));
                    break;
                }
                case 6: {
                    delete matrix;
                    matrix = new SquareMatrix<T, ListSequence>(3);
                    ShowMessage("Матрица обнулена");
                    break;
                }
            }
        } catch (const Exception& e) {
            ShowMessage(string("Ошибка: ") + e.what(), true);
        }
    }
}

void MatrixMenu() {
    MatrixMenuWithType<int>("int");
}