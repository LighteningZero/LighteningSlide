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
#include <cstdio>

#include <gtest/gtest.h>

#include "io/input.h"
#include "io/output.h"

TEST(FrontendIOTest, FileScannerScanAllTest) {
    FILE* file = fopen("a.txt", "w");
    fprintf(file, "abc");
    fclose(file);

    frontend::FileScanner f("a.txt");
    ASSERT_EQ(std::string("abc"), f.scanAll());
}

TEST(FrontendIOTest, FileWriterTest) {
    frontend::FileWriter f("b.txt");
    f.write("abcde");
    f.flush();

    FILE* file = fopen("b.txt", "r");
    char* data = new char[16];
    fscanf(file, "%s", data);
    std::string content(data);
    delete[] data;
    ASSERT_EQ(std::string("abcde"), content);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}