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

var render = [origin => {
    let count_mark_number = str => {
        let mark_number = 0;
        for (let i = 0; i < str.length; i += 1) {
            if (str[i] == '-') {
                mark_number += 1;
            } else {
                return 0;
            }
        }

        return mark_number;
    };

    let s = new Scanner(origin);
    let result = new String();

    s.setLineBreakToLFMode();
    s.makeMarkHere();

    while (true) {
        let str = s.scanLine();
        let mark_number = count_mark_number(str);

        if (mark_number >= 3) {
            result += '<hr/>\n';
        } else {
            result += s.getTextFormMark();
        }

        s.skipOneReturn();
        s.makeMarkHere();

        if (s.isEnd()) {
            result += s.getTextFormMark();
            break;
        }
    }

    return result;
}];