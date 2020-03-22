#pragma once
#include "LinkedList.hpp"
#include <mutex>

template <class T>
class Queue
{
    private:
        uint32_t size_;
        LinkedList<T> container_;
        std::mutex stack_lock_;
    public:
        Queue():size_(0) {}
        uint32_t size(void) { return size_; }
        bool isEmpty(void) { return size_ == 0; }
        void enqueue(T item) {
            const std::lock_guard<std::mutex> lock(stack_lock_);
            container_.push_back(item);
            size_ += 1;
        }
        T dequeue(void) {
            if (!isEmpty()) {
                const std::lock_guard<std::mutex> lock(stack_lock_);
                auto item = container_.front();
                container_.pop_front();
                size_ -= 1;
                return item;
            } else {
                throw("Cannot dequeue from empty queue");
            }
        }
};
