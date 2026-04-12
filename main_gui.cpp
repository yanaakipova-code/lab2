#define WIN32_LEAN__AND_MEAN
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <string>
#include <sstream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"

using namespace std;

ArraySequence<int>* array_seq = nullptr;
ListSequence<int>* list_seq = nullptr;
BitSequence<uint32_t>* bit_seq = nullptr;
int current_type = 0;

HWND main_window = NULL;
HWND list_box = NULL;
HWND status_bar = NULL;
HWND input_value = NULL;
HWND input_index = NULL;

int get_size() {
    if (current_type == 0) return array_seq->GetLength();
    if (current_type == 1) return list_seq->GetLength();
    return bit_seq->GetLength();
}

int get_number_from_field(HWND field) {
    wchar_t text[20] = {0};
    GetWindowTextW(field, text, 20);
    return _wtoi(text);
}

void show_data() {
    SendMessageW(list_box, LB_RESETCONTENT, 0, 0);
    
    wchar_t title[100];
    if (current_type == 0) {
        swprintf(title, 100, L" ArraySequence | Размер: %d", get_size());
    } else if (current_type == 1) {
        swprintf(title, 100, L"ListSequence | Размер: %d", get_size());
    } else {
        swprintf(title, 100, L"BitSequence | Размер: %d", get_size());
    }
    SendMessageW(list_box, LB_ADDSTRING, 0, (LPARAM)title);
    
    for (int i = 0; i < get_size() && i < 30; i++) {
        wchar_t line[100];
        
        if (current_type == 0) {
            swprintf(line, 100, L"[%d] = %d", i, array_seq->Get(i));
        } 
        else if (current_type == 1) {
            swprintf(line, 100, L"[%d] = %d", i, list_seq->Get(i));
        } 
        else {
            Bit<uint32_t> bit = bit_seq->Get(i);
            char bit_char = bit.GetBit(0) ? '1' : '0';
            swprintf(line, 100, L"[%d] = %c", i, bit_char);
        }
        
        SendMessageW(list_box, LB_ADDSTRING, 0, (LPARAM)line);
    }
}

void choose_array() {
    current_type = 0;
    show_data();
}

void choose_list() {
    current_type = 1;
    show_data();
}

void choose_bit() {
    current_type = 2;
    show_data();
}

void append() {
    int value = get_number_from_field(input_value);
    
    if (current_type == 0) {
        array_seq->Append(value);
    }
    else if (current_type == 1) {
        list_seq->Append(value);
    }
    else {
        Bit<uint32_t> bit(value != 0);
        bit_seq->Append(bit);
    }
    
    show_data();
}

void prepend() {
    int value = get_number_from_field(input_value);
    
    if (current_type == 0) {
        array_seq->Prepend(value);
    }
    else if (current_type == 1) {
        list_seq->Prepend(value);
    }
    else {
        Bit<uint32_t> bit(value != 0);
        bit_seq->Prepend(bit);
    }
    
    show_data();
}

void insert() {
    int value = get_number_from_field(input_value);
    int index = get_number_from_field(input_index) - 1;
    
    if (index < 0) return;
    
    if (current_type == 0) {
        array_seq->InsertAt(value, index);
    }
    else if (current_type == 1) {
        list_seq->InsertAt(value, index);
    }
    else {
        Bit<uint32_t> bit(value != 0);
        bit_seq->InsertAt(bit, index);
    }
    
    show_data();
}

void map_operation() {
    if (current_type == 0) {
        Sequence<int>* result = array_seq->Map([](int x) { return x * x; });
        delete array_seq;
        array_seq = dynamic_cast<ArraySequence<int>*>(result);
    }
    else if (current_type == 1) {
        Sequence<int>* result = list_seq->Map([](int x) { return x * x; });
        delete list_seq;
        list_seq = dynamic_cast<ListSequence<int>*>(result);
    }
    else {
        Sequence<Bit<uint32_t>>* result = bit_seq->Map([](Bit<uint32_t> b) { 
            Bit<uint32_t> new_bit(b.GetBit(0) ? false : true);
            return new_bit;
        });
        delete bit_seq;
        bit_seq = dynamic_cast<BitSequence<uint32_t>*>(result);
    }
    show_data();
}

void where_operation() {
    if (current_type == 0) {
        Sequence<int>* result = array_seq->Where([](int x) { return x % 2 == 0; });
        delete array_seq;
        array_seq = dynamic_cast<ArraySequence<int>*>(result);
    }
    else if (current_type == 1) {
        Sequence<int>* result = list_seq->Where([](int x) { return x % 2 == 0; });
        delete list_seq;
        list_seq = dynamic_cast<ListSequence<int>*>(result);
    }
    else {
        Sequence<Bit<uint32_t>>* result = bit_seq->Where([](Bit<uint32_t> b) { 
            return b.GetBit(0); 
        });
        delete bit_seq;
        bit_seq = dynamic_cast<BitSequence<uint32_t>*>(result);
    }
    show_data();
}

