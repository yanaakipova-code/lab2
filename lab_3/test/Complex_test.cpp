#include "catch.hpp"
#include "../Complex.hpp"
#include "../Set.hpp"
#include <string>

TEST_CASE("Complex: конструктор и геттеры") {
    Complex<double> c(3.0, 4.0);
    
    REQUIRE(c.GetRe() == 3.0);
    REQUIRE(c.GetIm() == 4.0);
}

TEST_CASE("Complex: копирование") {
    Complex<int> c1(1, 2);
    Complex<int> c2(c1);

    REQUIRE(c2.GetRe() == 1);
    REQUIRE(c2.GetIm() == 2);
}

TEST_CASE("Complex: SetRe и SetIm") {
    Complex<double> c(0, 0);
    c.SetRe(5.5);
    c.SetIm(6.6);
    
    REQUIRE(c.GetRe() == 5.5);
    REQUIRE(c.GetIm() == 6.6);
}

TEST_CASE("Complex: Abs - модуль") {
    Complex<double> c1(3, 4);
    REQUIRE(c1.Abs() == 5.0);
    
    Complex<double> c2(0, 5);
    REQUIRE(c2.Abs() == 5.0);
    
    Complex<double> c3(5, 0);
    REQUIRE(c3.Abs() == 5.0);
}

TEST_CASE("Complex: оператор +") {
    Complex<int> c1(1, 2);
    Complex<int> c2(3, 4);
    Complex<int> result = c1 + c2;
    
    REQUIRE(result.GetRe() == 4);
    REQUIRE(result.GetIm() == 6);
}

TEST_CASE("Complex: оператор -") {
    Complex<int> c1(5, 7);
    Complex<int> c2(2, 3);
    Complex<int> result = c1 - c2;
    
    REQUIRE(result.GetRe() == 3);
    REQUIRE(result.GetIm() == 4);
}

TEST_CASE("Complex: оператор *") {
    Complex<int> c1(1, 2);
    Complex<int> c2(3, 4);
    Complex<int> result = c1 * c2;

    REQUIRE(result.GetRe() == -5);
    REQUIRE(result.GetIm() == 10);
}

TEST_CASE("Complex: оператор /") {
    Complex<double> c1(1, 2);
    Complex<double> c2(3, 4);
    Complex<double> result = c1 / c2;
    
    REQUIRE(result.GetRe() == Approx(0.44));
    REQUIRE(result.GetIm() == Approx(0.08));
}

TEST_CASE("Complex: оператор = (int)") {
    Complex<int> c(1, 2);
    c = 5;
    
    REQUIRE(c.GetRe() == 5);
    REQUIRE(c.GetIm() == 0);
}

TEST_CASE("Complex: оператор > по модулю") {
    Complex<int> c1(3, 4); 
    Complex<int> c2(1, 1);
    Complex<int> c3(0, 6);
    
    REQUIRE(c1 > c2);
    REQUIRE(c3 > c1);
    REQUIRE_FALSE(c2 > c1);
}

TEST_CASE("Complex: оператор ==") {
    Complex<int> c1(1, 2);
    Complex<int> c2(1, 2);
    Complex<int> c3(1, 3);
    
    REQUIRE(c1 == c2);
    REQUIRE_FALSE(c1 == c3);
}

TEST_CASE("Complex: оператор !=") {
    Complex<int> c1(1, 2);
    Complex<int> c2(1, 2);
    Complex<int> c3(1, 3);
    
    REQUIRE(c1 != c3);
    REQUIRE_FALSE(c1 != c2);
}

TEST_CASE("Complex: ToString") {
    Complex<int> c1(1, 2);
    Complex<int> c2(1, -2);
    Complex<int> c3(0, 5);
    Complex<int> c4(5, 0);
    Complex<int> c5(0, 0);
    
    REQUIRE(c1.ToString() == "1+2i");
    REQUIRE(c2.ToString() == "1-2i");
}