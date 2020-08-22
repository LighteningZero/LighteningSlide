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

#ifndef JSON_RUNNER_EXCEPTION_H
#define JSON_RUNNER_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

namespace extension {

class JsonParsingError : public std::exception {
public:
    JsonParsingError(const std::string& msg);
    const char* what() const throw();

private:
    std::string _msg;
};

class JsonRuntimeError : public std::exception {
public:
    JsonRuntimeError(const std::string& msg);
    const char* what() const throw();

private:
    std::string _msg;
};

class JsonTypeError : public std::exception {
public:
    JsonTypeError(const std::string& msg);
    const char* what() const throw();

private:
    std::string _msg;
};

} // namespace extension

#endif // JSON_RUNNER_EXCEPTION_H