void reduce_operation() {
    stringstream text;
    
    if (current_type == 0) {
        int total = array_seq->Reduce([](int a, int b) { return a + b; }, 0);
        text << "Сумма = " << total;
    }
    else if (current_type == 1) {
        int total = list_seq->Reduce([](int a, int b) { return a + b; }, 0);
        text << "Сумма = " << total;
    }
    else {
        int count = 0;
        for (size_t i = 0; i < bit_seq->GetLength(); i++) {
            Bit<uint32_t> bit = bit_seq->Get(i);
            if (bit.GetBit(0)) {
                count++;
            }
        }
        text << "Единиц = " << count;
    }
    
    SetWindowTextA(status_bar, text.str().c_str());
}

void clear_all() {
    if (current_type == 0) {
        delete array_seq;
        array_seq = new ArraySequence<int>();
    }
    else if (current_type == 1) {
        delete list_seq;
        list_seq = new ListSequence<int>();
    }
    else {
        delete bit_seq;
        bit_seq->Append(Bit<uint32_t>(false));
    }
    show_data();
}

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM w, LPARAM l) {
    switch (message) {
        case WM_CREATE: {
            list_box = CreateWindowW(L"LISTBOX", NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                10, 10, 350, 380, window, NULL, NULL, NULL);
            
            CreateWindowW(L"BUTTON", L"Dynamic", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                370, 10, 80, 35, window, (HMENU)1, NULL, NULL);
                
            CreateWindowW(L"BUTTON", L"List", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                460, 10, 80, 35, window, (HMENU)2, NULL, NULL);
                
            CreateWindowW(L"BUTTON", L"Bit", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                550, 10, 80, 35, window, (HMENU)3, NULL, NULL);
            
            CreateWindowW(L"STATIC", L"Значение:", 
                WS_CHILD | WS_VISIBLE, 370, 60, 60, 25, window, NULL, NULL, NULL);
            input_value = CreateWindowW(L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                440, 60, 100, 30, window, NULL, NULL, NULL);
            
            CreateWindowW(L"STATIC", L"Индекс:", 
                WS_CHILD | WS_VISIBLE, 370, 100, 50, 25, window, NULL, NULL, NULL);
            input_index = CreateWindowW(L"EDIT", L"1",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                430, 100, 110, 30, window, NULL, NULL, NULL);
            
            CreateWindowW(L"BUTTON", L"Append", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                370, 150, 130, 35, window, (HMENU)4, NULL, NULL);
                
            CreateWindowW(L"BUTTON", L"Prepend", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                510, 150, 130, 35, window, (HMENU)5, NULL, NULL);
                
            CreateWindowW(L"BUTTON", L"Insert", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                370, 200, 130, 35, window, (HMENU)6, NULL, NULL);
                
            CreateWindowW(L"BUTTON", L"Map(^2/inv))", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                510, 200, 130, 35, window, (HMENU)7, NULL, NULL);
                
            CreateWindowW(L"BUTTON", L"Where(%2=0/1)", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                370, 250, 270, 35, window, (HMENU)8, NULL, NULL);
                
            CreateWindowW(L"BUTTON", L"Reduce(sum)", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                370, 300, 130, 35, window, (HMENU)9, NULL, NULL);
                
            CreateWindowW(L"BUTTON", L"Clear", 
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                510, 300, 130, 35, window, (HMENU)10, NULL, NULL);
            
            status_bar = CreateWindowW(L"STATIC", L"Готово",
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_SUNKEN,
                10, 410, 640, 25, window, NULL, NULL, NULL);
            break;
        }
        
        case WM_COMMAND: {
            int button_id = LOWORD(w);
            
            if (button_id == 1) choose_array();
            if (button_id == 2) choose_list();
            if (button_id == 3) choose_bit();
            if (button_id == 4) append();
            if (button_id == 5) prepend();
            if (button_id == 6) insert();
            if (button_id == 7) map_operation();
            if (button_id == 8) where_operation();
            if (button_id == 9) reduce_operation();
            if (button_id == 10) clear_all();
            break;
        }
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(window, message, w, l);
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
    (void)prev;
    (void)cmd;
    
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = inst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"MyWindow";
    
    RegisterClassExW(&wc);
    
    main_window = CreateWindowExW(0, L"MyWindow", L"Визуализатор последовательностей",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 680, 480,
        NULL, NULL, inst, NULL);
    
    if (!main_window) return 1;
    
    array_seq = new ArraySequence<int>();
    list_seq = new ListSequence<int>();
    bit_seq = new BitSequence<uint32_t>(0);
    
    for (int i = 1; i <= 5; i++) {
        array_seq->Append(i);
        list_seq->Append(i * 10);
    }
    
    bit_seq->Append(Bit<uint32_t>(true));
    bit_seq->Append(Bit<uint32_t>(false));
    bit_seq->Append(Bit<uint32_t>(true));
    bit_seq->Append(Bit<uint32_t>(true));
    bit_seq->Append(Bit<uint32_t>(false));
    
    ShowWindow(main_window, show);
    show_data();
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    delete array_seq;
    delete list_seq;
    delete bit_seq;
    
    return 0;
}