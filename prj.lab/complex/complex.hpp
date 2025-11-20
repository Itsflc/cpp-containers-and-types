#ifndef COMPLEX_COMPLEX_HPP
#define COMPLEX_COMPLEX_HPP

#include<iostream>
#include<sstream>

struct Complex {
    Complex() : Complex(0, 0) {}
    Complex(double real) : Complex(real, 0) {}
    explicit Complex(double real, double imagin);

    double real = 0.0;
    double imagin = 0.0;
    static const char LeftBrace;
    static const char RightBrace;
    static const char Separator;

    [[nodiscard]] bool operator==(const Complex& other) const;
    [[nodiscard]] bool operator!=(const Complex& other) const;

    [[nodiscard]] Complex operator-(const Complex& other) const;
    [[nodiscard]] Complex operator+(const Complex& other) const;
    [[nodiscard]] Complex operator*(const Complex& other) const;
    [[nodiscard]] Complex operator/(const Complex& other) const;

    Complex& operator+=(const Complex& other);
    Complex& operator+=(const double number);
    Complex& operator-=(const Complex& other);
    Complex& operator-=(const double number);
    Complex& operator*=(const Complex& other);
    Complex& operator*=(const double number);
    Complex& operator/=(const Complex& other);
    Complex& operator/=(const double number);

    std::ostream& WriteTo(std::ostream& OSTREAM) const;
    std::istream& ReadFrom(std::istream& ISTREAM);
};


[[nodiscard]] Complex operator-(const double& number, const Complex& ts);
[[nodiscard]] Complex operator+(const double& number, const Complex& ts);
[[nodiscard]] Complex operator*(const double number, const Complex& ts);
[[nodiscard]] Complex operator/(const double number, const Complex& ts);

std::ostream& operator<<(std::ostream& OSTREAM, const Complex& ts);
std::istream& operator>>(std::istream& ISTREAM, Complex& ts);

[[nodiscard]] bool testParse(const std::string& STRING);

#endif
