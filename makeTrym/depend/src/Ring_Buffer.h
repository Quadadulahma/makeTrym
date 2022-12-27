#pragma once

#include <array>
#include <cassert>

template <typename T, std::size_t N>
class Ring_Buffer {
public:
    Ring_Buffer() : head_(0), tail_(0) {}

    void push(T element) {
        if (size() + 1 == N) {
            tail_ = (tail_ + 1) % N;
        }
        buffer_[head_] = element;
        head_ = (head_ + 1) % N;
    }

    T& last_element() const {
        assert(!IsEmpty());  // Check that the buffer is not empty.
        return buffer_[(head_ - 1 + N) % N];
    }

    bool is_empty() const {return head_ == tail_;  }

    std::size_t size() const {
        if (head_ >= tail_) {
            return head_ - tail_;
        }
        else {
            return N - (tail_ - head_);
        }
    }

private:
    std::array<T, N> buffer_;
    std::size_t head_;
    std::size_t tail_;
};