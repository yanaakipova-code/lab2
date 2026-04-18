#include <curses.h>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#define BUTTON_COUNT 8


ArraySequence<int>* g_array_seq = nullptr;
ListSequence<int>* g_list_seq = nullptr;
BitSequence<uint8_t>* g_bit_seq = nullptr;
size_t type = 0;

int g_selected_button = 0;
int g_selected_menu = 0;
bool running = true;

const char* g_buttons[] = {"Append", "Prepend", "Insert", "Map", "Where", "Reduce", "Clear", "Exit"};
int g_selected_button = 0;

char g_value_str[20] = "0";
char g_index_str[20] = "1";
bool g_editingValue = true; 

std::string GetTypeName(){
    if (type == 0) return "ArraySequence";
    if (type == 1) return "ListSequence";
    else return "BitSequence";
}

size_t GetLenght(){
    if (type = 0) return g_array_seq->GetLength();
    if(type = 1) return g_list_seq->GetLength();
    else return g_bit_seq->GetLength();
}

std::string GetContents() {
    std::string result = "";
    size_t len = GetLenght();
    size_t maxShow = 20;
    
    if (len == 0) return "empty";
    
    if (type == 0) {
        for (size_t i = 0; i < len && i < maxShow; i++) {
            if (i > 0) result += ", ";
            result += std::to_string(g_array_seq->Get(i));
        }
    }
    else if (type == 1) {
        for (size_t i = 0; i < len && i < maxShow; i++) {
            if (i > 0) result += ", ";
            result += std::to_string(g_list_seq->Get(i));
        }
    }
    else {
        for (size_t i = 0; i < len && i < maxShow; i++) {
            if (i > 0) result += ", ";
            result += g_bit_seq->GetBit(i) ? "1" : "0";
        }
    }
    
    if (len > maxShow) result += "...";
    return result;
}

int square(int x) { return x * x; }
bool isEven(int x) { return x % 2 == 0; }
int sum(int a, int b) { return a + b; }

int GetValue() { return atoi(g_value_str); }
int GetIndex() { return atoi(g_index_str) - 1; }

void OnAppend() {
    int val = GetValue();
    if (type == 0) g_array_seq->Append(val);
    else if (type == 1) g_list_seq->Append(val);
    else g_bit_seq->Append(Bit<uint8_t>(val != 0));
}

void OnPrepend() {
    int val = GetValue();
    if (type == 0) g_array_seq->Prepend(val);
    else if (type == 1) g_list_seq->Prepend(val);
    else g_bit_seq->Prepend(Bit<uint8_t>(val != 0));
}

void OnInsert() {
    int val = GetValue();
    int idx = GetIndex();
    if (idx < 0) return;
    if (type == 0) g_array_seq->InsertAt(val, idx);
    else if (type == 1) g_list_seq->InsertAt(val, idx);
    else g_bit_seq->InsertAt(Bit<uint8_t>(val != 0), idx);
}

void OnMap() {
    if (type == 0) {
        auto* mapped = g_array_seq->Map(square);
        delete g_array_seq;
        g_array_seq = dynamic_cast<ArraySequence<int>*>(mapped);
    }
    else if (type == 1) {
        auto* mapped = g_list_seq->Map(square);
        delete g_list_seq;
        g_list_seq = dynamic_cast<ListSequence<int>*>(mapped);
    }
    else {
        auto* mapped = g_bit_seq->Map([](Bit<uint8_t> b) {
            return Bit<uint8_t>(!b.GetBit(0));
        });
        delete g_bit_seq;
        g_bit_seq = dynamic_cast<BitSequence<uint8_t>*>(mapped);
    }
}

void OnWhere() {
    if (type == 0) {
        auto* filtered = g_array_seq->Where(isEven);
        delete g_array_seq;
        g_array_seq = dynamic_cast<ArraySequence<int>*>(filtered);
    }
    else if (type == 1) {
        auto* filtered = g_list_seq->Where(isEven);
        delete g_list_seq;
        g_list_seq = dynamic_cast<ListSequence<int>*>(filtered);
    }
    else {
        auto* filtered = g_bit_seq->Where([](Bit<uint8_t> b) {
            return b.GetBit(0);
        });
        delete g_bit_seq;
        g_bit_seq = dynamic_cast<BitSequence<uint8_t>*>(filtered);
    }
}

