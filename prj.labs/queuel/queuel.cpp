#include <queuel/queuel.hpp>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

QueueL::QueueL(const QueueL& source) {
    if (source.head_ == nullptr) {
        head_ = nullptr;
        return;
    }

    head_ = new Node{ source.head_->val, nullptr };
    Node* current = head_;
    Node* source_current = source.head_->next;

    while (source_current != nullptr) {
        current->next = new Node{ source_current->val, nullptr };
        current = current->next;
        source_current = source_current->next;
    }
    first_ = current;
}

QueueL& QueueL::operator=(const QueueL& source) {
    if (this == &source) {
        return *this;
    }
    clear();
    if (source.head_ == nullptr) {
        head_ = nullptr;
        return *this;
    }

    head_ = new Node{ source.head_->val, nullptr };
    Node* current = head_;
    Node* source_current = source.head_->next;

    while (source_current != nullptr) {
        current->next = new Node{ source_current->val, nullptr };
        current = current->next;
        source_current = source_current->next;
    }
    first_ = current;
    return *this;
}

bool QueueL::is_empty() const noexcept {
    return (head_ == nullptr);
}

void QueueL::pop() noexcept {
    if (head_ == nullptr) {
        return;
    }
    if (head_->next == nullptr) {
        Node* temp = head_;
        head_ = nullptr;
        first_ = nullptr;
        delete temp;
        return;
    }

    Node* new_first = head_;
    
    while (new_first->next != first_) {
        new_first = new_first->next;
    }
    Node* temp = first_;
    first_ = new_first;
    new_first->next = nullptr;
    delete temp;
}

void QueueL::push(const int64_t val) {
    Node* new_node = new Node{ val, head_ };
    if (head_ == nullptr) {
        first_ = new_node;
    }
    head_ = new_node;
}

int64_t QueueL::top() const {
    if (head_ == nullptr) {
        throw std::invalid_argument("Top on empty queue");
    }
    return first_->val;
}

int64_t& QueueL::top() {
    if (head_ == nullptr) {
        throw std::invalid_argument("Top on empty queue");
    }
    return first_->val;
}

void QueueL::clear() noexcept {
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
    first_ = nullptr;
}

QueueL::~QueueL() {
    clear();
}
