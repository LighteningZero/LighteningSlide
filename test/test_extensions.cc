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

#include <fstream>
#include <string>
#include <gtest/gtest.h>

#include "io/io.h"
#include "extension-engine/main-engine.h"

TEST(ExtensionTest, HeaderTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.header:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("# header1\n"
                          "## header2\n"
                          "### header3\n"
                          "#### header4\n"
                          "##### header5");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("<h1>header1</h1>\n"
                          "<h2>header2</h2>\n"
                          "<h3>header3</h3>\n"
                          "<h4>header4</h4>\n"
                          "<h5>header5</h5>\n"),
              HTML);
}

TEST(ExtensionTest, BlockquoteTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.blockquote:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("abc > blockquote\n\n\nnormal text\n\n\n> blockquote");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("abc > blockquote\n\n\nnormal text\n\n\n<blockquote>blockquote</blockquote>"), HTML);
}

TEST(ExtensionTest, PageTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.page:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("+++ color #409EFF\n"
                          "page1\n"
                          "+++ image https://cdn.luogu.com.cn/upload/image_hosting/xdsuq4zj.png\n"
                          "page2\n"
                          "+++ iframe https://github.com/LighteningZero/LighteningSlide\n"
                          "page3");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("<div class=\"reveal\">\n<div class=\"slides\">\n<section  data-background-color=\"#409EFF\" "
                          " >\npage1\n</section>\n<section  "
                          "data-background-image=\"https://cdn.luogu.com.cn/upload/image_hosting/xdsuq4zj.png\"  "
                          ">\npage2\n</section>\n<section  "
                          "data-background-iframe=\"https://github.com/LighteningZero/LighteningSlide\"  "
                          ">\npage3\n</section>\n\n</div>\n</div>"),
              HTML);
}

TEST(ExtensionTest, FontStlyeTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.fontstyle:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\","
           "\"default.liblock\","
           "\"default.libinlinemark\","
           "\"default.libsign\","
           "\"default.libwrapper\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("__**~test1~**__  _*test2*_");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(
        std::string("\n<strong>\n<strong>\n<del>test1</del>\n</strong>\n</strong>\n  \n<i>\n<i>test2</i>\n</i>\n"),
        HTML);
}

TEST(ExtensionTest, TabTitleTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.tabtitle:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("%TITLE% abcd\n %title% bcde");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("<title>abcd</title>\n<title>bcde</title>\n"), HTML);
}

TEST(ExtensionTest, CodeTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.code:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("abc\n```cpp\n  a bc\n``\n```");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("abc\n<pre>\n<code>\n  a bc\n``\n</code>\n</pre>\n"), HTML);
}

TEST(ExtensionTest, LinkTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.link:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("[Lightening Slide](https://github.com/LighteningZero/LighteningSlide)");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("<a href=\"https://github.com/LighteningZero/LighteningSlide\">Lightening Slide</a>"), HTML);
}

TEST(ExtensionTest, ImgTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.image:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("![abc](https://cdn.luogu.com.cn/upload/image_hosting/9dnyge7l.png)");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("<img src=\"https://cdn.luogu.com.cn/upload/image_hosting/9dnyge7l.png\" alt=\"abc\"/>"),
              HTML);
}

TEST(ExtensionTest, SplitLineTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.splitline:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("---\ntest1\n----\ntest2");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("<hr/>\ntest1\n<hr/>\ntest2"), HTML);
}

TEST(ExtensionTest, InlineCodeTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.inlinecode:0\","
           "\"default.fontstyle:0\","
           "\"default.inlinecode:1\","
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\","
           "\"default.libinlinemark\","
           "\"default.liblock\","
           "\"default.libsign\","
           "\"default.libwrapper\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("`code  _III_`");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(std::string("\n<code>code  _III_</code>\n"), HTML);
}

TEST(ExtensionTest, ListTest) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.list:0\","
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\","
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("- abc\nabcde-abcde\n-abc\n\nabc\n- abc\n-   abc\n\n1. abc\n2. abc\nabc\n\n3. abc");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(
        std::string(
            "<ul>\n<li>\nabc<br>abcde-abcde<br>-abc\n</li>\n</ul>\nabc\n<ul>\n<li>\nabc\n</li>\n<li>\nabc\n</li>\n</"
            "ul>\n<ol>\n<li>\nabc\n</li>\n<li>\nabc<br>abc\n</li>\n</ol>\n<ol>\n<li>\nabc\n</li>\n</ol>\n"),
        HTML);
}

TEST(ExtensionTest, RevealTeat) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\":["
           "\"default.reveal:0\""
           "],"
           "\"extension.lib\":["
           "\"default.libstring\","
           "\"default.libscanner\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("%THEME% black\ntest");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(
        std::string("<link rel=\"stylesheet\" href=\"./data/reveal/dist/reveal.css\" />\n<link rel=\"stylesheet\" "
                    "href=\"./data/reveal/dist/theme/black.css\" />\ntest\n<script "
                    "src=\"./data/reveal/dist/reveal.js\"></script>\n<script "
                    "src=\"./data/reveal/plugin/zoom/zoom.js\"></script>\n<script "
                    "src=\"./data/reveal/plugin/notes/notes.js\"></script>\n<script "
                    "src=\"./data/reveal/plugin/search/search.js\"></script>\n<script "
                    "src=\"./data/reveal/plugin/markdown/markdown.js\"></script>\n<link rel=\"stylesheet\" "
                    "href=\"./reveal/plugin/highlight/monokai.css\" />\n<script "
                    "src=\"./data/reveal/plugin/highlight/highlight.js\"></script>\n<script "
                    "src=\"./data/reveal/plugin/math/math.js\"></script>\n<script> Reveal.initialize({ controls: true, "
                    "progress: true, center: true, hash: true, math: {mathjax: \"./data/mathjax/mathjax.js\", config: "
                    "\"TeX-AMS_HTML-full\", TeX: { Macros: { RR: \"{\\bf R}\" } } } ,plugins: [RevealZoom, "
                    "RevealNotes, RevealSearch, RevealMarkdown, RevealHighlight, RevealMath] }); </script>\n"),
        HTML);
}

