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

#include <string>

#include "io/io.h"
#include "slide/slide.h"
#include "extension-engine/main-engine.h"

void lightening::Slide::importFromHtmlString(const std::string& html) {
    this->HTML = html;
}

void lightening::Slide::importFromHtmlFile(const std::string& filename) {
    frontend::FileScanner html_file_scanner(filename);
    this->HTML = html_file_scanner.scanAll();
}

void lightening::Slide::importFromMarkdownString(const std::string& markdown) {
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown(markdown);
    ext.runExtensions();
    this->HTML = ext.getResult();
}

void lightening::Slide::importFromMarkdownFile(const std::string& filename) {
    frontend::FileScanner markdown_file_scanner(filename);
    std::string markdown = markdown_file_scanner.scanAll();

    this->importFromMarkdownString(markdown);
}