#pragma once
#include "Menu.hpp"
#include "../Matrix.hpp"
#include "../../ListSequence.hpp"
#include "../../Error.hpp"
#include "../Complex.hpp"
#include "ComplexInput.hpp"
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
    } else if constexpr (is_same<T, Complex<double>>::value) {
        (*matrix)(0, 0) = Complex<double>(1, 1);
        (*matrix)(0, 1) = Complex<double>(2, 0);
        (*matrix)(0, 2) = Complex<double>(3, -1);
        (*matrix)(1, 0) = Complex<double>(0, 2);
        (*matrix)(1, 1) = Complex<double>(5, 0);
        (*matrix)(1, 2) = Complex<double>(1, 1);
        (*matrix)(2, 0) = Complex<double>(2, 2);
        (*matrix)(2, 1) = Complex<double>(0, 0);
        (*matrix)(2, 2) = Complex<double>(4, -1);
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
                    function<T(size_t, size_t)> getter = [matrix](size_t i, size_t j) -> T {
                        return matrix->Get(i, j);
                    };
                    DisplayMatrixGeneric<T>("Матрица", matrix->GetSize(), getter);
                    break;
                }
                case 1: {
                    int row = InputNumber("Введите строку (0-based)");
                    int col = InputNumber("Введите столбец (0-based)");
                    T val = matrix->Get(row, col);
                    
                    if constexpr (is_same<T, int>::value) {
                        ShowMessage("Элемент [" + to_string(row) + "][" + to_string(col) + "] = " + to_string(val));
                    } else if constexpr (is_same<T, double>::value) {
                        ShowMessage("Элемент [" + to_string(row) + "][" + to_string(col) + "] = " + to_string(val));
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        ShowMessage("Элемент [" + to_string(row) + "][" + to_string(col) + "] = " + ComplexToString(val));
                    }
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
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        double re = InputDouble("Введите действительную часть");
                        double im = InputDouble("Введите мнимую часть");
                        val = Complex<double>(re, im);
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
                            } else if constexpr (is_same<T, Complex<double>>::value) {
                                double re = InputDouble("Элемент [" + to_string(i) + "][" + to_string(j) + "] (действительная часть)");
                                double im = InputDouble("Элемент [" + to_string(i) + "][" + to_string(j) + "] (мнимая часть)");
                                val = Complex<double>(re, im);
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
                    if constexpr (is_same<T, int>::value) {
                        T scalar = InputNumber("Введите скаляр");
                        auto result = matrix->Multiply(scalar);
                        *matrix = result;
                        ShowMessage("Умножено на " + to_string(scalar));
                    } else if constexpr (is_same<T, double>::value) {
                        T scalar = InputDouble("Введите скаляр");
                        auto result = matrix->Multiply(scalar);
                        *matrix = result;
                        ShowMessage("Умножено на " + to_string(scalar));
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        double re = InputDouble("Введите действительную часть скаляра");
                        double im = InputDouble("Введите мнимую часть скаляра");
                        T scalar(re, im);
                        auto result = matrix->Multiply(scalar);
                        *matrix = result;
                        ShowMessage("Умножено на " + ComplexToString(scalar));
                    }
                    break;
                }
                case 5: {
                    T norm = matrix->MatrixNorm();
                    if constexpr (is_same<T, int>::value) {
                        ShowMessage("Норма матрицы: " + to_string(norm));
                    } else if constexpr (is_same<T, double>::value) {
                        ShowMessage("Норма матрицы: " + to_string(norm));
                    } else if constexpr (is_same<T, Complex<double>>::value) {
                        ShowMessage("Норма матрицы: " + to_string(norm.GetRe()));
                    }
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
        } catch (const std::exception& e) {
            ShowMessage(string("STL Ошибка: ") + e.what(), true);
        } catch (...) {
            ShowMessage("Неизвестная ошибка!", true);
        }
    }
}

void MatrixMenu() {
    const char* typeItems[] = {
        "Целые числа (int)",
        "Вещественные числа (double)",
        "Комплексные числа (Complex)",
        "← Назад"
    };
    
    int choice = RunMenu("ВЫБЕРИТЕ ТИП МАТРИЦЫ", typeItems, 4);
    
    if (choice == 0) {
        MatrixMenuWithType<int>("int");
    } else if (choice == 1) {
        MatrixMenuWithType<double>("double");
    } else if (choice == 2) {
        MatrixMenuWithType<Complex<double>>("Complex");
    }
}