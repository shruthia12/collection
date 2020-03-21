#include <gtest/gtest.h>
#include "Stack.hpp"

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
    ASSERT_EQ(st.size(), 1);        /* After push operation of one element size() returns one*/
    ASSERT_EQ(st.container_[0], 10);/* check if the same element is pushed into the container*/
}


TEST(Stack, PushMultipleElementsIntoEmptyStack)
{
    Stack<int> st;
    for (int i = 0; i < 10  ; i++)
        st.push(i+10);
        ASSERT_EQ(st.size(), 10);           /* After push operation of multiple elements size() returns 10(in this case)*/
    for (int i = 0; i < 10  ; i++)
        ASSERT_EQ(st.container_[i], i+10); /* check if the same elements are pushed into the container*/
}


TEST(Stack, PushandPopMultipleElementsIntoEmptyStack)
{
    Stack<int> st;
    for (int i = 0; i < 10  ; i++)
        st.push(i+10);
        ASSERT_EQ(st.size(), 10);        /* After push operation of multiple elements size() returns 10(in this case)*/
    for (int i = 9; i >= 0  ; i--)
        ASSERT_EQ(st.pop(), i+10);      /* check if the same elements are popped in reverse order */
}





int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