TEST(ExtensionTest, TestAll) {
    std::ofstream out("./data/extension_config.json");
    out << "{"
           "\"extension.order\": ["
           "\"default.code:0\","
           "\"default.inlinecode:0\","
           "\"default.header:0\","
           "\"default.fontstyle:0\","
           "\"default.image:0\","
           "\"default.link:0\","
           "\"default.list:0\","
           "\"default.blockquote:0\","
           "\"default.inlinecode:1\","
           "\"default.page:0\","
           "\"default.splitline:0\","
           "\"default.tabtitle:0\","
           "\"default.reveal:0\","
           "\"default.framework:0\""
           "],"
           "\"extension.lib\": ["
           "\"default.libstring\","
           "\"default.libscanner\","
           "\"default.libinlinemark\","
           "\"default.liblock\","
           "\"default.libsign\","
           "\"default.libwrapper\""
           "]"
           "}";

    out.close();
    extension::ExtensionRunner ext;
    ext.setOriginMarkdown("%TITLE% LighteningSlide\n%THEME% white\n\n+++\n\n# H1\n## H2\n### H3\n#### "
                          "H4\n\n+++\n\n[LighteningSlide](https://github.com/LighteningZero/"
                          "LighteningSlide)\n\n---\n\n![LighteningSlide](https://s1.ax1x.com/2020/09/05/"
                          "wEkEsx.png)\n\n+++\n\n_abc_\n*abc*\n__abc__\n**abc**\n~~abc~~\n~abc~\n\n++"
                          "+\n\n- abc\nabc\n- bcd\n\n+++\n\n`#include <vector>`\n\n```cpp\n#include <iostream>\nint "
                          "main() {\n	int a, b;\n	std::cin >> a >> b;\n	std::cout << a + b;\n}\n```\n");
    ext.runExtensions();
    std::string HTML = ext.getResult();

    ASSERT_EQ(
        std::string(
            "<!DOCTYPE html>\n<html>\n<body>\n<link rel=\"stylesheet\" href=\"./data/reveal/dist/reveal.css\" />\n<div "
            "class=\"reveal\">\n<div class=\"slides\">\n<title>LighteningSlide</title>\n<link rel=\"stylesheet\" "
            "href=\"./data/reveal/dist/theme/white.css\" />\n<section "
            ">\n<h1>H1</h1>\n<h2>H2</h2>\n<h3>H3</h3>\n<h4>H4</h4>\n</section>\n<section >\n<a "
            "href=\"https://github.com/LighteningZero/LighteningSlide\">LighteningSlide</a>\n<hr/>\n<img "
            "src=\"https://s1.ax1x.com/2020/09/05/wEkEsx.png\" alt=\"LighteningSlide\"/>\n</section>\n<section "
            ">\n<i>abc</i>\n<i>abc</i>\n<strong>abc</strong>\n<strong>abc</strong>\n<del>abc</del>\n<del>abc</del>\n</"
            "section>\n<section >\n<ul>\n<li>\nabc<br>abc\n</li>\n<li>\nbcd\n</li>\n</ul>\n</section>\n<section "
            ">\n<code>#include <vector></code>\n<pre>\n<code>\n#include <iostream>\nint main() {\nint a, b;\nstd::cin "
            ">> a >> b;\nstd::cout << a + b;\n}\n</code>\n</pre>\n</section>\n</div>\n</div>\n<script "
            "src=\"./data/reveal/dist/reveal.js\"></script>\n<script "
            "src=\"./data/reveal/plugin/zoom/zoom.js\"></script>\n<script "
            "src=\"./data/reveal/plugin/notes/notes.js\"></script>\n<script "
            "src=\"./data/reveal/plugin/search/search.js\"></script>\n<script "
            "src=\"./data/reveal/plugin/markdown/markdown.js\"></script>\n<link rel=\"stylesheet\" "
            "href=\"./reveal/plugin/highlight/monokai.css\" />\n<script "
            "src=\"./data/reveal/plugin/highlight/highlight.js\"></script>\n<script "
            "src=\"./data/reveal/plugin/math/math.js\"></script>\n<script> Reveal.initialize({ controls: true, "
            "progress: true, center: true, hash: true, math: {mathjax: \"./data/mathjax/mathjax.js\", config: "
            "\"TeX-AMS_HTML-full\", TeX: { Macros: { RR: \"{\\bf R}\" } } } ,plugins: [RevealZoom, RevealNotes, "
            "RevealSearch, RevealMarkdown, RevealHighlight, RevealMath] }); </script>\n\n</body>\n</html>"),
        HTML);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    frontend::copyFile("./../../extension", "./extension", true);
    frontend::createDir("data");

    return RUN_ALL_TESTS();
}