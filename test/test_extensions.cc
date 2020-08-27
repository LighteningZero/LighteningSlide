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

#include "file/file.h"
#include "extension-engine/main-engine.h"

TEST(ExtensionTest, HeaderTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.header:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";
    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("# header1\n"
                          "## header2\n"
                          "### header3\n"
                          "#### header4\n"
                          "##### header5");
    ext.runExtensions();
    std::string HTML = ext.getResult();
    ASSERT_EQ(std::string("<h1>header1</h1>\n"
                          "<h2>header2</h2>\n"
                          "<h3>header3</h3>\n"
                          "<h4>header4</h4>\n"
                          "<h5>header5</h5>\n"),
              HTML);
}

TEST(ExtensionTest, BlockquoteTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.blockquote:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";
    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("> blockquote\n\n\nnormal text");
    ext.runExtensions();
    std::string HTML = ext.getResult();
    ASSERT_EQ(std::string("<blockquote>blockquote</blockquote>\n\nnormal  text"), HTML);
}

TEST(ExtensionTest, PageDividerTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.pagedivider:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";
    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("~~~\n"
                          "page1\n"
                          "~~~\n"
                          "page2\n"
                          "~~~\n"
                          "page3");
    ext.runExtensions();
    std::string HTML = ext.getResult();
    ASSERT_EQ(std::string("<section>\n"
                          "page1\n"
                          "</section>\n"
                          "<section>\n"
                          "page2\n"
                          "</section>\n"
                          "<section>\n"
                          "page3\n"
                          "</section>\n"),
              HTML);
}

TEST(ExtensionTest, FontStlyeTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.fontstyle:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";
    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("__**~test1~**__ _*test2*_");
    ext.runExtensions();
    std::string HTML = ext.getResult();
    ASSERT_EQ(std::string("<strong><strong><del>test1</del></strong></strong> <i><i>test2</i></i>"), HTML);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    file::copy("./../../extension", "./extension");
    file::createDir("data");

    return RUN_ALL_TESTS();
}