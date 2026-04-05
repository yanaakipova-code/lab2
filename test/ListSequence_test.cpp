#include "catch.hpp"
#include "../ListSequence.hpp"

TEST_CASE("Связная последовательность 40.1: ListSequence - конструктор по умолчанию"){
    ListSequence<int> seq;
    
    REQUIRE(seq.GetLength() == 0);
    REQUIRE_THROWS_AS(seq.GetFirst(), std::out_of_range);
    REQUIRE_THROWS_AS(seq.GetLast(), std::out_of_range);
}

TEST_CASE("Связная последовательность 40.2: ListSequence - конструктор из массива"){
    int temp[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(temp, 5);
    
    REQUIRE(seq.GetLength() == 5);
    REQUIRE(seq.GetFirst() == 1);
    REQUIRE(seq.GetLast() == 5);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(2) == 3);
    REQUIRE(seq.Get(4) == 5);
}

TEST_CASE("Связная последовательность 40.3: ListSequence - конструктор копирования"){
    int temp[] = {10, 20, 30};
    ListSequence<int> original(temp, 3);
    ListSequence<int> copy(original);
    
    REQUIRE(copy.GetLength() == 3);
    REQUIRE(copy.Get(0) == 10);
    REQUIRE(copy.Get(1) == 20);
    REQUIRE(copy.Get(2) == 30);
}

TEST_CASE("Связная последовательность 41.1: ListSequence - GetFirst"){
    int temp[] = {5, 10, 15};
    ListSequence<int> seq(temp, 3);
    
    REQUIRE(seq.GetFirst() == 5);
}

TEST_CASE("Связная последовательность 41.2: ListSequence - GetFirst на пустой последовательности"){
    ListSequence<int> seq;
    
    REQUIRE_THROWS_AS(seq.GetFirst(), std::out_of_range);
}

TEST_CASE("Связная последовательность 41.3: ListSequence - GetLast"){
    int temp[] = {5, 10, 15};
    ListSequence<int> seq(temp, 3);
    
    REQUIRE(seq.GetLast() == 15);
}

TEST_CASE("Связная последовательность 41.4: ListSequence - GetLast на пустой последовательности"){
    ListSequence<int> seq;
    
    REQUIRE_THROWS_AS(seq.GetLast(), std::out_of_range);
}

TEST_CASE("Связная последовательность 41.5: ListSequence - Get по индексу"){
    int temp[] = {100, 200, 300, 400};
    ListSequence<int> seq(temp, 4);
    
    REQUIRE(seq.Get(0) == 100);
    REQUIRE(seq.Get(1) == 200);
    REQUIRE(seq.Get(2) == 300);
    REQUIRE(seq.Get(3) == 400);
}

TEST_CASE("Связная последовательность 41.6: ListSequence - Get с неверным индексом"){
    int temp[] = {1, 2, 3};
    ListSequence<int> seq(temp, 3);
    
    REQUIRE_THROWS_AS(seq.Get(3), std::out_of_range);
    REQUIRE_THROWS_AS(seq.Get(100), std::out_of_range);
    REQUIRE_THROWS_AS(seq.Get(-1), std::out_of_range);
}

TEST_CASE("Связная последовательность 41.7: ListSequence - GetLength"){
    int temp[] = {1, 2, 3, 4, 5, 6, 7};
    ListSequence<int> seq(temp, 7);
    
    REQUIRE(seq.GetLength() == 7);
}

