#include "BitsetD.hpp"

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <stdexcept>


void exceptions::index(size_t size,int32_t idx)
{
    if (size >= idx && idx>=0) { return; }
    else
    {
        throw std::invalid_argument("Index out of range");
    }
}

void exceptions::size(size_t size)
{
    if (size >= 1)
    {
        return;
    }
    else
    {
        throw std::invalid_argument("Invalid size");
    }
}

 BitsetD::BitsetD(size_t size) {
    exceptions::size(size);
    size_ = size;
    capacity = (size + 31) / 32;
    bits_.resize(capacity, 0);
}


 

 BitsetD::BitsetD(const std::uint64_t mask, const int32_t size)
        : size_(size),
          capacity((size + 31) / 32),
          bits_(capacity, 0) {
    exceptions::size(size);
    for (int32_t i = 0; i < size && i < 64; ++i) {
        if (mask & (1ULL << i)) {
            int32_t word = i / 32;
            int32_t bit = i % 32;
            bits_[word] |= (1U << bit);
        }
    }
}


void BitsetD::resize(const std::int32_t new_size, const bool val) {
    exceptions::size(new_size);
    std::vector<uint32_t> old_bits = bits_;
    int32_t old_capacity = capacity;

    int32_t new_capacity = (new_size + 31) / 32;

    bits_.clear();
    bits_.resize(new_capacity, val ? ~0U : 0);

    int32_t copy_words = std::min(old_capacity, new_capacity);
    for (int32_t i = 0; i < copy_words; ++i) {
        bits_[i] = old_bits[i];
    }

    size_ = new_size;
    capacity = new_capacity;

    if (new_size % 32 != 0) {
        uint32_t mask = (1U << (new_size % 32)) - 1;
        bits_.back() &= mask;
    }
}

void BitsetD::set(const std::int32_t idx, const bool val) {
    exceptions::index(size_, idx);
    int32_t word = idx / 32;
    int32_t bit = idx % 32;

    if (val) {
        bits_[word] |= (1U << bit);
    } else {
        bits_[word] &= ~(1U << bit);
    }
}

bool BitsetD::get(const std::int32_t idx) const {
    exceptions::index(size_, idx);
    if (idx < 0 || idx >= size_) {
        throw std::out_of_range("Index out of range");
    }

    int32_t word = idx / 32;
    int32_t bit = idx % 32;

    return (bits_[word] >> bit) & 1U;
}

BitsetD BitsetD::invert() noexcept {
    for (int32_t i = 0; i < capacity; ++i) {
        bits_[i] = ~bits_[i];
    }


    if (size_ % 32 != 0) {
        uint32_t mask = (1U << (size_ % 32)) - 1;
        bits_.back() &= mask;
    }

    return *this;
}

void BitsetD::fill(const bool val) noexcept {
    for (int32_t i = 0; i < capacity; ++i) {
        bits_[i] = val;
    }


    if (size_ % 32 != 0 && val) {
        uint32_t mask = (1U << (size_ % 32)) - 1;
        bits_.back() &= mask;
    }
}


BitsetD &BitsetD::operator=(const BitsetD &other) {
    if (this != &other) {
        size_ = other.size();
        capacity = other.capacity;
        bits_ = other.bits_;
    }
    return *this;
}

BitsetD &BitsetD::operator&=(const BitsetD &other) {
    for (int32_t i = 0; i < capacity; i++) {
        bits_[i] &= other.bits_[i];
    }
    return *this;
}

BitsetD &BitsetD::operator|=(const BitsetD &other) {
    for (int32_t i = 0; i < capacity; i++) {
        bits_[i] |= other.bits_[i];
    }
    return *this;
}

BitsetD &BitsetD::operator^=(const BitsetD &other) {
    for (int32_t i = 0; i < capacity; i++) {
        bits_[i] ^= other.bits_[i];
    }
    return *this;
}

