#pragma once
#ifndef ARRAYT_ARRAYT_HPP
#define ARRAYT_ARRAYT_HPP


#include <cstddef>
#include<stdexcept>
#include<iostream>

template<typename T>
class ArrayT {

private:
	std::ptrdiff_t capacity_ = 0;
	std::ptrdiff_t size_ = 0;
	T* data_ = nullptr;

public:
	ArrayT() : ArrayT(1) {}
	ArrayT(std::ptrdiff_t Size) {
		if (Size < 0) {
			throw std::invalid_argument("Size should not be negative");
		}
		this->size_ = Size;
		this->capacity_ = Size + 3;
		this->data_ = new T[capacity_];
		for (int i = 0; i < capacity_; i++)
		{
			data_[i] = T();
		}
	}

	ArrayT(const ArrayT& other)
	{
		this->data_ = new T[other.capacity_];
		this->size_ = other.size_;
		this->capacity_ = other.capacity_;
		for (int i = 0; i < other.capacity_; i++)
		{
			this->data_[i] = other.data_[i];
		}
	}

	ArrayT& operator=(const ArrayT& other) {
		if (&other == this) {
			return *this;
		}
		if (this->data_ != nullptr) {
			delete[] this->data_;
		}
		this->capacity_ = other.capacity_;
		this->data_ = new T[other.capacity_];
		this->size_ = other.size_;

		for (int i = 0; i < other.capacity_; i++)
		{
			this->data_[i] = other.data_[i];
		}
		return *this;
	}

	T& operator[](const std::ptrdiff_t index) {
		if (index < 0 || index >= size_) {
			throw std::invalid_argument("Index out of range");
		}
		return data_[index];
	}

	T operator[](const std::ptrdiff_t index) const {
		if (index < 0 || index >= size_) {
			throw std::invalid_argument("Index out of range");
		}
		return data_[index];
	}

	std::ptrdiff_t size() const noexcept { return size_; }

	void resize(const std::ptrdiff_t new_size) {
		if (new_size < 0) {
			throw std::invalid_argument("Size should not be negative");
		}

		else if (new_size <= size_) {
			size_ = new_size;
		}

		else if (new_size <= capacity_) {
			for (std::ptrdiff_t i = size_; i < new_size; i++) {
				data_[i] = T();
			}
			size_ = new_size;
		}
		else {
			T* new_data = new T[new_size];

			for (std::ptrdiff_t i = 0; i < size_; i++) {
				new_data[i] = data_[i];
			}
			for (std::ptrdiff_t i = size_; i < new_size; i++) {
				new_data[i] = T();
			}
			delete[] data_;

			data_ = new_data;
			capacity_ = new_size;
			size_ = new_size;
		}
	}

	void insert(const std::ptrdiff_t index, const T value) {
		if (index < 0 || index > size_) {
			throw std::invalid_argument("Index out of range");
		}
		if (size_ == capacity_) {
			T* new_data = new T[size_ + 4];
			for (std::ptrdiff_t i = 0; i < size_; i++) {
				new_data[i] = data_[i];
			}
			for (std::ptrdiff_t i = size_; i < size_ + 4; i++) {
				new_data[i] = T();
			}
			delete[] data_;

			data_ = new_data;
			capacity_ = size_ + 4;
		}
		for (int i = size_ - 1; i >= index; i--) {
			data_[i + 1] = data_[i];
		}
		data_[index] = value;
		size_++;
	}

	void remove(std::ptrdiff_t index) {
		if (index < 0 || index >= size_) {
			throw std::invalid_argument("Index out of range");
		}
		for (int i = index + 1; i < size_; i++) {
			data_[i - 1] = data_[i];
		}
		resize(size_ - 1);
	}

	~ArrayT() {
		delete[] data_;
	}
};

#endif
