#include "bitsetd.hpp"
#include <stdexcept>


bitset::bitset(size_t size) {
    if (size < 1) { 
        throw std::invalid_argument("Invalid size");
    }

    size_ = size;
    capacity = (size + 31) / 32;
    bits_.resize(capacity, 0);
}

bitset::bitset(size_t size, short int value) {
    if (size < 1) {
        throw std::invalid_argument("Invalid size");
    };
    size_ = size;
    capacity = (size + 31) / 32;
    bits_.resize(capacity, value ? ~0U : 0);

    if (size % 32 != 0 && value) {
        uint32_t mask = (1U << (size % 32)) - 1;
        bits_.back() &= mask;
    }
}

bitset::bitset(const std::uint64_t mask, const int32_t size)
    : size_(size),
    capacity((size + 31) / 32),
    bits_(capacity, 0)
{
    if (size < 1) {
        throw std::invalid_argument("Invalid size");
    }

    for (int32_t i = 0; i < size && i < 64; ++i) {
        if (mask & (1ULL << i)) {
            int32_t word = i / 32;
            int32_t bit = i % 32;
            bits_[word] |= (1U << bit);
        }
    }
}

bitset::bitset(bitset&& other) noexcept
    : size_(other.size_),
    capacity(other.capacity),
    bits_(std::move(other.bits_))
{
    other.size_ = 0;
    other.capacity = 0;
}

bitset& bitset::operator=(bitset&& other) noexcept {
    if (this != &other) {
        size_ = other.size_;
        capacity = other.capacity;
        bits_ = std::move(other.bits_);
        other.size_ = 0;
        other.capacity = 0;
    }
    return *this;
}



void bitset::resize(const std::int32_t new_size, const bool val) {
    if (new_size < 1) {
        throw std::invalid_argument("Invalid size");
    }

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

void bitset::set(const std::int32_t idx, const bool val) {
    if (size_ <= idx || idx < 0) {
     throw std::invalid_argument("Index out of range"); 
    }

    int32_t word = idx / 32;
    int32_t bit = idx % 32;
    if (val) { bits_[word] |= (1U << bit); }
    else { bits_[word] &= ~(1U << bit); }
}

bool bitset::get(const std::int32_t idx) const {
    if (size_ <= idx || idx < 0) {
        throw std::invalid_argument("Index out of range");
    }

    int32_t word = idx / 32;
    int32_t bit = idx % 32;
    return (bits_[word] >> bit) & 1U;
}

bitset& bitset::invert() noexcept {
    for (int32_t i = 0; i < capacity; ++i) {
        bits_[i] = ~bits_[i];
    }
    if (size_ % 32 != 0) {
        uint32_t mask = (1U << (size_ % 32)) - 1;
        bits_.back() &= mask;
    }
    return *this;
}

void bitset::fill(const bool val) noexcept {
    for (int32_t i = 0; i < capacity; ++i) {
        bits_[i] = val ? ~0U : 0U;
    }
    if (size_ % 32 != 0 && val) {
        uint32_t mask = (1U << (size_ % 32)) - 1;
        bits_.back() &= mask;
    }
}



bitset& bitset::operator=(const bitset& other) {
    if (this != &other) {
        size_ = other.size_;
        capacity = other.capacity;
        bits_ = other.bits_;
    }
    return *this;
}

bitset& bitset::operator&=(const bitset& other) {
    for (int32_t i = 0; i < std::min(capacity, other.capacity); i++) {
        bits_[i] &= other.bits_[i];
    }
    return *this;
}

bitset& bitset::operator|=(const bitset& other) {
    for (int32_t i = 0; i < std::min(capacity, other.capacity); i++) {
        bits_[i] |= other.bits_[i];
    }
    return *this;
}

bitset& bitset::operator^=(const bitset& other) {
    for (int32_t i = 0; i < std::min(capacity, other.capacity); i++) {
        bits_[i] ^= other.bits_[i];
    }
    return *this;
}

bitset& bitset::operator>>=(const std::int32_t shift) {
    if (shift <= 0) return *this;
    if (shift >= size_) { fill(false); return *this; }

    int32_t word_shift = shift / 32;
    int32_t bit_shift = shift % 32;

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
            bits_[i] = (bits_[i] >> bit_shift) | (bits_[i + 1] << (32 - bit_shift));
        }
        bits_[capacity - 1] >>= bit_shift;
    }

    if (size_ % 32 != 0) {
        uint32_t mask = (1U << (size_ % 32)) - 1;
        bits_.back() &= mask;
    }

    return *this;
}

bitset& bitset::operator<<=(const std::int32_t shift) {
    if (shift <= 0) return *this;
    if (shift >= size_) { fill(false); return *this; }

    int32_t word_shift = shift / 32;
    int32_t bit_shift = shift % 32;

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
            bits_[i] = (bits_[i] << bit_shift) | (bits_[i - 1] >> (32 - bit_shift));
        }
        bits_[0] <<= bit_shift;
    }

    if (size_ % 32 != 0) {
        uint32_t mask = (1U << (size_ % 32)) - 1;
        bits_.back() &= mask;
    }

    return *this;
}

bitset operator<<(const bitset& lhs, const std::int32_t shift) {
    bitset result = lhs;
    result <<= shift;
    return result;
}

bitset operator>>(const bitset& lhs, const std::int32_t shift) {
    bitset result = lhs;
    result >>= shift;
    return result;
}

bitset operator&(const bitset& lhs, const bitset& rhs) {
    int32_t max_size = std::max(lhs.size(), rhs.size());
    int32_t min_size = std::min(lhs.size(), rhs.size());

    bitset result(static_cast<size_t>(max_size), static_cast<short int>(0));
    for (int32_t i = 0; i < min_size; ++i) {
        if (lhs.get(i) && rhs.get(i)) result.set(i, true);
    }
    return result;
}

bitset operator|(const bitset& lhs, const bitset& rhs) {
    int32_t max_size = std::max(lhs.size(), rhs.size());
    int32_t min_size = std::min(lhs.size(), rhs.size());

    bitset result(static_cast<size_t>(max_size), static_cast<short int>(0));
    for (int32_t i = 0; i < lhs.size(); ++i) {
        if (lhs.get(i)) result.set(i, true);
    }
    for (int32_t i = 0; i < rhs.size(); ++i) {
        if (rhs.get(i)) result.set(i, true);
    }
    return result;
}

bitset operator^(const bitset& lhs, const bitset& rhs) {
    int32_t max_size = std::max(lhs.size(), rhs.size());
    int32_t min_size = std::min(lhs.size(), rhs.size());

    bitset result(static_cast<size_t>(max_size), static_cast<short int>(0));
    for (int32_t i = 0; i < min_size; ++i) {
        if (lhs.get(i) != rhs.get(i)) result.set(i, true);
    }
    for (int32_t i = min_size; i < lhs.size(); ++i) {
        if (lhs.get(i)) result.set(i, true);
    }
    for (int32_t i = min_size; i < rhs.size(); ++i) {
        if (rhs.get(i)) result.set(i, true);
    }
    return result;
}



