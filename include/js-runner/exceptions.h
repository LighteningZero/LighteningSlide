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

#ifndef JS_RUNNER_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

namespace extension {

class JSParsingError : public std::exception {
public:
    JSParsingError(const std::string& msg);
    const char* what();

private:
    std::string _msg;
};

class JSRuntimeError : public std::exception {
public:
    JSRuntimeError(const std::string& msg);
    const char* what();

private:
    std::string _msg;
};

class JSTypeError : public std::exception {
public:
    JSTypeError(const std::string& msg);
    const char* what();

private:
    std::string _msg;
};

} // namespace extension

#endif // JS_RUNNER_EXCEPTION_H