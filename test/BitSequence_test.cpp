#include "catch.hpp"
#include "../BitSequence.hpp"

TEST_CASE("Битовая последовательность 27.1: BitSequence - конструктор из bool массива"){
    bool temp[] = {true, false, true, true, false};
    BitSequence seq(temp, 5);
    
    REQUIRE(seq.GetLength() == 5);
    REQUIRE(seq.GetBit(0) == true);
    REQUIRE(seq.GetBit(1) == false);
    REQUIRE(seq.GetBit(2) == true);
    REQUIRE(seq.GetBit(3) == true);
    REQUIRE(seq.GetBit(4) == false);
}

TEST_CASE("Битовая последовательность 27.2: BitSequence - конструктор с размером"){
    BitSequence seq(10);
    
    REQUIRE(seq.GetLength() == 10);
    for (size_t i = 0; i < 10; i++) {
        REQUIRE(seq.GetBit(i) == false);
    }
}

TEST_CASE("Битовая последовательность 27.3: BitSequence - конструктор копирования"){
    bool temp[] = {true, false, true};
    BitSequence original(temp, 3);
    BitSequence copy(original);
    
    REQUIRE(copy.GetLength() == 3);
    REQUIRE(copy.GetBit(0) == true);
    REQUIRE(copy.GetBit(1) == false);
    REQUIRE(copy.GetBit(2) == true);
    
    original.SetBit(0, false);
    REQUIRE(copy.GetBit(0) == true);
}

TEST_CASE("Битовая последовательность 28.1: BitSequence - GetFirst"){
    bool temp[] = {true, false, true};
    BitSequence seq(temp, 3);
    
    REQUIRE(seq.GetFirst().GetValue() == true);
}

TEST_CASE("Битовая последовательность 28.2: BitSequence - GetFirst на пустой последовательности"){
    BitSequence seq(0);
    
    REQUIRE_THROWS_AS(seq.GetFirst(), std::out_of_range);
}

TEST_CASE("Битовая последовательность 28.3: BitSequence - GetLast"){
    bool temp[] = {true, false, true};
    BitSequence seq(temp, 3);
    
    REQUIRE(seq.GetLast().GetValue() == true);
}

TEST_CASE("Битовая последовательность 28.4: BitSequence - GetLast на пустой последовательности"){
    BitSequence seq(0);
    
    REQUIRE_THROWS_AS(seq.GetLast(), std::out_of_range);
}

TEST_CASE("Битовая последовательность 28.5: BitSequence - Get по индексу"){
    bool temp[] = {true, false, true, false};
    BitSequence seq(temp, 4);
    
    REQUIRE(seq.Get(0).GetValue() == true);
    REQUIRE(seq.Get(1).GetValue() == false);
    REQUIRE(seq.Get(2).GetValue() == true);
    REQUIRE(seq.Get(3).GetValue() == false);
}

TEST_CASE("Битовая последовательность 28.6: BitSequence - Get с неверным индексом"){
    bool temp[] = {true, false, true};
    BitSequence seq(temp, 3);
    
    REQUIRE_THROWS_AS(seq.Get(3), std::out_of_range);
    REQUIRE_THROWS_AS(seq.Get(100), std::out_of_range);
}

TEST_CASE("Битовая последовательность 28.7: BitSequence - GetLength"){
    bool temp[] = {true, false, true, false, true, false, true};
    BitSequence seq(temp, 7);
    
    REQUIRE(seq.GetLength() == 7);
}

TEST_CASE("Битовая последовательность 29.1: BitSequence - Append"){
    BitSequence seq(0);
    
    seq.Append(Bit(true));
    seq.Append(Bit(false));
    seq.Append(Bit(true));
    
    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.GetBit(0) == true);
    REQUIRE(seq.GetBit(1) == false);
    REQUIRE(seq.GetBit(2) == true);
}

TEST_CASE("Битовая последовательность 29.2: BitSequence - Prepend"){
    BitSequence seq(0);
    
    seq.Append(Bit(false));
    seq.Append(Bit(true));
    seq.Prepend(Bit(true));
    
    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.GetBit(0) == true);
    REQUIRE(seq.GetBit(1) == false);
    REQUIRE(seq.GetBit(2) == true);
}

