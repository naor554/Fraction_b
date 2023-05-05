#include "Fraction.hpp"
#include <stdexcept>
#include <limits>
#include <cmath>

#include "Fraction.hpp"

namespace ariel{

    Fraction::Fraction(int numerator, int denominator)
        : numerator_(numerator), denominator_(denominator) {
        if (denominator == 0) {
            throw std::invalid_argument("denominator cannot be zero.");
        }
        reduce();
        if(denominator_ < 0){
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }

    Fraction::Fraction(float value) { // Additional constructor implementation
        int precision = 1000;
        denominator_ = precision;
        numerator_ = static_cast<int>(std::round(value * precision));
        reduce();
    }


    void Fraction::reduce() {
        int factor = gcd(numerator_, denominator_);
        numerator_ /= factor;
        denominator_ /= factor;
    }

    int Fraction::gcd(int a, int b) { // Additional gcd function implementation
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    int Fraction::getNumerator() const {
        return numerator_;
    }

    int Fraction::getDenominator() const {
        return denominator_;
    }

    // arithmetic operators

    Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
        int64_t num = int64_t(lhs.numerator_) * int64_t(rhs.denominator_) + int64_t(rhs.numerator_) * int64_t(lhs.denominator_);
        int64_t denom = int64_t(lhs.denominator_) * int64_t(rhs.denominator_);

        if (num > std::numeric_limits<int>::max() || denom > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Integer overflow occurred.");
        }

        if (num < std::numeric_limits<int>::min() || denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Underflow detected.");
        }

        return Fraction(static_cast<int>(num), static_cast<int>(denom));
    }


    Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
        int64_t num = int64_t(lhs.numerator_) * int64_t(rhs.denominator_) - int64_t(rhs.numerator_) * int64_t(lhs.denominator_);
        int64_t denom = int64_t(lhs.denominator_) * int64_t(rhs.denominator_);

        if (num > std::numeric_limits<int>::max() || denom > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Integer overflow occurred.");
        }

        if (num < std::numeric_limits<int>::min() || denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Underflow detected.");
        }

        return Fraction(static_cast<int>(num), static_cast<int>(denom));
    }

    
    Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
        int64_t num = int64_t(lhs.numerator_) * int64_t(rhs.numerator_);
        int64_t denom = int64_t(lhs.denominator_) * int64_t(rhs.denominator_);

        if (num > std::numeric_limits<int>::max() || denom > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Integer overflow occurred during multiplication.");
        }

        if (num < std::numeric_limits<int>::min() || denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Underflow detected in addition.");
        }

        return Fraction(static_cast<int>(num), static_cast<int>(denom));
    }

    Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
        if (rhs.numerator_ == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }

        int64_t num = int64_t(lhs.numerator_) * int64_t(rhs.denominator_);
        int64_t denom = int64_t(lhs.denominator_) * int64_t(rhs.numerator_);

        if (num > std::numeric_limits<int>::max() || denom > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Integer overflow occurred during multiplication.");
        }

        if (num < std::numeric_limits<int>::min() || denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Underflow detected in addition.");
        }

        return Fraction(static_cast<int>(num), static_cast<int>(denom));
    }

    

    // Overloaded arithmetic operators for float
    Fraction operator+(float lhs, const Fraction& rhs) {
        Fraction lhs_frac(lhs);
        return lhs_frac + rhs;
    }

    Fraction operator+(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs + rhs_frac;
    }


    Fraction operator-(float lhs, const Fraction& rhs) {
        Fraction lhs_frac(lhs);
        return lhs_frac - rhs;
    }

    Fraction operator-(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs - rhs_frac;
    }


    Fraction operator*(float lhs, const Fraction& rhs) {
        Fraction lhs_frac(lhs);
        return lhs_frac * rhs;
    }

    Fraction operator*(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs * rhs_frac;
    }


    Fraction operator/(float lhs, const Fraction& rhs) {
        Fraction lhs_frac(lhs);
        return lhs_frac / rhs;
    }

    Fraction operator/(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs / rhs_frac;
    }



    // comparing operators
    bool Fraction::operator==(const Fraction &other) const {
        return numerator_ == other.numerator_ && denominator_ == other.denominator_;
    }

    bool Fraction::operator!=(const Fraction &other) const {
        return !(*this == other);
    }

    bool Fraction::operator<(const Fraction &other) const {
        int left_product = numerator_ * other.denominator_;
        int right_product = other.numerator_ * denominator_;
        return denominator_ * other.denominator_ > 0 ? (left_product < right_product) : (left_product > right_product);
    }


    bool Fraction::operator<=(const Fraction &other) const {
        return *this < other || *this == other;
    }

    bool Fraction::operator>(const Fraction &other) const {
        return !(*this <= other);
    }

    bool Fraction::operator>=(const Fraction &other) const {
        return !(*this < other);
    }


    // Overloaded comparing operators for float
    bool operator==(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs == rhs_frac;
    }

    bool operator==(float lhs, const Fraction& rhs) {
        Fraction lhs_frac(lhs);
        return rhs == lhs_frac;
    }

    bool operator!=(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs != rhs_frac;
    }

    bool operator!=(float lhs, const Fraction& rhs) {
        Fraction lhs_frac(lhs);
        return rhs != lhs_frac;
    }

    bool operator>(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs > rhs_frac;
    }

    bool operator>(float lhs, const Fraction& rhs) {
       Fraction lhs_frac(lhs);
       return lhs_frac > rhs;
    }

    bool operator<(const Fraction& lhs, float rhs) {
       Fraction rhs_frac(rhs);
        return lhs < rhs_frac;
    }

    bool operator<(float lhs, const Fraction& rhs) {
        Fraction lhs_frac(lhs);
        return lhs_frac < rhs;
    }

    bool operator>=(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs >= rhs_frac;
    }

    bool operator>=(float lhs, const Fraction& rhs) {
        Fraction lhs_frac(lhs);
        return lhs_frac >= rhs;
    }

    bool operator<=(const Fraction& lhs, float rhs) {
        Fraction rhs_frac(rhs);
        return lhs <= rhs_frac;
    }

    bool operator<=(float lhs, const Fraction& rhs) {
       Fraction lhs_frac(lhs);
       return lhs_frac <= rhs;
    }



    Fraction &Fraction::operator++() {
        numerator_ += denominator_;
        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction temp = *this;
        numerator_ += denominator_;
        return temp;
    }


    Fraction &Fraction::operator--() {
        numerator_ -= denominator_;
        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction temp(*this);
        --(*this);
        return temp;
    }

    std::ostream &operator<<(std::ostream &os, const Fraction &fraction) {
        os << fraction.numerator_ << '/' << fraction.denominator_;
        return os;
    }

    std::istream &operator>>(std::istream &is, Fraction &fraction) {
        is.clear();
        int num, denom;
        is >> num;

        if (is.eof()) {
            throw std::invalid_argument("Invalid format for Fraction input.");
        }

        is >> denom;
        if (denom == 0) {
            throw std::runtime_error("denominator cannot be zero.");
        }

        fraction = Fraction(num, denom);
        return is;
    }

}
