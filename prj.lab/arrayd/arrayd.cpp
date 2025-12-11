#include "arrayd.hpp"
#include<stdexcept>
#include <cstddef>

ArrayD::ArrayD() : ArrayD(1) {}
ArrayD::ArrayD(std::ptrdiff_t Size) {
	if (Size < 0) { throw std::invalid_argument("Size should not be negative"); }
  
	this->size_ = Size;
	this->capacity_ = Size + 3;
	this->data_ = new float[capacity_];
	for (int i = 0; i < capacity_; i++) { data_[i] = 0; }
}

ArrayD::ArrayD(const ArrayD &other)
	{
		this->data_ = new float[other.capacity_];
		this->size_ = other.size_;
		this->capacity_ = other.capacity_;
		for (int i = 0; i < other.capacity_; i++) { this->data_[i] = other.data_[i]; }
	}

ArrayD& ArrayD::operator=(const ArrayD& other) {
		if (this != &other) {
			if (this->data_ != nullptr) { delete[] this->data_; }
			this->capacity_ = other.capacity_;
			this->data_ = new float[other.capacity_];
			this->size_ = other.size_;
			for (int i = 0; i < other.capacity_; i++) { this->data_[i] = other.data_[i]; }
		}
		return *this;
	}


float& ArrayD::operator[](const std::ptrdiff_t index) {
	if (index < 0 || index >= size_) { throw std::invalid_argument("Index out of range"); }
	return data_[index];
}

float ArrayD::operator[](const std::ptrdiff_t index) const {
	if (index < 0 || index >= size_) { throw std::invalid_argument("Index out of range"); }
	return data_[index];
}



void ArrayD::resize(const std::ptrdiff_t new_size) {
	if (new_size < 0) { throw std::invalid_argument("Size should not be negative"); }

	else if (new_size <= size_) { size_ = new_size; }

	else if (new_size <= capacity_) {
		for (std::ptrdiff_t i = size_; i < new_size; i++) { data_[i] = 0.0; }
		size_ = new_size;
	}
	else {
		float* new_data = new float[new_size];

		for (std::ptrdiff_t i = 0; i < size_; i++) { new_data[i] = data_[i]; }
		for (std::ptrdiff_t i = size_; i < new_size; i++) { new_data[i] = 0.0; }
		delete[] data_;

		data_ = new_data;
		capacity_ = new_size;
		size_ = new_size;
	}
}


 void ArrayD::insert(const std::ptrdiff_t index, const float value) {
		if (index < 0 || index > size_) { throw std::invalid_argument("Index out of range"); }
		if (size_ == capacity_) {
			float* new_data = new float[size_ + 4];
			for (std::ptrdiff_t i = 0; i < size_; i++) { new_data[i] = data_[i]; }
			for (std::ptrdiff_t i = size_; i < size_ + 4; i++) { new_data[i] = 0.0; }
			delete[] data_;
			data_ = new_data;
			capacity_ = size_ + 4;
		}
   
		for (int i = size_ - 1; i >= index; i--) { data_[i + 1] = data_[i]; }
		data_[index] = value;
		size_++;
	}


	void ArrayD::remove(std::ptrdiff_t index) {
		if (index < 0 || index >= size_) { throw std::invalid_argument("Index out of range"); }
		for (int i = index + 1; i < size_; i++) { data_[i - 1] = data_[i]; }
		resize(size_ - 1);
	}

ArrayD::~ArrayD(){
	delete[] data_;
}





