#include "catch.hpp"
#include "../MapReduce.hpp"

int multiplyByIndexFunc(const int& x, size_t i) {
    return static_cast<int>(x * i);
}

std::string toStringFunc(const int& x, size_t i) {
    return std::to_string(x) + "_" + std::to_string(i);
}

int sumPairFunc(const std::pair<int, int>& p, size_t i) {
    return p.first + p.second;
}

TEST_CASE("MapReduce 52.1: MapWithIndex - преобразование с индексом"){
    int temp[] = {10, 20, 30, 40};
    ArraySequence<int> seq(temp, 4);
    
    Sequence<int>* result = MapWithIndex<int, int>(seq, multiplyByIndexFunc);
    
    REQUIRE(result->GetLength() == 4);
    REQUIRE(result->Get(0) == 0);
    REQUIRE(result->Get(1) == 20);
    REQUIRE(result->Get(2) == 60);
    REQUIRE(result->Get(3) == 120);
    
    delete result;
}

TEST_CASE("MapReduce 52.2: MapWithIndex - пустая последовательность"){
    ArraySequence<int> seq;
    
    Sequence<int>* result = MapWithIndex<int, int>(seq, multiplyByIndexFunc);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 52.3: MapWithIndex - преобразование типа"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<std::string>* result = MapWithIndex<int, std::string>(seq, toStringFunc);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == "1_0");
    REQUIRE(result->Get(1) == "2_1");
    REQUIRE(result->Get(2) == "3_2");
    
    delete result;
}

TEST_CASE("MapReduce 53.1: Skip - пропуск первых элементов"){
    int temp[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(temp, 5);
    
    Sequence<int>* result = Skip(seq, 2);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == 3);
    REQUIRE(result->Get(1) == 4);
    REQUIRE(result->Get(2) == 5);
    
    delete result;
}

TEST_CASE("MapReduce 53.2: Skip - пропуск всех элементов"){
    int temp[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(temp, 5);
    
    Sequence<int>* result = Skip(seq, 5);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 53.3: Skip - пропуск больше чем элементов"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<int>* result = Skip(seq, 10);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 53.4: Skip - пропуск 0 элементов"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<int>* result = Skip(seq, 0);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    
    delete result;
}

TEST_CASE("MapReduce 53.5: Skip - пустая последовательность"){
    ArraySequence<int> seq;
    
    Sequence<int>* result = Skip(seq, 5);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 54.1: Take - взять первые элементы"){
    int temp[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(temp, 5);
    
    Sequence<int>* result = Take(seq, 3);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    
    delete result;
}

TEST_CASE("MapReduce 54.2: Take - взять 0 элементов"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<int>* result = Take(seq, 0);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 54.3: Take - взять больше чем элементов"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<int>* result = Take(seq, 10);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    
    delete result;
}

TEST_CASE("MapReduce 54.4: Take - пустая последовательность"){
    ArraySequence<int> seq;
    
    Sequence<int>* result = Take(seq, 5);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 55.1: Zip - объединение двух последовательностей"){
    int temp1[] = {1, 2, 3, 4};
    int temp2[] = {10, 20, 30, 40};
    ArraySequence<int> seq1(temp1, 4);
    ArraySequence<int> seq2(temp2, 4);
    
    Sequence<std::pair<int, int>>* result = Zip(seq1, seq2);
    
    REQUIRE(result->GetLength() == 4);
    REQUIRE(result->Get(0).first == 1);
    REQUIRE(result->Get(0).second == 10);
    REQUIRE(result->Get(1).first == 2);
    REQUIRE(result->Get(1).second == 20);
    REQUIRE(result->Get(2).first == 3);
    REQUIRE(result->Get(2).second == 30);
    REQUIRE(result->Get(3).first == 4);
    REQUIRE(result->Get(3).second == 40);
    
    delete result;
}

TEST_CASE("MapReduce 55.2: Zip - разная длина (берётся минимальная)"){
    int temp1[] = {1, 2, 3, 4, 5};
    int temp2[] = {10, 20, 30};
    ArraySequence<int> seq1(temp1, 5);
    ArraySequence<int> seq2(temp2, 3);
    
    Sequence<std::pair<int, int>>* result = Zip(seq1, seq2);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0).first == 1);
    REQUIRE(result->Get(0).second == 10);
    REQUIRE(result->Get(1).first == 2);
    REQUIRE(result->Get(1).second == 20);
    REQUIRE(result->Get(2).first == 3);
    REQUIRE(result->Get(2).second == 30);
    
    delete result;
}

