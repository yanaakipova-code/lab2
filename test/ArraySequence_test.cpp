#include "catch.hpp"
#include "../ArraySequence.hpp"
#include "../Error.hpp"

TEST_CASE("Динамическая последовательность 15.1: ArraySequence - конструктор по умолчанию"){
    ArraySequence<int> seq;
    
    REQUIRE(seq.GetLength() == 0);
    REQUIRE_THROWS_AS(seq.GetFirst(), OutOfRangeException);
    REQUIRE_THROWS_AS(seq.GetLast(), OutOfRangeException);
}

TEST_CASE("Динамическая последовательность 15.2: ArraySequence - конструктор из массива"){
    int temp[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(temp, 5);
    
    REQUIRE(seq.GetLength() == 5);
    REQUIRE(seq.GetFirst() == 1);
    REQUIRE(seq.GetLast() == 5);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(2) == 3);
    REQUIRE(seq.Get(4) == 5);
}

TEST_CASE("Динамическая последовательность 15.3: ArraySequence - конструктор копирования"){
    int temp[] = {10, 20, 30};
    ArraySequence<int> original(temp, 3);
    ArraySequence<int> copy(original);
    
    REQUIRE(copy.GetLength() == 3);
    REQUIRE(copy.Get(0) == 10);
    REQUIRE(copy.Get(1) == 20);
    REQUIRE(copy.Get(2) == 30);
    
    original.Set(0, 999);
    REQUIRE(copy.Get(0) == 10);
}

TEST_CASE("Динамическая последовательность 16.1: ArraySequence - GetFirst"){
    int temp[] = {5, 10, 15};
    ArraySequence<int> seq(temp, 3);
    
    REQUIRE(seq.GetFirst() == 5);
}

TEST_CASE("Динамическая последовательность 16.2: ArraySequence - GetFirst на пустой последовательности"){
    ArraySequence<int> seq;
    
    REQUIRE_THROWS_AS(seq.GetFirst(), OutOfRangeException);
}

TEST_CASE("Динамическая последовательность 16.3: ArraySequence - GetLast"){
    int temp[] = {5, 10, 15};
    ArraySequence<int> seq(temp, 3);
    
    REQUIRE(seq.GetLast() == 15);
}

TEST_CASE("Динамическая последовательность 16.4: ArraySequence - GetLast на пустой последовательности"){
    ArraySequence<int> seq;
    
    REQUIRE_THROWS_AS(seq.GetLast(), OutOfRangeException);
}

TEST_CASE("Динамическая последовательность 16.5: ArraySequence - Get по индексу"){
    int temp[] = {100, 200, 300, 400};
    ArraySequence<int> seq(temp, 4);
    
    REQUIRE(seq.Get(0) == 100);
    REQUIRE(seq.Get(1) == 200);
    REQUIRE(seq.Get(2) == 300);
    REQUIRE(seq.Get(3) == 400);
}

TEST_CASE("Динамическая последовательность 16.6: ArraySequence - Get с неверным индексом"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    REQUIRE_THROWS_AS(seq.Get(3), OutOfRangeException);
    REQUIRE_THROWS_AS(seq.Get(100), OutOfRangeException);
}

TEST_CASE("Динамическая последовательность 16.7: ArraySequence - GetLength"){
    int temp[] = {1, 2, 3, 4, 5, 6, 7};
    ArraySequence<int> seq(temp, 7);
    
    REQUIRE(seq.GetLength() == 7);
}

TEST_CASE("Динамическая последовательность 17.1: ArraySequence - Append"){
    ArraySequence<int> seq;
    
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

TEST_CASE("Динамическая последовательность 17.2: ArraySequence - Prepend"){
    ArraySequence<int> seq;
    
    seq.Append(20);
    seq.Append(30);
    seq.Prepend(10);
    
    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.GetFirst() == 10);
    REQUIRE(seq.Get(0) == 10);
    REQUIRE(seq.Get(1) == 20);
    REQUIRE(seq.Get(2) == 30);
}

TEST_CASE("Динамическая последовательность 17.3: ArraySequence - InsertAt в начало"){
    int temp[] = {2, 3, 4};
    ArraySequence<int> seq(temp, 3);
    
    seq.InsertAt(1, 0);
    
    REQUIRE(seq.GetLength() == 4);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(1) == 2);
    REQUIRE(seq.Get(2) == 3);
    REQUIRE(seq.Get(3) == 4);
}

TEST_CASE("Динамическая последовательность 17.4: ArraySequence - InsertAt в середину"){
    int temp[] = {1, 2, 4, 5};
    ArraySequence<int> seq(temp, 4);
    
    seq.InsertAt(3, 2);
    
    REQUIRE(seq.GetLength() == 5);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(1) == 2);
    REQUIRE(seq.Get(2) == 3);
    REQUIRE(seq.Get(3) == 4);
    REQUIRE(seq.Get(4) == 5);
}

