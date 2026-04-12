#include "catch.hpp"
#include "../BitSequence.hpp"
#include "../Error.hpp"

TEST_CASE("Битовая последовательность 1: конструктор по умолчанию"){
    BitSequence<uint32_t> seq(0);
    
    REQUIRE(seq.GetLength() == 0);
    REQUIRE_THROWS_AS(seq.GetFirst(), EmptySequenceException);
    REQUIRE_THROWS_AS(seq.GetLast(), EmptySequenceException);
}

TEST_CASE("Битовая последовательность 2: Append"){
    BitSequence<uint32_t> seq(0);
    
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    
    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.GetFirst().GetBit(0) == true);
    REQUIRE(seq.GetLast().GetBit(0) == true);
    REQUIRE(seq.GetBit(0) == true);
    REQUIRE(seq.GetBit(1) == false);
    REQUIRE(seq.GetBit(2) == true);
}

TEST_CASE("Битовая последовательность 3: Prepend"){
    BitSequence<uint32_t> seq(0);
    
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    seq.Prepend(Bit<uint32_t>(true));
    
    REQUIRE(seq.GetLength() == 3);
    REQUIRE(seq.GetFirst().GetBit(0) == true);
    REQUIRE(seq.GetBit(0) == true);
    REQUIRE(seq.GetBit(1) == false);
    REQUIRE(seq.GetBit(2) == true);
}

TEST_CASE("Битовая последовательность 4: InsertAt"){
    BitSequence<uint32_t> seq(0);
    
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(true));
    seq.InsertAt(Bit<uint32_t>(false), 1);
    
    REQUIRE(seq.GetLength() == 4);
    REQUIRE(seq.GetBit(0) == true);
    REQUIRE(seq.GetBit(1) == false);
    REQUIRE(seq.GetBit(2) == true);
    REQUIRE(seq.GetBit(3) == true);
}

TEST_CASE("Битовая последовательность 5: Map"){
    BitSequence<uint32_t> seq(0);
    
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    
    auto invert = [](Bit<uint32_t> b) { 
        return Bit<uint32_t>(!b.GetBit(0)); 
    };
    Sequence<Bit<uint32_t>>* mapped = seq.Map(invert);
    
    REQUIRE(mapped->GetLength() == 3);
    REQUIRE(mapped->Get(0).GetBit(0) == false);
    REQUIRE(mapped->Get(1).GetBit(0) == true);
    REQUIRE(mapped->Get(2).GetBit(0) == false);
    
    delete mapped;
}

TEST_CASE("Битовая последовательность 6: Where"){
    BitSequence<uint32_t> seq(0);
    
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    
    auto isTrue = [](Bit<uint32_t> b) { 
        return b.GetBit(0); 
    };
    Sequence<Bit<uint32_t>>* filtered = seq.Where(isTrue);
    
    REQUIRE(filtered->GetLength() == 3);
    REQUIRE(filtered->Get(0).GetBit(0) == true);
    REQUIRE(filtered->Get(1).GetBit(0) == true);
    REQUIRE(filtered->Get(2).GetBit(0) == true);
    
    delete filtered;
}

TEST_CASE("Битовая последовательность 7: Reduce"){
    BitSequence<uint32_t> seq(0);
    
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    
    auto orOp = [](Bit<uint32_t> a, Bit<uint32_t> b) { 
        return Bit<uint32_t>(a.GetBit(0) || b.GetBit(0)); 
    };
    Bit<uint32_t> result = seq.Reduce(orOp, Bit<uint32_t>(false));
    
    REQUIRE(result.GetBit(0) == true);
}

TEST_CASE("Битовая последовательность 8: AND операция"){
    BitSequence<uint32_t> seq1(0);
    BitSequence<uint32_t> seq2(0);
    
    seq1.Append(Bit<uint32_t>(true));
    seq1.Append(Bit<uint32_t>(false));
    seq1.Append(Bit<uint32_t>(true));
    
    seq2.Append(Bit<uint32_t>(true));
    seq2.Append(Bit<uint32_t>(true));
    seq2.Append(Bit<uint32_t>(false));
    
    auto result = seq1.And(seq2);
    
    REQUIRE(result->GetBit(0) == true);
    REQUIRE(result->GetBit(1) == false);
    REQUIRE(result->GetBit(2) == false);
}

TEST_CASE("Битовая последовательность 9: OR операция"){
    BitSequence<uint32_t> seq1(0);
    BitSequence<uint32_t> seq2(0);
    
    seq1.Append(Bit<uint32_t>(true));
    seq1.Append(Bit<uint32_t>(false));
    seq1.Append(Bit<uint32_t>(true));
    
    seq2.Append(Bit<uint32_t>(false));
    seq2.Append(Bit<uint32_t>(true));
    seq2.Append(Bit<uint32_t>(false));
    
    auto result = seq1.Or(seq2);
    
    REQUIRE(result->GetBit(0) == true);
    REQUIRE(result->GetBit(1) == true);
    REQUIRE(result->GetBit(2) == true);
}

TEST_CASE("Битовая последовательность 10: NOT операция"){
    BitSequence<uint32_t> seq(0);
    
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    
    auto result = seq.Not();
    
    REQUIRE(result->GetBit(0) == false);
    REQUIRE(result->GetBit(1) == true);
    REQUIRE(result->GetBit(2) == false);
}

TEST_CASE("Битовая последовательность 11: Concat"){
    BitSequence<uint32_t> seq1(0);
    BitSequence<uint32_t> seq2(0);
    
    seq1.Append(Bit<uint32_t>(true));
    seq1.Append(Bit<uint32_t>(false));
    
    seq2.Append(Bit<uint32_t>(true));
    seq2.Append(Bit<uint32_t>(true));
    
    Sequence<Bit<uint32_t>>* result = seq1.Concat(&seq2);
    
    REQUIRE(result->GetLength() == 4);
    REQUIRE(result->Get(0).GetBit(0) == true);
    REQUIRE(result->Get(1).GetBit(0) == false);
    REQUIRE(result->Get(2).GetBit(0) == true);
    REQUIRE(result->Get(3).GetBit(0) == true);
    
    delete result;
}

TEST_CASE("Битовая последовательность 12: GetSubsequence"){
    BitSequence<uint32_t> seq(0);
    
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    seq.Append(Bit<uint32_t>(false));
    seq.Append(Bit<uint32_t>(true));
    
    Sequence<Bit<uint32_t>>* subseq = seq.GetSubsequence(1, 3);
    
    REQUIRE(subseq->GetLength() == 3);
    REQUIRE(subseq->Get(0).GetBit(0) == false);
    REQUIRE(subseq->Get(1).GetBit(0) == true);
    REQUIRE(subseq->Get(2).GetBit(0) == false);
    
    delete subseq;
}