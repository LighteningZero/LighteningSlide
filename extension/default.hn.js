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

function count(str) {
    let c = 0;
    for (let i = 0; i < str.length; i += 1) {
        if (str[i] !== "#") {
            return 0;
        } else {
            c += 1;
            if (c > 6) return 0;
        }
    }
    return c;
}

var render = [origin => {
    let s = new Scanner(origin);
    let result = new String();
    s.makeMarkHere();
    while (true) {
        let str = s.scanToken();
        let res = count(str);
        if (!res) {
            result += s.getTextFormMark();
        } else {
            let content = s.scanLine();
            result += '<h' + res + '>' + content + '</h' + res + '>\n';
        }
        
        s.skipBlank();
        s.makeMarkHere();
        if (s.isEnd()) {
            break;
        }
    }

    return result;
}];