#include <curses.h>
#include <locale.h>
#include "menu/Menu.hpp"
#include "menu/TypeSelector.hpp"
#include "menu/QueueMenu.hpp"
#include "menu/SetMenu.hpp"
#include "menu/MatrixMenu.hpp"
#include "Complex.hpp"
#include "Person.hpp"

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    const char* mainItems[] = {
        "Очередь",
        "Множество",
        "Матрица",
        "Выход"
    };
    
    while (true) {
        int choice = RunMenu("ЛАБОРАТОРНАЯ РАБОТА №3", mainItems, 4);
        
        if (choice == -1 || choice == 3) break;
        
        if (choice == 0) {
            int type = SelectType("очереди");
            if (type == TYPE_INT) QueueMenuWithType<int>("int");
            else if (type == TYPE_DOUBLE) QueueMenuWithType<double>("double");
            else if (type == TYPE_COMPLEX) QueueMenuWithType<Complex<double>>("Комплексные");
            else if (type == TYPE_PERSON) QueueMenuWithType<Person>("Персона");
        }
        else if (choice == 1) {
            int type = SelectType("множества");
            if (type == TYPE_INT) SetMenuWithType<int>("int");
            else if (type == TYPE_DOUBLE) SetMenuWithType<double>("double");
            else if (type == TYPE_COMPLEX) SetMenuWithType<Complex<double>>("Комплексные");
            else if (type == TYPE_PERSON) SetMenuWithType<Person>("Персона");
        }
        else if (choice == 2) {
            int type = SelectType("матрицы");
            if (type == TYPE_INT) MatrixMenuWithType<int>("int");
            else if (type == TYPE_DOUBLE) MatrixMenuWithType<double>("double");
            else if (type == TYPE_COMPLEX) {
                ShowMessage("Матрица для комплексных чисел пока не реализована", true);
            } else if (type == TYPE_PERSON) {
                ShowMessage("Матрица для персон пока не реализована", true);
            }
        }
    }
    
    endwin();
    return 0;
}