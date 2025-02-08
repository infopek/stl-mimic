#include <vector.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(VectorTests, VectorAddTest) {
    core::Vector<int> vec{};

    // Initialized with correct length & capacity
    EXPECT_EQ(vec.length(), 0);
    EXPECT_EQ(vec.capacity(), 2);

    vec.pushBack(6);
    vec.pushBack(7);
    vec.pushBack(8);

    // Length & capacity increase dynamically
    EXPECT_EQ(vec.length(), 3);
    EXPECT_EQ(vec.capacity(), 4);

    // Elements are in the vector, in the correct order
    const int* data = vec.data();
    EXPECT_EQ(data[0], 6);
    EXPECT_EQ(data[1], 7);
    EXPECT_EQ(data[2], 8);
}

TEST(VectorTests, VectorPopBackTest) {
    core::Vector<int> vec{};

    vec.pushBack(6);
    vec.pushBack(7);
    vec.pushBack(8);

    vec.popBack();

    EXPECT_EQ(vec.length(), 2);

    EXPECT_EQ(vec[0], 6);
    EXPECT_EQ(vec[1], 7);
    EXPECT_THAT([&]() { vec.at(2);},
        testing::Throws<std::runtime_error>());
}

TEST(VectorTests, VectorPopFrontTest) {
    core::Vector<int> vec{};

    vec.pushBack(6);
    vec.pushBack(7);
    vec.pushBack(8);

    vec.popFront();

    EXPECT_EQ(vec.length(), 2);

    EXPECT_EQ(vec[0], 7);
    EXPECT_EQ(vec[1], 8);
    EXPECT_THAT([&]() { vec.at(2);},
        testing::Throws<std::runtime_error>());
}

TEST(VectorTests, IteratorTest) {
    core::Vector<int> vec{};

    vec.pushBack(1);
    vec.pushBack(4);
    vec.pushBack(6);

    int i = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it, ++i) {
        ASSERT_EQ(*it, vec[i]);
    }

    i = 0;
    for (auto n : vec) {
        ASSERT_EQ(n, vec[i]);
        ++i;
    }
}
