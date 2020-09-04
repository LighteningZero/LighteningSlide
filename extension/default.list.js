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
    let s = new Scanner(markdown);
    let result = new String();

    s.setLineBreakToLFMode();
    s.makeMarkHere();

    while (true) {
        let str = s.scanToken();
        if (str === '-') {
            let content = new String();
            content += '<li>' + s.scanLine() + '</li>';
            while (true) {
                s.skipOneReturn();
                if (s.isEnd()) {
                    break;
                }
                let str2 = s.scanToken();
                console.log(str2);
                if (str2 == '') {
                    s.skipOneReturn();
                    break;
                } else if (str2 == '-') {
                    content += '\n<br>\n<li>' + s.scanLine() + '</li>';
                } else {
                    content += '\n<br>\n<li>' + str2 + s.scanLine() + '</li>';
                }
            }
            result += '<ul>\n' + content + '\n</ul>\n';
        } else {
            result += s.getTextFormMark();
        }

        s.makeMarkHere();
        s.skipOneReturn();

        if (s.isEnd()) {
            break;
        }
    }

    return result;
}];