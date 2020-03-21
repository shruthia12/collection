#pragma once
#include <vector>

template <class T>
class Stack
{
    private:
        uint32_t size_;
        std::vector<T> container_;
    public:
        Stack():size_(0) {}
        uint32_t size(void) { return size_; }
        bool isEmpty(void) { return size_ == 0; }
        void push(T item) { container_.push_back(item); size_ += 1;}
        T pop(void) {
            if (!isEmpty()) {
                auto item = container_.back();
                container_.pop_back();
                size_ -= 1;
                return item;
            } else {
                throw("Cannot pop from empty stack");
            }
        }
};
