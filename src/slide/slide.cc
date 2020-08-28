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

#include "slide/slide.h"
#include <string>
#include <fmt/core.h>
#include "io/io.h"
#include "extension-engine/main-engine.h"

void frontend::Slide::importFromHtmlString(const std::string& html) {
    this->_HTML = html;
}

void frontend::Slide::importFromHtmlFile(const std::string& filename) {
    frontend::FileScanner html_file_scanner(filename);
    this->_HTML = html_file_scanner.scanAll();
}

void frontend::Slide::importFromMarkdownString(const std::string& markdown) {
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown(markdown);
    ext.runExtensions();
    this->_HTML = ext.getResult();
}

void frontend::Slide::importFromMarkdownFile(const std::string& filename) {
    frontend::FileScanner markdown_file_scanner(filename);
    std::string markdown = markdown_file_scanner.scanAll();

    this->importFromMarkdownString(markdown);
}

std::string frontend::Slide::getHTML() {
    return this->_HTML;
}

void frontend::Slide::exportSlide(const std::string& filepath) {
    frontend::FileWriter slide_file_writer(filepath + "slide.html");
    slide_file_writer.write(this->_HTML);

    frontend::copyFile(fmt::format("{}/reveal", frontend::CurrentPath::get()), filepath + "/reveal");
}