void OnReduce() {
    std::stringstream ss;
    if (type == 0) {
        ss << "Sum = " << g_array_seq->Reduce(sum, 0);
    }
    else if (type == 1) {
        ss << "Sum = " << g_list_seq->Reduce(sum, 0);
    }
    else {
        int count = 0;
        for (size_t i = 0; i < g_bit_seq->GetLength(); i++) {
            if (g_bit_seq->GetBit(i)) count++;
        }
        ss << "Ones = " << count;
    }
    mvprintw(22, 2, "Result: %s", ss.str().c_str());
    refresh();
    napms(1500);
}

void OnClear() {
    if (type == 0) {
        delete g_array_seq;
        g_array_seq = new ArraySequence<int>();
    }
    else if (type == 1) {
        delete g_list_seq;
        g_list_seq = new ListSequence<int>();
    }
    else {
        delete g_bit_seq;
        g_bit_seq = new BitSequence<uint8_t>(0);
    }
}

void ExecuteButton() {
    switch (g_selected_button) {
        case 0: OnAppend(); break;
        case 1: OnPrepend(); break;
        case 2: OnInsert(); break;
        case 3: OnMap(); break;
        case 4: OnWhere(); break;
        case 5: OnReduce(); break;
        case 6: OnClear(); break;
        case 7: running = false; break;
    }
}

void DrawBorder() {
    for (int i = 0; i < COLS; i++) {
        mvaddch(0, i, '=');
        mvaddch(LINES - 1, i, '=');
    }
    for (int i = 0; i < LINES; i++) {
        mvaddch(i, 0, '|');
        mvaddch(i, COLS - 1, '|');
    }
}

void DrawTypeSelector() {
    mvprintw(3, 2, "Type: ");
    
    const char* types[] = {"Array", "List", "Bit"};
    for (int i = 0; i < 3; i++) {
        if (type == i) {
            attron(A_REVERSE);
            mvprintw(3, 10 + i * 8, " %s ", types[i]);
            attroff(A_REVERSE);
        } else {
            mvprintw(3, 10 + i * 8, " %s ", types[i]);
        }
    }
    mvprintw(4, 2, "Press 1, 2 or 3 to change type");
}


void DrawInfo() {
    mvprintw(6, 2, "Size: %zu", GetLenght());
    
    std::string content = GetContents();
    if (content.length() > COLS - 15) {
        content = content.substr(0, COLS - 18) + "...";
    }
    mvprintw(7, 2, "Contents: %s", content.c_str());
}

void DrawInputFields() {
    mvprintw(9, 2, "Value: ");
    if (g_editingValue) {
        attron(A_REVERSE);
    }
    mvprintw(9, 10, "%-10s", g_value_str);
    if (g_editingValue) {
        attroff(A_REVERSE);
    }
    
    mvprintw(10, 2, "Index (1-based): ");
    if (!g_editingValue) {
        attron(A_REVERSE);
    }
    mvprintw(10, 20, "%-10s", g_index_str);
    if (!g_editingValue) {
        attroff(A_REVERSE);
    }
    
    mvprintw(12, 2, "Tab - switch fields | Backspace - delete");
}
void DrawTypeSelector() {
    mvprintw(3, 2, "Type: ");
    
    const char* types[] = {"Array", "List", "Bit"};
    for (int i = 0; i < 3; i++) {
        if (type == i) {
            attron(A_REVERSE);
            mvprintw(3, 10 + i * 8, " %s ", types[i]);
            attroff(A_REVERSE);
        } else {
            mvprintw(3, 10 + i * 8, " %s ", types[i]);
        }
    }
    mvprintw(4, 2, "Press 1, 2 or 3 to change type");
}

void DrawInfo() {
    mvprintw(6, 2, "Size: %zu", GetLenght());
    
    std::string content = GetContents();
    if (content.length() > COLS - 15) {
        content = content.substr(0, COLS - 18) + "...";
    }
    mvprintw(7, 2, "Contents: %s", content.c_str());
}

