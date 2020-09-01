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

#include "io/io.h"

TEST(FileSystemTest, TestAll) {
    frontend::createDir("in");
    frontend::createDir("ans");
    frontend::createFile("in/test.txt");
    frontend::FileWriter in_writer("./in/test.txt");
    in_writer.write("abc");
    in_writer.flush();

    frontend::copyFile("./in/test.txt", "./ans/test.txt", false);
    frontend::moveFile("./ans/test.txt", "./ans/ans.txt");
    frontend::FileScanner ans_scanner("./ans/ans.txt");
    std::string res = ans_scanner.scanAll();
    ASSERT_EQ(res, "abc");
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}