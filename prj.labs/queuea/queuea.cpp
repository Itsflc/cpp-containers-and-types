#include <queuea/queuea.hpp>

QueueA::QueueA() {
	data_ = new int64_t[20];
	size_ = 0;
	capacity_ = 20;
	start_ind = 0;
}

QueueA::QueueA(const QueueA& other) {
	data_ = new int64_t[other.capacity_];
	capacity_ = other.capacity_;
	size_ = other.size_;
	start_ind = 0;
	for (int64_t i = 0; i < other.size_; i++) {
		data_[i] = other.data_[other.start_ind + i];
	}
}

QueueA& QueueA::operator=(const QueueA& other) {
	if (this == &other) { 
		return *this;
	}
	if (data_ != nullptr) { 
		delete[] data_;
		data_ = nullptr;
	}

	data_ = new int64_t[other.capacity_];
	capacity_ = other.capacity_;
	size_ = other.size_;
	start_ind = 0;

	for (int64_t i = 0; i < other.size_; i++) {
		data_[i] = other.data_[other.start_ind + i];
	}
	return *this;
}

bool QueueA::is_empty() const noexcept { return size_ == 0; }

void QueueA::pop() { 
	if (size_ == 0) { 
	throw std::invalid_argument("pop on empty queue"); 
	} 
	else { 
		size_--;
		start_ind++; 
	} 
}


void QueueA::push(const int64_t value) {
	if (size_ + start_ind == capacity_) {
		int64_t* new_data = new int64_t[capacity_ + 10];
		for (int64_t i = 0; i < size_; i++) { 
			new_data[i] = data_[i + start_ind]; 
		}
		capacity_ += 10;
		delete[] data_;
		start_ind = 0;
		data_ = new_data;
	}
	data_[start_ind + size_] = value;
	size_++;
}

int64_t& QueueA::top() {
	if (size_ == 0) { throw std::invalid_argument("top of an empty queue"); }
	return data_[start_ind];
}

int64_t QueueA::top() const {
	if (size_ == 0) { throw std::invalid_argument("top of an empty queue"); }
	return data_[start_ind];
}

void QueueA::clear() noexcept {
	size_ = 0;
	start_ind = 0;
}

QueueA::~QueueA() noexcept {
	delete[] data_;
}


int main() {
	std::cout << "Hello> WORLD";
}
