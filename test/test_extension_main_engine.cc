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
#include <cstdlib>
#include <gtest/gtest.h>

#include "file/file.h"
#include "extension-engine/main-engine.h"

TEST(ExtensionMainEngineTest, Test) {
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("%THEME% white\n%TITLE% test\n+++\n# PAGE1\n+++\n# PAGE2\n+++");
    ext.runExtensions();
    std::string HTML = ext.getResult();
    ASSERT_EQ(
        std::string(
            "<!DOCTYPE html>\n<html>\n<body>\n<div class=\"reveal\">\n<div class=\"slides\">\n<link rel=\"stylesheet\" "
            "href=\"./reveal/dist/theme/white.css\"></link><title>test</title>\n<section>\n<h1>PAGE1</h1>\n</"
            "section>\n<section>\n<h1>PAGE2</h1>\n</section>\n</div>\n</div>\n<link rel=\"stylesheet\" "
            "href=\"./reveal/dist/reveal.css\"></link>\n<script src=\"./reveal/dist/reveal.js\"></script>\n<script "
            "src=\"./reveal/plugin/highlight/highlight.js\"></script>\n<script> Reveal.initialize(); "
            "</script>\n\n</body>\n</html>"),
        HTML);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    file::copy("./../../extension", "./extension");
    file::createDir("data");
    file::copy("./../../template.json", "./data/extension_config.json");

    return RUN_ALL_TESTS();
}