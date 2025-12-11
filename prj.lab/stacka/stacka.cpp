#include <stacka/stacka.hpp>
#include<cstdint>
#include<stdexcept>

StackA::StackA() {
	data_ = new int64_t[10];
	size_ = 0;
	capacity_ = 10;
}

StackA::StackA(const StackA& other) {
	data_ = new int64_t[other.capacity_];
	capacity_ = other.capacity_;
	size_ = other.size_;
	for (int64_t i = 0; i < other.size_; i++) { data_[i] = other.data_[i]; }
}

StackA& StackA::operator=(const StackA& other) {
	if (data_ != nullptr) { delete[] data_; }
	data_ = new int64_t[other.capacity_];
	capacity_ = other.capacity_;
	size_ = other.size_;
	for (int64_t i = 0; i < other.size_; i++) { data_[i] = other.data_[i]; }
	return *this;
}

bool StackA::is_empty() const noexcept { return size_ == 0; }

void StackA::pop() noexcept { if (size_ > 0) { size_--; } }


void StackA::push(const int64_t value) {
	if (size_ == capacity_) {
		int64_t* new_data = new int64_t[size_ + 10];
		for (int64_t i = 0; i < size_; i++) { new_data[i] = data_[i]; }
		capacity_ += 10;
		delete[] data_;
		data_ = new_data;
	}
	data_[size_] = value;
	size_++;
}

int64_t& StackA::top() {
	if (size_ == 0) { throw std::invalid_argument("top of an empty stack"); }
	return data_[size_ - 1];
}

int64_t StackA::top() const {
	if (size_ == 0) { throw std::invalid_argument("top of an empty stack"); }
	return data_[size_ - 1];
}

void StackA::clear() noexcept { 
	size_ = 0; 
	data_[0] = 0;
}

StackA::~StackA() noexcept {
	delete[] data_;
