#include <complex/complex.hpp>
#include <cmath>
#include <limits>

Complex::Complex(double real, double imagin) noexcept {
    this->re = real;
    this->im = imagin;
}

const char Complex::LeftBrace = '{';
const char Complex::RightBrace = '}';
const char Complex::Separator = ',';

bool Complex::operator==(const Complex& other) const noexcept { 
	constexpr double EPSILON = 1e-9;
	return std::abs(this->re - other.re) < EPSILON && std::abs(this->im - other.im) < EPSILON;
}
bool Complex::operator!=(const Complex& other) const noexcept { return !(*this == other); }


Complex Complex::operator-() const noexcept {
  Complex temp;
  temp.re = -this->re;
  temp.im = -this->im;
  return temp;
}


Complex Complex::operator-(const Complex& other) const noexcept {
	Complex temp;
	temp.re = this->re - other.re;
	temp.im = this->im - other.im;
	return temp;
}
Complex Complex::operator+(const Complex& other) const noexcept {
	Complex temp;
	temp.re = this->re + other.re;
	temp.im = this->im + other.im;
	return temp;
}
Complex Complex::operator*(const Complex& other) const noexcept {
	Complex temp;
	temp.re = this->re * other.re - this->im * other.im;
	temp.im = this->re * other.im + this->im * other.re;
	return temp;
}
Complex Complex::operator/(const Complex& other) const {
	double znamenatel = other.re * other.re + other.im * other.im;
	Complex conj(other.re, -1 * other.im);
	Complex temp = *this * conj;
	return Complex(temp.re / znamenatel, temp.im / znamenatel);
}

Complex& Complex::operator+=(const Complex& other) noexcept {
	this->re += other.re;
	this->im += other.im;
	return *this;
}

Complex& Complex::operator+=(const double number) noexcept {
	this->re += number;
	return *this;
}
Complex& Complex::operator-=(const Complex& other) noexcept {
	this->re -= other.re;
	this->im -= other.im;
	return *this;
}
Complex& Complex::operator-=(const double number) noexcept {
	this->re -= number;
	return *this;
}
Complex& Complex::operator*=(const Complex& other) noexcept {
	*this = *this * other;
	return *this;
}
Complex& Complex::operator*=(const double number) noexcept {
	this->re *= number;
	this->im *= number;
	return *this;
}
Complex& Complex::operator/=(const Complex& other) {
	*this = *this / other;
	return *this;
}
Complex& Complex::operator/=(const double number) {
	this->re /= number;
	this->im /= number;
	return *this;
}


std::ostream& Complex::WriteTo(std::ostream& OSTREAM) const {
	OSTREAM << Complex::LeftBrace << this->re << Complex::Separator << this->im << Complex::RightBrace;
	return OSTREAM;
}

std::istream& Complex::ReadFrom(std::istream& ISTREAM) {
	char LeftBrace = 0;
	char Separator = 0;
	char RightBrace = 0;
	double real = 0.0;
	double imagin = 0.0;

	ISTREAM >> LeftBrace >> re >> Separator >> im >> RightBrace;
	if (ISTREAM.good()) {
		if ( (Complex::LeftBrace == LeftBrace) && (Complex::Separator == Separator) && (Complex::RightBrace == RightBrace) ) 
		{
			re = real;
			im = imagin;
		}
		else {
			real = 0.0;
			imagin = 0.0;
			ISTREAM.setstate(std::ios_base::failbit);
		}
	}
	else {
		real = 0.0;
		imagin = 0.0;
	}
	return ISTREAM;
}


Complex operator+(const double& number, const Complex& ts) noexcept {
	Complex temp(ts.re + number, ts.im);
	return temp;
}
Complex operator-(const double& number, const Complex& ts) noexcept {
	Complex temp(number - ts.re, -1 * ts.im);
	return temp;
}
Complex operator*(const double number, const Complex& ts) noexcept {
	Complex temp(ts.re * number, ts.im * number);
	return temp;
}
Complex operator/(const double number, const Complex& ts) {
	double znamenatel;
	znamenatel = ts.re * ts.re + ts.im * ts.im;
	Complex temp(number * ts.re / znamenatel, -1 * ts.im * number / znamenatel );
	return temp;
}


std::ostream& operator<<(std::ostream& OSTREAM, const Complex& ts) {
	return ts.WriteTo(OSTREAM);
}
std::istream& operator>>(std::istream& ISTREAM, Complex& ts) {
	return ts.ReadFrom(ISTREAM);
}

bool testParse(const std::string& STRING) {
	std::istringstream inp_str_stream(STRING);
	Complex z;
	inp_str_stream >> z;
	if (inp_str_stream.good()) { std::cout << "Read success: " << STRING << " -> " << z << std::endl; }
	else { std::cout << "Read error: " << STRING << " -> " << z << std::endl; }
	return inp_str_stream.good();
}
