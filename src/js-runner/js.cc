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
    this->_run_result = nullptr;
    this->GC_now_pending = 0;
}

extension::JSContainer::~JSContainer() {
    this->freeParsedScript();
    this->freeRunResult();

    jerry_cleanup();
}

void extension::JSContainer::freeParsedScript() {
    if (this->_parsed_script == nullptr)
        return;

    jerry_release_value(*this->_parsed_script);
    delete this->_parsed_script;
    this->commitGC();
}

void extension::JSContainer::freeRunResult() {
    if (this->_run_result == nullptr)
        return;

    jerry_release_value(*this->_run_result);
    delete this->_run_result;
    this->commitGC();
}

void extension::JSContainer::setParsedScript(const jerry_value_t& value) {
    this->freeParsedScript();
    this->_parsed_script = new jerry_value_t;
    *this->_parsed_script = value;
    this->commitGC();
}

void extension::JSContainer::setRunResult(const jerry_value_t& value) {
    this->freeRunResult();
    this->_run_result = new jerry_value_t;
    *this->_run_result = value;
    this->commitGC();
}

void extension::JSContainer::commitGC(int x) {
    this->GC_now_pending += x;
    if (this->GC_now_pending >= extension::JSContainer::GC_ratio) {
        jerry_gc(JERRY_GC_PRESSURE_LOW);

        while (this->GC_now_pending > extension::JSContainer::GC_ratio)
            this->GC_now_pending -= extension::JSContainer::GC_ratio;
    }
}

void extension::JSContainer::setScript(const std::string& script) {
    jerry_char_t* j_script = new jerry_char_t[(script.size() + 1) * sizeof(char)];
    size_t j_script_length = sizeof(char) * (script.size());
    memcpy((char*)j_script, script.c_str(), j_script_length);
    j_script[j_script_length] = '\0';

    jerry_value_t value = jerry_parse(nullptr, 0, j_script, j_script_length, JERRY_PARSE_NO_OPTS);

    if (jerry_value_is_error(value))
        throw extension::JSParsingError(
            fmt::format("Error Value: {} {}", __FUNCTION__, jerry_get_value_from_error(value, false)));

    this->setParsedScript(value);

    delete[] j_script;
    this->commitGC(5);
}

void extension::JSContainer::runScript() {
    jerry_value_t value = jerry_run(*this->_parsed_script);
    if (jerry_value_is_error(value))
        throw extension::JSRuntimeError(
            fmt::format("Error value: {} {}", __FUNCTION__, jerry_get_value_from_error(value, false)));

    this->setRunResult(value);
    this->commitGC(60);
}

void extension::JSContainer::runFunction(const std::string& function_name, const jerry_value_t function_args[],
                                         size_t length_args) {
    jerry_value_t global_object = jerry_get_global_object();
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t*)function_name.c_str());

    jerry_value_t target_function = jerry_get_property(global_object, prop_name);

    if (!jerry_value_is_function(target_function)) {
        std::string temp_function_name = fmt::format("__now_func{}", rand());
        std::string mark_script = fmt::format("var {}={};", temp_function_name, function_name).c_str();
        bool mark_script_ret =
            jerry_eval((const jerry_char_t*)(mark_script.c_str()), mark_script.length(), JERRY_PARSE_NO_OPTS);
        if (!mark_script_ret)
            throw extension::JSTypeError(fmt::format("Error running function '{}' (may not found)", function_name));

        jerry_release_value(target_function);
        jerry_release_value(prop_name);
        prop_name = jerry_create_string((const jerry_char_t*)temp_function_name.c_str());
        target_function = jerry_get_property(global_object, prop_name);

        this->commitGC(5);
    }

    jerry_value_t this_val = jerry_create_undefined();
    jerry_value_t ret_val = jerry_call_function(target_function, this_val, function_args, length_args);

    if (jerry_value_is_error(ret_val))
        throw extension::JSRuntimeError(fmt::format("Runtime Error when running function '{}'", function_name));

    this->setRunResult(ret_val);

    jerry_release_value(global_object);
    jerry_release_value(prop_name);
    jerry_release_value(target_function);
    jerry_release_value(this_val);

    this->commitGC(60);
}

std::string extension::JSContainer::getResultAsString() {
    if (this->_run_result == nullptr)
        throw std::logic_error(fmt::format("Trying to get result before run any script [{}]", __FUNCTION__));

    jerry_value_t str_value = jerry_value_to_string(*this->_run_result);
    jerry_size_t str_size = jerry_get_utf8_string_size(str_value);
    jerry_char_t* str_buffer = new jerry_char_t[str_size + 5];

    jerry_size_t bytes_copied = jerry_string_to_utf8_char_buffer(str_value, str_buffer, str_size);
    str_buffer[bytes_copied] = '\0';

    std::string result((const char*)str_buffer);

    delete[] str_buffer;
    jerry_release_value(str_value);
    this->commitGC(1);

    return result;
}