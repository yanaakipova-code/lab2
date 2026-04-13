#include "catch.hpp"
#include "../DynamicArray.hpp"
#include "../Error.hpp"

TEST_CASE("Динамический массив 1.1: конструктор по умолчанию"){
    DynamicArray<int> array;
    
    REQUIRE(array.GetSize() == 0);
}

TEST_CASE("Динамический массив 1.2: конструктор из массива"){
    int temp[] = {1, 2, 3, 4, 5};
    DynamicArray<int> array(temp, 5);
    
    REQUIRE(array.GetSize() == 5);
    REQUIRE(array.Get(0) == 1);
    REQUIRE(array.Get(2) == 3);
    REQUIRE(array.Get(4) == 5);
}

TEST_CASE("Динамический массив 1.3: конструктор с размером"){
    DynamicArray<int> array(5);
    
    REQUIRE(array.GetSize() == 5);
}

TEST_CASE("Динамический массив 1.4: конструктор копирования"){
    int temp[] = {10, 20, 30};
    DynamicArray<int> original(temp, 3);
    DynamicArray<int> copy(original);
    
    REQUIRE(copy.GetSize() == 3);
    REQUIRE(copy.Get(0) == 10);
    REQUIRE(copy.Get(1) == 20);
    REQUIRE(copy.Get(2) == 30);
}

TEST_CASE("Динамический массив 2.1: Get - корректный индекс"){
    int temp[] = {100, 200, 300};
    DynamicArray<int> array(temp, 3);
    
    REQUIRE(array.Get(0) == 100);
    REQUIRE(array.Get(1) == 200);
    REQUIRE(array.Get(2) == 300);
}

TEST_CASE("Динамический массив 2.2: Get - отрицательный индекс"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    // Исправлено: ожидаем OutOfRangeException, а не std::out_of_range
    REQUIRE_THROWS_AS(array.Get(-1), OutOfRangeException);
}

TEST_CASE("Динамический массив 2.3: Get - индекс за пределами"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    REQUIRE_THROWS_AS(array.Get(3), OutOfRangeException);
    REQUIRE_THROWS_AS(array.Get(100), OutOfRangeException);
}

TEST_CASE("Динамический массив 3.1: Set - корректный индекс"){
    int temp[] = {1, 2, 3, 4, 5};
    DynamicArray<int> array(temp, 5);
    
    array.Set(2, 100);
    
    REQUIRE(array.Get(2) == 100);
}

TEST_CASE("Динамический массив 3.2: Set - отрицательный индекс"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    REQUIRE_THROWS_AS(array.Set(-1, 100), OutOfRangeException);
}

TEST_CASE("Динамический массив 3.3: Set - исключение при неверном индексе"){
    int temp[] = {1, 2, 3, 4, 5};
    DynamicArray<int> array(temp, 5);
    
    REQUIRE_THROWS_AS(array.Set(5, 100), OutOfRangeException);
    REQUIRE_THROWS_AS(array.Set(10, 100), OutOfRangeException);
}

TEST_CASE("Динамический массив 4.1: Resize - увеличение размера"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    array.Resize(5);
    
    REQUIRE(array.GetSize() == 5);
    REQUIRE(array.Get(0) == 1);
    REQUIRE(array.Get(1) == 2);
    REQUIRE(array.Get(2) == 3);
}

TEST_CASE("Динамический массив 4.2: Resize - уменьшение размера"){
    int temp[] = {1, 2, 3, 4, 5};
    DynamicArray<int> array(temp, 5);
    
    array.Resize(3);
    
    REQUIRE(array.GetSize() == 3);
    REQUIRE(array.Get(0) == 1);
    REQUIRE(array.Get(1) == 2);
    REQUIRE(array.Get(2) == 3);
    REQUIRE_THROWS_AS(array.Get(3), OutOfRangeException);
}

TEST_CASE("Динамический массив 4.3: Resize - тот же размер"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    array.Resize(3);
    
    REQUIRE(array.GetSize() == 3);
    REQUIRE(array.Get(0) == 1);
    REQUIRE(array.Get(1) == 2);
    REQUIRE(array.Get(2) == 3);
}

TEST_CASE("Динамический массив 4.4: Resize - размер 0"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    array.Resize(0);
    
    REQUIRE(array.GetSize() == 0);
    REQUIRE_THROWS_AS(array.Get(0), OutOfRangeException);
}

TEST_CASE("Динамический массив 5.1: GetRef - получение ссылки"){
    int temp[] = {10, 20, 30};
    DynamicArray<int> array(temp, 3);
    
    int& ref = array.GetRef(1);
    ref = 200;
    
    REQUIRE(array.Get(1) == 200);
}

TEST_CASE("Динамический массив 5.2: GetRef - константная ссылка"){
    int temp[] = {10, 20, 30};
    const DynamicArray<int> array(temp, 3);
    
    const int& ref = array.GetRef(1);
    
    REQUIRE(ref == 20);
}

TEST_CASE("Динамический массив 5.3: GetRef - неверный индекс"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    REQUIRE_THROWS_AS(array.GetRef(3), OutOfRangeException);
}

TEST_CASE("Динамический массив 6.1: GetData - получение указателя"){
    int temp[] = {5, 6, 7, 8};
    DynamicArray<int> array(temp, 4);
    
    int* data = array.GetData();
    
    REQUIRE(data[0] == 5);
    REQUIRE(data[1] == 6);
    REQUIRE(data[2] == 7);
    REQUIRE(data[3] == 8);
}

TEST_CASE("Динамический массив 6.2: GetData - константный указатель"){
    int temp[] = {5, 6, 7, 8};
    const DynamicArray<int> array(temp, 4);
    
    const int* data = array.GetData();
    
    REQUIRE(data[0] == 5);
    REQUIRE(data[1] == 6);
    REQUIRE(data[2] == 7);
    REQUIRE(data[3] == 8);
}

TEST_CASE("Динамический массив 6.3: GetData - пустой массив"){
    DynamicArray<int> array;
    
    int* data = array.GetData();
    
    REQUIRE(data == nullptr);
}