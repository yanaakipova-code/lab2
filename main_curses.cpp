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
int g_current_type = 0; // 0 - Array, 1 - List, 2 - Bit

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
    
    const size_t MAX_DISPLAY = 50;
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

int square(int x) { return x * x; }
bool isEven(int x) { return x % 2 == 0; }
int sum(int a, int b) { return a + b; }

bool InvertBit(bool b) { return !b; }
bool IsOne(bool b) { return b; }

void OnSwitchType(int type) {
    g_current_type = type;
}

void OnAppend() {
    int val;
    echo();
    mvprintw(14, 0, "Enter value: ");
    refresh();
    scanw("%d", &val);
    noecho();
    
    try {
        if (g_current_type == 0) {
            g_array_seq->Append(val);
        }
        else if (g_current_type == 1) {
            g_list_seq->Append(val);
        }
        else {
            g_bit_seq->Append(Bit<uint32_t>(val != 0));
        }
    } catch (const exception& e) {
        mvprintw(16, 0, "Error: %s", e.what());
        refresh();
        getch();
    }
}

void OnPrepend() {
    int val;
    echo();
    mvprintw(14, 0, "Enter value: ");
    refresh();
    scanw("%d", &val);
    noecho();
    
    try {
        if (g_current_type == 0) {
            g_array_seq->Prepend(val);
        }
        else if (g_current_type == 1) {
            g_list_seq->Prepend(val);
        }
        else {
            g_bit_seq->Prepend(Bit<uint32_t>(val != 0));
        }
    } catch (const exception& e) {
        mvprintw(16, 0, "Error: %s", e.what());
        refresh();
        getch();
    }
}

void OnInsert() {
    int pos, val;
    echo();
    mvprintw(14, 0, "Enter index (1-based): ");
    refresh();
    scanw("%d", &pos);
    mvprintw(14, 0, "Enter value: ");
    refresh();
    scanw("%d", &val);
    noecho();
    
    size_t idx = pos - 1;
    
    try {
        if (g_current_type == 0) {
            g_array_seq->InsertAt(val, idx);
        }
        else if (g_current_type == 1) {
            g_list_seq->InsertAt(val, idx);
        }
        else {
            g_bit_seq->InsertAt(Bit<uint32_t>(val != 0), idx);
        }
    } catch (const exception& e) {
        mvprintw(16, 0, "Error: %s", e.what());
        refresh();
        getch();
    }
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
            auto* mapped = g_bit_seq->Map([](Bit<uint32_t> b) {
                return Bit<uint32_t>(!b.GetBit(0));
            });
            delete g_bit_seq;
            g_bit_seq = dynamic_cast<BitSequence<uint32_t>*>(mapped);
        }
    } catch (const exception& e) {
        mvprintw(16, 0, "Error: %s", e.what());
        refresh();
        getch();
    }
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
            auto* filtered = g_bit_seq->Where([](Bit<uint32_t> b) {
                return b.GetBit(0);
            });
            delete g_bit_seq;
            g_bit_seq = dynamic_cast<BitSequence<uint32_t>*>(filtered);
        }
    } catch (const exception& e) {
        mvprintw(16, 0, "Error: %s", e.what());
        refresh();
        getch();
    }
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
        
        mvprintw(14, 0, "%s", ss.str().c_str());
        refresh();
        getch();
    } catch (const exception& e) {
        mvprintw(16, 0, "Error: %s", e.what());
        refresh();
        getch();
    }
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
    } catch (const exception& e) {
        mvprintw(16, 0, "Error: %s", e.what());
        refresh();
        getch();
    }
}

void DrawUI() {
    clear();
    
    attron(A_BOLD);
    mvprintw(0, 0, "=== SEQUENCE VISUALIZER ===");
    attroff(A_BOLD);
    
    mvprintw(2, 0, "Type: %s", GetCurrentTypeName().c_str());
    mvprintw(3, 0, "Size: %zu", GetCurrentLength());
    

    mvprintw(5, 0, "Contents: [%s]", GetContentsString().c_str());

    mvprintw(7, 0, "----------------------------------------");
    
    mvprintw(8, 0, "COMMANDS:");
    mvprintw(9, 0, "  1 - Array       2 - List       3 - Bit");
    mvprintw(10, 0, "  A - Append      P - Prepend    I - Insert");
    mvprintw(11, 0, "  M - Map         W - Where      R - Reduce");
    mvprintw(12, 0, "  C - Clear       Q - Exit");
    
    mvprintw(13, 0, "----------------------------------------");
    
    refresh();
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    g_array_seq = new ArraySequence<int>();
    g_list_seq = new ListSequence<int>();
    g_bit_seq = new BitSequence<uint32_t>(0);
    
    for (int i = 1; i <= 5; i++) {
        g_array_seq->Append(i);
        g_list_seq->Append(i * 10);
    }
    g_bit_seq->Append(Bit<uint32_t>(true));
    g_bit_seq->Append(Bit<uint32_t>(false));
    g_bit_seq->Append(Bit<uint32_t>(true));
    g_bit_seq->Append(Bit<uint32_t>(true));
    g_bit_seq->Append(Bit<uint32_t>(false));
    
    DrawUI();
    
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
                mvprintw(16, 0, "Unknown command. Press any key...");
                refresh();
                getch();
                break;
        }
        DrawUI();
    }
    
    delete g_array_seq;
    delete g_list_seq;
    delete g_bit_seq;
    endwin();
    
    return 0;
}