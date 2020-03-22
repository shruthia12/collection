#pragma once

template <class T>
struct list_node
{
    T item;
    struct list_node *next;
    struct list_node *prev;
    list_node() : next(NULL), prev(NULL) {}
};

template <class T>
class LinkedList
{
    private:
        struct list_node<T> *head_;
        struct list_node<T> *tail_;
        uint32_t size_;
    public:
        LinkedList() : head_(NULL), tail_(NULL), size_(0) {}
        uint32_t size(void) {return size_;}
        void push_back(T item) {
            struct list_node<T> *node = new struct list_node<T>();
            if (!node) throw ("Insufficient memory");
            node->item = item;
            if (head_ == NULL) head_ = node;
            if (tail_ == NULL) tail_ = node;
            else {
                tail_->next = node;
                node->prev = tail_;
                tail_ = node;
            }
            size_ += 1;
        }
        T back() {
            if (size_ == 0) throw ("Nothing to return from empty list");
            return tail_->item;
        }
        void pop_back() {
            if (size_ == 0) throw ("Nothing to pop");
            if (head_ == tail_) {
                delete head_;
                head_ = NULL;
                tail_ = NULL;
            } else {
                struct list_node<T> *node = tail_;
                tail_ = tail_->prev;
                tail_->next = NULL;
                delete node;
            }
            size_ -= 1;
        }

};
