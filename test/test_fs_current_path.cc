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
#include <fmt/core.h>
#include <gtest/gtest.h>
#include "io/io.h"

TEST(FileSystemCurrentPathTest, TestAll) {
    system("sh output_pwd.sh > current_path.out");
    frontend::FileScanner f("current_path.out");
    fmt::print("+{}\n", frontend::CurrentPath::get());
    
    std::string res(f.scanAll());
    res.pop_back();
    res.push_back('/');
    ASSERT_EQ(res, frontend::CurrentPath::get());
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    frontend::FileWriter f("output_pwd.sh");
    f.write("#! /bin/sh\ncur_dir=$(cd \"$(dirname \"$0\")\"; pwd)\necho $cur_dir\n");
    f.flush();
    return RUN_ALL_TESTS();
}