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

#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <gflags/gflags.h>
#include <unistd.h>
#include "io/io.h"
#include "slide/slide.h"

DEFINE_string(input, "/dev/stdin", "Input markdown file.");
DEFINE_string(output, "/dev/stdout", "Output directory. Where to place render slide");
DEFINE_bool(license, false, "Output program license");

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

    frontend::Slide slide_maker;
    slide_maker.importFromMarkdownFile(FLAGS_input);
    slide_maker.exportSlide(FLAGS_output);
    return 0;
}