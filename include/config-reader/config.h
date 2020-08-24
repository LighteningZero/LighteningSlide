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

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <json/json.h>

namespace extension {

class ConfigContainer {
public:
    // Load JSON
    void loadFromString(const std::string& jsonContent);
    void loadFromFile(const std::string& filePath);

    // Read item
    Json::Value getItem(const std::string& itemPath);
    int getItemAsInt(const std::string& itemPath);
    unsigned int getItemAsUnsignedInt(const std::string& itemPath);
    long long getItemAsInt64(const std::string& itemPath);
    unsigned long long getItemAsUnsignedInt64(const std::string& itemPath);
    bool getItemAsBool(const std::string& itemPath);
    double getItemAsDouble(const std::string& itemPath);
    std::string getItemAsString(const std::string& itemPath);

    // Write item
    template <typename __T> void setItem(const std::string& itemPath, __T val);
    void addItem(const std::string& itemPath);

private:
    Json::Value jsonRoot;

    // Parse JSON path
    std::vector<std::string> parseJsonPath(const std::string& itemPath);
};

} // namespace extension

#include "../src/config-reader/config-writer.tpp"

#endif // CONFIG_READER_H