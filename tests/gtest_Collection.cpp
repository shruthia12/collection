#include <gtest/gtest.h>
#include "Collection.hpp"
#include <chrono>
#include <random>


TEST(Collection, errorCreatingCollection)
{
    ASSERT_ANY_THROW(CollectionFactory<int> c(CollectionType::NOT_IMPLEMENTED));
}

TEST(Collection, createCollection)
{
    CollectionFactory<int> fifo(CollectionType::FIFO);
    ASSERT_EQ(fifo.size(), 0);
    ASSERT_EQ(fifo.isEmpty(), true);
    ASSERT_ANY_THROW(fifo.get());

    CollectionFactory<int> lifo(CollectionType::LIFO);
    ASSERT_EQ(lifo.size(), 0);
    ASSERT_EQ(lifo.isEmpty(), true);
    ASSERT_ANY_THROW(lifo.get());
}

TEST(Collection, addgetCollection)
{
    CollectionFactory<int> fifo(CollectionType::FIFO);
    for (int i = 0; i < 10; i++) {
        fifo.add(i);
    }
    ASSERT_EQ(fifo.size(), 10);
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(fifo.get(), i);
    }
    ASSERT_EQ(fifo.size(), 0);
    ASSERT_EQ(fifo.isEmpty(), true);

    CollectionFactory<int> lifo(CollectionType::LIFO);
    for (int i = 0; i < 10; i++) {
        lifo.add(i);
    }
    ASSERT_EQ(lifo.size(), 10);
    for (int i = 9; i >= 0; i--) {
        ASSERT_EQ(lifo.get(), i);
    }
    ASSERT_EQ(lifo.size(), 0);
    ASSERT_EQ(lifo.isEmpty(), true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

