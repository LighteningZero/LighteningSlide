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

#ifndef EXPORT_SLIDE_H
#define EXPORT_SLIDE_H

#include <string>

namespace frontend {

class Slide {
public:
    // Import slide
    void importFromHtmlFile(const std::string& filename);
    void importFromHtmlString(const std::string& html);
    void importFromMarkdownFile(const std::string& filename);
    void importFromMarkdownString(const std::string& markdown);

    // Export Slide
    void exportSlide(const std::string& filepath);

    std::string getHTML();

private:
    std::string _HTML;
};

} // namespace frontend

#endif // EXPORT_SLIDE_H