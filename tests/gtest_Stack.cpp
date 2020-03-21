#include <gtest/gtest.h>
#include "Stack.hpp"
#include <random>
#include <thread>


TEST(Stack, StackCreation)
{
    Stack<int> st;                  /* Create a stack to hold integers */
    ASSERT_EQ(st.size_, 0);         /* On creation ensure size is zero */
    ASSERT_EQ(st.size(), 0);        /* After creation size() returns zero */
}

TEST(Stack, PopFromEmptyStack)
{
    Stack<int> st;
    ASSERT_ANY_THROW(st.pop());
}

TEST(Stack, PushIntoEmptyStack)
{
    Stack<int> st;
    st.push(10);
    ASSERT_EQ(st.size(), 1);            /* After push operation of one element size() returns one*/
    ASSERT_EQ(st.container_[0], 10);    /* check if the same element is pushed into the container*/
}


TEST(Stack, PushMultipleElementsIntoEmptyStack)
{
    Stack<int> st;
    for (int i = 0; i < 10; i++) {
        st.push(i+10);
    }
    ASSERT_EQ(st.size(), 10);               /* After push operation of multiple elements size() returns 10(in this case)*/
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(st.container_[i], i+10);  /* check if the same elements are pushed into the container*/
    }
}

TEST(Stack, PushandPopMultipleElementsIntoEmptyStack)
{
    Stack<int> st;
    for (int i = 0; i < 10; i++) {
        st.push(i+10);
    }
    ASSERT_EQ(st.size(), 10);           /* After push operation of multiple elements size() returns 10(in this case)*/
    for (int i = 9; i >= 0; i--) {
        ASSERT_EQ(st.pop(), i+10);      /* check if the same elements are popped in reverse order */
    }
}


TEST(Stack, PushandPopRandomNumberOfElements)
{

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distr(1, 100);   /* Random number  between 1 and 100 */
    uint32_t size = distr(generator);
    Stack<int> st;
    std::vector<int> holder;
    for (int i = 0; i < size; i++) {
        int item = distr(generator);
        holder.push_back(item);
        st.push(item);
    }
    ASSERT_EQ(st.size(), size);
    for (int i = size-1; i >= 0; i--) {
        int item = st.pop();
        ASSERT_EQ(item, holder[i]);
    }
    ASSERT_EQ(st.size(), 0);
    ASSERT_EQ(st.isEmpty(), true);
}


class PrePopulatedStack : public ::testing::Test
{
    public:
        Stack<int> *p_st;

        virtual void SetUp() {
            p_st = new Stack<int>();
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> distr(1, 100);
            uint32_t size = distr(generator);
            for (int i = 0; i < size; i++) {
                int item = distr(generator);
                p_st->push(item);
            }
        }

        virtual void TearDown() {
            delete p_st;
        }
};

TEST_F(PrePopulatedStack, PushonPrePopulatedStack)
{
    uint32_t size = p_st->size();
    p_st->push(10);
    ASSERT_EQ(p_st->size(), size+1);            /* Ensure size is increased by 1 */
}

TEST_F(PrePopulatedStack, PoponPrePopulatedStack)
{
    uint32_t size = p_st->size();
    p_st->pop();
    ASSERT_EQ(p_st->size(), size-1);            /* Ensure size is decreased by 1 */
}


void push_onto_stack(Stack<int> *st, int thread_id)
{
    for(int i = 0; i < 10; i++) {
        st->push( thread_id*10 + i );
    }
}

void pop_from_stack(Stack<int> *st)
{
    for(int i = 0; i < 10; i++) {
        st->pop();
    }
}

// Non Functional tests
TEST(Stack, MultiThreadedPushandPop)
{
    std::thread  thrs[10];
    Stack<int> *st = new Stack<int>();

    for (int i = 0; i < 10; i++) {
        thrs[i] = std::thread(push_onto_stack, st, i);
    }

    for (int i = 0; i < 10; i++) {
        thrs[i].join();
    }

    ASSERT_EQ(st->size(), 100);             /* 10 threads each pushing 10 items so 100 */

    for (int i = 0; i < 10; i++) {
        thrs[i] = std::thread(pop_from_stack, st);
    }

    for (int i = 0; i < 10; i++) {
        thrs[i].join();
    }

    ASSERT_EQ(st->size(), 0);
    ASSERT_EQ(st->isEmpty(), true);

    delete st;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

