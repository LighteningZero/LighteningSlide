// -*- javascript -*- LighteningZero

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

function inlineMark(origin, mark, handle, is_double_mark) {
    let s = new Scanner(origin);
    let result = new String();

    s.setLineBreakToLFMode();

    while (true) {
        let ch = s.scanChar();
        if (ch == undefined) ch = '';
        if (ch == mark) {
            if (is_double_mark) {
                if (s.isEnd()) {
                    result += ch;
                    return result;
                }
                ch = s.scanChar();
                if (ch == undefined) ch = '';
                if (ch != mark) {
                    result += mark + ch;
                    continue;
                }
            }

            if (s.isEnd()) {
                result += mark;
                if (is_double_mark) {
                    result += mark;
                }
                return result;
            }

            let mid = '';
            let have_end = true;

            while (true) {
                ch = s.scanChar();
                if (ch == undefined) ch = '';
                if (ch == mark) {
                    if (is_double_mark) {
                        if (s.isEnd()) {
                            have_end = false;
                            break;
                        }
                        ch = s.scanChar();
                        if (ch == undefined) ch = '';
                        if (ch == mark) {
                            break;
                        }
                        mid += mark;
                    }
                    break;
                }
                mid += ch;
                if (s.isEnd() || ch == '\n') {
                    have_end = false;
                    break;
                }
            }

            if (have_end && mid != '') {
                result += handle(mid);
            } else {
                if (mid == '') {
                    result += mark;
                    if (is_double_mark) {
                        result += mark;
                    }
                }
                result += mark;
                if (is_double_mark) {
                    result += mark;
                }
                if (mid != undefined) {
                    result += mid;
                }
            }
        } else {
            result += ch;
        }

        if (s.isEnd()) {
            break;
        }
    }

    return result;
};