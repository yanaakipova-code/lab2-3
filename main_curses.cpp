#include <curses.h>
#include <string>
#include <sstream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"

using namespace std;

extern ArraySequence<int>* g_array_seq;
extern ListSequence<int>* g_list_seq;
extern BitSequence* g_bit_seq;
extern int g_current_type;


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
        for (size_t i = 0; i < g_array_seq->GetLength(); i++) {
            if (!first) result += ", ";
            result += to_string(g_array_seq->Get(i));
            first = false;
        }
    }
    else if (g_current_type == 1) {
        for (size_t i = 0; i < g_list_seq->GetLength(); i++) {
            if (!first) result += ", ";
            result += to_string(g_list_seq->Get(i));
            first = false;
        }
    }
    else {
        for (size_t i = 0; i < g_bit_seq->GetLength(); i++) {
            if (!first) result += ", ";
            result += g_bit_seq->GetBit(i) ? "1" : "0";
            first = false;
        }
    }
    return result;
}

void DrawUI() {
    clear();
    mvprintw(1, 0, "Type: %s", GetCurrentTypeName().c_str());
    mvprintw(2, 0, "Length: %zu", GetCurrentLength());
    mvprintw(4, 0, "Contents: [%s]", GetContentsString().c_str());
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
        mvprintw(14, 0, "Inserted at position %zu", idx);
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
            g_bit_seq = dynamic_cast<BitSequence*>(mapped);
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
            g_bit_seq = dynamic_cast<BitSequence*>(filtered);
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
            g_bit_seq = new BitSequence(0);
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