void DrawInputFields() {
    mvprintw(9, 2, "Value: ");
    if (g_editingValue) {
        attron(A_REVERSE);
    }
    mvprintw(9, 10, "%-10s", g_value_str);
    if (g_editingValue) {
        attroff(A_REVERSE);
    }
    
    mvprintw(10, 2, "Index (1-based): ");
    if (!g_editingValue) {
        attron(A_REVERSE);
    }
    mvprintw(10, 20, "%-10s", g_index_str);
    if (!g_editingValue) {
        attroff(A_REVERSE);
    }
    
    mvprintw(12, 2, "Tab - switch fields | Backspace - delete");
}

void DrawButtons() {
    int startX = 2;
    int startY = 14;
    int button_width = 12;
    
    for (int i = 0; i < BUTTON_COUNT; i++) {
        int x = startX + (i % 4) * (button_width + 2);
        int y = startY + (i / 4) * 3;
        
        if (g_selected_button == i) {
            attron(A_REVERSE | A_BOLD);
            mvprintw(y, x, "[%s]", g_buttons[i]);
            attroff(A_REVERSE | A_BOLD);
        } else {
            mvprintw(y, x, " %s ", g_buttons[i]);
        }
    }
    
    mvprintw(startY + 8, 2, "Arrows - navigate | Enter - execute | Q - quit");
}
void ProcessTypeSelection(int ch) {
    if (ch == '1') type = 0;
    if (ch == '2') type = 1;
    if (ch == '3') type = 2;
}

void NavigateButtons(int ch) {
    switch (ch) {
        case KEY_LEFT:
            g_selected_button = (g_selected_button > 0) ? g_selected_button - 1 : 0;
            break;
        case KEY_RIGHT:
            g_selected_button = (g_selected_button < BUTTON_COUNT - 1) ? g_selected_button + 1 : BUTTON_COUNT - 1;
            break;
        case KEY_UP:
            g_selected_button = (g_selected_button >= 4) ? g_selected_button - 4 : g_selected_button;
            break;
        case KEY_DOWN:
            g_selected_button = (g_selected_button < BUTTON_COUNT - 4) ? g_selected_button + 4 : g_selected_button;
            break;
    }
}

void ProcessInputField(int ch) {
    if (ch == '\t') {
        g_editingValue = !g_editingValue;
    }
    else if (ch == KEY_BACKSPACE || ch == 127) {
        char* current = g_editingValue ? g_value_str : g_index_str;
        int len = strlen(current);
        if (len > 0) {
            current[len - 1] = '\0';
        }
        if (len == 1) {
            current[0] = '0';
        }
    }
    else if (ch >= '0' && ch <= '9') {
        char* current = g_editingValue ? g_value_str : g_index_str;
        int len = strlen(current);
        if (len < 10) {
            current[len] = ch;
            current[len + 1] = '\0';
        }
    }
}


void InitData() {
    g_array_seq = new ArraySequence<int>();
    g_list_seq = new ListSequence<int>();
    g_bit_seq = new BitSequence<uint8_t>(0);
    
    for (int i = 1; i <= 5; i++) {
        g_array_seq->Append(i);
        g_list_seq->Append(i * 10);
    }
    g_bit_seq->Append(Bit<uint8_t>(true));
    g_bit_seq->Append(Bit<uint8_t>(false));
    g_bit_seq->Append(Bit<uint8_t>(true));
    g_bit_seq->Append(Bit<uint8_t>(true));
    g_bit_seq->Append(Bit<uint8_t>(false));
}

void CleanupData() {
    delete g_array_seq;
    delete g_list_seq;
    delete g_bit_seq;
}

void InitCurses(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
}

void OutCurses(){
    endwin();
}


int main() {
    InitCurses();
    InitData();
    
    while (running) {
        
        
        int ch = getch();
        
        if (ch == 'q' || ch == 'Q') {
            running = false;
        }
        else if (ch >= '1' && ch <= '3') {
            ProcessTypeSelection(ch);
        }
        else if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN) {
            NavigateButtons(ch);
        }
        else if (ch == '\t' || ch == KEY_BACKSPACE || ch == 127 || (ch >= '0' && ch <= '9')) {
            ProcessInputField(ch);
        }
        else if (ch == '\n') {
            ExecuteButton();
        }
    }
    
    CleanupData();
    endwin();
    return 0;
}