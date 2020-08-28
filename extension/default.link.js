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

let render = [origin => {
    let s = new Scanner(origin);
    let result = new String();
    
    s.setLineBreakToLFMode();

    while (true) {
        let ch = s.scanChar();
        if (ch == '[') {
            if (s.isEnd()) {
                result += '[';
                return result;
            }

            let mid = '';
            let have_end = true;

            while (true) {
                ch = s.scanChar();
                if (ch == ']') {
                    break;
                }
                mid += ch;
                if (s.isEnd() || ch == '\n') {
                    have_end = false;
                    break;
                }
            }

            if (have_end) {
                ch = s.scanChar();
                if (ch == '(') {
                    if (s.isEnd()) {
                        result += '[' + mid + ']' + '(';
                        return result;
                    }

                    let mid_link = '';
                    let have_end_link = true;
                    
                    while (true) {
                        ch = s.scanChar();
                        if (ch == ')') {
                            break;
                        }
                        mid_link += ch;
                        if (s.isEnd() || ch == '\n') {
                            have_end_link = false;
                            break;
                        }
                    }

                    if (have_end_link) {
                        result += '<a href="' + mid_link + '">' + mid + '</a>';
                    } else {
                        result += '[' + mid + ']' + '(' + mid_link;
                    }
                } else {
                    result += '[' + mid + ']' + ch;
                }
            } else {
                result += '[' + mid;
            }
        } else {
            result += ch;
        }

        if (s.isEnd()) {
            break;
        }
    }

    return result;
}];