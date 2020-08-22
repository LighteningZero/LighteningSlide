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
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>

#include <fmt/core.h>
#include <json/json.h>

#include "config-reader/config.h"
#include "config-reader/exceptions.h"

void extension::ConfigContainer::loadFromString(const std::string& jsonContent) {
    std::stringstream json_string_stream;
    json_string_stream << jsonContent;
    json_string_stream >> this->jsonRoot;
}

void extension::ConfigContainer::loadFromFile(const std::string& filePath) {
    std::ifstream config_file(filePath, std::ifstream::binary);
    config_file >> this->jsonRoot;
}

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

Json::Value extension::ConfigContainer::getItem(const std::string& itemPath) {
    std::vector<std::string> itemName = parseJsonPath(itemPath);

    Json::Value currentItem;
    currentItem = this->jsonRoot;

    for (size_t i = 0; i < itemName.size(); i += 1) {
        Json::Value nextItem = currentItem[itemName[i]];

        if (nextItem.empty())
            throw extension::JsonParsingError(fmt::format("Invalid JSON path '{}' at '{}'", itemPath, itemName[i]));

        if (i == itemName.size() - 1)
            return nextItem;

        currentItem = nextItem;
    }

    Json::Value null;
    return null;
}

int extension::ConfigContainer::getItemAsInt(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isInt())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not int"));

    return item.asInt();
}

unsigned int extension::ConfigContainer::getItemAsUnsignedInt(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isUInt())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not unsigned int"));

    return item.asUInt();
}

long long extension::ConfigContainer::getItemAsInt64(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (item.isInt64() == false)
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not long long"));

    return item.asInt64();
}

unsigned long long extension::ConfigContainer::getItemAsUnsignedInt64(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isUInt64())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not unsigned long long"));

    return item.asUInt64();
}

std::string extension::ConfigContainer::getItemAsString(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isString())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not string"));

    return item.asString();
}

bool extension::ConfigContainer::getItemAsBool(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (!item.isBool())
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not bool"));

    return item.asBool();
}

double extension::ConfigContainer::getItemAsDouble(const std::string& itemPath) {
    Json::Value item;
    item = getItem(itemPath);

    if (item.isDouble() == false)
        throw extension::JsonTypeError(fmt::format("JSON path '{}' value's type is not double"));

    return item.asDouble();
}