TEST_CASE("MapReduce 55.3: Zip - первая последовательность короче"){
    int temp1[] = {1, 2};
    int temp2[] = {10, 20, 30, 40};
    ArraySequence<int> seq1(temp1, 2);
    ArraySequence<int> seq2(temp2, 4);
    
    Sequence<std::pair<int, int>>* result = Zip(seq1, seq2);
    
    REQUIRE(result->GetLength() == 2);
    REQUIRE(result->Get(0).first == 1);
    REQUIRE(result->Get(0).second == 10);
    REQUIRE(result->Get(1).first == 2);
    REQUIRE(result->Get(1).second == 20);
    
    delete result;
}

TEST_CASE("MapReduce 55.4: Zip - пустые последовательности"){
    ArraySequence<int> seq1;
    ArraySequence<int> seq2;
    
    Sequence<std::pair<int, int>>* result = Zip(seq1, seq2);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 55.5: Zip - с разными типами"){
    int temp1[] = {1, 2, 3};
    std::string temp2[] = {"a", "b", "c"};
    ArraySequence<int> seq1(temp1, 3);
    ArraySequence<std::string> seq2(temp2, 3);
    
    Sequence<std::pair<int, std::string>>* result = Zip(seq1, seq2);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0).first == 1);
    REQUIRE(result->Get(0).second == "a");
    REQUIRE(result->Get(1).first == 2);
    REQUIRE(result->Get(1).second == "b");
    REQUIRE(result->Get(2).first == 3);
    REQUIRE(result->Get(2).second == "c");
    
    delete result;
}

// Вспомогательные функции для FlatMap
Sequence<int>* duplicateFunc(const int& x) {
    int arr[] = {x, x};
    return new ArraySequence<int>(arr, 2);
}

Sequence<int>* emptyFunc(const int& x) {
    return new ArraySequence<int>();
}

Sequence<int>* rangeFunc(const int& x) {
    int* arr = new int[x];
    for (int i = 0; i < x; i++) {
        arr[i] = i;
    }
    Sequence<int>* result = new ArraySequence<int>(arr, x);
    delete[] arr;
    return result;
}

Sequence<std::string>* toStringSeqFunc(const int& x) {
    std::string arr[] = {std::to_string(x), std::to_string(x * 2)};
    return new ArraySequence<std::string>(arr, 2);
}

TEST_CASE("MapReduce 56.1: FlatMap - преобразование каждого элемента в последовательность"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<int>* result = FlatMap<int, int>(seq, duplicateFunc);
    
    REQUIRE(result->GetLength() == 6);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 1);
    REQUIRE(result->Get(2) == 2);
    REQUIRE(result->Get(3) == 2);
    REQUIRE(result->Get(4) == 3);
    REQUIRE(result->Get(5) == 3);
    
    delete result;
}

TEST_CASE("MapReduce 56.2: FlatMap - каждый элемент в пустую последовательность"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<int>* result = FlatMap<int, int>(seq, emptyFunc);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 56.3: FlatMap - каждый элемент в последовательность разной длины"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<int>* result = FlatMap<int, int>(seq, rangeFunc);
    
    REQUIRE(result->GetLength() == 6);
    REQUIRE(result->Get(0) == 0);
    REQUIRE(result->Get(1) == 0);
    REQUIRE(result->Get(2) == 1);
    REQUIRE(result->Get(3) == 0);
    REQUIRE(result->Get(4) == 1);
    REQUIRE(result->Get(5) == 2);
    
    delete result;
}

TEST_CASE("MapReduce 56.4: FlatMap - пустая исходная последовательность"){
    ArraySequence<int> seq;
    
    Sequence<int>* result = FlatMap<int, int>(seq, duplicateFunc);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 56.5: FlatMap - с изменением типа"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<std::string>* result = FlatMap<int, std::string>(seq, toStringSeqFunc);
    
    REQUIRE(result->GetLength() == 6);
    REQUIRE(result->Get(0) == "1");
    REQUIRE(result->Get(1) == "2");
    REQUIRE(result->Get(2) == "2");
    REQUIRE(result->Get(3) == "4");
    REQUIRE(result->Get(4) == "3");
    REQUIRE(result->Get(5) == "6");
    
    delete result;
}

TEST_CASE("MapReduce 57.1: Range - возрастающий диапазон"){
    Sequence<int>* result = Range(1, 5);
    
    REQUIRE(result->GetLength() == 4);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    REQUIRE(result->Get(3) == 4);
    
    delete result;
}

TEST_CASE("MapReduce 57.2: Range - с шагом 2"){
    Sequence<int>* result = Range(1, 10, 2);
    
    REQUIRE(result->GetLength() == 5);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 3);
    REQUIRE(result->Get(2) == 5);
    REQUIRE(result->Get(3) == 7);
    REQUIRE(result->Get(4) == 9);
    
    delete result;
}

