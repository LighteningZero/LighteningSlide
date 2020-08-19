#include <cstdio>
#include "js-runner/js.h"
using namespace std;
using namespace extension;

int main() {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "(function(x){return x+1;})(5)";
    runner->setScript(script);
    runner->runScript();
    std::string res = runner->getResualtAsString();
    printf("%s\n", res.c_str());
    return 0;
}