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

#include <exception>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <fmt/color.h>
#include <fmt/core.h>
#include <gflags/gflags.h>
#include <unistd.h>

#include "io/io.h"
#include "slide/slide.h"

DEFINE_string(input, "", "Input markdown file.");
DEFINE_string(output, "", "Output directory. Where to place rendered slide");
DEFINE_bool(license, false, "Output program license");
DEFINE_bool(config, false, "Show config");
DEFINE_bool(path, false, "Show current path");

void printIcon(bool large) {
    if (large) {
        std::string icon = "\n"
                           "    +-------------------+  │\n"
                           "+-------------------+###|  │  Lightening Slide V0.1a\n"
                           "|########@@@@#######|###|  │  Copyright (C) 2020 Lightening Zero\n"
                           "|#######@@@@########|###|  │\n"
                           "|######@@@@@@@######|###|  │  For Help:      --help\n"
                           "|#####@@@@@@@#######|###|  │  Make Slide:    --input /path --output /path\n"
                           "|########@@@########|###|  │  Modigy Config: --config\n"
                           "|########@@#########|###|  │  Get Path:      --path\n"
                           "|########@##########|---+  │\n"
                           "+-------------------+      │\n\n";

        for (size_t i = 0; i < icon.size(); i++) {
            if (icon[i] == '@') {
                fmt::print(bg(fmt::color::light_blue) | fg(fmt::color::yellow) | fmt::emphasis::bold, "@");
            } else if (icon[i] == '#') {
                fmt::print(bg(fmt::color::light_blue) | fg(fmt::color::light_blue), "#");
            } else if (icon[i] == '-' && icon[i + 1] == '+' || icon[i] == '-' && icon[i + 2] == '+'
                       || icon[i] == '-' && icon[i + 2] == '-' || icon[i] == '+' || icon[i] == '|') {
                fmt::print(bg(fmt::color::light_blue) | fg(fmt::color::sky_blue) | fmt::emphasis::bold, "{}", icon[i]);
            } else {
                fmt::print("{}", icon[i]);
            }
        }
    } else {
        std::string icon = "\n"
                           "    +-------------------+\n"
                           "+-------------------+###|\n"
                           "|########@@@@#######|###|\n"
                           "|#######@@@@########|###|\n"
                           "|######@@@@@@@######|###|\n"
                           "|#####@@@@@@@#######|###|\n"
                           "|########@@@########|###|\n"
                           "|########@@#########|###|\n"
                           "|########@##########|---+\n"
                           "+-------------------+    \n";

        for (size_t i = 0; i < icon.size(); i++) {
            if (icon[i] == '@') {
                fmt::print(bg(fmt::color::light_blue) | fg(fmt::color::yellow) | fmt::emphasis::bold, "@");
            } else if (icon[i] == '#') {
                fmt::print(bg(fmt::color::light_blue) | fg(fmt::color::light_blue), "#");
            } else if (icon[i] == '-' || icon[i] == '+' || icon[i] == '|') {
                fmt::print(bg(fmt::color::light_blue) | fg(fmt::color::sky_blue) | fmt::emphasis::bold, "{}", icon[i]);
            } else {
                fmt::print("{}", icon[i]);
            }
        }
    }
}

int main(int argc, char** argv) {
    GFLAGS_NAMESPACE::SetUsageMessage(
        "This program make slides.\n\nLighteningSlide Copyright (C) 2020 LighteningZero\nThis program comes with "
        "ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it\nunder certain "
        "conditions; type `--license' for details.\n");
    GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, false);

    if (FLAGS_license) {
        frontend::FileScanner license_file("LICENSE");
        fmt::print(license_file.scanAll());
        return 0;
    }

    if (FLAGS_config) {
        system(fmt::format("/usr/bin/editor {}data/extension_config.json", frontend::CurrentPath::get()).c_str());
        return 0;
    }

    if (FLAGS_path) {
        fmt::print(fmt::emphasis::underline, "{}\n", frontend::CurrentPath::get());
        return 0;
    }

    if (FLAGS_input.size() > 0 && FLAGS_output.size() > 0) {
        frontend::Slide slide_maker;

        try {
            slide_maker.importFromMarkdownFile(FLAGS_input);
        } catch (std::invalid_argument& err) {
            fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::bold, "ERR: ");
            fmt::print("{}\n", err.what());
            return 0;
        } catch (std::runtime_error& err) {
            fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::bold, "ERR: ");
            fmt::print("{}\n", err.what());
            return 0;
        }

        try {
            slide_maker.exportSlide(FLAGS_output);
        } catch (std::invalid_argument& err) {
            fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::bold, "ERR: ");
            fmt::print("{}\n", err.what());
            return 0;
        } catch (std::runtime_error& err) {
            fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::bold, "ERR: ");
            fmt::print("{}\n", err.what());
            return 0;
        }

        return 0;
    } else if (FLAGS_input.size() == 0 && FLAGS_output.size() > 0) {
        fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::bold, "ERR: ");
        fmt::print("Missing --input\n");
        return 0;
    } else if (FLAGS_output.size() == 0 && FLAGS_input.size() > 0) {
        fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::bold, "ERR: ");
        fmt::print("Missing --output\n");
        return 0;
    }

    printIcon(true);

    return 0;
}
