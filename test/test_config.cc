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

#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "config-reader/config.h"

TEST(ConfigReaderTest, getItemAsInt) {
    std::string JsonContent = "{"
                              "\"name\":\"10\","
                              "\"age\":14,"
                              "\"major\":["
                              "{\"AI1\":\"MachineLearning\"},"
                              "{\"AI2\":\"DeepLearning\"},"
                              "{\"AI3\":\"ComputerVision\"}"
                              "]"
                              "}";
    extension::ConfigContainer config;
    config.loadFromString(JsonContent);
    int res = config.getItemAsInt("age");
    ASSERT_EQ(14, res);
}

TEST(ConfigReaderTest, loadFromFile) {
    std::string JsonContent = "{"
                              "\"name\":\"10\","
                              "\"age\":14,"
                              "\"major\":{"
                              "\"AI1\":101,"
                              "\"AI2\":\"DeepLearning\","
                              "\"AI3\":\"ComputerVision\""
                              "}"
                              "}";
    FILE* file = fopen("config_test.json", "w");
    fprintf(file, "%s\n", JsonContent.c_str());
    fclose(file);
    extension::ConfigContainer config;
    config.loadFromFile("config_test.json");
    std::string res = config.getItemAsString("major:AI2");
    ASSERT_EQ("DeepLearning", res);
}

TEST(ConfigReaderTest, getItemAsInt2) {
    std::string JsonContent = "{"
                              "\"name\":\"10\","
                              "\"age\":14,"
                              "\"major\":{"
                              "\"AI1\":101,"
                              "\"AI2\":\"DeepLearning\","
                              "\"AI3\":\"ComputerVision\""
                              "}"
                              "}";
    extension::ConfigContainer config;
    config.loadFromString(JsonContent);
    int res = config.getItemAsInt("major:AI1");
    ASSERT_EQ(101, res);
}

TEST(ConfigReaderTest, getItemAsString) {
    std::string JsonContent = "{"
                              "\"name\":\"10\","
                              "\"age\":14,"
                              "\"major\":{"
                              "\"AI1\":101,"
                              "\"AI2\":\"DeepLearning\","
                              "\"AI3\":\"ComputerVision\""
                              "}"
                              "}";
    extension::ConfigContainer config;
    config.loadFromString(JsonContent);
    std::string res = config.getItemAsString("name");
    ASSERT_EQ("10", res);
}

TEST(ConfigReaderTest, getItemAsString2) {
    std::string JsonContent = "{"
                              "\"name\":\"10\","
                              "\"age\":14,"
                              "\"major\":{"
                              "\"AI1\":101,"
                              "\"AI2\":\"DeepLearning\","
                              "\"AI3\":\"ComputerVision\""
                              "}"
                              "}";
    extension::ConfigContainer config;
    config.loadFromString(JsonContent);
    std::string res = config.getItemAsString("major:AI2");
    ASSERT_EQ("DeepLearning", res);
}

TEST(ConfigReaderTest, getItemAsBool) {
    std::string JsonContent = "{"
                              "\"name\":\"10\","
                              "\"male\":true,"
                              "\"major\":{"
                              "\"AI1\":101,"
                              "\"AI2\":\"DeepLearning\","
                              "\"AI3\":\"ComputerVision\""
                              "}"
                              "}";
    extension::ConfigContainer config;
    config.loadFromString(JsonContent);
    bool res = config.getItemAsBool("male");
    ASSERT_EQ(true, res);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}