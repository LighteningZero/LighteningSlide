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

var render = [markdown => {
    print(markdown);
    let count_mark_number = str => {
        let mark_number = 0;
        for (let i = 0; i < str.length; i += 1) {
            if (str[i] === '~') {
                mark_number += 1;
            } else {
                mark_number = 0;
                break;
            }
        }

        return mark_number;
    }

    let scanner = new Scanner(markdown);
    let result = new String();
    let last_is_section = false;
    let first_mark = true;
    scanner.setLineBreakToLFMode();
    scanner.makeMarkHere();

    while (true) {
        let str = scanner.scanLine();
        let mark_number = count_mark_number(str);

        if (mark_number >= 3) {
            if (first_mark) {
                first_mark = false;
            } else {
                result += '</section>\n';
            }
            if (!scanner.isEnd()) {
                result += '<section>\n';
            }
            last_is_section = true;
        } else {
            if (first_mark) {
                result += '<section>\n';
                first_mark = false;
            }
            result += scanner.getTextFormMark();
            last_is_section = false;
        }

        scanner.skipOneReturn();
        scanner.makeMarkHere();
        if (scanner.isEnd()) {
            result += scanner.getTextFormMark();
            if (!last_is_section) {
                result += '\n</section>\n';
            }
            break;
        }
    }

    return result;
}];