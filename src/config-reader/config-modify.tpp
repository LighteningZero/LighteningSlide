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
#include <sstream>
#include <string>
#include <vector>

#include <fmt/core.h>
#include <json/json.h>

#include "io/io.h"
#include "config-reader/config.h"
#include "config-reader/exceptions.h"

// Modify item
template <typename __T>
void extension::ConfigContainer::setItem(const std::string& itemPath, __T val) {
    std::vector<std::string> itemName = parseJsonPath(itemPath);

    Json::Value* currentItem;
    currentItem = &this->jsonRoot;

    for (size_t i = 0; i < itemName.size(); i += 1) {
        Json::Value* nextItem;

        // Parse array
        if (currentItem->isArray()) {
            // Turn std::string to number
            std::stringstream to_int_string_stream;
            to_int_string_stream << itemName[i];
            int item_number;
            to_int_string_stream >> item_number;

            nextItem = &currentItem->operator[](item_number);
        } else {
            nextItem = &currentItem->operator[](itemName[i]);
        }

        // Empty item
        if (nextItem->empty()) {
            if (i == itemName.size() - 1) {
                bool is_array = true;
                for (size_t j = 0; j < itemName[i].size(); j += 1) 
                    if (itemName[i][j] < '0' || itemName[i][j] > '9')
                        is_array = false;

                if (is_array) 
                    currentItem->append(val);
                else
                    currentItem->operator[](itemName[i]) = val;
            } else {
                throw extension::JsonParsingError(fmt::format("Invalid JSON path '{}' at '{}'", itemPath, itemName[i]));
            }
        }

        if (i == itemName.size() - 1) {
            *nextItem = val;
            return;
        }

        currentItem = nextItem;
    }
}
