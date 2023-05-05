#pragma once
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <sstream>


#ifndef EX3_CPP_A_FRACTION_H
#define EX3_CPP_A_FRACTION_H
#endif //EX3_CPP_A_FRACTION_H

using namespace std;


namespace ariel{

    class Fraction {
    private:
        int numerator_;
        int denominator_;

        void reduce();
        int gcd(int num1, int num2); // Additional gcd function


    public:
        Fraction(): numerator_(1), denominator_(1) {}// default constructor
        Fraction(int num, int denom);
        Fraction(float value); // Additional constructor to handle float values
        int getNumerator() const;
        int getDenominator() const;

        friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
        friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);
        friend Fraction operator*(const Fraction& lhs, const Fraction& rhs);
        friend Fraction operator/(const Fraction& lhs, const Fraction& rhs);
        
        // Overloaded arithmetic operators for float
        friend Fraction operator+(float lhs, const Fraction& rhs);
        friend Fraction operator+(const Fraction& lhs, float rhs);
        friend Fraction operator-(float lhs, const Fraction& rhs);
        friend Fraction operator-(const Fraction& lhs, float rhs);
        friend Fraction operator*(float lhs, const Fraction& rhs);
        friend Fraction operator*(const Fraction& lhs, float rhs);
        friend Fraction operator/(float lhs, const Fraction& rhs);
        friend Fraction operator/(const Fraction& lhs, float rhs);
        

        bool operator==(const Fraction &other) const;
        bool operator!=(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;

        Fraction &operator++();    // Prefix increment
        Fraction operator++(int);  // Postfix increment
        Fraction &operator--();    // Prefix decrement
        Fraction operator--(int);  // Postfix decrement

        friend std::ostream &operator<<(std::ostream &ostream, const Fraction &fraction);
        friend std::istream &operator>>(std::istream &istream, Fraction &fraction);
    };

    // comapring operators with float
        bool operator==(const Fraction& frac, float num);
        bool operator==(float num, const Fraction& frac);
        bool operator!=(const Fraction& frac, float num);
        bool operator!=(float num, const Fraction& frac);
        bool operator>(const Fraction& frac, float num);
        bool operator>(float num, const Fraction& frac);
        bool operator<(const Fraction& frac, float num);
        bool operator<(float num, const Fraction& frac);
        bool operator>=(const Fraction& frac, float num);
        bool operator>=(float num, const Fraction& frac);
        bool operator<=(const Fraction& frac, float num);
        bool operator<=(float num, const Fraction& frac);
}
