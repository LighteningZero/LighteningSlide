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

#include "config-reader/exceptions.h"

extension::JsonParsingError::JsonParsingError(const std::string& msg) {
    this->_msg = msg;
}

const char* extension::JsonParsingError::what() const throw() {
    return this->_msg.c_str();
}

extension::JsonRuntimeError::JsonRuntimeError(const std::string& msg) {
    this->_msg = msg;
}

const char* extension::JsonRuntimeError::what() const throw() {
    return this->_msg.c_str();
}

extension::JsonTypeError::JsonTypeError(const std::string& msg) {
    this->_msg = msg;
}

const char* extension::JsonTypeError::what() const throw() {
    return this->_msg.c_str();
}