TEST_CASE("Битовая последовательность 29.3: BitSequence - InsertAt в начало"){
    bool temp[] = {false, false, false};
    BitSequence seq(temp, 3);
    
    seq.InsertAt(Bit(true), 0);
    
    REQUIRE(seq.GetLength() == 4);
    REQUIRE(seq.GetBit(0) == true);
    REQUIRE(seq.GetBit(1) == false);
    REQUIRE(seq.GetBit(2) == false);
    REQUIRE(seq.GetBit(3) == false);
}

TEST_CASE("Битовая последовательность 29.4: BitSequence - InsertAt в середину"){
    bool temp[] = {true, true, true, true};
    BitSequence seq(temp, 4);
    
    seq.InsertAt(Bit(false), 2);
    
    REQUIRE(seq.GetLength() == 5);
    REQUIRE(seq.GetBit(0) == true);
    REQUIRE(seq.GetBit(1) == true);
    REQUIRE(seq.GetBit(2) == false);
    REQUIRE(seq.GetBit(3) == true);
    REQUIRE(seq.GetBit(4) == true);
}

TEST_CASE("Битовая последовательность 29.5: BitSequence - InsertAt в конец"){
    bool temp[] = {true, true, true};
    BitSequence seq(temp, 3);
    
    seq.InsertAt(Bit(false), 3);
    
    REQUIRE(seq.GetLength() == 4);
    REQUIRE(seq.GetBit(3) == false);
    REQUIRE(seq.GetLast().GetValue() == false);
}

TEST_CASE("Битовая последовательность 29.6: BitSequence - InsertAt с неверным индексом"){
    bool temp[] = {true, false, true};
    BitSequence seq(temp, 3);
    
    REQUIRE_THROWS_AS(seq.InsertAt(Bit(true), 5), std::out_of_range);
    REQUIRE_THROWS_AS(seq.InsertAt(Bit(true), 100), std::out_of_range);
}

TEST_CASE("Битовая последовательность 30.1: BitSequence - SetBit"){
    bool temp[] = {false, false, false, false, false};
    BitSequence seq(temp, 5);
    
    seq.SetBit(2, true);
    
    REQUIRE(seq.GetBit(2) == true);
    REQUIRE(seq.GetBit(0) == false);
    REQUIRE(seq.GetBit(1) == false);
    REQUIRE(seq.GetBit(3) == false);
    REQUIRE(seq.GetBit(4) == false);
}

TEST_CASE("Битовая последовательность 30.2: BitSequence - SetBit с неверным индексом"){
    bool temp[] = {true, false, true};
    BitSequence seq(temp, 3);
    
    REQUIRE_THROWS_AS(seq.SetBit(3, true), std::out_of_range);
    REQUIRE_THROWS_AS(seq.SetBit(100, true), std::out_of_range);
}

TEST_CASE("Битовая последовательность 31.1: BitSequence - GetSubsequence"){
    bool temp[] = {true, false, true, false, true, false};
    BitSequence seq(temp, 6);
    
    Sequence<Bit>* subseq = seq.GetSubsequence(1, 4);
    
    REQUIRE(subseq->GetLength() == 4);
    REQUIRE(subseq->Get(0).GetValue() == false);
    REQUIRE(subseq->Get(1).GetValue() == true);
    REQUIRE(subseq->Get(2).GetValue() == false);
    REQUIRE(subseq->Get(3).GetValue() == true);
    
    delete subseq;
}

TEST_CASE("Битовая последовательность 31.2: BitSequence - GetSubsequence из одного элемента"){
    bool temp[] = {true, false, true, false, true};
    BitSequence seq(temp, 5);
    
    Sequence<Bit>* subseq = seq.GetSubsequence(2, 2);
    
    REQUIRE(subseq->GetLength() == 1);
    REQUIRE(subseq->GetFirst().GetValue() == true);
    
    delete subseq;
}

