#pragma once
#ifndef RATIONAL_RATIONAL_HPP
#define RATIONAL_RATIONAL_HPP

#include <cstdint>
#include <iosfwd>
#include<iostream>
#include<sstream>

class Rational {
private:
	std::int32_t num_ = 0;
	std::int32_t den_ = 1;

public:
  Rational() : Rational(0, 1) {}
  Rational(std::int32_t numer) : Rational(numer, 1) {}
  Rational(std::int32_t numer, std::int32_t denom);
  Rational& normalize() noexcept;
static const char Separator = '/';

std::int32_t num() const;
std::int32_t den() const;

  [[nodiscard]] bool operator==(const Rational& other) const noexcept;
  [[nodiscard]] bool operator!=(const Rational& other) const noexcept;
  [[nodiscard]] bool operator<(const Rational& other) const noexcept;
  [[nodiscard]] bool operator<=(const Rational& other) const noexcept;
  [[nodiscard]] bool operator>(const Rational& other) const noexcept;
  [[nodiscard]] bool operator>=(const Rational& other) const noexcept;

	[[nodiscard]] Rational operator-() noexcept;

	[[nodiscard]] Rational operator+(const Rational& other) const noexcept;
	[[nodiscard]] Rational operator-(const Rational& other) const noexcept;
	[[nodiscard]] Rational operator*(const Rational& other) const noexcept;
	Rational operator/(const Rational& other) const;

	Rational& operator+=(const Rational& other) noexcept;
	Rational& operator-=(const Rational& other) noexcept;
	Rational& operator*=(const Rational& other) noexcept;
	Rational& operator/=(const Rational& other);

	std::ostream& WriteTo(std::ostream& OSTREAM) const;
	std::istream& ReadFrom(std::istream& ISTREAM);
};

[[nodiscard]] Rational operator+(const int& number, const Rational& ts) noexcept;
[[nodiscard]] Rational operator-(const int& number, const Rational& ts) noexcept;
[[nodiscard]] Rational operator*(const int& number, const Rational& ts) noexcept;
[[nodiscard]] Rational operator/(const int& number, const Rational& ts);

std::ostream& operator<<(std::ostream& OSTREAM, const Rational& ts);
std::istream& operator>>(std::istream& ISTREAM, Rational& ts);

[[nodiscard]] bool testParse(const std::string& STRING);

#endif 