TEST_CASE("MapReduce 57.3: Range - убывающий диапазон"){
    Sequence<int>* result = Range(10, 1, -2);
    
    REQUIRE(result->GetLength() == 5);
    REQUIRE(result->Get(0) == 10);
    REQUIRE(result->Get(1) == 8);
    REQUIRE(result->Get(2) == 6);
    REQUIRE(result->Get(3) == 4);
    REQUIRE(result->Get(4) == 2);
    
    delete result;
}

TEST_CASE("MapReduce 57.4: Range - пустой диапазон (start == end)"){
    Sequence<int>* result = Range(5, 5);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 57.5: Range - пустой диапазон (неправильное направление)"){
    Sequence<int>* result = Range(10, 1, 1);
    
    REQUIRE(result->GetLength() == 0);
    
    delete result;
}

TEST_CASE("MapReduce 57.6: Range - с отрицательными числами"){
    Sequence<int>* result = Range(-5, 5, 3);
    
    REQUIRE(result->GetLength() == 4);
    REQUIRE(result->Get(0) == -5);
    REQUIRE(result->Get(1) == -2);
    REQUIRE(result->Get(2) == 1);
    REQUIRE(result->Get(3) == 4);
    
    delete result;
}

TEST_CASE("MapReduce 57.7: Range - шаг 0 выбрасывает исключение"){
    REQUIRE_THROWS_AS(Range(1, 10, 0), std::invalid_argument);
}

TEST_CASE("MapReduce 57.8: Range - тип double"){
    Sequence<double>* result = Range(1.0, 5.0, 0.5);
    
    REQUIRE(result->GetLength() == 8);
    REQUIRE(result->Get(0) == 1.0);
    REQUIRE(result->Get(1) == 1.5);
    REQUIRE(result->Get(2) == 2.0);
    REQUIRE(result->Get(3) == 2.5);
    REQUIRE(result->Get(4) == 3.0);
    REQUIRE(result->Get(5) == 3.5);
    REQUIRE(result->Get(6) == 4.0);
    REQUIRE(result->Get(7) == 4.5);
    
    delete result;
}

TEST_CASE("MapReduce 58.1: Комбинация Skip и Take"){
    int temp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ArraySequence<int> seq(temp, 10);
    
    Sequence<int>* skipped = Skip(seq, 3);
    Sequence<int>* result = Take(*skipped, 4);
    
    REQUIRE(result->GetLength() == 4);
    REQUIRE(result->Get(0) == 4);
    REQUIRE(result->Get(1) == 5);
    REQUIRE(result->Get(2) == 6);
    REQUIRE(result->Get(3) == 7);
    
    delete skipped;
    delete result;
}

TEST_CASE("MapReduce 58.2: Комбинация Zip и MapWithIndex"){
    int temp1[] = {1, 2, 3};
    int temp2[] = {10, 20, 30};
    ArraySequence<int> seq1(temp1, 3);
    ArraySequence<int> seq2(temp2, 3);
    
    Sequence<std::pair<int, int>>* zipped = Zip(seq1, seq2);
    
    Sequence<int>* result = MapWithIndex<std::pair<int, int>, int>(*zipped, sumPairFunc);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == 11);
    REQUIRE(result->Get(1) == 22);
    REQUIRE(result->Get(2) == 33);
    
    delete zipped;
    delete result;
}

TEST_CASE("MapReduce 58.3: Комбинация Range и Where"){
    Sequence<int>* range = Range(1, 20);
    
    auto isEven = [](int x) { return x % 2 == 0; };
    Sequence<int>* filtered = range->Where(isEven);
    
    REQUIRE(filtered->GetLength() == 9);
    REQUIRE(filtered->Get(0) == 2);
    REQUIRE(filtered->Get(1) == 4);
    REQUIRE(filtered->Get(2) == 6);
    REQUIRE(filtered->Get(3) == 8);
    REQUIRE(filtered->Get(4) == 10);
    REQUIRE(filtered->Get(5) == 12);
    REQUIRE(filtered->Get(6) == 14);
    REQUIRE(filtered->Get(7) == 16);
    REQUIRE(filtered->Get(8) == 18);
    
    delete range;
    delete filtered;
}

TEST_CASE("MapReduce 58.4: Комбинация FlatMap и Reduce"){
    int temp[] = {1, 2, 3};
    ArraySequence<int> seq(temp, 3);
    
    Sequence<int>* flattened = FlatMap<int, int>(seq, duplicateFunc);
    
    auto sum = [](int a, int b) { return a + b; };
    int result = flattened->Reduce(sum, 0);
    
    REQUIRE(result == 12);
    
    delete flattened;
}