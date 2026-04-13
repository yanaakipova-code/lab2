#include "catch.hpp"
#include "../DynamicArray.hpp"
#include "../Error.hpp"

TEST_CASE("DynamicArray 1.1: конструктор по умолчанию"){
    DynamicArray<int> arr;
    
    REQUIRE(arr.GetSize() == 0);
}

TEST_CASE("DynamicArray 1.2: конструктор из массива"){
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr(items, 5);
    
    REQUIRE(arr.GetSize() == 5);
    REQUIRE(arr.Get(0) == 1);
    REQUIRE(arr.Get(2) == 3);
    REQUIRE(arr.Get(4) == 5);
}

TEST_CASE("DynamicArray 1.3: конструктор с размером"){
    DynamicArray<int> arr(10);
    
    REQUIRE(arr.GetSize() == 10);
}

TEST_CASE("DynamicArray 1.4: конструктор копирования"){
    int items[] = {10, 20, 30};
    DynamicArray<int> original(items, 3);
    DynamicArray<int> copy(original);
    
    REQUIRE(copy.GetSize() == 3);
    REQUIRE(copy.Get(0) == 10);
    REQUIRE(copy.Get(1) == 20);
    REQUIRE(copy.Get(2) == 30);
    
    original.Set(0, 999);
    REQUIRE(copy.Get(0) == 10);
}

TEST_CASE("DynamicArray 2.1: Get - корректный индекс"){
    int items[] = {100, 200, 300};
    DynamicArray<int> arr(items, 3);
    
    REQUIRE(arr.Get(0) == 100);
    REQUIRE(arr.Get(1) == 200);
    REQUIRE(arr.Get(2) == 300);
}

TEST_CASE("DynamicArray 2.2: Get - индекс за пределами"){
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    
    REQUIRE_THROWS_AS(arr.Get(3), OutOfRangeException);
    REQUIRE_THROWS_AS(arr.Get(100), OutOfRangeException);
}

TEST_CASE("DynamicArray 3.1: GetSize"){
    int items[] = {1, 2, 3, 4, 5, 6, 7};
    DynamicArray<int> arr(items, 7);
    
    REQUIRE(arr.GetSize() == 7);
}

TEST_CASE("DynamicArray 3.2: GetSize на пустом массиве"){
    DynamicArray<int> arr;
    
    REQUIRE(arr.GetSize() == 0);
}

TEST_CASE("DynamicArray 4.1: Set - корректный индекс"){
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr(items, 5);
    
    arr.Set(2, 100);
    
    REQUIRE(arr.Get(2) == 100);
    REQUIRE(arr.Get(0) == 1);
    REQUIRE(arr.Get(1) == 2);
    REQUIRE(arr.Get(3) == 4);
    REQUIRE(arr.Get(4) == 5);
}

TEST_CASE("DynamicArray 4.2: Set - индекс за пределами"){
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    
    REQUIRE_THROWS_AS(arr.Set(3, 100), OutOfRangeException);
    REQUIRE_THROWS_AS(arr.Set(100, 100), OutOfRangeException);
}

TEST_CASE("DynamicArray 5.1: Resize - увеличение размера"){
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    
    arr.Resize(5);
    
    REQUIRE(arr.GetSize() == 5);
    REQUIRE(arr.Get(0) == 1);
    REQUIRE(arr.Get(1) == 2);
    REQUIRE(arr.Get(2) == 3);
    // Новые элементы должны быть инициализированы значением по умолчанию
    REQUIRE(arr.Get(3) == 0);
    REQUIRE(arr.Get(4) == 0);
}

TEST_CASE("DynamicArray 5.2: Resize - уменьшение размера"){
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr(items, 5);
    
    arr.Resize(3);
    
    REQUIRE(arr.GetSize() == 3);
    REQUIRE(arr.Get(0) == 1);
    REQUIRE(arr.Get(1) == 2);
    REQUIRE(arr.Get(2) == 3);
    REQUIRE_THROWS_AS(arr.Get(3), OutOfRangeException);
}

TEST_CASE("DynamicArray 5.3: Resize - тот же размер"){
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    
    arr.Resize(3);
    
    REQUIRE(arr.GetSize() == 3);
    REQUIRE(arr.Get(0) == 1);
    REQUIRE(arr.Get(1) == 2);
    REQUIRE(arr.Get(2) == 3);
}

TEST_CASE("DynamicArray 5.4: Resize - размер 0"){
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    
    arr.Resize(0);
    
    REQUIRE(arr.GetSize() == 0);
    REQUIRE_THROWS_AS(arr.Get(0), OutOfRangeException);
}

