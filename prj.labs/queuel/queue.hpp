#pragma once
#ifndef QUEUEL_QUEUEL_HPP
#def QUEUEL_QUEUEL_HPP


#include <cstddef>
#include <cstdint>
#include <stdexcept>

class QueueL {
public:
    QueueL() = default;
    QueueL(const QueueL& source);
    ~QueueL();
    QueueL& operator=(const QueueL& source);

    [[nodiscard]] bool is_empty() const noexcept;
    void pop() noexcept;
    void push(const int64_t val);
    [[nodiscard]] int64_t& top();
    [[nodiscard]] int64_t top() const;
    void clear() noexcept;

private:
    struct Node {
        int64_t val = 0;
        Node* next = nullptr;
    };

    Node* head_ = nullptr;
    Node* first_ = nullptr;
};

#endif
