#include <gtest/gtest.h>
#include "LinkedList.hpp"
#include <chrono>
#include <random>
#include <thread>


TEST(LinkedList, LinkedListCreation)
{
    LinkedList<int> list;
    ASSERT_EQ(list.size_, 0);
    ASSERT_EQ(list.size(), 0);          /* After creation size() returns zero */
    ASSERT_EQ(list.head_, (void *)NULL);        /* Check head is null */
    ASSERT_EQ(list.tail_,  (void *)NULL);        /* tail is null */
}

TEST(LinkedList, PopandPeekFromEmptyLinkedList)
{
    LinkedList<int> list;
    ASSERT_ANY_THROW(list.pop_back());
    ASSERT_ANY_THROW(list.back());
}

TEST(LinkedList, PushIntoEmptyLinkedList)
{
    LinkedList<int> list;
    list.push_back(10);
    ASSERT_EQ(list.size(), 1);              /* After push operation of one element size() returns one*/
    ASSERT_NE(list.head_, (void *)NULL);
    ASSERT_NE(list.tail_, (void *)NULL);
    ASSERT_EQ(list.head_, list.tail_);        /* list head and tail should point to the only element */

    /* Push one more element */
    list.push_back(20);
    ASSERT_EQ(list.size(), 2);              /* Sixe return 2 */
    ASSERT_EQ(list.head_->prev, (void *)NULL);
    ASSERT_EQ(list.tail_->next, (void *)NULL);
    ASSERT_EQ(list.head_->next, list.tail_);
    ASSERT_EQ(list.tail_->prev, list.head_);
}


TEST(LinkedList, PushMultipleElementsIntoEmptyLinkedList)
{
    LinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i+10);
        ASSERT_EQ(list.head_->prev, (void *)NULL);
        ASSERT_EQ(list.tail_->next, (void *)NULL);
    }
    ASSERT_EQ(list.size(), 10);               /* After push operation of multiple elements size() returns 10(in this case)*/
}

TEST(LinkedList, PushandPopMultipleElementsIntoEmptyLinkedList)
{
    LinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i+10);
    }
    ASSERT_EQ(list.size(), 10);           /* After push operation of multiple elements size() returns 10(in this case)*/
    for (int i = 9; i >= 0; i--) {
        ASSERT_EQ(list.back(), i+10);      /* check if the same elements are popped in reverse order */
        list.pop_back();
    }
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.head_, (void *)NULL);
    ASSERT_EQ(list.tail_, (void *)NULL);
}


TEST(LinkedList, PushandPopRandomNumberOfElements)
{

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distr(1, 100);   /* Random number  between 1 and 100 */
    uint32_t size = distr(generator);
    LinkedList<int> list;
    std::vector<int> holder;
    for (int i = 0; i < size; i++) {
        int item = distr(generator);
        holder.push_back(item);
        list.push_back(item);
    }
    ASSERT_EQ(list.size(), size);
    for (int i = size-1; i >= 0; i--) {
        int item = list.back();
        ASSERT_EQ(item, holder[i]);
        list.pop_back();
    }
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.head_, (void *)NULL);
    ASSERT_EQ(list.tail_, (void *)NULL);
}


class PrePopulatedLinkedList : public ::testing::Test
{
    public:
        LinkedList<int> *p_list;

        virtual void SetUp() {
            p_list = new LinkedList<int>();
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> distr(1, 100);
            uint32_t size = distr(generator);
            for (int i = 0; i < size; i++) {
                int item = distr(generator);
                p_list->push_back(item);
            }
        }

        virtual void TearDown() {
            delete p_list;
        }
};

TEST_F(PrePopulatedLinkedList, PushonPrePopulatedLinkedList)
{
    uint32_t size = p_list->size();
    auto prev_tail = p_list->tail_;
    p_list->push_back(10);
    ASSERT_EQ(p_list->size(), size+1);            /* Ensure size is increased by 1 */
    ASSERT_EQ(p_list->tail_->prev, prev_tail);
    ASSERT_EQ(prev_tail->next, p_list->tail_);
}

TEST_F(PrePopulatedLinkedList, PoponPrePopulatedLinkedList)
{
    uint32_t size = p_list->size();
    auto tail = p_list->tail_;
    auto prev_tail = tail->prev;
    auto prev_prev_tail = prev_tail->prev;
    p_list->pop_back();
    ASSERT_EQ(p_list->size(), size-1);            /* Ensure size is decreased by 1 */
    ASSERT_EQ(p_list->tail_, prev_tail);
    ASSERT_EQ(p_list->tail_->prev, prev_prev_tail);
    ASSERT_EQ(p_list->tail_->next, (void *)NULL);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

