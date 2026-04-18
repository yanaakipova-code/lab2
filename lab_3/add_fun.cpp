#include <stdexcept>

using namespace std;

int Squaring(const int& x){
    return (x * x);
}

int DoublingUp(const int& x){
    return (x * 2);
}

double DoubleDoubling(const double& x){
    return (x * 2);
}

string ToUpper(const string& str){
    string result = str;
    for (size_t i = 0; i < str.length(); i++){
        result[i] = toupper(result[i]);
    }
    return result;
}

string ToLower(const string& str){
    string result = str;
    for (size_t i = 0; i < result.length(); i++){
        result[i] = tolower(result[i]);
    }
    return result;
}

bool DivisibleByTwo(const int& x){
    return (x % 2 == 0);
}

bool DivisibleByEleven(const int& x){
    return (x % 11 == 0);
}

bool IsPositive(const int& x) {
    return x > 0;
}

bool IsNegative(const int& x) {
    return x < 0;
}

int Sum(const int& a, const int& b) {
    return a + b;
}

int Multiply(const int& a, const int& b) {
    return a * b;
}

