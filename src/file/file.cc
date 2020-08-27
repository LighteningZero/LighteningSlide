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
#include <sys/stat.h>

#include "file/file.h"
#include "io/io.h"

void file::move(const std::string& originFilename, const std::string& newFilename) {
    std::string command = "mv " + originFilename + " " + newFilename;
    system(command.c_str());
}

void file::copy(const std::string& originFilename, const std::string& newFilename) {
    std::string command = "cp -r " + originFilename + " " + newFilename;
    system(command.c_str());
}

void file::createFile(const std::string& filename) {
    std::string command = "touch " + filename;
    system(command.c_str());
}

void file::createDir(const std::string& filename) {
    mkdir(filename.c_str(), S_IRWXU);
}