TEST_CASE("Битовая последовательность 31.3: BitSequence - GetSubsequence с неверными индексами"){
    bool temp[] = {true, false, true, false, true};
    BitSequence seq(temp, 5);
    
    REQUIRE_THROWS_AS(seq.GetSubsequence(3, 1), std::out_of_range);
    REQUIRE_THROWS_AS(seq.GetSubsequence(0, 5), std::out_of_range);
    REQUIRE_THROWS_AS(seq.GetSubsequence(2, 10), std::out_of_range);
}

TEST_CASE("Битовая последовательность 32.1: BitSequence - Concat"){
    bool temp1[] = {true, false, true};
    bool temp2[] = {false, true, false};
    BitSequence seq1(temp1, 3);
    BitSequence seq2(temp2, 3);
    
    Sequence<Bit>* result = seq1.Concat(&seq2);
    
    REQUIRE(result->GetLength() == 6);
    REQUIRE(result->Get(0).GetValue() == true);
    REQUIRE(result->Get(1).GetValue() == false);
    REQUIRE(result->Get(2).GetValue() == true);
    REQUIRE(result->Get(3).GetValue() == false);
    REQUIRE(result->Get(4).GetValue() == true);
    REQUIRE(result->Get(5).GetValue() == false);
    
    delete result;
}

TEST_CASE("Битовая последовательность 32.2: BitSequence - Concat с пустой последовательностью"){
    bool temp[] = {true, false, true};
    BitSequence seq1(temp, 3);
    BitSequence seq2(0);
    
    Sequence<Bit>* result = seq1.Concat(&seq2);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0).GetValue() == true);
    REQUIRE(result->Get(1).GetValue() == false);
    REQUIRE(result->Get(2).GetValue() == true);
    
    delete result;
}

TEST_CASE("Битовая последовательность 33.1: BitSequence - And"){
    bool temp1[] = {true, true, false, false};
    bool temp2[] = {true, false, true, false};
    BitSequence seq1(temp1, 4);
    BitSequence seq2(temp2, 4);
    
    auto result = seq1.And(seq2);
    
    REQUIRE(result->GetBit(0) == true);
    REQUIRE(result->GetBit(1) == false);
    REQUIRE(result->GetBit(2) == false);
    REQUIRE(result->GetBit(3) == false);
}

TEST_CASE("Битовая последовательность 33.2: BitSequence - Or"){
    bool temp1[] = {true, true, false, false};
    bool temp2[] = {true, false, true, false};
    BitSequence seq1(temp1, 4);
    BitSequence seq2(temp2, 4);
    
    auto result = seq1.Or(seq2);
    
    REQUIRE(result->GetBit(0) == true);
    REQUIRE(result->GetBit(1) == true);
    REQUIRE(result->GetBit(2) == true);
    REQUIRE(result->GetBit(3) == false);
}

TEST_CASE("Битовая последовательность 33.3: BitSequence - Xor"){
    bool temp1[] = {true, true, false, false};
    bool temp2[] = {true, false, true, false};
    BitSequence seq1(temp1, 4);
    BitSequence seq2(temp2, 4);
    
    auto result = seq1.Xor(seq2);
    
    REQUIRE(result->GetBit(0) == false);
    REQUIRE(result->GetBit(1) == true);
    REQUIRE(result->GetBit(2) == true);
    REQUIRE(result->GetBit(3) == false);
}

TEST_CASE("Битовая последовательность 33.4: BitSequence - Not"){
    bool temp[] = {true, false, true, false};
    BitSequence seq(temp, 4);
    
    auto result = seq.Not();
    
    REQUIRE(result->GetBit(0) == false);
    REQUIRE(result->GetBit(1) == true);
    REQUIRE(result->GetBit(2) == false);
    REQUIRE(result->GetBit(3) == true);
}

TEST_CASE("Битовая последовательность 33.5: BitSequence - And с разной длиной"){
    bool temp1[] = {true, false, true};
    bool temp2[] = {true, false, true, false};
    BitSequence seq1(temp1, 3);
    BitSequence seq2(temp2, 4);
    
    REQUIRE_THROWS_AS(seq1.And(seq2), std::invalid_argument);
}

