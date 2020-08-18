#include <gtest/gtest.h>
#include <string>

TEST(GoogleTestFrameworkTests, EqualTest) {
    EXPECT_EQ(3, 1 + 2);
    EXPECT_EQ(6, 7 - 1);
    EXPECT_EQ(6, 6);
    EXPECT_STREQ("123", "123");
    EXPECT_EQ(nullptr, nullptr);

    EXPECT_EQ(std::string("123"), std::string("123"));
}

TEST(GoogleTestFrameworkTests, NotEqualTest) {
    EXPECT_NE(5, 6);
    EXPECT_NE("123", "123e");
}

TEST(GoogleTestFrameworkTests, LessTest) {
    EXPECT_LT(23, 34);
    EXPECT_LT(23, 24);

    EXPECT_LE(23, 23);
    EXPECT_LE(23, 234);
}

TEST(GoogleTestFrameworkTests, GreaterTest) {
    EXPECT_GT(24, 23);
    EXPECT_GT(234, 24);

    EXPECT_GE(23, 23);
    EXPECT_GE(333, 234);
}

TEST(GoogleTestFrameworkTests, BooleanTest) {
    EXPECT_TRUE(true);
    EXPECT_TRUE(1);
    EXPECT_TRUE(12);

    EXPECT_FALSE(false);
    EXPECT_FALSE(0);
}
