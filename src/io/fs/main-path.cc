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

#include "io/fs/main-path.h"
#include <exception>
#include <filesystem>
#include <stdexcept>
#include <cstdlib>
#include <errno.h>
#include <fmt/core.h>
#include <limits.h>
#include <unistd.h>

frontend::CurrentPath* frontend::CurrentPath::_instance = nullptr;

frontend::CurrentPath::CurrentPath() {
    this->calcCurrentPath();
}

frontend::CurrentPath* frontend::CurrentPath::getInstance() {
    if (frontend::CurrentPath::_instance == nullptr)
        frontend::CurrentPath::_instance = new frontend::CurrentPath;

    return frontend::CurrentPath::_instance;
}

frontend::CurrentPath::~CurrentPath() {}

void frontend::CurrentPath::calcCurrentPath() {
    const int PATH_SIZE_MAX = PATH_MAX + 1;
    char* current_absolute_path = new char[PATH_SIZE_MAX];
    int len = readlink("/proc/self/exe", current_absolute_path, SIZE_MAX);
    if (len < 0 || len >= SIZE_MAX)
        throw std::runtime_error(fmt::format("Cannot read symbol link of current: [{}] {}", errno, strerror(errno)));

    for (int i = len; i >= 0; --i) {
        if (current_absolute_path[i] == '/') {
            current_absolute_path[i + 1] = '\0';
            break;
        }
    }

    this->_path = current_absolute_path;
    delete[] current_absolute_path;
}

std::string frontend::CurrentPath::getCurrentPath() {
    auto that = frontend::CurrentPath::getInstance();
    return that->_path;
}