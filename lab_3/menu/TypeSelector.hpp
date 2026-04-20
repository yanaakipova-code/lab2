#pragma once
#include "Menu.hpp"
#include "../Complex.hpp"
#include "../Person.hpp"

enum ElementType {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_COMPLEX,
    TYPE_PERSON,
    TYPE_PAIR
};

int SelectType(const string& context) {
    const char* typeItems[] = {
        "Целые числа (int)",
        "Вещественные числа (double)",
        "Комплексные числа (Complex)",
        "Персона (Person)",
        "Пары (Pair)",
        "← Назад"
    };
    return RunMenu(("Выберите тип для " + context).c_str(), typeItems, 6);
}