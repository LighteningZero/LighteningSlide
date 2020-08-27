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

#ifndef FILE_FILE_H
#define FILE_FILE_H

#include <string>

namespace file {

// Move files
void move(const std::string& originFilename, const std::string& newFilename);

// Copy files
void copy(const std::string& originFilename, const std::string& newFilename);

// Create files
void createFile(const std::string& filename);
void createDir(const std::string& filename);

} // namespace file

#endif // FILE_FILE_H