#pragma once
#include <iostream>
#include <cmath>

using namespace std;

template<typename U>
class Complex{
private:
    U m_re;
    U m_im;
public:
    Complex(U re, U im ): m_re(re), m_im(im){}
    Complex(const Complex& other): m_re(other.m_re), m_im(other.m_im){}

    U GetRe() const{
        return m_re;
    }
    U GetIm() const{
        return m_im;
    }
    void SetRe(U re){
        m_re = re;
    }
    void SetIm(U im){
        m_im = im;
    }

    U Abs() const{
        return sqrt((m_re * m_re) + (m_im * m_im));
    }

    Complex operator+(const Complex& other){
        return Complex(m_re + other.m_re, m_im + other.m_im);
    }
    Complex operator-(const Complex& other){
        return Complex(m_re - other.m_re, m_im - other.m_im);
    }
    Complex operator*(const Conplex& other){
        U re = (m_re * other.m_re) - (m_im * other.m_im);
        U im = (m_re * other.m_re) + (m_im * other.m_im);

        return Complex(re, im);
    }
    Complex operator/(const Complex& other){
        U del = (other.m_re * other.m_re) + (other.m_im * other.m_im); 
        U re = ((m_re * other.m_re) + (m_im * other.m_im)) / del;
        U im = ((m_im * other.m_re) - (m_im * other.m_re)) / del;

        return Complex(re, im);
    }
    Complex& operator=(int value) {
        m_re = value;
        m_im = 0;
        return *this;
    }
    bool operator>(const Complex& other) const {
    return Abs() > other.Abs();
    }

    bool operator==(const Complex& other) const {
        return m_re == other.m_re && m_im == other.m_im;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    friend U abs(const Complex& z) {
    return z.Abs();
    }

    string ToString() const{
        string res;
        if(m_re = 0){
            res = to_string(m_im) + "i";
        }
        if (m_im = 0){
            res = to_string(m_re)
        }
        if(m_im > 0){
            res = to_string(m_re) + "+" to_string(m_im) + "i"
        }
        if(m_im < 0){
            res = to_string(m_re) + "-" to_string(m_im) + "i"
        }
        return res;
    }
};