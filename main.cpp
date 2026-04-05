#include <curses.h>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"

using namespace std;

ArraySequence<int>* g_array_seq = nullptr;
ListSequence<int>* g_list_seq = nullptr;
BitSequence* g_bit_seq = nullptr;
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
    
    g_bit_seq->Append(Bit(true));
    g_bit_seq->Append(Bit(false));
    g_bit_seq->Append(Bit(true));
    g_bit_seq->Append(Bit(true));
    g_bit_seq->Append(Bit(false));
    
    DrawUI();
    mvprintw(14, 0, "Press 1,2,3 to select type, A/P/I/M/W/R/C/Q to execute");
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

    delete g_array_seq;
    delete g_list_seq;
    delete g_bit_seq;
    endwin();
    
    return 0;
}