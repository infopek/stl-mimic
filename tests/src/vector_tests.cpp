#include <vector.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(VectorTests, VectorAddTest) {
    core::Vector vec{};

    // Initialized with correct length & capacity
    EXPECT_EQ(vec.length(), 0);
    EXPECT_EQ(vec.capacity(), 1);

    vec.add(6);
    vec.add(7);
    vec.add(8);

    // Length & capacity increase dynamically
    EXPECT_EQ(vec.length(), 3);
    EXPECT_EQ(vec.capacity(), 4);

    // Elements are in the vector, in the correct order
    const int* data = vec.data();
    EXPECT_EQ(data[0], 6);
    EXPECT_EQ(data[1], 7);
    EXPECT_EQ(data[2], 8);
}

TEST(VectorTests, VectorPopTest) {
    core::Vector vec{};

    vec.add(6);
    vec.add(7);
    vec.add(8);

    const int* data1 = vec.data();
    EXPECT_EQ(data1[0], 6);
    EXPECT_EQ(data1[1], 7);
    EXPECT_EQ(data1[2], 8);

    vec.pop();

    const int* data2 = vec.data();
    EXPECT_EQ(data1[0], 6);
    EXPECT_EQ(data1[1], 7);
    EXPECT_THAT([]() {throw std::runtime_error("Index out of bounds"); },
        Throws<std::runtime_error>());
}
