//#include "DioStrB.hpp"
#include <dio/dio.hpp>



DioStrB::DioStrB() : DioStrB("") {}

DioStrB::DioStrB(std::string data) : data_(std::move(data)) {}

std::string DioStrB::val() const {
    return data_;
}

std::ostream& DioStrB::WriteTo(std::ostream& OSTREAM) const {
    OSTREAM << data_;
    return OSTREAM;
}

std::istream& DioStrB::ReadFrom(std::istream& ISTREAM) {
    std::string temp_data;
    if (ISTREAM >> temp_data) {
        data_ = temp_data;
    }
    return ISTREAM;
}

std::ostream& operator<<(std::ostream& OSTREAM, const DioStrB& ts) {
    return ts.WriteTo(OSTREAM);
}

std::istream& operator>>(std::istream& ISTREAM, DioStrB& ts) {
    return ts.ReadFrom(ISTREAM);
}
