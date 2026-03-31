#include <windows.h>
#include <string>
#include <sstream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "BitSequence.hpp"
#include "MapReduce.hpp"

using namespace std;

ArraySequence<int>* g_array_seq = nullptr;
ListSequence<int>* g_list_seq = nullptr;
BitSequence* g_bit_seq = nullptr;
size_t g_current_type = 0;

HWND g_h_Output = nullptr;  
HWND g_h_value_input = nullptr;
HWND g_h_index_input = nullptr;

string GetCurrentTypeName(){
    if(g_current_type == 0) return "ArraySequence";
    if (g_current_type == 1) return "ListSequence";
    return "BitSequence";
}

size_t GetCurrentLength(){
    if(g_current_type == 0) return g_array_seq->GetLength();
    if (g_current_type == 1) return g_list_seq->GetLength();
    return g_bit_seq->GetLength();
}

string GetContentsString() {
    string result = "";
    bool first = true;
    
    if (g_current_type == 0) {
        for (auto it = g_array_seq->begin(); !(it == g_array_seq->end()); ++it) {
            if (!first) result += ", ";
            result += to_string(*it);
            first = false;
        }
    }
    else if (g_current_type == 1) {
        for (auto it = g_list_seq->begin(); !(it == g_list_seq->end()); ++it) {
            if (!first) result += ", ";
            result += to_string(*it);
            first = false;
        }
    }
    else {
        for (auto it = g_bit_seq->begin(); !(it == g_bit_seq->end()); ++it) {
            if (!first) result += ", ";
            result += (it->GetValue() ? "1" : "0");
            first = false;
        }
    }
    
    return result;
}

int GetInputValue() {
    int len = GetWindowTextLengthA(g_h_value_input);
    if (len == 0) return 0;
    
    std::string buffer(len + 1, '\0');
    GetWindowTextA(g_h_value_input, &buffer[0], len + 1);
    return std::stoi(buffer);
}

int GetInputIndex() {
    int len = GetWindowTextLengthA(g_h_index_input);
    if (len == 0) return 0;
    
    std::string buffer(len + 1, '\0');
    GetWindowTextA(g_h_index_input, &buffer[0], len + 1);
    return std::stoi(buffer);
}

void UpdateDisplay() {
    string text = "";
    text += "====================================\n";
    text += "CURRENT: " + GetCurrentTypeName() + "\n";
    text += "Length: " + to_string(GetCurrentLength()) + "\n";
    text += "====================================\n";
    text += "CONTENTS:\n[" + GetContentsString() + "]\n";
    text += "====================================\n";
    
    SetWindowTextA(g_h_Output, text.c_str());
}

void OnAppend() {
    int val = GetInputValue();
    try {
        if (g_current_type == 0) g_array_seq->Append(val);
        else if (g_current_type == 1) g_list_seq->Append(val);
        else g_bit_seq->Append(Bit(val != 0));
        
        UpdateDisplay();
        SetWindowTextA(g_h_value_input, "");
    }catch (const exception& e) {
        MessageBoxA(NULL, e.what(), "Ошибка", MB_OK);
    }
}

void OnPrepend() {
    int val = GetInputValue();
    try {
        if (g_current_type == 0) g_array_seq->Prepend(val);
        else if (g_current_type == 1) g_list_seq->Prepend(val);
        else g_bit_seq->Prepend(Bit(val != 0));
        
        UpdateDisplay();
        SetWindowTextA(g_h_value_input, "");
    } catch (const exception& e) {
        MessageBoxA(NULL, e.what(), "Ошибка", MB_OK);
    }
}

void OnInsert() {
    int idx = GetInputIndex();
    int val = GetInputValue();
    try {
        if (g_current_type == 0) g_array_seq->InsertAt(val, idx);
        else if (g_current_type == 1) g_list_seq->InsertAt(val, idx);
        else g_bit_seq->InsertAt(Bit(val != 0), idx);
        
        UpdateDisplay();
        SetWindowTextA(g_h_value_input, "");
        SetWindowTextA(g_h_index_input, "");
    } catch (const exception& e) {
        MessageBoxA(NULL, e.what(), "Ошибка", MB_OK);
    }
}

int square(int x) {
    return x * x;
}
Bit invert(Bit b) {
    return !b; 
}

void OnMap() {
    try {
        if (g_current_type == 0) {
            delete g_array_seq;
            g_array_seq = dynamic_cast<ArraySequence<int>*>(g_array_seq->Map(square));
        }
        else if (g_current_type == 1) {
            delete g_list_seq;
            g_list_seq = dynamic_cast<ListSequence<int>*>(g_list_seq->Map(square));
        }
        else {
            delete g_bit_seq;
            auto* mapped = g_bit_seq->Map(invert); 
            g_bit_seq = dynamic_cast<BitSequence*>(mapped);
        }
        UpdateDisplay();
    } catch (const exception& e) {
        MessageBoxA(NULL, e.what(), "Ошибка", MB_OK);
    }
}

bool isEven(int x) {
    return x % 2 == 0;
}

bool isOne(Bit b) {
    return b.GetValue() == true;
}

void OnWhere() {
    try {
        if (g_current_type == 0) {
            delete g_array_seq;
            g_array_seq = dynamic_cast<ArraySequence<int>*>(g_array_seq->Where(isEven));
        }
        else if (g_current_type == 1) {
            delete g_list_seq;
            g_list_seq = dynamic_cast<ListSequence<int>*>(g_list_seq->Where(isEven));
        }
        else {
            delete g_bit_seq;
            auto* filtered = g_bit_seq->Where(isOne);
            g_bit_seq = dynamic_cast<BitSequence*>(filtered);
        }
        UpdateDisplay();
    } catch (const exception& e) {
        MessageBoxA(NULL, e.what(), "Ошибка", MB_OK);
    }
}

int sum(int a, int b) {
    return a + b;
}


void OnReduce() {
    try {
        stringstream ss;
        
        if (g_current_type == 0) {
            int result = g_array_seq->Reduce(sum, 0);
            ss << "REDUCE (сумма):\nResult: " << result;
        }
        else if (g_current_type == 1) {
            int result = g_list_seq->Reduce(sum, 0);
            ss << "REDUCE (сумма):\nResult: " << result;
        }
         else {
            size_t count = 0;
            for (size_t i = 0; i < g_bit_seq->GetLength(); i++) {
                if (g_bit_seq->GetBit(i)) count++;
            }
            ss << "REDUCE (кол-во единиц):\nResult: " << count;
        }
        
        SetWindowTextA(g_h_Output, ss.str().c_str());
    } catch (const exception& e) {
        MessageBoxA(NULL, e.what(), "Error", MB_OK);
    }
}