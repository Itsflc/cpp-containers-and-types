#pragma once
#ifndef QUEUEA_QUEUEA_HPP
#define QUEUEA_QUEUEA_HPP

#include<cstdint>
#include<stdexcept>
#include<iostream>

class QueueA {
private:
	int64_t* data_ = nullptr;
	int64_t size_ = 0;
	int64_t capacity_ = 0;
	int64_t start_ind = 0;

public:
	QueueA();
	QueueA(const QueueA& other);
	QueueA& operator=(const QueueA& other);
	bool is_empty() const noexcept;
	void pop();
	void push(const int64_t value);
	int64_t& top();
	int64_t top() const;
	void clear() noexcept;
	~QueueA() noexcept;
};

#endif
