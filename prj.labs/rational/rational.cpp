#include "rational.hpp"
#include<stdexcept>


Rational::Rational(std::int32_t numer, std::int32_t denom) {
	num_ = numer;
	if (denom != 0) { den_ = denom; }
	else { throw std::invalid_argument("Division by zero"); }
	normalize();
}
std::int32_t Rational::num() const { return num_; }
std::int32_t Rational::den() const { return den_; }


Rational& Rational::normalize() noexcept {
	if (this->den_ < 0) {
		this->den_ *= -1;
		this->num_ *= -1;
	}
	bool flagg = false;
	if (this->num_ < 0) {
		flagg = true;
		this->num_ *= -1;
	}

	std::int32_t copy_n = this->num();
	std::int32_t copy_d = this->den();

	while (copy_d != 0) {
		std::int32_t temp = copy_d;
		copy_d = copy_n % copy_d;
		copy_n = temp;
	}
	this->den_ /= copy_n;
	this->num_ /= copy_n;

	if (flagg) { this-> num_ *= -1; }
	return *this;
}

bool Rational::operator==(const Rational& other) const noexcept { return (this->num_ * other.den_ == this->den_ * other.num_); }
bool Rational::operator!=(const Rational& other) const noexcept { return !(*this == other); }
bool Rational::operator>(const Rational& other) const noexcept { return (this->num_ * other.den_ > this->den_ * other.num_); }
bool Rational::operator<(const Rational& other) const noexcept { return (this->num_ * other.den_ < this->den_ * other.num_); }
bool Rational::operator>=(const Rational& other) const noexcept { return !(*this < other); }
bool Rational::operator<=(const Rational& other) const noexcept { return !(*this > other); }

Rational Rational::operator-() noexcept{
	Rational temp(-1 * this->num_, this->den_);
	return temp;
}



Rational Rational::operator+(const Rational& other) const noexcept{
	Rational temp(this->num_ * other.den_ + this->den_ * other.num_, this->den_ * other.den_);
	return temp;
}
Rational Rational::operator-(const Rational& other) const noexcept {
	Rational temp(this->num_ * other.den_ - this->den_ * other.num_, this->den_ * other.den_);
	return temp;
}
Rational Rational::operator*(const Rational& other) const noexcept {
	Rational temp(this->num_ * other.num_, this->den_ * other.den_);
	return temp;
}
Rational Rational::operator/(const Rational& other) const {
	if (other.num() == 0) { throw std::invalid_argument("Division by zero"); }
	Rational temp(this->num_ * other.den_, this->den_ * other.num_);
	return temp;
}

Rational& Rational::operator+=(const Rational& other) noexcept {
	*this = *this + other;
	return *this;
}
Rational& Rational::operator-=(const Rational& other) noexcept {
	*this = *this - other;
	return *this;
}
Rational& Rational::operator*=(const Rational& other) noexcept {
	*this = *this * other;
	return *this;
}
Rational& Rational::operator/=(const Rational& other) {
	*this = *this / other;
	return *this;
}


std::ostream& Rational::WriteTo(std::ostream& OSTREAM) const {
	OSTREAM << this->num_ << Rational::Separator << this->den_;
	return OSTREAM;
}
std::istream& Rational::ReadFrom(std::istream& ISTREAM) {
	char Separator = 0;
	std::int32_t numerator = 0;
	std::int32_t denominator = 0;

	ISTREAM >> numerator >> Separator >> denominator;
	if (!ISTREAM.fail()) {
			num_ = numerator;
			den_ = denominator;
			normalize();
		}
		if (Rational::Separator != Separator || denominator == 0) {
			ISTREAM.setstate(std::ios_base::failbit);
		}
	}
	else {
		ISTREAM.setstate(std::ios_base::failbit);
	}
	return ISTREAM;
}

Rational operator+(const int& number, const Rational& ts) noexcept {
	Rational temp(ts.num() + ts.den() * number, ts.den());
	return temp;
}
Rational operator-(const int& number, const Rational& ts) noexcept {
	Rational temp(ts.den() * number - ts.num(), ts.den());
	return temp;
}
Rational operator*(const int& number, const Rational& ts) noexcept {
	Rational temp(ts.num() * number, ts.den());
	return temp;
}
Rational operator/(const int& number, const Rational& ts) {
	Rational temp(ts.den() * number, ts.num());
	return temp;
}


std::ostream& operator<<(std::ostream& OSTREAM, const Rational& ts) {
	return ts.WriteTo(OSTREAM);
}
std::istream& operator>>(std::istream& ISTREAM, Rational& ts) {
	return ts.ReadFrom(ISTREAM);
}


bool testParse(const std::string& STRING) {
	std::istringstream inp_str_stream(STRING);
	Rational r;
	inp_str_stream >> r;
	if (!inp_str_stream.fail()) { std::cout << "Read success: " << STRING << " -> " << r << std::endl; }
	else { std::cout << "Read error: " << STRING << " -> " << r << std::endl; }
	return (!inp_str_stream.fail());
}

