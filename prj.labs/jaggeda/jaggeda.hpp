// 2026 by Polevoi Dmitry under Unlicense

#pragma once
#ifndef JAGGEDA_JAGGEDA_HPP
#define JAGGEDA_JAGGEDA_HPP

#include <cstdint>

class JaggedA {
public:
    JaggedA() noexcept;
    JaggedA(const JaggedA&) noexcept;
    JaggedA(JaggedA&&) noexcept;
    JaggedA(const int siz);

    JaggedA& operator=(const JaggedA& other) noexcept;
    JaggedA& operator=(JaggedA&& other) noexcept;

    ~JaggedA() noexcept;

    bool operator==(const JaggedA& rhs) const noexcept;

    [[nodiscard]] int32_t size() const noexcept;
    void resize(const int32_t size);

    [[nodiscard]] int32_t size(const int32_t i) const;
    void resize(const int32_t i, const int32_t size);

    [[nodiscard]] int32_t& at(const int32_t i, const int32_t j);
    [[nodiscard]] const int32_t& at(const int32_t i, const int32_t j) const;

    void swap(const int32_t i_l, const int32_t i_r);

    void insert(const int32_t i);
    void remove(const int32_t i);

    void insert(const int32_t i, const int32_t j);
    void remove(const int32_t i, const int32_t j);

private:
    int32_t** data = nullptr;
    int32_t  rows = 0;
    int32_t* sizes = nullptr;
};

#endif