TEST_CASE("Динамическая последовательность 17.5: ArraySequence - InsertAt в конец"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    seq.InsertAt(4, 3);
    
    REQUIRE(seq.GetLength() == 4);
    REQUIRE(seq.Get(3) == 4);
    REQUIRE(seq.GetLast() == 4);
}

TEST_CASE("Динамическая последовательность 17.6: ArraySequence - InsertAt с неверным индексом"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    REQUIRE_THROWS_AS(seq.InsertAt(99, 5), OutOfRangeException);
    REQUIRE_THROWS_AS(seq.InsertAt(99, 100), OutOfRangeException);
}

TEST_CASE("Динамическая последовательность 18.1: ArraySequence - Set"){
    int temp[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(temp, 5);
    
    seq.Set(2, 100);
    
    REQUIRE(seq.Get(2) == 100);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(1) == 2);
    REQUIRE(seq.Get(3) == 4);
    REQUIRE(seq.Get(4) == 5);
}

TEST_CASE("Динамическая последовательность 18.2: ArraySequence - Set с неверным индексом"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    REQUIRE_THROWS_AS(seq.Set(3, 100), OutOfRangeException);
    REQUIRE_THROWS_AS(seq.Set(100, 100), OutOfRangeException);
}

TEST_CASE("Динамическая последовательность 19.1: ArraySequence - GetSubsequence"){
    int temp[] = {10, 20, 30, 40, 50, 60};
    ArraySequence<int> seq(temp, 6);
    
    Sequence<int>* subseq = seq.GetSubsequence(1, 4);
    
    REQUIRE(subseq->GetLength() == 4);
    REQUIRE(subseq->Get(0) == 20);
    REQUIRE(subseq->Get(1) == 30);
    REQUIRE(subseq->Get(2) == 40);
    REQUIRE(subseq->Get(3) == 50);
    
    delete subseq;
}

