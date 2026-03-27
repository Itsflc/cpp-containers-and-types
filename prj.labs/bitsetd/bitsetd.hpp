#pragma once
#ifndef BITSETD_BITSETD_HPP
#define BITSETD_BITSETD_HPP



#include<iostream>
#include<cstdint>
#include<vector>
#include<algorithm>
#include<stdexcept>

class bitset {
public:
    bitset() = default;

    explicit bitset(size_t size);

    bitset(size_t size, short int value);

    explicit bitset(const std::uint64_t mask, const int32_t size);

    bitset(const bitset& other) = default;
    bitset& operator=(const bitset& other);

    //move
    bitset(bitset&& other) noexcept;
    bitset& operator=(bitset&& other) noexcept;

    ~bitset() = default;

    bitset& operator>>=(const std::int32_t shift);
    bitset& operator<<=(const std::int32_t shift);
    bitset& operator^=(const bitset& other);
    bitset& operator&=(const bitset& other);
    bitset& operator|=(const bitset& other);


    class BitProx
    {
    public:
        BitProx() = delete;
        BitProx(const BitProx&) = delete;
        BitProx& operator=(const BitProx&) = delete;
        ~BitProx() = default;

        //move
        BitProx(BitProx&& other) noexcept : bs_(other.bs_), idx_(other.idx_) {}

        BitProx(bitset& bs, const int32_t idx) : bs_(bs), idx_(idx) {}
        operator bool() const { return bs_.get(idx_); }
        void operator=(const bool val) { bs_.set(idx_, val); }

    private:
        bitset& bs_;
        const int32_t idx_ = 0;
    };

    BitProx operator[](int32_t idx) {
        return BitProx(*this, idx);
    }

    class BitProxC {
    public:
        BitProxC() = delete;
        BitProxC(const BitProxC&) = delete;
        BitProxC& operator=(const BitProxC&) = delete;
        ~BitProxC() = default;

        //move
        BitProxC(BitProxC&& other) noexcept : val_(other.val_) {}

        BitProxC(const bitset& bs, const int32_t idx) : val_(bs.get(idx)) {}
        operator bool() const { return val_; }

    private:
        bool val_ = false;
    };

    BitProxC operator[](int32_t idx) const {
        return BitProxC(*this, idx);
    }

    std::int32_t size() const noexcept { return size_; }

    void resize(const std::int32_t new_size, const bool val = false);

    bool get(const std::int32_t idx) const;

    void set(const std::int32_t idx, const bool val);

    bitset& invert() noexcept;

    void fill(const bool val) noexcept;

private:
    std::int32_t size_ = 0;
    std::int32_t capacity = 0;
    std::vector<std::uint32_t> bits_;
};


inline bitset operator~(const bitset& rhs) noexcept { return bitset(rhs).invert(); }

bitset operator<<(const bitset& lhs, const std::int32_t shift);
bitset operator>>(const bitset& lhs, const std::int32_t shift);
bitset operator&(const bitset& lhs, const bitset& rhs);
bitset operator|(const bitset& lhs, const bitset& rhs);
bitset operator^(const bitset& lhs, const bitset& rhs);


#endif
