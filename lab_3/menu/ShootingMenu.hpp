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


void DrawTrajectorySimple(double v0, double angle_deg) {
    clear();
    DrawBorder();
    
    const int width = 60;
    const int height = 18;
    
    double rad = angle_deg * pi / 180;
    double vx = v0 * cos(rad);
    double vy = v0 * sin(rad);
    double T = 2 * vy / 9.8;
    double max_range = vx * T;
    double max_height = vy * vy / 19.6;
    
    mvprintw(2, 2, "=== ТРАЕКТОРИЯ ПОЛЕТА ===");
    mvprintw(3, 2, "v0 = %.0f м/с, угол = %.0f°", v0, angle_deg);
    mvprintw(4, 2, "Дальность: %.1f м, Высота: %.1f м", max_range, max_height);
    mvprintw(5, 2, "");
    
    for (int y_pixel = 0; y_pixel < height; y_pixel++) {
        double y = max_height * (1 - (double)y_pixel / height);
        
        mvprintw(6 + y_pixel, 2, "|");
        
        for (int x_pixel = 0; x_pixel < width; x_pixel++) {
            double x = (max_range * x_pixel) / width;
            double t = x / vx;
            double y_calc = vy * t - 4.9 * t * t;
            
            if (y_calc >= y - 0.5 && y_calc <= y + 0.5 && y_calc >= 0) {
                mvprintw(6 + y_pixel, 3 + x_pixel, "*");
            }
        }
    }
    
    mvprintw(6 + height, 2, "+");
    for (int x = 0; x < width; x++) {
        mvprintw(6 + height, 3 + x, "-");
    }
    mvprintw(6 + height, 3 + width, "> X");
    
    mvprintw(LINES - 3, 2, "Нажмите любую клавишу для продолжения...");
    refresh();
    getch();
}

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
        velocities + 20.0 + 25.0 + 30.0 + 35.0 + 40.0 + 45.0;
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
        attron(A_BOLD);
        mvprintw(9, 2, "ПОПАДАНИЕ!");
        attroff(A_BOLD);
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
    double target = (x1 + x2) / 2;
    
    for (const auto& v0 : velocities) {
        double max_range = GetMaxDistance(v0);
        
        if (max_range < x1 - 1e-6) {
            mvprintw(line++, 2, "  %6.2f   |   %6.2f   | не долетает", v0, max_range);
        } else {
            Set<double, ArraySequence> bounds;
            size_t iterations = 0;
            double angle = FindAngle<ArraySequence>(v0, target, bounds, iterations);
            double dist = GetDistance(v0, angle);
            
            if (dist >= x1 - 1e-6 && dist <= x2 + 1e-6) {
                mvprintw(line++, 2, "  %6.2f   |   %6.2f   |   %6.2f°  |   %6.2f   | ПОПАДАНИЕ", 
                         v0, max_range, angle, dist);
            } else {
                mvprintw(line++, 2, "  %6.2f   |   %6.2f   |   %6.2f°  |   %6.2f   | мимо", 
                         v0, max_range, angle, dist);
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

void RunShootingMenu() {
    const char* items[] = {
        "Найти оптимальный выстрел",
        "Показать таблицу всех скоростей",
        "Показать траекторию полета",
        "Ввести новый список скоростей",
        "← Назад"
    };
    
    static Set<double, ArraySequence> velocities;
    static bool velocities_initialized = false;
    
    if (!velocities_initialized) {
        velocities + 20.0 + 25.0 + 30.0 + 35.0 + 40.0 + 45.0;
        velocities_initialized = true;
   }
    
    while (true) {
        int choice = RunMenu("РАСЧЕТ ТРАЕКТОРИИ ПОЛЕТА (ПРИСТРЕЛКА)", items, 5);
        
        if (choice == -1 || choice == 4) break;
        
        if (choice == 0) {
            clear();
            DrawBorder();
            
            mvprintw(2, 2, "=== ВВОД ПАРАМЕТРОВ ЦЕЛИ ===");
            refresh();
            
            double x1 = InputDouble("Левая граница (x1)");
            double x2 = InputDouble("Правая граница (x2)");
            
            if (x1 >= x2) {
                ShowMessage("Ошибка: x1 должно быть меньше x2!", true);
                continue;
            }
            
            if (velocities.GetSize() == 0) {
                ShowMessage("Список скоростей пуст! Введите скорости.", true);
                velocities = InputVelocities();
                if (velocities.GetSize() == 0) {
                    ShowMessage("Нет скоростей для расчета!", true);
                    continue;
                }
            }
            
            try {
                ShootingResult result = FindShooting<ArraySequence>(x1, x2, velocities);
                ShowShootingResult(result, x1, x2);
            } catch (const ImpossibleToGetInException& e) {
                ShowMessage(string("Ошибка: ") + e.what(), true);
            } catch (const std::exception& e) {
                ShowMessage(string("Ошибка: ") + e.what(), true);
            }
        }
        else if (choice == 1) {
            if (velocities.GetSize() == 0) {
                ShowMessage("Список скоростей пуст! Сначала введите скорости.", true);
                velocities = InputVelocities();
                if (velocities.GetSize() == 0) {
                    continue;
                }
            }
            
            clear();
            DrawBorder();
            
            double x1 = InputDouble("Левая граница (x1)");
            double x2 = InputDouble("Правая граница (x2)");
            
            if (x1 >= x2) {
                ShowMessage("Ошибка: x1 должно быть меньше x2!", true);
                continue;
            }
            
            try {
                ShowVelocitiesTable(x1, x2, velocities);
            } catch (const std::exception& e) {
                ShowMessage(string("Ошибка: ") + e.what(), true);
            }
        }
        else if (choice == 2) {
            clear();
            DrawBorder();
            
            mvprintw(2, 2, "=== ПОКАЗАТЬ ТРАЕКТОРИЮ ===");
            refresh();
            
            double v0 = InputDouble("Введите начальную скорость (м/с)");
            double angle = InputDouble("Введите угол (градусы)");
            
            DrawTrajectorySimple(v0, angle);
        }
        else if (choice == 3) {
            velocities = InputVelocities();
            velocities_initialized = true;
        }
    }
}