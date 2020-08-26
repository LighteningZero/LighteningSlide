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

#include "extension-engine/main-engine.h"
#include "js-runner/js.h"
#include "config-reader/config.h"
#include "io/io.h"

#include <string>
#include <exception>
#include <stdexcept>
#include <fmt/core.h>
#include <jerryscript-core.h>

extension::ExtensionRunner::ExtensionRunner() {}

extension::ExtensionRunner::~ExtensionRunner() {}

std::string extension::ExtensionRunner::findExtensionFile(const std::string& filename) {
    if(frontend::isFileExist(fmt::format("./data/extension/{}.js", filename)))
        return fmt::format("./data/extension/{}.js", filename);

    if(frontend::isFileExist(fmt::format("./extension/{}.js", filename))) 
        return fmt::format("./extension/{}.js", filename);


    throw std::runtime_error(fmt::format("Can not find extension '{}'", filename));
}

void extension::ExtensionRunner::runExtensions() {
    extension::ConfigContainer ConfigReader;
    ConfigReader.loadFromFile("./data/config.json");
    for(size_t i = 0; i < ConfigReader.getItemSize("extension.lib"); i ++) {
        std::string lib;
        lib = ConfigReader.getItemAsString(fmt::format("extension.lib:{}", i));

        std::string libPath;
        libPath = this->findExtensionFile(lib);
        frontend::FileScanner file(libPath);
        std::string fileContent = file.scanAll();

        auto js = extension::JSContainer::getInstance();
        js->setScript(fileContent);
        js->runScript();
    }
    for(size_t i = 0; i < ConfigReader.getItemSize("extension.order"); i ++) {
        std::string ext;
        ext = ConfigReader.getItemAsString(fmt::format("extension.order:{}", i));

        std::string extName, funcId;
        bool isfuncId = false;
        for(size_t j = 0; j < ext.size(); j ++) {
            if(ext[j] == ':') {
                isfuncId = true;
                continue;
            }

            if(!isfuncId) {
                extName += ext[j];
            } else {
                funcId += ext[j];
            }
        }

        std::string extPath;
        extPath = this->findExtensionFile(extName);
        frontend::FileScanner file(extPath);
        std::string fileContent = file.scanAll();

        auto js = extension::JSContainer::getInstance();
        js->setScript(fileContent);
        js->runScript();
        jerry_value_t *js_markdown = new jerry_value_t;
        *js_markdown = jerry_create_string((const jerry_char_t *)this->markdown.c_str());
        js->runFunction(fmt::format("render[{}]", funcId), js_markdown, 1);
        jerry_release_value(*js_markdown);

        this->markdown = js->getResultAsString();
        fmt::print("{}", this->markdown);
    }
}

void extension::ExtensionRunner::setOriginMarkdown(const std::string& markdown) {
    this->markdown = markdown;
}

std::string extension::ExtensionRunner::getResult() {
    return this->markdown;
}
