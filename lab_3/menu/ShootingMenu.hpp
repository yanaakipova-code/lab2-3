// ShootingMenu.hpp
#pragma once
#include "Menu.hpp"
#include "../Set.hpp"
#include "../../ArraySequence.hpp"
#include "../../Error.hpp"
#include "../Shooting.hpp"
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

Set<double, ArraySequence> InputVelocities() {
    Set<double, ArraySequence> velocities;
    
    clear();
    DrawBorder();
    
    mvprintw(2, 2, "=== ВВОД СКОРОСТЕЙ ===");
    mvprintw(4, 2, "Введите скорости по одной.");
    mvprintw(5, 2, "Для завершения введите 0.");
    mvprintw(7, 2, "Скорости по умолчанию: 20, 25, 30, 35, 40, 45");
    mvprintw(9, 2, "Использовать скорости по умолчанию? (y/n): ");
    refresh();
    
    int ch = getch();
    if (ch == 'y' || ch == 'Y') {
        velocities.Add(20.0);
        velocities.Add(25.0);
        velocities.Add(30.0);
        velocities.Add(35.0);
        velocities.Add(40.0);
        velocities.Add(45.0);
        return velocities;
    }
    
    int line = 11;
    int count = 0;
    
    while (true) {
        if (line >= LINES - 5) {
            mvprintw(LINES - 3, 2, "Нажмите Enter для продолжения...");
            refresh();
            getch();
            clear();
            DrawBorder();
            mvprintw(2, 2, "=== ВВОД СКОРОСТЕЙ (продолжение) ===");
            mvprintw(4, 2, "Введите 0 для завершения");
            line = 6;
        }
        
        mvprintw(line, 2, "Скорость #%d (0 для завершения): ", count + 1);
        refresh();
        
        double v = InputDouble("");
        
        if (v <= 0.01) {
            if (count == 0) {
                velocities.Add(20.0);
                velocities.Add(25.0);
                velocities.Add(30.0);
                velocities.Add(35.0);
                velocities.Add(40.0);
                velocities.Add(45.0);
            }
            break;
        }
        
        velocities.Add(v);
        mvprintw(line, 2, "Добавлено: %.2f                                     ", v);
        refresh();
        line++;
        count++;
    }
    
    return velocities;
}

void ShowShootingResult(const ShootingResult& result, double x1, double x2) {
    clear();
    DrawBorder();
    
    mvprintw(2, 2, "=== РЕЗУЛЬТАТ ПРИСТРЕЛКИ ===");
    mvprintw(4, 2, "Цель: [%.2f, %.2f] метров", x1, x2);
    mvprintw(5, 2, "Центр цели: %.2f метров", (x1 + x2) / 2);
    mvprintw(7, 2, "----------------------------------------");
    
    if (result.success) {
        attron(A_BOLD | A_REVERSE);
        mvprintw(9, 2, " ПОПАДАНИЕ! ");
        attroff(A_BOLD | A_REVERSE);
    } else {
        attron(A_BOLD);
        mvprintw(9, 2, "Точного попадания нет");
        attroff(A_BOLD);
        mvprintw(10, 2, "  (наилучшее приближение)");
    }
    
    mvprintw(12, 2, "----------------------------------------");
    mvprintw(13, 2, "Начальная скорость: %.2f м/с", result.v0);
    mvprintw(14, 2, "Угол:               %.2f°", result.angle);
    mvprintw(15, 2, "Дальность полета:   %.2f м", result.distance);
    mvprintw(16, 2, "Итераций:           %zu", result.iterations);
    
    double deviation = result.distance - (x1 + x2) / 2;
    mvprintw(17, 2, "Отклонение от центра: %.2f м", deviation);
    
    mvprintw(19, 2, "----------------------------------------");
    mvprintw(21, 2, "Нажмите любую клавишу для продолжения...");
    refresh();
    getch();
}

void ShowVelocitiesTable(double x1, double x2, const Set<double, ArraySequence>& velocities) {
    clear();
    DrawBorder();
    
    mvprintw(2, 2, "=== ТАБЛИЦА ПРОВЕРКИ СКОРОСТЕЙ ===");
    mvprintw(3, 2, "Цель: [%.2f, %.2f] метров", x1, x2);
    
    mvprintw(5, 2, "----------------------------------------");
    mvprintw(6, 2, "Скорость | Макс.дальн | Угол    | Дальность | Результат");
    mvprintw(7, 2, "----------------------------------------");
    
    int line = 8;
    
    for (const auto& v0 : velocities) {
        double max_range = GetMaxDistance(v0);
        
        if (max_range < x1 - 1e-6) {
            mvprintw(line++, 2, "  %.2f    |   %.2f    | не долетает", v0, max_range);
        } else {
            size_t iterations = 0;
            double alpha = FindAngle(v0, x1, x2, iterations);
            double dist = GetDistance(v0, alpha);
            
            if (dist >= x1 - 1e-6 && dist <= x2 + 1e-6) {
                mvprintw(line++, 2, "  %.2f    |   %.2f    |   %.2f°   |   %.2f   | ✓ ПОПАДАНИЕ", 
                         v0, max_range, alpha, dist);
            } else {
                mvprintw(line++, 2, "  %.2f    |   %.2f    |   %.2f°   |   %.2f   | мимо", 
                         v0, max_range, alpha, dist);
            }
        }
        
        if (line > LINES - 5) {
            mvprintw(LINES - 3, 2, "Нажмите Enter для продолжения...");
            refresh();
            getch();
            clear();
            DrawBorder();
            mvprintw(2, 2, "=== ТАБЛИЦА ПРОВЕРКИ СКОРОСТЕЙ (продолжение) ===");
            mvprintw(4, 2, "----------------------------------------");
            mvprintw(5, 2, "Скорость | Макс.дальн | Угол    | Дальность | Результат");
            mvprintw(6, 2, "----------------------------------------");
            line = 7;
        }
    }
    
    mvprintw(line + 2, 2, "----------------------------------------");
    mvprintw(line + 4, 2, "Нажмите любую клавишу для продолжения...");
    refresh();
    getch();
}

