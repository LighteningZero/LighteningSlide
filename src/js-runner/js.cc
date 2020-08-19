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

#include "js-runner/js.h"
#include "js-runner/exceptions.h"

#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <fmt/core.h>

extension::JSContainer* extension::JSContainer::_instance = nullptr;
const int extension::JSContainer::GC_ratio = 100;

extension::JSContainer* extension::JSContainer::getInstance() {
    if (JSContainer::_instance == nullptr)
        JSContainer::_instance = new JSContainer();

    return JSContainer::_instance;
}

extension::JSContainer::JSContainer() {
    jerry_init(JERRY_INIT_EMPTY);
    srand((unsigned)time(nullptr)); // Randomize random seed for Math.random()

    this->_parsed_script = nullptr;
    this->_run_resualt = nullptr;
    this->GC_now_pending = 0;
}

extension::JSContainer::~JSContainer() {
    if (this->_parsed_script != nullptr)
        jerry_release_value(*this->_parsed_script);

    if (this->_run_resualt != nullptr)
        jerry_release_value(*this->_run_resualt);

    jerry_cleanup();
}

void extension::JSContainer::CommitGC(int x) {
    this->GC_now_pending += x;
    if (this->GC_now_pending > extension::JSContainer::GC_ratio) {
        jerry_gc(JERRY_GC_PRESSURE_LOW);

        while (this->GC_now_pending > extension::JSContainer::GC_ratio)
            this->GC_now_pending -= extension::JSContainer::GC_ratio;
    }
}

void extension::JSContainer::setScript(const std::string& script) {
    if (this->_parsed_script != nullptr)
        jerry_release_value(*this->_parsed_script);

    jerry_char_t* j_script = new jerry_char_t[(script.size() + 1) * sizeof(char)];
    size_t j_script_length = sizeof(char) * (script.size());
    memcpy((char*)j_script, script.c_str(), j_script_length);
    j_script[j_script_length + 1] = '\0';

    jerry_value_t value = jerry_parse(nullptr, 0, j_script, j_script_length, JERRY_PARSE_NO_OPTS);

    if (jerry_value_is_error(value))
        throw extension::JSParsingError(
            fmt::format("[{}] Error Value: {}", __FUNCTION__, jerry_get_value_from_error(value, false)));

    this->_parsed_script = &value;
    delete[] j_script;

    this->CommitGC(5);
}

void extension::JSContainer::runScript() {
    if (this->_run_resualt != nullptr)
        jerry_release_value(*this->_run_resualt);

    jerry_value_t value = jerry_run(*this->_parsed_script);
    if (jerry_value_is_error(value))
        throw extension::JSRuntimeError(
            fmt::format("[{}] Error value: {}", __FUNCTION__, jerry_get_value_from_error(value, false)));

    this->_run_resualt = &value;

    this->CommitGC(60);
}

void extension::JSContainer::runFunction(const std::string& function_name, const jerry_value_t function_args[],
                                         size_t length_args) {
    jerry_value_t global_object = jerry_get_global_object();
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t*)function_name.c_str());

    jerry_value_t target_function = jerry_get_property(global_object, prop_name);

    if (!jerry_value_is_function(target_function))
        throw extension::JSTypeError(fmt::format("[{}] \"{}\" is not a function", __FUNCTION__, function_name));

    jerry_value_t this_val = jerry_create_undefined();
    jerry_value_t ret_val = jerry_call_function(target_function, this_val, function_args, length_args);

    if (this->_run_resualt != nullptr)
        jerry_release_value(*this->_run_resualt);

    this->_run_resualt = &ret_val;

    jerry_release_value(global_object);
    jerry_release_value(prop_name);
    jerry_release_value(target_function);
    jerry_release_value(this_val);

    this->CommitGC(60);
}

std::string extension::JSContainer::getResualtAsString() {
    if (this->_run_resualt == nullptr)
        throw std::logic_error(fmt::format("[{}] Trying to get resualt before run any script!", __FUNCTION__));

    jerry_value_t str_value = jerry_value_to_string(*this->_run_resualt);
    jerry_size_t str_size = jerry_get_utf8_string_size(str_value);
    jerry_char_t* str_buffer = new jerry_char_t[str_size + 5];

    jerry_size_t bytes_copied = jerry_string_to_utf8_char_buffer(str_value, str_buffer, str_size);
    str_buffer[bytes_copied] = '\0';

    std::string resualt((const char*)str_buffer);

    delete[] str_buffer;
    jerry_release_value(str_value);
    this->CommitGC(1);

    return resualt;
}