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

#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdio.h>

#include <fmt/core.h>
#include <json/json.h>

#include "io/io.h"
#include "config-reader/config.h"
#include "config-reader/exceptions.h"

// Load JSON from std::string
void extension::ConfigContainer::loadFromString(const std::string& jsonContent) {
    std::stringstream json_string_stream;
    json_string_stream << jsonContent;
    json_string_stream >> this->jsonRoot;
}

// Load JSON from a .json file
void extension::ConfigContainer::loadFromFile(const std::string& filePath) {
    frontend::FileScanner file_scanner(filePath); // IO file_scanner
    std::string file_content;
    file_content = file_scanner.scanAll(); // Get the entire file content to string
    loadFromString(file_content);          // Load from string
}

// Write JSON to file
std::string extension::ConfigContainer::writeToString() {
    std::string str;
    Json::StreamWriterBuilder writer;
    std::stringstream json_string_stream;
    json_string_stream << Json::writeString(writer, this->jsonRoot);
    json_string_stream >> str;

    return str;
}

void extension::ConfigContainer::writeToFile(const std::string& filePath) {
    frontend::FileWriter file_writer(filePath);
    file_writer.write(writeToString());
}

// Parse JSON path from string path
std::vector<std::string> extension::ConfigContainer::parseJsonPath(const std::string& itemPath) {
    std::vector<std::string> itemName;
    int name_start = 0;
    for (size_t i = 0; i < itemPath.size(); i += 1) {
        if (itemPath[i] == ':') {
            itemName.push_back(itemPath.substr(name_start, i - name_start));
            name_start = i + 1;
        }
    }

    itemName.push_back(itemPath.substr(name_start, itemPath.size() - name_start));
    return itemName;
}

// Get Json::Value from JSON path
Json::Value extension::ConfigContainer::getItem(const std::string& itemPath) {
    std::vector<std::string> itemName = parseJsonPath(itemPath);

    Json::Value currentItem;
    currentItem = this->jsonRoot;

    for (size_t i = 0; i < itemName.size(); i += 1) {
        Json::Value nextItem;

        // Parse array
        if (currentItem.isArray()) {
            // Turn std::string to number
            std::stringstream to_int_string_stream;
            to_int_string_stream << itemName[i];
            int item_number;
            to_int_string_stream >> item_number;

            nextItem = currentItem[item_number];
        } else {
            nextItem = currentItem[itemName[i]];
        }

        // Empty item
        if (nextItem.empty())
            throw extension::JsonParsingError(fmt::format("Invalid JSON path '{}' at '{}'", itemPath, itemName[i]));

        if (i == itemName.size() - 1)
            return nextItem;

        currentItem = nextItem;
    }

    Json::Value null;
    return null;
}

// Get item as type
int extension::ConfigContainer::getItemAsInt(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isInt())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not int", itemPath));

    return item.asInt();
}

unsigned int extension::ConfigContainer::getItemAsUnsignedInt(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isUInt())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not unsigned int", itemPath));

    return item.asUInt();
}

long long extension::ConfigContainer::getItemAsInt64(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isInt64())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not long long", itemPath));

    return item.asInt64();
}

unsigned long long extension::ConfigContainer::getItemAsUnsignedInt64(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isUInt64())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not unsigned long long", itemPath));

    return item.asUInt64();
}

std::string extension::ConfigContainer::getItemAsString(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isString())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not string", itemPath));

    return item.asString();
}

bool extension::ConfigContainer::getItemAsBool(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isBool())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not bool", itemPath));

    return item.asBool();
}

double extension::ConfigContainer::getItemAsDouble(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isDouble())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not double", itemPath));

    return item.asDouble();
}