BitsetD &BitsetD::operator>>=(const std::int32_t shift) {
    if (shift <= 0) return *this;
    if (shift >= size_) {
        fill(false);
        return *this;
    }

    int32_t word_shift = shift / 32;
    int32_t bit_shift = shift % 32;

    // Сдвиг вправо
    if (word_shift > 0) {
        for (int32_t i = 0; i < capacity - word_shift; ++i) {
            bits_[i] = bits_[i + word_shift];
        }
        for (int32_t i = capacity - word_shift; i < capacity; ++i) {
            bits_[i] = 0;
        }
    }

    if (bit_shift > 0) {
        for (int32_t i = 0; i < capacity - 1; ++i) {
            bits_[i] = (bits_[i] >> bit_shift) |
                       (bits_[i + 1] << (32 - bit_shift));
        }
        bits_[capacity - 1] >>= bit_shift;
    }

    // Обрезаем лишние биты
    if (size_ % 32 != 0) {
        uint32_t mask = (1U << (size_ % 32)) - 1;
        bits_.back() &= mask;
    }

    return *this;
}

BitsetD &BitsetD::operator<<=(const std::int32_t shift) {
    if (shift <= 0) return *this;
    if (shift >= size_) {
        fill(false);
        return *this;
    }

    int32_t word_shift = shift / 32;
    int32_t bit_shift = shift % 32;

    // Сдвиг влево
    if (word_shift > 0) {
        for (int32_t i = capacity - 1; i >= word_shift; --i) {
            bits_[i] = bits_[i - word_shift];
        }
        for (int32_t i = 0; i < word_shift; ++i) {
            bits_[i] = 0;
        }
    }

    if (bit_shift > 0) {
        for (int32_t i = capacity - 1; i > 0; --i) {
            bits_[i] = (bits_[i] << bit_shift) |
                       (bits_[i - 1] >> (32 - bit_shift));
        }
        bits_[0] <<= bit_shift;
    }

    // Обрезаем лишние биты
    if (size_ % 32 != 0) {
        uint32_t mask = (1U << (size_ % 32)) - 1;
        bits_.back() &= mask;
    }

    return *this;
}

BitsetD operator<<(const BitsetD &lhs, const std::int32_t shift) {
    BitsetD result = lhs;
    result <<= shift;
    return result;
}

BitsetD operator>>(const BitsetD &lhs, const std::int32_t shift) {
    BitsetD result = lhs;
    result >>= shift;
    return result;
}

BitsetD operator&(const BitsetD &lhs, const BitsetD &rhs) {
    int32_t max_size = std::max(lhs.size(), rhs.size());
    int32_t min_size = std::min(lhs.size(), rhs.size());

    BitsetD result(static_cast<size_t>(max_size), false);

    for (int32_t i = 0; i < min_size; ++i) {
        if (lhs.get(i) && rhs.get(i)) {
            result.set(i, true);
        }
    }

    return result;
}

BitsetD operator|(const BitsetD &lhs, const BitsetD &rhs) {
    int32_t max_size = std::max(lhs.size(), rhs.size());
    int32_t min_size = std::min(lhs.size(), rhs.size());

    BitsetD result(static_cast<size_t>(max_size), false);


    for (int32_t i = 0; i < lhs.size(); ++i) {
        if (lhs.get(i)) result.set(i, true);
    }

    for (int32_t i = 0; i < min_size; ++i) {
        if (rhs.get(i)) result.set(i, true);
    }

    return result;
}

BitsetD operator^(const BitsetD &lhs, const BitsetD &rhs) {
    int32_t max_size = std::max(lhs.size(), rhs.size());
    int32_t min_size = std::min(lhs.size(), rhs.size());

    BitsetD result(static_cast<size_t>(max_size), false);


    for (int32_t i = 0; i < min_size; ++i) {
        if (lhs.get(i) != rhs.get(i)) {
            result.set(i, true);
        }
    }

    for (int32_t i = min_size; i < lhs.size(); ++i) {
        if (lhs.get(i)) result.set(i, true);
    }
    for (int32_t i = min_size; i < rhs.size(); ++i) {
        if (rhs.get(i)) result.set(i, true);
    }

    return result;
}

bool BitsetD::operator==(const BitsetD& other) const
{
    if (other.size_ == size_&& other.capacity==capacity)
    {
        for(int32_t i =0;i<size_;++i)
        { 
            if(other.get(i) != get(i))
            {
                return false;
            }
        }
    }
    else { return false; }
    return true;
}

bool BitsetD::operator!=(const BitsetD& rhs)
{
    return !(*this == rhs);
}
