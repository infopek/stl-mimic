#include <stack.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>

class StackTest : public testing::Test {
protected:
    StackTest() {
        s1.push(6);
        s1.push(7);
        s1.push(9);
        s1.push(1);

        s2.push(1.9f);
        s2.push(2.3f);
        s2.push(4.5f);
    }
    ~StackTest() override {
    }

    void SetUp() override {

    }

    void TearDown() override {

    }

    core::Stack<int> s1;
    core::Stack<float> s2;
};

TEST_F(StackTest, PushWorks) {
    int prevTop = s1.peek();

    s1.push(191);

    EXPECT_NE(prevTop, s1.peek());
    EXPECT_EQ(s1.peek(), 191);
}

TEST_F(StackTest, PopWorks) {
    int prevTop = s2.peek();

    s2.pop();

    EXPECT_NE(s2.peek(), prevTop);
    EXPECT_EQ(s2.peek(), 2.3f);
}

TEST_F(StackTest, EmptyStack_PopThrows) {
    s2.pop();
    s2.pop();
    s2.pop();

    EXPECT_THAT([&]() { s2.pop(); },
        testing::Throws<std::logic_error>());
}

TEST_F(StackTest, EmptyWorks) {
    EXPECT_FALSE(s1.empty());

    s1.pop();
    s1.pop();
    s1.pop();
    s1.pop();

    EXPECT_TRUE(s1.empty());
}
