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

#ifndef IO_FS_H
#define IO_FS_H

#include <string>

namespace frontend {

bool isFileExist(const std::string& filepath);
void moveFile(const std::string& originFilename, const std::string& newFilename);
void copyFile(const std::string& originFilename, const std::string& newFilename, bool withDir);
void createFile(const std::string& filename);
void createDir(const std::string& filename);

} // namespace frontend

#endif // IO_FS_H
