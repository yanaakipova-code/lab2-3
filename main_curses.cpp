#include <curses.h>
#include <string>
#include <sstream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"

using namespace std;

ArraySequence<int>* g_array_seq = nullptr;
ListSequence<int>* g_list_seq = nullptr;
BitSequence<uint32_t>* g_bit_seq = nullptr;
int g_current_type = 0;

void DrawUI();
void OnAppend();
void OnPrepend();
void OnInsert();
void OnMap();
void OnWhere();
void OnReduce();
void OnClear();
void OnSwitchType(int type);
string GetCurrentTypeName();
size_t GetCurrentLength();

string GetCurrentTypeName() {
    if (g_current_type == 0) return "ArraySequence";
    if (g_current_type == 1) return "ListSequence";
    return "BitSequence";
}

size_t GetCurrentLength() {
    if (g_current_type == 0) return g_array_seq->GetLength();
    if (g_current_type == 1) return g_list_seq->GetLength();
    return g_bit_seq->GetLength();
}

string GetContentsString() {
    string result = "";
    bool first = true;
    size_t len = GetCurrentLength();
    
    // Ограничиваем вывод для больших последовательностей
    const size_t MAX_DISPLAY = 100;
    bool truncated = false;
    size_t display_len = len;
    
    if (len > MAX_DISPLAY) {
        display_len = MAX_DISPLAY;
        truncated = true;
    }
    
    if (g_current_type == 0) {
        for (size_t i = 0; i < display_len; i++) {
            if (!first) result += ", ";
            result += to_string(g_array_seq->Get(i));
            first = false;
        }
    }
    else if (g_current_type == 1) {
        for (size_t i = 0; i < display_len; i++) {
            if (!first) result += ", ";
            result += to_string(g_list_seq->Get(i));
            first = false;
        }
    }
    else {
        for (size_t i = 0; i < display_len; i++) {
            if (!first) result += ", ";
            result += g_bit_seq->GetBit(i) ? "1" : "0";
            first = false;
        }
    }
    
    if (truncated) {
        result += "... (total " + to_string(len) + " elements)";
    }
    
    return result;
}

void DrawUI() {
    clear();
    try {
        mvprintw(1, 0, "Type: %s", GetCurrentTypeName().c_str());
        mvprintw(2, 0, "Length: %zu", GetCurrentLength());
        mvprintw(4, 0, "Contents: [%s]", GetContentsString().c_str());
    } catch (const exception& e) {
        mvprintw(4, 0, "Contents: [ERROR: %s]", e.what());
    }
    mvprintw(6, 0, "----------------------------------------");
    mvprintw(7, 0, "COMMANDS:");
    mvprintw(8, 0,  "1 - Array     2 - List       3 - Bit");
    mvprintw(9, 0,  "A - Append    P - Prepend    I - Insert");
    mvprintw(10, 0, "M - Map       W - Where      R - Reduce");
    mvprintw(11, 0, "C - Clear     Q - Exit");
    mvprintw(12, 0, "----------------------------------------");
    refresh();
}

int square(int x) { return x * x; }
Bit invert(Bit b) { return !b; }
bool isEven(int x) { return x % 2 == 0; }
bool isOne(Bit b) { return b.GetValue(); }
int sum(int a, int b) { return a + b; }

void OnAppend() {
    mvprintw(14, 0, "Enter value: ");
    refresh();
    echo();
    int val;
    scanw("%d", &val);
    noecho();
    
    try {
        if (g_current_type == 0) g_array_seq->Append(val);
        else if (g_current_type == 1) g_list_seq->Append(val);
        else g_bit_seq->Append(Bit(val != 0));
        
        DrawUI();
        mvprintw(14, 0, "Added successfully");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(14, 0, "Error: %s", e.what());
    }
    refresh();
    getch();
    DrawUI();
}

void OnPrepend() {
    mvprintw(14, 0, "Enter value: ");
    refresh();
    echo();
    int val;
    scanw("%d", &val);
    noecho();
    
    try {
        if (g_current_type == 0) g_array_seq->Prepend(val);
        else if (g_current_type == 1) g_list_seq->Prepend(val);
        else g_bit_seq->Prepend(Bit(val != 0));
        
        DrawUI();
        mvprintw(14, 0, "Added to beginning");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(14, 0, "Error: %s", e.what());
    }
    refresh();
    getch();
    DrawUI();
}

void OnInsert() {
    mvprintw(14, 0, "Enter index (1-based): ");
    refresh();
    echo();
    int pos;
    scanw("%d", &pos);
    
    mvprintw(14, 0, "Enter value: ");
    refresh();
    int val;
    scanw("%d", &val);
    noecho();
    
    size_t idx = pos - 1;
    try {
        if (g_current_type == 0) g_array_seq->InsertAt(val, idx);
        else if (g_current_type == 1) g_list_seq->InsertAt(val, idx);
        else g_bit_seq->InsertAt(Bit(val != 0), idx);
        
        DrawUI();
        mvprintw(14, 0, "Inserted at position %zu", idx + 1);
    } catch (const exception& e) {
        DrawUI();
        mvprintw(14, 0, "Error: %s", e.what());
    }
    refresh();
    getch();
    DrawUI();
}