TEST_CASE("Битовая последовательность 34.1: BitSequence - оператор &"){
    bool temp1[] = {true, true, false, false};
    bool temp2[] = {true, false, true, false};
    BitSequence seq1(temp1, 4);
    BitSequence seq2(temp2, 4);
    
    BitSequence result = seq1 & seq2;
    
    REQUIRE(result.GetBit(0) == true);
    REQUIRE(result.GetBit(1) == false);
    REQUIRE(result.GetBit(2) == false);
    REQUIRE(result.GetBit(3) == false);
}

TEST_CASE("Битовая последовательность 34.2: BitSequence - оператор |"){
    bool temp1[] = {true, true, false, false};
    bool temp2[] = {true, false, true, false};
    BitSequence seq1(temp1, 4);
    BitSequence seq2(temp2, 4);
    
    BitSequence result = seq1 | seq2;
    
    REQUIRE(result.GetBit(0) == true);
    REQUIRE(result.GetBit(1) == true);
    REQUIRE(result.GetBit(2) == true);
    REQUIRE(result.GetBit(3) == false);
}

TEST_CASE("Битовая последовательность 34.3: BitSequence - оператор ^"){
    bool temp1[] = {true, true, false, false};
    bool temp2[] = {true, false, true, false};
    BitSequence seq1(temp1, 4);
    BitSequence seq2(temp2, 4);
    
    BitSequence result = seq1 ^ seq2;
    
    REQUIRE(result.GetBit(0) == false);
    REQUIRE(result.GetBit(1) == true);
    REQUIRE(result.GetBit(2) == true);
    REQUIRE(result.GetBit(3) == false);
}

TEST_CASE("Битовая последовательность 34.4: BitSequence - оператор ~"){
    bool temp[] = {true, false, true, false};
    BitSequence seq(temp, 4);
    
    BitSequence result = ~seq;
    
    REQUIRE(result.GetBit(0) == false);
    REQUIRE(result.GetBit(1) == true);
    REQUIRE(result.GetBit(2) == false);
    REQUIRE(result.GetBit(3) == true);
}

TEST_CASE("Битовая последовательность 35.1: BitSequence - Map"){
    bool temp[] = {true, false, true, false};
    BitSequence seq(temp, 4);
    
    auto invert = [](Bit b) { return !b; };
    Sequence<Bit>* mapped = seq.Map(invert);
    BitSequence* bitMapped = dynamic_cast<BitSequence*>(mapped);
    
    REQUIRE(bitMapped->GetLength() == 4);
    REQUIRE(bitMapped->GetBit(0) == false);
    REQUIRE(bitMapped->GetBit(1) == true);
    REQUIRE(bitMapped->GetBit(2) == false);
    REQUIRE(bitMapped->GetBit(3) == true);
    
    delete mapped;
}

TEST_CASE("Битовая последовательность 35.2: BitSequence - Map на пустой последовательности"){
    BitSequence seq(0);
    
    auto invert = [](Bit b) { return !b; };
    Sequence<Bit>* mapped = seq.Map(invert);
    
    REQUIRE(mapped->GetLength() == 0);
    
    delete mapped;
}

TEST_CASE("Битовая последовательность 36.1: BitSequence - Where"){
    bool temp[] = {true, false, true, true, false};
    BitSequence seq(temp, 5);
    
    auto isTrue = [](Bit b) { return b.GetValue(); };
    Sequence<Bit>* filtered = seq.Where(isTrue);
    BitSequence* bitFiltered = dynamic_cast<BitSequence*>(filtered);
    
    REQUIRE(bitFiltered->GetLength() == 3);
    REQUIRE(bitFiltered->GetBit(0) == true);
    REQUIRE(bitFiltered->GetBit(1) == true);
    REQUIRE(bitFiltered->GetBit(2) == true);
    
    delete filtered;
}

