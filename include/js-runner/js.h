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

#ifndef JS_RUNNER_H
#define JS_RUNNER_H

#include <string>
#include <jerryscript.h>
namespace extension {

class JSContainer {
public:
    static JSContainer* getInstance();
    void setScript(const std::string& script);
    void runScript();
    void runFunction(const std::string& function_name, const jerry_value_t function_args[], size_t length_args);

    std::string getResultAsString();

private:
    JSContainer();
    ~JSContainer();

    void freeParsedScript();
    void freeRunResult();

    static JSContainer* _instance;

    int GC_now_pending;
    void commitGC(int x = 1);

    jerry_value_t* _parsed_script;
    jerry_value_t* _run_result;

public:
    static const int GC_ratio;
};

} // namespace extension

#endif // JS_RUNNER_H
