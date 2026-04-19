#pragma once
#include <curses.h>
#include <cstring>
#include <string>
#include "../../../Error.hpp"

using namespace std;

void DrawBorder(){
    for (int i = 0;i < COLS; i++ ){
        mvaddch(0, i, '=');
        mvaddch(LINES - 1, i, '=');
    }
    for ( int i = 0; i < LINES; i ++){
        mvaddch(i, 0, '|');
        mvaddch(i, COLS - 1, '|');
    }
}

void  ClearMessageLine(){
    mvprintw(LINES - 2, 2, "%-88s", "");
    refresh();
}

void ShowMessage(const string& msg, bool isError = false) {
    if (isError) {
        attron(A_REVERSE);
    }
    mvprintw(LINES - 2, 2, "%.*s", COLS - 5, msg.c_str());
    if (isError) {
        attroff(A_REVERSE);
    }
    mvprintw(LINES - 1, 2, "Нажмите любую клавишу...");
    refresh();
    getch();
    
    mvprintw(LINES - 2, 2, "%-80s", "");
    mvprintw(LINES - 1, 2, "%-80s", "");
    refresh();
}

int InputNumber(const string& prompt){
    echo();
    curs_set(1);

    int number = 0;
    int pos = 0;

    mvprintw(LINES - 5, 2, "%s: ", prompt.c_str());
    mvprintw(LINES - 4, 2, "-> ");
    refresh();

    while (true) {
        int ch = getch();
        
        if (ch == '\n') {
            break;
        }
        
        if (ch >= '0' && ch <= '9') {
            if (number > 214748364) {
                continue;
            }
            number = number * 10 + (ch - '0');
            mvprintw(LINES - 4, 5, "%d", number);
            refresh();
        }
    }
    
    noecho();
    curs_set(0);
    
    mvprintw(LINES - 5, 2, "%-*s", COLS - 4, "");
    mvprintw(LINES - 4, 2, "%-*s", COLS - 4, "");
    refresh();
    
    return number;
}

string InputString(const string& prompt) {
    echo();
    curs_set(1);
    
    string result;
    
    mvprintw(LINES - 5, 2, "%s: ", prompt.c_str());
    mvprintw(LINES - 4, 2, "-> ");
    refresh();
    
    while (true) {
        int ch = getch();
        if (ch == '\n') break;
        if (ch >= 32 && ch <= 126 && result.length() < 98) {
            result.push_back(static_cast<char>(ch));
            mvprintw(LINES - 4, 5, "%s", result.c_str());
            refresh();
        }
    }
    
    noecho();
    curs_set(0);
    
    for (int i = LINES - 6; i <= LINES - 3; ++i) {
        mvprintw(i, 0, "%-*s", COLS, "");
    }
    refresh();
    
    return result;
}

double InputDouble(const string& prompt) {
    echo();
    curs_set(1);
    
    double number;
    
    mvprintw(LINES - 5, 2, "%s: ", prompt.c_str());
    mvprintw(LINES - 4, 2, "-> ");
    refresh();
    
    scanw("%lf", &number);
    
    noecho();
    curs_set(0);
    
    for (int i = LINES - 6; i <= LINES - 3; i++) {
        mvprintw(i, 0, "%-*s", COLS, "");
    }
    refresh();
    
    return number;
}

int RunMenu(const string& title, const char* items[], int itemCount) {
    int selected = 0;
    int ch;
    
    while (true) {
        clear();
        DrawBorder();
        
        attron(A_BOLD);
        int titleX = (COLS - title.length()) / 2;
        if (titleX < 0) titleX = 0;
        mvprintw(1, titleX, "%s", title.c_str());
        attroff(A_BOLD);
        
        mvprintw(3, 2, "----------------------------------------");
        
        for (int i = 0; i < itemCount; i++) {
            if (i == selected) {
                attron(A_REVERSE | A_BOLD);
                mvprintw(5 + i, 4, " → %s", items[i]);
                attroff(A_REVERSE | A_BOLD);
            } else {
                mvprintw(5 + i, 4, "   %s", items[i]);
            }
        }
        
        mvprintw(LINES - 3, 2, "↑/↓ - перемещение | Enter - выбор | Q - выход");
        refresh();
        ch = getch();
        
        switch (ch) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = itemCount - 1;
                break;
                
            case KEY_DOWN:
                selected++;
                if (selected >= itemCount) selected = 0;
                break;
                
            case '\n':
                return selected;
                
            case 'q':
            case 'Q':
                return -1;
        }
    }
}


void ClearContentArea() {
    for (int i = 10; i < LINES - 5; i++) {
        mvprintw(i, 2, "%-80s", "");
    }
}

void DisplaySequence(const string& typeName, int size, const string& content) {
    clear();
    DrawBorder();
    
    mvprintw(2, 2, "=== %s ===", typeName.c_str());
    mvprintw(3, 2, "Размер: %d", size);
    mvprintw(4, 2, "Содержимое:");
    mvprintw(5, 4, "%s", content.c_str());
    
    mvprintw(LINES - 3, 2, "Нажмите любую клавишу для продолжения...");
    refresh();
    getch();
}

void DisplayMatrix(const string& name, size_t size, int (*getFunc)(size_t, size_t)) {
    clear();
    DrawBorder();
    
    mvprintw(2, 2, "=== %s ===", name.c_str());
    mvprintw(3, 2, "Размер: %zux%zu", size, size);
    
    for (size_t i = 0; i < size; i++) {
        mvprintw(5 + i, 4, "%d", getFunc(i, 0));
        for (size_t j = 1; j < size; j++) {
            mvprintw(5 + i, 4 + j * 8, "%d", getFunc(i, j));
        }
    }
    
    mvprintw(LINES - 3, 2, "Нажмите любую клавишу...");
    refresh();
    getch();
}