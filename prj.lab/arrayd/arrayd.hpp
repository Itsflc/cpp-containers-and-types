#pragma once
#ifndef ARRAYD_ARRAYD_HPP
#define ARRAYD_ARRAYD_HPP

#include <cstddef>

class ArrayD{
  std::ptrdiff_t capacity_ = 0;
  std::ptrdiff_t size_ = 0;
  float* data_ = nullptr;

public: 
  ArrayD();
  ArrayD(std::ptrdiff_t Size);
  ArrayD(const ArrayD &other);
  ArrayD& operator=(const ArrayD& other);
  float& operator[](const std::ptrdiff_t index);
  float operator[](const std::ptrdiff_t index) const;
  std::ptrdiff_t size() const noexcept { return size_; }
  void resize(const std::ptrdiff_t new_size);
  void insert(const std::ptrdiff_t index, const float value);
  void remove(std::ptrdiff_t index);
  ~ArrayD();
}


#endif
