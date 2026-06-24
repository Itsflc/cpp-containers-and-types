#include "JaggedA.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>



JaggedA::JaggedA() noexcept
    : data(nullptr), rows(0), sizes(nullptr) {
}

JaggedA::JaggedA(const JaggedA& other) noexcept
    : data(nullptr), rows(0), sizes(nullptr) {
    rows = other.rows;
    sizes = new int32_t[rows];
    data = new int32_t * [rows];

    for (int32_t i = 0; i < rows; ++i) {
        sizes[i] = other.sizes[i];
        data[i] = new int32_t[sizes[i]];
        for (int32_t j = 0; j < sizes[i]; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

JaggedA::JaggedA(JaggedA&& other) noexcept
    : data(other.data), rows(other.rows), sizes(other.sizes) {
    other.data = nullptr;
    other.rows = 0;
    other.sizes = nullptr;
}

JaggedA::JaggedA(const int siz)
    : data(new int32_t* [siz]), rows(siz), sizes(new int32_t[siz]) {
    for (int32_t i = 0; i < rows; ++i) {
        sizes[i] = 0;
        data[i] = nullptr;
    }
}

JaggedA& JaggedA::operator=(const JaggedA& other) noexcept {
    if (this == &other) {
        return *this;
    }
    for (int32_t i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
    delete[] sizes;

    rows = other.rows;
    sizes = new int32_t[rows];
    data = new int32_t * [rows];

    for (int32_t i = 0; i < rows; ++i) {
        sizes[i] = other.sizes[i];
        data[i] = new int32_t[sizes[i]];
        for (int32_t j = 0; j < sizes[i]; ++j) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

JaggedA& JaggedA::operator=(JaggedA&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    for (int32_t i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
    delete[] sizes;

    rows = other.rows;
    sizes = other.sizes;
    data = other.data;

    other.data = nullptr;
    other.rows = 0;
    other.sizes = nullptr;
    return *this;
}

JaggedA::~JaggedA() noexcept {
    for (int32_t i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
    delete[] sizes;
}

bool JaggedA::operator==(const JaggedA& other) const noexcept {
    if (rows != other.rows) {
        return false;
    }
    for (int32_t i = 0; i < rows; ++i) {
        if (sizes[i] != other.sizes[i]) {
            return false;
        }
        for (int32_t j = 0; j < sizes[i]; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int32_t JaggedA::size() const noexcept {
    return rows;
}

void JaggedA::resize(const int32_t size) {
    if (size == rows) return;

    int32_t** new_data = nullptr;
    int32_t* new_sizes = nullptr;

    if (size < rows) {
        new_data = new int32_t * [size];
        new_sizes = new int32_t[size];

        for (int32_t i = 0; i < size; ++i) {
            new_sizes[i] = sizes[i];
            new_data[i] = new int32_t[new_sizes[i]];
            for (int32_t j = 0; j < sizes[i]; ++j) {
                new_data[i][j] = data[i][j];
            }
        }
    }
    else if (size > rows) {
        new_data = new int32_t * [size];
        new_sizes = new int32_t[size];

        for (int32_t i = 0; i < rows; ++i) {
            new_data[i] = data[i];
            new_sizes[i] = sizes[i];
        }
        for (int32_t i = rows; i < size; ++i) {
            new_data[i] = nullptr;
            new_sizes[i] = 0;
        }
    }

    for (int32_t i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
    delete[] sizes;

    data = new_data;
    sizes = new_sizes;
    rows = size;
}

int32_t JaggedA::size(const int32_t i) const {
    if (i < 0 || i >= rows) {
        throw std::out_of_range("index out of range");
    }
    return sizes[i];
}

void JaggedA::resize(const int32_t i, const int32_t size) {
    if (i < 0 || i >= rows) {
        throw std::out_of_range("index out of range");
    }
    if (size == sizes[i]) {
        return;
    }

    int32_t* new_row = new int32_t[size];
    int32_t copy_count = (size < sizes[i]) ? size : sizes[i];

    for (int32_t j = 0; j < copy_count; ++j) {
        new_row[j] = data[i][j];
    }
    for (int32_t j = sizes[i]; j < size; ++j) {
        new_row[j] = 0;
    }

    delete[] data[i];
    data[i] = new_row;
    sizes[i] = size;
}

int32_t& JaggedA::at(const int32_t i, const int32_t j) {
    if (i < 0 || i >= rows) {
        throw std::out_of_range("index out of range");
    }
    if (j < 0 || j >= sizes[i]) {
        throw std::out_of_range("index out of range");
    }
    return data[i][j];
}

const int32_t& JaggedA::at(const int32_t i, const int32_t j) const {
    if (i < 0 || i >= rows) {
        throw std::out_of_range("index out of range");
    }
    if (j < 0 || j >= sizes[i]) {
        throw std::out_of_range("index out of range");
    }
    return data[i][j];
}

void JaggedA::swap(const int32_t i_l, const int32_t i_r) {
    if (i_l < 0 || i_l >= rows || i_r < 0 || i_r >= rows) {
        throw std::out_of_range("index out of range");
    }
    if (i_l == i_r) {
        return;
    }
    std::swap(data[i_l], data[i_r]);
    std::swap(sizes[i_l], sizes[i_r]);
}

void JaggedA::insert(const int32_t i) {
    if (i < 0 || i > rows) {
        throw std::out_of_range("index out of range");
    }

    int32_t** new_data = new int32_t * [rows + 1];
    int32_t* new_sizes = new int32_t[rows + 1];

    for (int32_t j = 0; j < i; ++j) {
        new_data[j] = data[j];
        new_sizes[j] = sizes[j];
    }

    new_data[i] = nullptr;
    new_sizes[i] = 0;

    for (int32_t j = i; j < rows; ++j) {
        new_data[j + 1] = data[j];
        new_sizes[j + 1] = sizes[j];
    }

    delete[] data;
    delete[] sizes;

    data = new_data;
    sizes = new_sizes;
    rows += 1;
}

void JaggedA::remove(const int32_t i) {
    if (i < 0 || i >= rows) {
        throw std::out_of_range("index out of range");
    }

    delete[] data[i];

    int32_t** new_data = new int32_t * [rows - 1];
    int32_t* new_sizes = new int32_t[rows - 1];

    for (int32_t j = 0; j < i; ++j) {
        new_data[j] = data[j];
        new_sizes[j] = sizes[j];
    }

    for (int32_t j = i + 1; j < rows; ++j) {
        new_data[j - 1] = data[j];
        new_sizes[j - 1] = sizes[j];
    }

    delete[] data;
    delete[] sizes;

    data = new_data;
    sizes = new_sizes;
    rows -= 1;
}

void JaggedA::insert(const int32_t i, const int32_t j) {
    if (i < 0 || i >= rows) {
        throw std::out_of_range("index out of range");
    }
    if (j < 0 || j > sizes[i]) {
        throw std::out_of_range("index out of range");
    }

    int32_t* new_row = new int32_t[sizes[i] + 1];

    for (int32_t k = 0; k < j; ++k) {
        new_row[k] = data[i][k];
    }

    new_row[j] = 0;

    for (int32_t k = j; k < sizes[i]; ++k) {
        new_row[k + 1] = data[i][k];
    }

    delete[] data[i];
    data[i] = new_row;
    sizes[i] += 1;
}

void JaggedA::remove(const int32_t i, const int32_t j) {
    if (i < 0 || i >= rows) {
        throw std::out_of_range("index out of range");
    }
    if (j < 0 || j >= sizes[i]) {
        throw std::out_of_range("index out of range");
    }

    int32_t* new_row = new int32_t[sizes[i] - 1];

    for (int32_t k = 0; k < j; ++k) {
        new_row[k] = data[i][k];
    }

    for (int32_t k = j + 1; k < sizes[i]; ++k) {
        new_row[k - 1] = data[i][k];
    }

    delete[] data[i];
    data[i] = new_row;
    sizes[i] -= 1;
}

int main()
{
    return 0;
}
