#include <cstddef>
#include <cstdint>

class StackL {
public:
    StackL() = default;

    StackL(const StackL& source);

    ~StackL() = default;

    StackL& operator=(const StackL& source);

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
};
