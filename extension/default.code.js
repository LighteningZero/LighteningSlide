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
    let s = new Scanner(origin);
    let result = new String();

    s.setLineBreakToLFMode();
    s.makeMarkHere();

    while (true) {
        let str = s.scanToken();
        let isCodeStart = true;
        for (let i = 0; i < 3; i += 1) {
            if (str[i] != '`') {
                isCodeStart = false;
                break;
            }
        }

        if(isCodeStart) {
            result += '<pre>\n<code>\n';
            s.scanLine();
            s.skipOneReturn();
            s.makeMarkHere();
            while (true) {
                let str2 = s.scanToken();
                let isCodeEnd = true;
                for (let i = 0; i < Math.max(3, str2.length); i += 1) {
                    if (str2[i] != '`') {
                        isCodeEnd = false;
                        break;
                    }
                }
                s.scanLine();
                if (isCodeEnd) {
                    result += '</code>\n</pre>\n';
                    s.makeMarkHere();
                    break;
                }
                result += s.getTextFormMark();
                s.skipOneReturn();
                s.makeMarkHere();
            }
        } else {
            s.scanLine();
            result += s.getTextFormMark();
        }

        s.skipOneReturn();
        s.makeMarkHere();

        if (s.isEnd()) {
            break;
        }
    }

    return result;
}];