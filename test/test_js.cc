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
    std::string script = "function RunFunctionTest_add(x) {\n\treturn x+1;\n};";
    runner->setScript(script);
    runner->runScript();

    jerry_value_t a = jerry_create_number(5);
    runner->runFunction(std::string("RunFunctionTest_add"), &a, 1);

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
TEST(JSRunnerEngineTest, LongCodeTest) {
    auto runner = extension::JSContainer::getInstance();
    std::string script = "// -*- javascript -*- LighteningZero\n\n// Copyright (C) 2020  Lightening Zero\n//\n// This program is free software: you can redistribute it and/or modify\n// it under the terms of the GNU General Public License as published by\n// the Free Software Foundation, either version 3 of the License, or\n// (at your option) any later version.\n\n// This program is distributed in the hope that it will be useful,\n// but WITHOUT ANY WARRANTY; without even the implied warranty of\n// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n// GNU General Public License for more details.\n\n// You should have received a copy of the GNU General Public License\n// along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\nfunction isDigit(x) {\n    if (typeof(x) !== \"string\") {\n        return false;\n    }\n\n    // OPTIMIZE '0' and '9' to ASCII code\n    if (\"0\".charCodeAt() <= x.charCodeAt() && x.charCodeAt() <= \"9\".charCodeAt()) {\n        return true;\n    }\n\n    return false;\n}\n\nfunction isBlankChar(x) {\n    if (typeof(x) !== \"string\") {\n        return false;\n    }\n\n    if (x == ' ' || x == '\t' || x == '\n' || x == '\r') {\n        return true;\n    }\n\n    return false;\n}\n\nfunction Scanner(text) {\n    this.text = text;\n    this.pointer = 0;\n    this.mark = undefined;\n\n    this.resetScanner = () => {\n        this.pointer = 0;\n        this.mark = undefined;\n    }\n\n    this.setLineBreakToLFMode = () => {\n        this.text = this.text.replaceAll(\"\r\n\", \"\n\");\n        this.text = this.text.replaceAll(\"\r\", \"\n\");\n    }\n\n    this.skipSpace = () => {\n        let result = false;\n        while (this.text[this.pointer] == ' ') {\n            this.pointer += 1;\n            result = true;\n        }\n\n        return result;\n    };\n\n    this.skipTab = () => {\n        let result = false;\n        while (this.text[this.pointer] == '\t') {\n            this.pointer += 1;\n            result = true;\n        }\n\n        return result;\n    };\n\n    this.skipReturn = () => {\n        let result = false;\n        while (this.text[this.pointer] == '\r' || this.text[this.pointer] == '\n') {\n            this.pointer += 1;\n            result = true;\n        }\n\n        return result;\n    };\n\n    this.skipOneReturn = () => {\n        let result = false;\n        if (this.text[this.pointer] == '\r' || this.text[this.pointer] == '\n') {\n            this.pointer += 1;\n            result = true;\n        }\n\n        return result;\n    };\n\n    this.skipEmpty = () => {\n        let result = false;\n        while (this.skipSpace() || this.skipTab()) {\n            result = true;\n        }\n\n        return result;\n    };\n\n    this.skipBlank = () => {\n        let result = false;\n        while (this.skipEmpty() || this.skipReturn()) {\n            result = true;\n        }\n\n        return result;\n    }\n\n    this.skipChar = (length=1) => {\n        this.pointer += length;\n    };\n\n    this.getChar = () => {\n        return this.text[this.pointer];\n    };\n\n    this.skipUntil = target => {\n        let match_length = 0;\n        let result = false;\n\n        while (!this.isEnd()) {\n            if (this.scanChar() == target[match_length]) {\n                match_length += 1;\n            }\n\n            // if (match_length == target)\n        }\n\n        return result;\n    }\n    \n    this.scanChar = () => {\n        this.pointer += 1;\n        return this.text[this.pointer - 1];\n    };\n\n    this.isEnd = () => {\n        if (this.text[this.pointer] === undefined) {\n            return true;\n        }\n\n        return false;\n    }\n\n    this.scanNumber = () => {\n        let result = new Number(0);\n        \n        this.skipEmpty();\n        while (isDigit(this.getChar())) {\n            result *= 10;\n            result += Number(this.scanChar());\n            if (this.isEnd()) {\n                break;\n            }\n        }\n\n        return result;\n    }\n\n    this.scanToken = () => {\n        let result = new String();\n\n        this.skipEmpty();\n        while (!isBlankChar(this.getChar()) && this.getChar() != undefined) {\n            result += this.scanChar();\n            if (this.isEnd()) {\n                break;\n            }\n        }\n\n        return result;\n    }\n\n    this.scanLine = () => {\n        let result = new String();\n        this.skipEmpty();\n\n        while (this.getChar() !== '\n' && this.getChar() !== '\r' && this.getChar() != undefined) {\n            result += this.scanChar();\n            if (this.isEnd()) {\n                break;\n            }\n        }\n\n        return result;\n    }\n\n\n    this.makeMark = point => {\n        this.mark = point;\n    }\n\n    this.makeMarkHere = () => {\n        this.mark = this.pointer;\n    }\n\n    this.clearMark = () => {\n        this.mark = undefined;\n    }\n\n    this.getTextFormMark = () => {\n        if (this.mark === undefined) {\n            return undefined;\n        }\n        \n        return this.text.substr(this.mark, this.pointer - this.mark + 1);\n    }\n\n    return this;\n}";
    runner->setScript(script);
    runner->runScript();
    script = "// -*- javascript -*- LighteningZero\n\n// Copyright (C) 2020  Lightening Zero\n//\n// This program is free software: you can redistribute it and/or modify\n// it under the terms of the GNU General Public License as published by\n// the Free Software Foundation, either version 3 of the License, or\n// (at your option) any later version.\n\n// This program is distributed in the hope that it will be useful,\n// but WITHOUT ANY WARRANTY; without even the implied warranty of\n// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n// GNU General Public License for more details.\n\n// You should have received a copy of the GNU General Public License\n// along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\nvar render = [origin => {\n    let countSharpNumber = str => {\n        let c = 0;\n        for (let i = 0; i < str.length; i += 1) {\n            if (str[i] !== \"#\") {\n                return 0;\n            } else {\n                c += 1;\n                if (c > 6) return 0;\n            }\n        }\n        return c;\n    };\n\n    let s = new Scanner(origin);\n    let result = new String();\n    s.makeMarkHere();\n    while (true) {\n        let str = s.scanToken();\n        let sharpNumber = countSharpNumber(str);\n        if (sharpNumber === 0) {\n            result += s.getTextFormMark();\n        } else {\n            let content = s.scanLine();\n            result += '<h' + sharpNumber + '>' + content + '</h' + sharpNumber + '>\n';\n        }\n        \n        s.skipBlank();\n        s.makeMarkHere();\n        if (s.isEnd()) {\n            break;\n        }\n    }\n\n    return result;\n}];\n";
    runner->setScript(script);
    runner->runScript();
    jerry_value_t js_markdown[1];
    js_markdown[0] = jerry_create_string((const jerry_char_t *)"# abc");
    runner->runFunction("render[0]", js_markdown, 1);
    std::string res = runner->getResualtAsString();
    ASSERT_EQ(std::string("<h1>abc</h1>"), res);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

