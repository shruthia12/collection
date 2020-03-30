#pragma once
#include "LinkedList.hpp"
#include <mutex>

template <class T>
class Stack
{
    private:
        uint32_t size_;
        LinkedList<T> container_;
        std::mutex stack_lock_;
    public:
        Stack():size_(0) {}
        uint32_t size(void) { return size_; }
        bool isEmpty(void) {
            //const std::lock_guard<std::mutex> lock(stack_lock_);
            return size_ == 0;
        }
        void push(T item) {
            const std::lock_guard<std::mutex> lock(stack_lock_);
            container_.push_back(item);
            size_ += 1;
        }
        T pop(void) {
            const std::lock_guard<std::mutex> lock(stack_lock_);
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
