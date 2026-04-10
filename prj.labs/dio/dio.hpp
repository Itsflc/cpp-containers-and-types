#pragma once
#ifndef DIO_DIO_HPP
#define DIO_DIO_HPP

#include <iostream>
#include <string>

class DioStrB {
private:
    std::string data_;
public:
    DioStrB();
    explicit DioStrB(std::string data);
    std::string val() const;
    std::ostream& WriteTo(std::ostream& OSTREAM) const;
    std::istream& ReadFrom(std::istream& ISTREAM);
};

std::ostream& operator<<(std::ostream& OSTREAM, const DioStrB& ts);
std::istream& operator>>(std::istream& ISTREAM, DioStrB& ts);



#endif
