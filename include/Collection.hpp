#pragma once
#include <cstdint>
#include <iostream>

#include "Stack.hpp"
#include "Queue.hpp"

enum class CollectionType
{
    FIFO,
    LIFO,
    NOT_IMPLEMENTED
};

template <class T>
class AbstractCollection
{
    public:
        virtual void add(T) = 0;
        virtual T get(void) = 0;
        virtual uint32_t size(void) = 0;
        virtual bool isEmpty(void) = 0;
};

template <class T>
class CollectionFactory : public AbstractCollection<T>
{
    private:
        CollectionType type_;
        Stack<T> *st;
        Queue<T> *q;
    public:
        explicit CollectionFactory(CollectionType);
        void add(T) override;
        T get(void) override;
        uint32_t size(void) override;
        bool isEmpty(void) override;
        ~CollectionFactory(void);

};

// Templated function definitions
template <class T>
CollectionFactory<T>::CollectionFactory(CollectionType type) : type_(type)
{
    switch(type_)
    {
        case CollectionType::FIFO:
            /* Create a queue here */
            std::cout << "Creating a FIFO" << std::endl;
            q = new Queue<T>();
            break;
        case CollectionType::LIFO:
            /* Create a stack here */
            std::cout << "Creating a LIFO" << std::endl;
            st = new Stack<T>();
            break;
        default:
            throw ("Not a valid collection type");
            break;
    }
}

template <class T>
CollectionFactory<T>::~CollectionFactory(void)
{
    switch(type_)
    {
        case CollectionType::FIFO:
            /* Create a queue here */
            std::cout << "Destroying a FIFO" << std::endl;
            delete q;
            break;
        case CollectionType::LIFO:
            /* Create a stack here */
            std::cout << "Destroying a LIFO" << std::endl;
            delete st;
            break;
    }
}

template <class T>
void CollectionFactory<T>::add(T item)
{
    switch(type_)
    {
        case CollectionType::FIFO:
            /* Enqueue into queue here*/
            q->enqueue(item);
            break;
        case CollectionType::LIFO:
            /* Push into stack here */
            st->push(item);
            break;
    }

}

template <class T>
T CollectionFactory<T>::get()
{
    T item;
    switch(type_)
    {
        case CollectionType::FIFO:
            /* dequeue from queue here */
            item = q->dequeue();
            break;
        case CollectionType::LIFO:
            /* pop from stack here */
            item = st->pop();
            break;
    }

    return item;
}

template <class T>
uint32_t CollectionFactory<T>::size()
{
    uint32_t size;
    /* Return size of the collection here */
    switch(type_)
    {
        case CollectionType::FIFO:
            /* dequeue from queue here */
            size = q->size();
            break;
        case CollectionType::LIFO:
            /* pop from stack here */
            size = st->size();
            break;
    }

    return size;
}

template <class T>
bool CollectionFactory<T>::isEmpty()
{
    /* Return true if collection is empty */
    bool isEmpty;
    /* Return size of the collection here */
    switch(type_)
    {
        case CollectionType::FIFO:
            /* dequeue from queue here */
            isEmpty = q->isEmpty();
            break;
        case CollectionType::LIFO:
            /* pop from stack here */
            isEmpty = st->isEmpty();
            break;
    }

    return isEmpty;
}

