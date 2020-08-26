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

#include "js-runner/js.h"

TEST(JSRunnerEngineTest, RunCodeTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "(function(x){return x+1;})(5)";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("6"), res);
}

TEST(JSRunnerEngineTest, RunFunctionTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "function RunFunctionTest_add(x) {\n\treturn x+1;\n};";
    runner->setScript(script);
    runner->runScript();

    jerry_value_t a = jerry_create_number(5);
    runner->runFunction(std::string("RunFunctionTest_add"), &a, 1);

    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("6"), res);

    jerry_release_value(a);
}

TEST(JSRunnerEngineTest, RunUnameFunctionTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "var RunUnameFunctionTest_add = x => {\n\treturn x+1;\n};";
    runner->setScript(script);
    runner->runScript();

    jerry_value_t a = jerry_create_number(5);
    runner->runFunction(std::string("RunUnameFunctionTest_add"), &a, 1);

    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("6"), res);

    jerry_release_value(a);
}

TEST(JSRunnerEngineTest, ES5ArrowFunctionTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "var ES5LetVarTest_foo = x => x * 2;ES5LetVarTest_foo(123)";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("246"), res);
}

TEST(JSRunnerEngineTest, ES5LetVarTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "let ES5LetVarTest_x = 4;ES5LetVarTest_x += 1;ES5LetVarTest_x * 2";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("10"), res);
}

TEST(JSRunnerEngineTest, ES5ConstVarTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "const ES5ConstVarTest_x = 4;ES5ConstVarTest_x * 2";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("8"), res);
}
// TEST(JSRunnerEngineTest, LongCodeTest) {
//     auto runner = extension::JSContainer::getInstance();
//     std::ifstream in1("./../../extension/default.libstring.js");
//     std::ifstream in2("./../../extension/default.libscanner.js");
//     std::ifstream in3("./../../extension/default.header.js");
//     std::ofstream out3("./test.js");
//     std::string script1;
//     std::string script2;
//     std::string script3;
//     in1 >> script1;
//     in1.close();
//     in2 >> script2;
//     in2.close();
//     in3 >> script3;
//     out3 << script3;
//     runner->setScript(script1);
//     runner->runScript();
//     runner->setScript(script2);
//     runner->runScript();
//     runner->setScript(script3);
//     runner->runScript();
//     jerry_value_t js_markdown[1];
//     js_markdown[0] = jerry_create_string((const jerry_char_t *)"# abc");
//     runner->runFunction("render[0]", js_markdown, 1);
//     std::string res = runner->getResualtAsString();
//     ASSERT_EQ(std::string("<h1>abc</h1>"), res);
// }

TEST(JSRunnerEngineTest, FunctionInArrayTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "var FunctionInArrayTest_f = [x => x * 2, x => x + 1]";
    runner->setScript(script);
    runner->runScript();

    jerry_value_t x = jerry_create_number(10);

    runner->runFunction("FunctionInArrayTest_f[0]", &x, 1);
    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("20"), res);

    runner->runFunction("FunctionInArrayTest_f[1]", &x, 1);
    res = runner->getResualtAsString();
    ASSERT_EQ(std::string("11"), res);

    jerry_release_value(x);
}

TEST(JSRunnerEngineTest, TestTwice) {
    auto runner = extension::JSContainer::getInstance();
    std::string script1 = "var render = [x => {return x + 1;}];";
    std::string script2 = "var render = [y => {return y + 2;}];";
    jerry_value_t js_number[1];
    js_number[0] = jerry_create_number(5);
    runner->setScript(script1);
    runner->runScript();
    runner->runFunction("render[0]", js_number, 1);

    std::string res1 = runner->getResualtAsString();

    runner->setScript(script2);
    runner->runScript();
    runner->runFunction("render[0]", js_number, 1);

    std::string res2 = runner->getResualtAsString();

    ASSERT_EQ(res1, "6");
    ASSERT_EQ(res2, "7");
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

