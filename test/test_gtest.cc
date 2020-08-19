// -*- C++ -*- LighteningZero

// Copyright (C) 2020  Lightening Zero
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <string>
#include <gtest/gtest.h>

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

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}