TEST_CASE("Динамическая последовательность 19.2: ArraySequence - GetSubsequence из одного элемента"){
    int temp[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(temp, 5);
    
    Sequence<int>* subseq = seq.GetSubsequence(2, 2);
    
    REQUIRE(subseq->GetLength() == 1);
    REQUIRE(subseq->GetFirst() == 3);
    
    delete subseq;
}

TEST_CASE("Динамическая последовательность 19.3: ArraySequence - GetSubsequence с неверными индексами"){
    int temp[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(temp, 5);
    
    REQUIRE_THROWS_AS(seq.GetSubsequence(3, 1), InvalidArgumentException);
    REQUIRE_THROWS_AS(seq.GetSubsequence(0, 5), InvalidArgumentException);
    REQUIRE_THROWS_AS(seq.GetSubsequence(2, 10), InvalidArgumentException);
}

TEST_CASE("Динамическая последовательность 20.1: ArraySequence - Concat"){
    int temp1[] = {1, 2, 3};
    int temp2[] = {4, 5, 6};
    ArraySequence<int> seq1(temp1, 3);
    ArraySequence<int> seq2(temp2, 3);
    
    Sequence<int>* result = seq1.Concat(&seq2);
    
    REQUIRE(result->GetLength() == 6);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    REQUIRE(result->Get(3) == 4);
    REQUIRE(result->Get(4) == 5);
    REQUIRE(result->Get(5) == 6);
    
    delete result;
}

TEST_CASE("Динамическая последовательность 20.2: ArraySequence - Concat с пустой последовательностью"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq1(temp, 3);
    ArraySequence<int> seq2;
    
    Sequence<int>* result = seq1.Concat(&seq2);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    
    delete result;
}

TEST_CASE("Динамическая последовательность 21.1: ArraySequence - Map"){
    int temp[] = {1, 2, 3, 4};
    ArraySequence<int> seq(temp, 4);
    
    auto square = [](int x) { return x * x; };
    Sequence<int>* mapped = seq.Map(square);
    
    REQUIRE(mapped->GetLength() == 4);
    REQUIRE(mapped->Get(0) == 1);
    REQUIRE(mapped->Get(1) == 4);
    REQUIRE(mapped->Get(2) == 9);
    REQUIRE(mapped->Get(3) == 16);
    
    delete mapped;
}

TEST_CASE("Динамическая последовательность 21.2: ArraySequence - Map на пустой последовательности"){
    ArraySequence<int> seq;
    
    auto square = [](int x) { return x * x; };
    Sequence<int>* mapped = seq.Map(square);
    
    REQUIRE(mapped->GetLength() == 0);
    
    delete mapped;
}

TEST_CASE("Динамическая последовательность 22.1: ArraySequence - Where"){
    int temp[] = {1, 2, 3, 4, 5, 6};
    ArraySequence<int> seq(temp, 6);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    Sequence<int>* filtered = seq.Where(isEven);
    
    REQUIRE(filtered->GetLength() == 3);
    REQUIRE(filtered->Get(0) == 2);
    REQUIRE(filtered->Get(1) == 4);
    REQUIRE(filtered->Get(2) == 6);
    
    delete filtered;
}

TEST_CASE("Динамическая последовательность 22.2: ArraySequence - Where ничего не подходит"){
    int temp[] = {1, 3, 5, 7};
    ArraySequence<int> seq(temp, 4);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    Sequence<int>* filtered = seq.Where(isEven);
    
    REQUIRE(filtered->GetLength() == 0);
    
    delete filtered;
}

TEST_CASE("Динамическая последовательность 23.1: ArraySequence - Reduce"){
    int temp[] = {1, 2, 3, 4};
    ArraySequence<int> seq(temp, 4);
    
    auto sum = [](int a, int b) { return a + b; };
    int result = seq.Reduce(sum, 0);
    
    REQUIRE(result == 10);
}

TEST_CASE("Динамическая последовательность 23.2: ArraySequence - Reduce с умножением"){
    int temp[] = {1, 2, 3, 4};
    ArraySequence<int> seq(temp, 4);
    
    auto product = [](int a, int b) { return a * b; };
    int result = seq.Reduce(product, 1);
    
    REQUIRE(result == 24);
}

TEST_CASE("Динамическая последовательность 23.3: ArraySequence - Reduce на пустой последовательности"){
    ArraySequence<int> seq;
    
    auto sum = [](int a, int b) { return a + b; };
    int result = seq.Reduce(sum, 0);
    
    REQUIRE(result == 0);
}

TEST_CASE("Динамическая последовательность 24.1: ArraySequence - TryGetFirst без предиката"){
    int temp[] = {5, 10, 15, 20};
    ArraySequence<int> seq(temp, 4);
    
    Option<int> first = seq.TryGetFirst();
    
    REQUIRE(first.HasValue() == true);
    REQUIRE(first.GetValue() == 5);
}

TEST_CASE("Динамическая последовательность 24.2: ArraySequence - TryGetFirst с предикатом"){
    int temp[] = {5, 10, 15, 20};
    ArraySequence<int> seq(temp, 4);
    
    auto isGreaterThan10 = [](int x) { return x > 10; };
    Option<int> first = seq.TryGetFirst(isGreaterThan10);
    
    REQUIRE(first.HasValue() == true);
    REQUIRE(first.GetValue() == 15);
}

TEST_CASE("Динамическая последовательность 24.3: ArraySequence - TryGetFirst ничего не найдено"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    auto isNegative = [](int x) { return x < 0; };
    Option<int> first = seq.TryGetFirst(isNegative);
    
    REQUIRE(first.HasValue() == false);
    REQUIRE_THROWS_AS(first.GetValue(), std::runtime_error);
}

TEST_CASE("Динамическая последовательность 24.4: ArraySequence - TryGetLast без предиката"){
    int temp[] = {5, 10, 15, 20};
    ArraySequence<int> seq(temp, 4);
    
    Option<int> last = seq.TryGetLast();
    
    REQUIRE(last.HasValue() == true);
    REQUIRE(last.GetValue() == 20);
}

TEST_CASE("Динамическая последовательность 24.5: ArraySequence - TryGetLast с предикатом"){
    int temp[] = {5, 10, 15, 20};
    ArraySequence<int> seq(temp, 4);
    
    auto isLessThan15 = [](int x) { return x < 15; };
    Option<int> last = seq.TryGetLast(isLessThan15);
    
    REQUIRE(last.HasValue() == true);
    REQUIRE(last.GetValue() == 10);
}

TEST_CASE("Динамическая последовательность 25.1: ArraySequence - оператор []"){
    int temp[] = {10, 20, 30, 40};
    ArraySequence<int> seq(temp, 4);
    
    REQUIRE(seq[0] == 10);
    REQUIRE(seq[1] == 20);
    REQUIRE(seq[2] == 30);
    REQUIRE(seq[3] == 40);
}

TEST_CASE("Динамическая последовательность 25.2: ArraySequence - оператор [] изменение элемента"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    seq[1] = 100;
    
    REQUIRE(seq[1] == 100);
    REQUIRE(seq.Get(1) == 100);
}

TEST_CASE("Динамическая последовательность 25.3: ArraySequence - константный оператор []"){
    int temp[] = {5, 6, 7};
    ArraySequence<int> seq(temp, 3);
    const ArraySequence<int>& constSeq = seq;
    
    REQUIRE(constSeq[0] == 5);
    REQUIRE(constSeq[1] == 6);
    REQUIRE(constSeq[2] == 7);
}