TEST_CASE("DynamicArray 5.5: Resize - несколько раз"){
    DynamicArray<int> arr(2);
    arr.Set(0, 10);
    arr.Set(1, 20);
    
    arr.Resize(5);
    arr.Set(2, 30);
    arr.Set(3, 40);
    arr.Set(4, 50);
    
    arr.Resize(3);
    
    REQUIRE(arr.GetSize() == 3);
    REQUIRE(arr.Get(0) == 10);
    REQUIRE(arr.Get(1) == 20);
    REQUIRE(arr.Get(2) == 30);
}

TEST_CASE("DynamicArray 6.1: GetRef - получение ссылки"){
    int items[] = {10, 20, 30};
    DynamicArray<int> arr(items, 3);
    
    int& ref = arr.GetRef(1);
    ref = 200;
    
    REQUIRE(arr.Get(1) == 200);
}

TEST_CASE("DynamicArray 6.2: GetRef - константная ссылка"){
    int items[] = {10, 20, 30};
    const DynamicArray<int> arr(items, 3);
    
    const int& ref = arr.GetRef(1);
    
    REQUIRE(ref == 20);
}

TEST_CASE("DynamicArray 6.3: GetRef - неверный индекс"){
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    
    REQUIRE_THROWS_AS(arr.GetRef(3), OutOfRangeException);
    REQUIRE_THROWS_AS(arr.GetRef(100), OutOfRangeException);
}

TEST_CASE("DynamicArray 7.1: GetData - получение указателя"){
    int items[] = {5, 6, 7, 8};
    DynamicArray<int> arr(items, 4);
    
    int* data = arr.GetData();
    
    REQUIRE(data[0] == 5);
    REQUIRE(data[1] == 6);
    REQUIRE(data[2] == 7);
    REQUIRE(data[3] == 8);
    
    data[2] = 100;
    REQUIRE(arr.Get(2) == 100);
}

TEST_CASE("DynamicArray 7.2: GetData - константный указатель"){
    int items[] = {5, 6, 7, 8};
    const DynamicArray<int> arr(items, 4);
    
    const int* data = arr.GetData();
    
    REQUIRE(data[0] == 5);
    REQUIRE(data[1] == 6);
    REQUIRE(data[2] == 7);
    REQUIRE(data[3] == 8);
}

TEST_CASE("DynamicArray 7.3: GetData - пустой массив"){
    DynamicArray<int> arr;
    
    int* data = arr.GetData();
    
    REQUIRE(data == nullptr);
}

TEST_CASE("DynamicArray 8.1: работа с разными типами"){
    DynamicArray<double> arr(3);
    arr.Set(0, 1.5);
    arr.Set(1, 2.7);
    arr.Set(2, 3.14);
    
    REQUIRE(arr.Get(0) == 1.5);
    REQUIRE(arr.Get(1) == 2.7);
    REQUIRE(arr.Get(2) == 3.14);
}

TEST_CASE("DynamicArray 8.2: работа со строками"){
    DynamicArray<std::string> arr(3);
    arr.Set(0, "hello");
    arr.Set(1, "world");
    arr.Set(2, "test");
    
    REQUIRE(arr.Get(0) == "hello");
    REQUIRE(arr.Get(1) == "world");
    REQUIRE(arr.Get(2) == "test");
}

TEST_CASE("DynamicArray 9.1: множественные операции"){
    DynamicArray<int> arr(3);
    arr.Set(0, 1);
    arr.Set(1, 2);
    arr.Set(2, 3);
    
    arr.Resize(5);
    arr.Set(3, 4);
    arr.Set(4, 5);
    
    arr.Resize(2);
    
    REQUIRE(arr.GetSize() == 2);
    REQUIRE(arr.Get(0) == 1);
    REQUIRE(arr.Get(1) == 2);
    
    arr.Resize(4);
    arr.Set(2, 10);
    arr.Set(3, 20);
    
    REQUIRE(arr.Get(0) == 1);
    REQUIRE(arr.Get(1) == 2);
    REQUIRE(arr.Get(2) == 10);
    REQUIRE(arr.Get(3) == 20);
}

TEST_CASE("DynamicArray 9.2: копирование после изменений"){
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> original(items, 5);
    original.Set(2, 100);
    
    DynamicArray<int> copy(original);
    
    REQUIRE(copy.Get(0) == 1);
    REQUIRE(copy.Get(1) == 2);
    REQUIRE(copy.Get(2) == 100);
    REQUIRE(copy.Get(3) == 4);
    REQUIRE(copy.Get(4) == 5);
    
    original.Set(0, 999);
    REQUIRE(copy.Get(0) == 1);
}