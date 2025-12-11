#pragma once
#ifndef STACKL_STACKA_HPP
#define STACKL_STACKA_HPP

#include <cstdint>

class StackA {
private:
	int64_t* data_ = nullptr;
	int64_t size_ = 0;
	int64_t capacity_ = 0;

public:
	StackA();
	StackA(const StackA& other);
	StackA& operator=(const StackA& other);
	bool is_empty() const noexcept;
	void pop() noexcept;
	void push(const int64_t value);
	int64_t& top();
	int64_t top() const;
	void clear() noexcept;
	~StackA() noexcept;
};

#endif
