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
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>

#include "extension-engine/main-engine.h"

TEST(ExtensionTest, HeaderTest) {
    std::ofstream out("./data/config.json");
    out << "{\"extension.order\":[\"default.header:0\"],\"extension.lib\":[\"default.libstring\",\"default.libscanner\"]}";
    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("# abc");
    ext.runExtensions();
    std::string HTML = ext.getResult();
    ASSERT_EQ(std::string("<h1>abc</h1>\n"), HTML);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    system("cp -r ../../extension ./extension");
    mkdir("data", S_IRWXU);
    // system("cp ../../template.json ./data/config.json");

    return RUN_ALL_TESTS();
}