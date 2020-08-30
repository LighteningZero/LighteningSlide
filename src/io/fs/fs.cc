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

#include "io/fs/fs.h"
#include <exception>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <errno.h>
#include <fmt/core.h>
#include <sys/stat.h>

bool frontend::isFileExist(const std::string& filepath) {
    FILE* fp = fopen(filepath.c_str(), "r");
    if (fp == nullptr)
        return false;

    return true;
}

void frontend::moveFile(const std::string& originFilename, const std::string& newFilename) {
    std::string command(fmt::format("mv {} {}", originFilename, newFilename));
    system(command.c_str());
}

void frontend::copyFile(const std::string& originFilename, const std::string& newFilename, const bool withDir) {
    std::string command;
    if (withDir) {
        command = fmt::format("cp -r {} {}", originFilename, newFilename);
    } else {
        command = fmt::format("cp {} {}", originFilename, newFilename);
    }
    system(command.c_str());
}

void frontend::createFile(const std::string& filename) {
    FILE* file = fopen(filename.c_str(), "w");
    if (file == nullptr)
        throw std::runtime_error(
            fmt::format("[{}] Cannot create file '{}': [{}] {}", __FUNCTION__, filename, errno, strerror(errno)));

    fclose(file);
}

void frontend::createDir(const std::string& filename) {
    mkdir(filename.c_str(), S_IRWXU | S_IXGRP | S_IRGRP | S_IXOTH | S_IROTH);
}