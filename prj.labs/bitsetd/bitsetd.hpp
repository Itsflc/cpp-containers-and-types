#pragma once
#ifndef BitsetD_LIBRARY_H
#define BitsetD_LIBRARY_H

#include<iostream>
#include<cstdint>
#include<vector>

class exceptions
{ public:
    static void size(size_t size);
    static void index(size_t size,int32_t idx);
    
};

class BitsetD {
public:
    BitsetD() = default;

    explicit BitsetD(size_t size);


    explicit BitsetD(const std::uint64_t mask, const int32_t size );

    ~BitsetD() {};

    bool operator!=(const BitsetD &rhs);

    BitsetD &operator=(const BitsetD &other);

    BitsetD &operator>>=(const std::int32_t shift);

    BitsetD &operator<<=(const std::int32_t shift);

    BitsetD &operator^=(const BitsetD &other);

    BitsetD &operator&=(const BitsetD &other);

    BitsetD &operator|=(const BitsetD &other);

    bool operator==(const BitsetD& other) const;

    class BitProx

    {
    public:
        BitProx() = delete;
        BitProx(const BitProx&) = delete;
        ~BitProx() = default;
        BitProx& operator=(const BitProx&) = delete;
        BitProx(BitsetD& bs, const int32_t idx) : bs_(bs), idx_(idx) {}
        operator bool() const { return bs_.get(idx_); }
        void operator=(const bool val) { bs_.set(idx_, val); }

    private:
        BitsetD& bs_;
        const int32_t idx_ = 0;
    };

    BitProx operator[](int32_t idx) {
        return BitProx(*this, idx); 
    }

    class BitProxC {
    public:
        BitProxC() = delete;
        BitProxC(const BitProxC&) = delete;
        ~BitProxC() = default;
        BitProxC& operator=(const BitProxC&) = delete;
        BitProxC(const BitsetD& bs, const int32_t idx) : val_(bs.get(idx)) {}
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

    BitsetD invert() noexcept;

    void fill(const bool val) noexcept;


private:
    std::int32_t size_ = 0;
    std::int32_t capacity = 0;
    std::vector<std::uint32_t> bits_;

};




inline BitsetD operator~(const BitsetD& rhs) noexcept { return BitsetD(rhs).invert(); }


BitsetD operator<<(const BitsetD &lhs, const std::int32_t shift);

BitsetD operator>>(const BitsetD &lhs, const std::int32_t shift);

BitsetD operator&(const BitsetD &lhs, const BitsetD &rhs);

BitsetD operator|(const BitsetD &lhs, const BitsetD &rhs);

BitsetD operator^(const BitsetD &lhs, const BitsetD &rhs);

#endif //BitsetD_LIBRARY_H
