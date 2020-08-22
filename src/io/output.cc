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

#include "io/output.h"
#include <exception>
#include <stdexcept>
#include <cerrno>
#include <fmt/core.h>

frontend::FileWriter::FileWriter(std::string filename) {
    this->_file = fopen(filename.c_str(), "wb");
    if (this->_file == nullptr)
        throw std::invalid_argument(fmt::format("[{}] Cannot open file '{}': [Err {}] {}", __FUNCTION__, filename,
                                                errno, std::strerror(errno)));
}

frontend::FileWriter::~FileWriter() {
    fclose(this->_file);
}

void frontend::FileWriter::write(std::string content) {
    fmt::print(this->_file, content);
}

void frontend::FileWriter::flush() {
    fflush(this->_file);
}