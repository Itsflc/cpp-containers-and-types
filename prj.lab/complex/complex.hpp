#ifndef COMPLEX_COMPLEX_HPP
#define COMPLEX_COMPLEX_HPP

#include <iostream>
#include <sstream>

struct Complex {
    Complex() {}
    explicit Complex(const double real);
    Complex(const double real, const double imaginary);
    
    bool operator==(const Complex& rhs) const { return (re == rhs.re) && (im == rhs.im); }
    bool operator!=(const Complex& rhs) const { return !operator==(rhs); }
    
    Complex& operator+=(const Complex& rhs);
    Complex& operator+=(const double rhs) { return operator+=(Complex(rhs)); }
    Complex& operator-=(const Complex& rhs);
    Complex& operator-=(const double rhs) { return operator-=(Complex(rhs)); }
    Complex& operator*=(const Complex& rhs);
    Complex& operator*=(const double rhs);
    
    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::istream& istrm);

    double re{ 0.0 };
    double im{ 0.0 };

    static const char leftBrace{ '{' };
    static const char separator{ ',' };
    static const char rightBrace{ '}' };
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs);
std::istream& operator>>(std::istream& istrm, Complex& rhs);

bool testParse(const std::string& str);


#endif
