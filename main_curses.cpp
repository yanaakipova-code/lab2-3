#include <curses.h>
#include <string>
#include <sstream>
#include <windows.h> 
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include "MapReduce.hpp"

using namespace std;

ArraySequence<int>* g_array_seq = nullptr;
ListSequence<int>* g_list_seq = nullptr;
BitSequence* g_bit_seq = nullptr;
int g_current_type = 0;

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
     if (g_current_type == 0) {
        for (auto it = g_array_seq->begin(); it != g_array_seq->end(); ++it) {
            if (!first) result += ", ";
            result += to_string(*it);
            first = false;
        }
    }
    else if (g_current_type == 1) {
        for (auto it = g_list_seq->begin(); it != g_list_seq->end();++it) {
            if (!first) result += ", ";
            result += to_string(*it);
            first = false;
        }
    }
    else {
        for (auto it = g_bit_seq->begin(); it != g_bit_seq->end(); ++it) {
            if (!first) result += ", ";
    
            if (g_bit_seq->GetBit(*it)) {
                result += "1";
            } else {
                result += "0";
            }
            first = false;
        }
    }
    return result;
}

void DrawUI() {
    clear();
    mvprintw(1,0,"Type: %s", GetCurrentTypeName().c_str());
    mvprintw(2,0, "Length: %zu", GetCurrentLength());

    mvprintw(4, 0, "Contents: [%s]", GetContentsString().c_str());

    mvprintw(6, 0, "----------------------------------------");
    mvprintw(78, 0, "What my program can do:");
    mvprintw(9, 0, "1 - Array 2 - List 3 - Bit");
    mvprintw(10, 0, " A - Append P - Prepend  I - Insert");
    mvprintw(11, 0, "M - Map W - Where R - Reduce");
    mvprintw(12, 0, "C - Clear Q - Exit");
    mvprintw(13, 0, "----------------------------------------");
    refresh();
}

int square(int x) { return x * x; }
Bit invert(Bit b) { return !b; }
bool isEven(int x) { return x % 2 == 0; }
bool isOne(Bit b) { return b.GetValue(); }
int sum(int a, int b) { return a + b; }

// ========== EVENT HANDLERS ==========

void OnAppend() {
    mvprintw(15, 0, "Value: "); 
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
        mvprintw(16, 2, "successfully!");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(16, 2, "Error");
        refresh();
    }
    
    DrawUI();
}

void OnPrepend() {
    mvprintw(15, 0, "Enter value: ");
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
        mvprintw(15, 0, "Added to beginning!");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(15, 0, "Error");
    }
    refresh();
    getch();
    DrawUI();
}

void OnInsert() {
    mvprintw(15, 0, "Enter index: ");
    refresh();
    echo();
    int idx;
    scanw("%d", &idx);
    
    mvprintw(15, 0, "Enter value: ");
    refresh();
    int val;
    scanw("%d", &val);
    noecho();
    
    try {
        if (g_current_type == 0) g_array_seq->InsertAt(val, idx);
        else if (g_current_type == 1) g_list_seq->InsertAt(val, idx);
        else g_bit_seq->InsertAt(Bit(val != 0), idx);
        DrawUI();
        mvprintw(15, 0, "Inserted at position %d", idx);
    } catch (const exception& e) {
        DrawUI();
        mvprintw(15, 0, "Error");
    }
    refresh();//показываем строку на экране
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
            g_bit_seq = dynamic_cast<BitSequence*>(mapped);
        }
        DrawUI();
        mvprintw(15, 0, "MAP completed");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(15, 0, "Error");
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
            g_bit_seq = dynamic_cast<BitSequence*>(filtered);
        }
        DrawUI();
        mvprintw(15, 0, "WHERE completed");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(15, 0, "Error");
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
            ss <<   "Number of ones:" << count;
        }
        
        DrawUI();
        mvprintw(15, 0, "successfully");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(15,0 ,"successfully");
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
            g_bit_seq = new BitSequence(0);
        }
        DrawUI();
        mvprintw(15, 0, "Sequence cleared");
    } catch (const exception& e) {
        DrawUI();
        mvprintw(15, 0, "Error");
    }
    refresh();
    getch();
    DrawUI();
}

void OnSwitchType(int type) {
    g_current_type = type;
    DrawUI();
    mvprintw(18, 2, "Switched to %s", GetCurrentTypeName().c_str());
    refresh();
    getch();
    DrawUI();
}

int main() {
    
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    g_array_seq = new ArraySequence<int>();
    g_list_seq = new ListSequence<int>();
    g_bit_seq = new BitSequence(0);
    
    g_array_seq->Append(1);
    g_array_seq->Append(2);
    g_array_seq->Append(3);
    g_array_seq->Append(4);
    g_array_seq->Append(5);
    
    g_list_seq->Append(1);
    g_list_seq->Append(2);
    g_list_seq->Append(3);
    g_list_seq->Append(4);
    g_list_seq->Append(5);
    
    g_bit_seq->Append(Bit(1));
    g_bit_seq->Append(Bit(0));
    g_bit_seq->Append(Bit(1));
    g_bit_seq->Append(Bit(1));
    g_bit_seq->Append(Bit(0));
    
    DrawUI();
    mvprintw(15, 0, "select an option:");
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
                mvprintw(18, 2, "input error");
                refresh();
                getch();
                DrawUI();
                break;
        }
    }
    
    delete g_array_seq;
    delete g_list_seq;
    delete g_bit_seq;
    endwin();
    
    return 0;
}