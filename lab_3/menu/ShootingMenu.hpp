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


