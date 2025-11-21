#ifndef COMPLEX_COMPLEX_HPP
#define COMPLEX_COMPLEX_HPP

#include<iostream>
#include<sstream>

class Complex {
public:
    Complex() noexcept : Complex(0, 0) {}
    Complex(double real) noexcept : Complex(real, 0) {}
    explicit Complex(double real, double imagin) noexcept;

    double real = 0.0;
    double imagin = 0.0;
    static const char LeftBrace;
    static const char RightBrace;
    static const char Separator;

    [[nodiscard]] bool operator==(const Complex& other) const noexcept;
    [[nodiscard]] bool operator!=(const Complex& other) const noexcept;

    [[nodiscard]] Complex operator-() const noexcept;

    [[nodiscard]] Complex operator-(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator+(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator*(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator/(const Complex& other) const;

    Complex& operator+=(const Complex& other) noexcept;
    Complex& operator+=(const double number) noexcept;
    Complex& operator-=(const Complex& other) noexcept;
    Complex& operator-=(const double number) noexcept; 
    Complex& operator*=(const Complex& other) noexcept;
    Complex& operator*=(const double number) noexcept;
    Complex& operator/=(const Complex& other);
    Complex& operator/=(const double number);

    std::ostream& WriteTo(std::ostream& OSTREAM) const;
    std::istream& ReadFrom(std::istream& ISTREAM);
};


[[nodiscard]] Complex operator-(const double& number, const Complex& ts) noexcept;
[[nodiscard]] Complex operator+(const double& number, const Complex& ts) noexcept;
[[nodiscard]] Complex operator*(const double number, const Complex& ts) noexcept;
[[nodiscard]] Complex operator/(const double number, const Complex& ts);

std::ostream& operator<<(std::ostream& OSTREAM, const Complex& ts);
std::istream& operator>>(std::istream& ISTREAM, Complex& ts);

[[nodiscard]] bool testParse(const std::string& STRING);

#endif
