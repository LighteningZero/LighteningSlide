#include <gtest/gtest.h>

#include <string>
#include "js-runner/js.h"

TEST(JSRunnerEngineTest, RunCodeTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "(function(x){return x+1;})(5)";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("6"), res);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}