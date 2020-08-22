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

#include "io/input.h"
#include <exception>
#include <stdexcept>
#include <cerrno>
#include <fmt/core.h>

frontend::FileScanner::FileScanner(std::string filename) {
    this->_file = fopen(filename.c_str(), "rb");
    if (this->_file == nullptr)
        throw std::invalid_argument(fmt::format("[{}] Cannot open file '{}': [Err {}] {}", __FUNCTION__, filename,
                                                errno, std::strerror(errno)));
}

frontend::FileScanner::~FileScanner() {
    fclose(this->_file);
}

std::string frontend::FileScanner::scanAll() {
    fseek(this->_file, 0, SEEK_END);   // jump to end
    int length = ftell(this->_file);   // calc file length
    char* data = new char[length + 1]; // new need space(+1 for '\0')
    rewind(this->_file);               // jump back to begin

    length = fread(data, length, 1, this->_file);
    data[length + 1] = '\0';
    std::string result(data);

    delete[] data;
    return result;
}