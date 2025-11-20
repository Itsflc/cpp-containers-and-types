#include <complex/complex.hpp>

Complex::Complex(double real, double imagin) noexcept {
    this->real = real;
    this->imagin = imagin;
}

const char Complex::LeftBrace = '{';
const char Complex::RightBrace = '}';
const char Complex::Separator = ',';

bool Complex::operator==(const Complex& other) const noexcept { return (this->imagin == other.imagin && this->real == other.real); }
bool Complex::operator!=(const Complex& other) const noexcept { return !(*this == other); }


Complex Complex::operator-(const Complex& other) const noexcept {
	Complex temp;
	temp.real = this->real - other.real;
	temp.imagin = this->imagin - other.imagin;
	return temp;
}
Complex Complex::operator+(const Complex& other) const noexcept {
	Complex temp;
	temp.real = this->real + other.real;
	temp.imagin = this->imagin + other.imagin;
	return temp;
}
Complex Complex::operator*(const Complex& other) const noexcept {
	Complex temp;
	temp.real = this->real * other.real - this->imagin * other.imagin;
	temp.imagin = this->real * other.imagin + this->imagin * other.real;
	return temp;
}
Complex Complex::operator/(const Complex& other) const {
	double znamenatel = other.real * other.real + other.imagin * other.imagin;
	Complex conj(other.real, -1 * other.imagin);
	Complex temp = *this * conj;
	return Complex(temp.real / znamenatel, temp.imagin / znamenatel);
}

Complex& Complex::operator+=(const Complex& other) noexcept {
	this->real += other.real;
	this->imagin += other.imagin;
	return *this;
}

Complex& Complex::operator+=(const double number) noexcept {
	this->real += number;
	return *this;
}
Complex& Complex::operator-=(const Complex& other) noexcept {
	this->real -= other.real;
	this->imagin -= other.imagin;
	return *this;
}
Complex& Complex::operator-=(const double number) noexcept {
	this->real -= number;
	return *this;
}
Complex& Complex::operator*=(const Complex& other) noexcept {
	*this = *this * other;
	return *this;
}
Complex& Complex::operator*=(const double number) noexcept {
	this->real *= number;
	this->imagin *= number;
	return *this;
}
Complex& Complex::operator/=(const Complex& other) {
	*this = *this / other;
	return *this;
}
Complex& Complex::operator/=(const double number) {
	this->real /= number;
	this->imagin /= number;
	return *this;
}


std::ostream& Complex::WriteTo(std::ostream& OSTREAM) const {
	OSTREAM << Complex::LeftBrace << this->real << Complex::Separator << this->imagin << Complex::RightBrace;
	return OSTREAM;
}

std::istream& Complex::ReadFrom(std::istream& ISTREAM) {
	char LeftBrace = 0;
	char Separator = 0;
	char RightBrace = 0;
	double re = 0.0;
	double im = 0.0;

	ISTREAM >> LeftBrace >> re >> Separator >> im >> RightBrace;
	if (ISTREAM.good()) {
		if ( (Complex::LeftBrace == LeftBrace) && (Complex::Separator == Separator) && (Complex::RightBrace == RightBrace) ) 
		{
			real = re;
			imagin = im;
		}
		else {
			re = 0.0;
			im = 0.0;
			ISTREAM.setstate(std::ios_base::failbit);
		}
	}
	else {
		re = 0.0;
		im = 0.0;
	}
	return ISTREAM;
}


Complex operator+(const double& number, const Complex& ts) noexcept {
	Complex temp(ts.real + number, ts.imagin);
	return temp;
}
Complex operator-(const double& number, const Complex& ts) noexcept {
	Complex temp(number - ts.real, -1 * ts.imagin);
	return temp;
}
Complex operator*(const double number, const Complex& ts) noexcept {
	Complex temp(ts.real * number, ts.imagin * number);
	return temp;
}
Complex operator/(const double number, const Complex& ts) {
	double znamenatel;
	znamenatel = ts.real * ts.real + ts.imagin * ts.imagin;
	Complex temp(number * ts.real / znamenatel, -1 * ts.imagin * number / znamenatel );
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