TEST_CASE("Битовая последовательность 36.2: BitSequence - Where ничего не подходит"){
    bool temp[] = {false, false, false};
    BitSequence seq(temp, 3);
    
    auto isTrue = [](Bit b) { return b.GetValue(); };
    Sequence<Bit>* filtered = seq.Where(isTrue);
    
    REQUIRE(filtered->GetLength() == 0);
    
    delete filtered;
}

TEST_CASE("Битовая последовательность 37.1: BitSequence - Reduce"){
    bool temp[] = {true, true, false, true};
    BitSequence seq(temp, 4);
    
    auto bitAnd = [](Bit a, Bit b) { return a & b; };
    Bit result = seq.Reduce(bitAnd, Bit(true));
    
    REQUIRE(result.GetValue() == false);
}

TEST_CASE("Битовая последовательность 37.2: BitSequence - Reduce с Or"){
    bool temp[] = {false, false, true, false};
    BitSequence seq(temp, 4);
    
    auto bitOr = [](Bit a, Bit b) { return a | b; };
    Bit result = seq.Reduce(bitOr, Bit(false));
    
    REQUIRE(result.GetValue() == true);
}

TEST_CASE("Битовая последовательность 38.1: BitSequence - TryGetFirst без предиката"){
    bool temp[] = {false, true, false, true};
    BitSequence seq(temp, 4);
    
    Option<Bit> first = seq.TryGetFirst();
    
    REQUIRE(first.HasValue() == true);
    REQUIRE(first.GetValue().GetValue() == false);
}

TEST_CASE("Битовая последовательность 38.2: BitSequence - TryGetFirst с предикатом"){
    bool temp[] = {false, false, true, true};
    BitSequence seq(temp, 4);
    
    auto isTrue = [](Bit b) { return b.GetValue(); };
    Option<Bit> first = seq.TryGetFirst(isTrue);
    
    REQUIRE(first.HasValue() == true);
    REQUIRE(first.GetValue().GetValue() == true);
}

TEST_CASE("Битовая последовательность 38.3: BitSequence - TryGetFirst ничего не найдено"){
    bool temp[] = {false, false, false};
    BitSequence seq(temp, 3);
    
    auto isTrue = [](Bit b) { return b.GetValue(); };
    Option<Bit> first = seq.TryGetFirst(isTrue);
    
    REQUIRE(first.HasValue() == false);
}

TEST_CASE("Битовая последовательность 38.4: BitSequence - TryGetLast без предиката"){
    bool temp[] = {false, true, false, true};
    BitSequence seq(temp, 4);
    
    Option<Bit> last = seq.TryGetLast();
    
    REQUIRE(last.HasValue() == true);
    REQUIRE(last.GetValue().GetValue() == true);
}

TEST_CASE("Битовая последовательность 38.5: BitSequence - TryGetLast с предикатом"){
    bool temp[] = {true, true, false, false};
    BitSequence seq(temp, 4);
    
    auto isTrue = [](Bit b) { return b.GetValue(); };
    Option<Bit> last = seq.TryGetLast(isTrue);
    
    REQUIRE(last.HasValue() == true);
    REQUIRE(last.GetValue().GetValue() == true);
}

TEST_CASE("Битовая последовательность 39.1: BitSequence - ToMutable"){
    bool temp[] = {true, false, true, true, false};
    BitSequence seq(temp, 5);
    
    auto mutableSeq = seq.ToMutable();
    
    REQUIRE(mutableSeq->GetLength() == 5);
    REQUIRE(mutableSeq->Get(0).GetValue() == true);
    REQUIRE(mutableSeq->Get(1).GetValue() == false);
    REQUIRE(mutableSeq->Get(2).GetValue() == true);
    REQUIRE(mutableSeq->Get(3).GetValue() == true);
    REQUIRE(mutableSeq->Get(4).GetValue() == false);
}

TEST_CASE("Битовая последовательность 39.2: BitSequence - ToMutable на пустой последовательности"){
    BitSequence seq(0);
    
    auto mutableSeq = seq.ToMutable();
    
    REQUIRE(mutableSeq->GetLength() == 0);
}