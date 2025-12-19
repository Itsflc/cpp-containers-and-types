#include "stackl.hpp"

StackL::StackL(const StackL& source) {
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
}

StackL& StackL::operator=(const StackL& source) {
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

    return *this;
}

bool StackL::is_empty() const noexcept {
    return (head_ == nullptr);
}

void StackL::pop() noexcept {
    if (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

void StackL::push(const int64_t val) {
    Node* new_node = new Node{ val, head_ };
    head_ = new_node;
}

int64_t& StackL::top() {
    return head_->val;
}

int64_t StackL::top() const {
    return head_->val;
}

void StackL::clear() noexcept {
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}
