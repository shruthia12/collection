#include <gtest/gtest.h>
#include "Queue.hpp"
#include <chrono>
#include <random>
#include <thread>


TEST(Queue, QueueCreation)
{
    Queue<int> q;                  /* Create a queue to hold integers */
    ASSERT_EQ(q.size_, 0);         /* On creation ensure size is zero */
    ASSERT_EQ(q.size(), 0);        /* After creation size() returns zero */
}

TEST(Queue, dequeueFromEmptyQueue)
{
    Queue<int> q;
    ASSERT_ANY_THROW(q.dequeue());
}

TEST(Queue, enqueueIntoEmptyQueue)
{
    Queue<int> q;
    q.enqueue(10);
    ASSERT_EQ(q.size(), 1);            /* After enqueue operation of one element size() returns one*/
}


TEST(Queue, enqueueMultipleElementsIntoEmptyQueue)
{
    Queue<int> q;
    for (uint32_t i = 0; i < 10; i++) {
        q.enqueue(i+10);
    }
    ASSERT_EQ(q.size(), 10);               /* After enqueue operation of multiple elements size() returns 10(in this case)*/
}

TEST(Queue, enqueueanddequeueMultipleElementsIntoEmptyQueue)
{
    Queue<int> q;
    for (uint32_t i = 0; i < 10; i++) {
        q.enqueue(i+10);
    }
    ASSERT_EQ(q.size(), 10);           /* After enqueue operation of multiple elements size() returns 10(in this case)*/
    for (uint32_t i = 0; i < 10; i++) {
        ASSERT_EQ(q.dequeue(), i+10);      /* check if the same elements are dequeueped in reverse order */
    }
    ASSERT_EQ(q.size(), 0);
    ASSERT_EQ(q.isEmpty(), true);
}


TEST(Queue, enqueueanddequeueRandomNumberOfElements)
{

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distr(1, 100);   /* Random number  between 1 and 100 */
    uint32_t size = distr(generator);
    Queue<int> q;
    std::vector<int> holder;
    for (uint32_t i = 0; i < size; i++) {
        int item = distr(generator);
        holder.push_back(item);
        q.enqueue(item);
    }
    ASSERT_EQ(q.size(), size);
    for (uint32_t i = 0; i < size; i++) {
        int item = q.dequeue();
        ASSERT_EQ(item, holder[i]);
    }
    ASSERT_EQ(q.size(), 0);
    ASSERT_EQ(q.isEmpty(), true);
}


class PredequeueulatedQueue : public ::testing::Test
{
    public:
        Queue<int> *p_q;

        virtual void SetUp() {
            p_q = new Queue<int>();
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> distr(1, 100);
            uint32_t size = distr(generator);
            for (uint32_t i = 0; i < size; i++) {
                int item = distr(generator);
                p_q->enqueue(item);
            }
        }

        virtual void TearDown() {
            delete p_q;
        }
};

TEST_F(PredequeueulatedQueue, enqueueonPredequeueulatedQueue)
{
    uint32_t size = p_q->size();
    p_q->enqueue(10);
    ASSERT_EQ(p_q->size(), size+1);            /* Ensure size is increased by 1 */
}

TEST_F(PredequeueulatedQueue, dequeueonPredequeueulatedQueue)
{
    uint32_t size = p_q->size();
    p_q->dequeue();
    ASSERT_EQ(p_q->size(), size-1);            /* Ensure size is decreased by 1 */
}


void enqueue_onto_queue(Queue<int> *q, int thread_id)
{
    for(int i = 0; i < 10; i++) {
        q->enqueue( thread_id*10 + i );
    }
}

void dequeue_from_queue(Queue<int> *q)
{
    for(int i = 0; i < 10; i++) {
        q->dequeue();
    }
}

// Non Functional tests
TEST(Queue, MultiThreadedenqueueanddequeue)
{
    std::thread  thrs[10];
    Queue<int> *q = new Queue<int>();

    for (int i = 0; i < 10; i++) {
        thrs[i] = std::thread(enqueue_onto_queue, q, i);
    }

    for (int i = 0; i < 10; i++) {
        thrs[i].join();
    }

    ASSERT_EQ(q->size(), 100);             /* 10 threads each enqueueing 10 items so 100 */

    for (int i = 0; i < 10; i++) {
        thrs[i] = std::thread(dequeue_from_queue, q);
    }

    for (int i = 0; i < 10; i++) {
        thrs[i].join();
    }

    ASSERT_EQ(q->size(), 0);
    ASSERT_EQ(q->isEmpty(), true);

    delete q;
}

TEST(Queue, TimingenqueueanddequeueOp)
{
    Queue<int> q;

    auto start_time = std::chrono::high_resolution_clock::now();
    /* Million enqueue */
    for (int i = 0; i < 1000000; i++) {
        q.enqueue(i);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Time to perform 1 Million enqueuees: " << elapsed_time << " microseconds" << std::endl;
    ASSERT_EQ(q.size(), 1000000);

    start_time = std::chrono::high_resolution_clock::now();
    /* Million enqueue */
    for (int i = 0; i < 1000000; i++) {
        q.dequeue();
    }
    end_time = std::chrono::high_resolution_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Time to perform 1 Million dequeues: " << elapsed_time << " microseconds" << std::endl;
    ASSERT_EQ(q.isEmpty(), true);

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