void OnMap() {
    try {
        if (g_current_type == 0) {
            auto* mapped = g_array_seq->Map(square);
            delete g_array_seq;
            g_array_seq = dynamic_cast<ArraySequence<int>*>(mapped);
        }
        else if (g_current_type == 1) {
            auto* mapped = g_list_seq->Map(square);
            delete g_list_seq;
            g_list_seq = dynamic_cast<ListSequence<int>*>(mapped);
        }
        else {
            auto* mapped = g_bit_seq->Map(invert);
            delete g_bit_seq;
            g_bit_seq = dynamic_cast<BitSequence<uint32_t>*>(mapped);
        }
        DrawUI();
        mvprintw(14, 0, "Map completed");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(14, 0, "Error: %s", e.what());
    }
    refresh();
    getch();
    DrawUI();
}

void OnWhere() {
    try {
        if (g_current_type == 0) {
            auto* filtered = g_array_seq->Where(isEven);
            delete g_array_seq;
            g_array_seq = dynamic_cast<ArraySequence<int>*>(filtered);
        }
        else if (g_current_type == 1) {
            auto* filtered = g_list_seq->Where(isEven);
            delete g_list_seq;
            g_list_seq = dynamic_cast<ListSequence<int>*>(filtered);
        }
        else {
            auto* filtered = g_bit_seq->Where(isOne);
            delete g_bit_seq;
            g_bit_seq = dynamic_cast<BitSequence<uint32_t>*>(filtered);
        }
        DrawUI();
        mvprintw(14, 0, "Where completed");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(14, 0, "Error: %s", e.what());
    }
    refresh();
    getch();
    DrawUI();
}

void OnReduce() {
    try {
        stringstream ss;
        
        if (g_current_type == 0) {
            int result = g_array_seq->Reduce(sum, 0);
            ss << "Sum: " << result;
        }
        else if (g_current_type == 1) {
            int result = g_list_seq->Reduce(sum, 0);
            ss << "Sum: " << result;
        }
        else {
            size_t count = 0;
            for (size_t i = 0; i < g_bit_seq->GetLength(); i++) {
                if (g_bit_seq->GetBit(i)) count++;
            }
            ss << "Number of ones: " << count;
        }
        
        DrawUI();
        mvprintw(14, 0, "%s", ss.str().c_str());
    } catch (const exception& e) {
        DrawUI();
        mvprintw(14, 0, "Error: %s", e.what());
    }
    refresh();
    getch();
    DrawUI();
}

void OnClear() {
    try {
        if (g_current_type == 0) {
            delete g_array_seq;
            g_array_seq = new ArraySequence<int>();
        }
        else if (g_current_type == 1) {
            delete g_list_seq;
            g_list_seq = new ListSequence<int>();
        }
        else {
            delete g_bit_seq;
            g_bit_seq = new BitSequence<uint32_t>(0);
        }
        DrawUI();
        mvprintw(14, 0, "Sequence cleared");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(14, 0, "Error: %s", e.what());
    }
    refresh();
    getch();
    DrawUI();
}

void OnSwitchType(int type) {
    g_current_type = type;
    DrawUI();
    mvprintw(14, 0, "Switched to %s", GetCurrentTypeName().c_str());
    refresh();
    getch();
    DrawUI();
}

int main() {
    // Инициализация curses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    // Инициализация последовательностей с начальными данными
    g_array_seq = new ArraySequence<int>();
    g_list_seq = new ListSequence<int>();
    g_bit_seq = new BitSequence<uint32_t>(0);
    
    // Добавляем начальные данные для демонстрации
    for (int i = 1; i <= 5; i++) {
        g_array_seq->Append(i);
        g_list_seq->Append(i * 10);
    }
    g_bit_seq->Append(Bit(true));
    g_bit_seq->Append(Bit(false));
    g_bit_seq->Append(Bit(true));
    g_bit_seq->Append(Bit(true));
    g_bit_seq->Append(Bit(false));
    
    DrawUI();
    mvprintw(14, 0, "Enter the command");
    refresh();
    
    int ch;
    while ((ch = getch()) != 'q' && ch != 'Q') {
        switch (ch) {
            case '1': OnSwitchType(0); break;
            case '2': OnSwitchType(1); break;
            case '3': OnSwitchType(2); break;
            case 'a': case 'A': OnAppend(); break;
            case 'p': case 'P': OnPrepend(); break;
            case 'i': case 'I': OnInsert(); break;
            case 'm': case 'M': OnMap(); break;
            case 'w': case 'W': OnWhere(); break;
            case 'r': case 'R': OnReduce(); break;
            case 'c': case 'C': OnClear(); break;
            default:
                mvprintw(16, 0, "Unknown command.");
                refresh();
                getch();
                DrawUI();
                break;
        }
    }
    
    // Очистка
    delete g_array_seq;
    delete g_list_seq;
    delete g_bit_seq;
    endwin();
    
    return 0;
}