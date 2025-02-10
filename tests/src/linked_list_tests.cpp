#include <linked_list.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

class SLinkedListTest : public testing::Test {
protected:
    SLinkedListTest() {
        l1.pushBack(4);
        l1.pushBack(6);

        l2.pushBack(1.0f);
        l2.pushBack(4.3f);
        l2.pushBack(2.2f);

        l3.pushBack("moment");
        l3.pushBack("um");
    }
    ~SLinkedListTest() override
    {
    }

    void SetUp() override {

    }

    void TearDown() override {

    }

    SLinkedList<int> empty_list;
    SLinkedList<int> l1;
    SLinkedList<float> l2;
    SLinkedList<std::string> l3;
};

TEST_F(SLinkedListTest, PushFrontWorks) {
    l1.pushFront(13);
    EXPECT_EQ(l1.front(), 13);
}

TEST_F(SLinkedListTest, PushBackWorks) {
    l2.pushBack(3.14f);
    EXPECT_EQ(l2.back(), 3.14f);
}

TEST_F(SLinkedListTest, InsertWorks) {
    l3.insert(1, "tester");

    std::string expected[] = { "moment", "tester", "um" };
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(l3.front(), expected[i]);
    }
}

TEST_F(SLinkedListTest, InvalidIndex_InsertThrows) {
    EXPECT_THAT([&]() { l2.insert(4, 7.0f); },
        testing::Throws<std::out_of_range>());
}

TEST_F(SLinkedListTest, PopFrontWorks) {
    EXPECT_EQ(l1.front(), 4);
    l1.popFront();
    EXPECT_EQ(l1.front(), 6);
}

TEST_F(SLinkedListTest, PopBackWorks) {
    EXPECT_EQ(l1.back(), 6);
    l1.popBack();
    EXPECT_EQ(l1.back(), 4);
}

TEST_F(SLinkedListTest, EraseWorks) {
    l2.erase(4.3f);
    EXPECT_FALSE(l2.find(4.3f));
}

TEST_F(SLinkedListTest, InvalidItem_EraseThrows) {
    EXPECT_THAT([&]() { l2.erase(7.0f); },
        testing::Throws<std::invalid_argument>());
}

TEST_F(SLinkedListTest, GetFrontWorks) {
    EXPECT_EQ(l1.front(), 4);
    EXPECT_EQ(l2.front(), 1.0f);
    EXPECT_EQ(l3.front(), "moment");
}

TEST_F(SLinkedListTest, GetBackWorks) {
    EXPECT_EQ(l1.back(), 6);
    EXPECT_EQ(l2.back(), 2.2f);
    EXPECT_EQ(l3.back(), "um");
}

TEST_F(SLinkedListTest, FindWorks) {
    EXPECT_TRUE(l1.find(4));
    EXPECT_TRUE(l2.find(2.2f));
    EXPECT_TRUE(l3.find("um"));

    EXPECT_FALSE(l1.find(5));
    EXPECT_FALSE(l2.find(3.2f));
    EXPECT_FALSE(l3.find("qum"));
}

TEST_F(SLinkedListTest, EmptyWorks) {
    EXPECT_TRUE(empty_list.empty());

    EXPECT_FALSE(l2.empty());
    EXPECT_FALSE(l3.empty());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}