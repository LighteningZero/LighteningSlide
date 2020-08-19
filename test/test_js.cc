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
    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("6"), res);
}

TEST(JSRunnerEngineTest, RunFunctionTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "function add(x) {\n\treturn x+1;\n};";
    runner->setScript(script);
    runner->runScript();
    
    jerry_value_t a = jerry_create_number(5);
    runner->runFunction(std::string("add"), &a, 1);

    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("6"), res);

    jerry_release_value(a);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}