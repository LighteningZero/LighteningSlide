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

#include <gflags/gflags.h>
#include "slide/slide.h"
#include <cstdio>

DEFINE_string(input, "/dev/stdin", "Input markdown file.");
DEFINE_string(output, "/dev/stdout", "Output directory. Where to place render slide");

int main(int argc, char** argv) {
    GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, false);
    frontend::Slide slide_maker;
    slide_maker.importFromMarkdownFile(FLAGS_input);
    slide_maker.exportSlide(FLAGS_output);
    return 0;
}