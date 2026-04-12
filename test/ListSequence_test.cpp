#include "catch.hpp"
#include "../ListSequence.hpp"
#include "../Error.hpp"

TEST_CASE("Списочная последовательность 1: конструктор по умолчанию"){
    ListSequence<int> seq;
    
    REQUIRE(seq.GetLength() == 0);
    REQUIRE_THROWS_AS(seq.GetFirst(), OutOfRangeException);
    REQUIRE_THROWS_AS(seq.GetLast(), EmptySequenceException);
}

TEST_CASE("Списочная последовательность 2: конструктор из массива"){
    int temp[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(temp, 5);
    
    REQUIRE(seq.GetLength() == 5);
    REQUIRE(seq.GetFirst() == 1);
    REQUIRE(seq.GetLast() == 5);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(2) == 3);
    REQUIRE(seq.Get(4) == 5);
}

TEST_CASE("Списочная последовательность 3: конструктор копирования"){
    int temp[] = {10, 20, 30};
    ListSequence<int> original(temp, 3);
    ListSequence<int> copy(original);
    
    REQUIRE(copy.GetLength() == 3);
    REQUIRE(copy.Get(0) == 10);
    REQUIRE(copy.Get(1) == 20);
    REQUIRE(copy.Get(2) == 30);
}

TEST_CASE("Списочная последовательность 4: Append"){
    ListSequence<int> seq;
    
    seq.Append(10);
    seq.Append(20);
    seq.Append(30);
    
    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.GetFirst() == 10);
    REQUIRE(seq.GetLast() == 30);
    REQUIRE(seq.Get(0) == 10);
    REQUIRE(seq.Get(1) == 20);
    REQUIRE(seq.Get(2) == 30);
}

TEST_CASE("Списочная последовательность 5: Prepend"){
    ListSequence<int> seq;
    
    seq.Append(20);
    seq.Append(30);
    seq.Prepend(10);
    
    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.GetFirst() == 10);
    REQUIRE(seq.Get(0) == 10);
    REQUIRE(seq.Get(1) == 20);
    REQUIRE(seq.Get(2) == 30);
}

TEST_CASE("Списочная последовательность 6: InsertAt"){
    int temp[] = {1, 2, 4, 5};
    ListSequence<int> seq(temp, 4);
    
    seq.InsertAt(3, 2);
    
    REQUIRE(seq.GetLength() == 5);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(1) == 2);
    REQUIRE(seq.Get(2) == 3);
    REQUIRE(seq.Get(3) == 4);
    REQUIRE(seq.Get(4) == 5);
}

TEST_CASE("Списочная последовательность 7: Map"){
    int temp[] = {1, 2, 3, 4};
    ListSequence<int> seq(temp, 4);
    
    auto square = [](int x) { return x * x; };
    Sequence<int>* mapped = seq.Map(square);
    
    REQUIRE(mapped->GetLength() == 4);
    REQUIRE(mapped->Get(0) == 1);
    REQUIRE(mapped->Get(1) == 4);
    REQUIRE(mapped->Get(2) == 9);
    REQUIRE(mapped->Get(3) == 16);
    
    delete mapped;
}

TEST_CASE("Списочная последовательность 8: Where"){
    int temp[] = {1, 2, 3, 4, 5, 6};
    ListSequence<int> seq(temp, 6);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    Sequence<int>* filtered = seq.Where(isEven);
    
    REQUIRE(filtered->GetLength() == 3);
    REQUIRE(filtered->Get(0) == 2);
    REQUIRE(filtered->Get(1) == 4);
    REQUIRE(filtered->Get(2) == 6);
    
    delete filtered;
}

TEST_CASE("Списочная последовательность 9: Reduce"){
    int temp[] = {1, 2, 3, 4};
    ListSequence<int> seq(temp, 4);
    
    auto sum = [](int a, int b) { return a + b; };
    int result = seq.Reduce(sum, 0);
    
    REQUIRE(result == 10);
}

TEST_CASE("Списочная последовательность 10: оператор []"){
    int temp[] = {10, 20, 30, 40};
    ListSequence<int> seq(temp, 4);
    
    REQUIRE(seq[0] == 10);
    REQUIRE(seq[1] == 20);
    REQUIRE(seq[2] == 30);
    REQUIRE(seq[3] == 40);
}

TEST_CASE("Списочная последовательность 11: оператор [] изменение элемента"){
    int temp[] = {1, 2, 3};
    ListSequence<int> seq(temp, 3);
    
    seq[1] = 100;
    
    REQUIRE(seq[1] == 100);
    REQUIRE(seq.Get(1) == 100);
}