TEST_CASE("Связная последовательность 42.1: ListSequence - Append"){
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

TEST_CASE("Связная последовательность 42.2: ListSequence - Prepend"){
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

TEST_CASE("Связная последовательность 42.3: ListSequence - InsertAt в начало"){
    int temp[] = {2, 3, 4};
    ListSequence<int> seq(temp, 3);
    
    seq.InsertAt(1, 0);
    
    REQUIRE(seq.GetLength() == 4);
    REQUIRE(seq.Get(0) == 1);
    REQUIRE(seq.Get(1) == 2);
    REQUIRE(seq.Get(2) == 3);
    REQUIRE(seq.Get(3) == 4);
}

TEST_CASE("Связная последовательность 42.4: ListSequence - InsertAt в середину"){
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

TEST_CASE("Связная последовательность 42.5: ListSequence - InsertAt в конец"){
    int temp[] = {1, 2, 3};
    ListSequence<int> seq(temp, 3);
    
    seq.InsertAt(4, 3);
    
    REQUIRE(seq.GetLength() == 4);
    REQUIRE(seq.Get(3) == 4);
    REQUIRE(seq.GetLast() == 4);
}

TEST_CASE("Связная последовательность 42.6: ListSequence - InsertAt с неверным индексом"){
    int temp[] = {1, 2, 3};
    ListSequence<int> seq(temp, 3);
    
    REQUIRE_THROWS_AS(seq.InsertAt(99, 5), std::out_of_range);
    REQUIRE_THROWS_AS(seq.InsertAt(99, 100), std::out_of_range);
}

TEST_CASE("Связная последовательность 44.1: ListSequence - GetSubsequence"){
    int temp[] = {10, 20, 30, 40, 50, 60};
    ListSequence<int> seq(temp, 6);
    
    Sequence<int>* subseq = seq.GetSubsequence(1, 4);
    
    REQUIRE(subseq->GetLength() == 4);
    REQUIRE(subseq->Get(0) == 20);
    REQUIRE(subseq->Get(1) == 30);
    REQUIRE(subseq->Get(2) == 40);
    REQUIRE(subseq->Get(3) == 50);
    
    delete subseq;
}

TEST_CASE("Связная последовательность 44.2: ListSequence - GetSubsequence из одного элемента"){
    int temp[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(temp, 5);
    
    Sequence<int>* subseq = seq.GetSubsequence(2, 2);
    
    REQUIRE(subseq->GetLength() == 1);
    REQUIRE(subseq->GetFirst() == 3);
    
    delete subseq;
}

TEST_CASE("Связная последовательность 44.3: ListSequence - GetSubsequence с неверными индексами"){
    int temp[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(temp, 5);
    
    REQUIRE_THROWS_AS(seq.GetSubsequence(3, 1), std::out_of_range);
    REQUIRE_THROWS_AS(seq.GetSubsequence(0, 5), std::out_of_range);
    REQUIRE_THROWS_AS(seq.GetSubsequence(2, 10), std::out_of_range);
}

TEST_CASE("Связная последовательность 45.1: ListSequence - Concat"){
    int temp1[] = {1, 2, 3};
    int temp2[] = {4, 5, 6};
    ListSequence<int> seq1(temp1, 3);
    ListSequence<int> seq2(temp2, 3);
    
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

TEST_CASE("Связная последовательность 45.2: ListSequence - Concat с пустой последовательностью"){
    int temp[] = {1, 2, 3};
    ListSequence<int> seq1(temp, 3);
    ListSequence<int> seq2;
    
    Sequence<int>* result = seq1.Concat(&seq2);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    
    delete result;
}

TEST_CASE("Связная последовательность 46.1: ListSequence - Map"){
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

TEST_CASE("Связная последовательность 46.2: ListSequence - Map на пустой последовательности"){
    ListSequence<int> seq;
    
    auto square = [](int x) { return x * x; };
    Sequence<int>* mapped = seq.Map(square);
    
    REQUIRE(mapped->GetLength() == 0);
    
    delete mapped;
}

TEST_CASE("Связная последовательность 47.1: ListSequence - Where"){
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

TEST_CASE("Связная последовательность 47.2: ListSequence - Where ничего не подходит"){
    int temp[] = {1, 3, 5, 7};
    ListSequence<int> seq(temp, 4);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    Sequence<int>* filtered = seq.Where(isEven);
    
    REQUIRE(filtered->GetLength() == 0);
    
    delete filtered;
}

TEST_CASE("Связная последовательность 48.1: ListSequence - Reduce"){
    int temp[] = {1, 2, 3, 4};
    ListSequence<int> seq(temp, 4);
    
    auto sum = [](int a, int b) { return a + b; };
    int result = seq.Reduce(sum, 0);
    
    REQUIRE(result == 10);
}

TEST_CASE("Связная последовательность 48.2: ListSequence - Reduce с умножением"){
    int temp[] = {1, 2, 3, 4};
    ListSequence<int> seq(temp, 4);
    
    auto product = [](int a, int b) { return a * b; };
    int result = seq.Reduce(product, 1);
    
    REQUIRE(result == 24);
}

TEST_CASE("Связная последовательность 48.3: ListSequence - Reduce на пустой последовательности"){
    ListSequence<int> seq;
    
    auto sum = [](int a, int b) { return a + b; };
    int result = seq.Reduce(sum, 0);
    
    REQUIRE(result == 0);
}

TEST_CASE("Связная последовательность 49.1: ListSequence - TryGetFirst без предиката"){
    int temp[] = {5, 10, 15, 20};
    ListSequence<int> seq(temp, 4);
    
    Option<int> first = seq.TryGetFirst();
    
    REQUIRE(first.HasValue() == true);
    REQUIRE(first.GetValue() == 5);
}

TEST_CASE("Связная последовательность 49.2: ListSequence - TryGetFirst с предикатом"){
    int temp[] = {5, 10, 15, 20};
    ListSequence<int> seq(temp, 4);
    
    auto isGreaterThan10 = [](int x) { return x > 10; };
    Option<int> first = seq.TryGetFirst(isGreaterThan10);
    
    REQUIRE(first.HasValue() == true);
    REQUIRE(first.GetValue() == 15);
}

TEST_CASE("Связная последовательность 49.3: ListSequence - TryGetFirst ничего не найдено"){
    int temp[] = {1, 2, 3};
    ListSequence<int> seq(temp, 3);
    
    auto isNegative = [](int x) { return x < 0; };
    Option<int> first = seq.TryGetFirst(isNegative);
    
    REQUIRE(first.HasValue() == false);
    REQUIRE_THROWS_AS(first.GetValue(), std::runtime_error);
}

TEST_CASE("Связная последовательность 49.4: ListSequence - TryGetLast без предиката"){
    int temp[] = {5, 10, 15, 20};
    ListSequence<int> seq(temp, 4);
    
    Option<int> last = seq.TryGetLast();
    
    REQUIRE(last.HasValue() == true);
    REQUIRE(last.GetValue() == 20);
}

TEST_CASE("Связная последовательность 49.5: ListSequence - TryGetLast с предикатом"){
    int temp[] = {5, 10, 15, 20};
    ListSequence<int> seq(temp, 4);
    
    auto isLessThan15 = [](int x) { return x < 15; };
    Option<int> last = seq.TryGetLast(isLessThan15);
    
    REQUIRE(last.HasValue() == true);
    REQUIRE(last.GetValue() == 10);
}

TEST_CASE("Связная последовательность 50.1: ListSequence - оператор []"){
    int temp[] = {10, 20, 30, 40};
    ListSequence<int> seq(temp, 4);
    
    REQUIRE(seq[0] == 10);
    REQUIRE(seq[1] == 20);
    REQUIRE(seq[2] == 30);
    REQUIRE(seq[3] == 40);
}

TEST_CASE("Связная последовательность 50.2: ListSequence - оператор [] изменение элемента"){
    int temp[] = {1, 2, 3};
    ListSequence<int> seq(temp, 3);
    
    seq[1] = 100;
    
    REQUIRE(seq[1] == 100);
    REQUIRE(seq.Get(1) == 100);
}

TEST_CASE("Связная последовательность 50.3: ListSequence - константный оператор []"){
    int temp[] = {5, 6, 7};
    ListSequence<int> seq(temp, 3);
    const ListSequence<int>& constSeq = seq;
    
    REQUIRE(constSeq[0] == 5);
    REQUIRE(constSeq[1] == 6);
    REQUIRE(constSeq[2] == 7);
}

TEST_CASE("Связная последовательность 51.1: ListSequence - итераторы range-based for"){
    int temp[] = {10, 20, 30, 40};
    ListSequence<int> seq(temp, 4);
    
    int expected[] = {10, 20, 30, 40};
    size_t i = 0;
    for (int val : seq) {
        REQUIRE(val == expected[i]);
        i++;
    }
    REQUIRE(i == 4);
}

TEST_CASE("Связная последовательность 51.2: ListSequence - итераторы явное использование"){
    int temp[] = {1, 2, 3, 4};
    ListSequence<int> seq(temp, 4);
    
    auto it = seq.begin();
    REQUIRE(*it == 1);
    ++it;
    REQUIRE(*it == 2);
    ++it;
    REQUIRE(*it == 3);
    ++it;
    REQUIRE(*it == 4);
    ++it;
    REQUIRE(it == seq.end());
}