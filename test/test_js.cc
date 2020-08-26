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

#include "js-runner/js.h"

TEST(JSRunnerEngineTest, RunCodeTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "(function(x){return x+1;})(5)";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResultAsString();
    ASSERT_EQ(std::string("6"), res);
}

TEST(JSRunnerEngineTest, RunFunctionTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "function RunFunctionTest_add(x) {\n\treturn x+1;\n};";
    runner->setScript(script);
    runner->runScript();

    jerry_value_t a = jerry_create_number(5);
    runner->runFunction(std::string("RunFunctionTest_add"), &a, 1);

    std::string res = runner->getResultAsString();
    ASSERT_EQ(std::string("6"), res);

    jerry_release_value(a);
}

TEST(JSRunnerEngineTest, ES5ArrowFunctionTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "var ES5LetVarTest_foo = x => x * 2;ES5LetVarTest_foo(123)";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResultAsString();
    ASSERT_EQ(std::string("246"), res);
}

TEST(JSRunnerEngineTest, ES5LetVarTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "let ES5LetVarTest_x = 4;ES5LetVarTest_x += 1;ES5LetVarTest_x * 2";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResultAsString();
    ASSERT_EQ(std::string("10"), res);
}

TEST(JSRunnerEngineTest, ES5ConstVarTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "const ES5ConstVarTest_x = 4;ES5ConstVarTest_x * 2";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResultAsString();
    ASSERT_EQ(std::string("8"), res);
}

TEST(JSRunnerEngineTest, FunctionInArrayTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "var FunctionInArrayTest_f = [x => x * 2, x => x + 1]";
    runner->setScript(script);
    runner->runScript();

    jerry_value_t x = jerry_create_number(10);

    runner->runFunction("FunctionInArrayTest_f[0]", &x, 1);
    std::string res = runner->getResultAsString();
    ASSERT_EQ(std::string("20"), res);

    runner->runFunction("FunctionInArrayTest_f[1]", &x, 1);
    res = runner->getResultAsString();
    ASSERT_EQ(std::string("11"), res);

    jerry_release_value(x);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}