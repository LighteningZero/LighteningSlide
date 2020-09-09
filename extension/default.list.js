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

function check_ordered_list(str) {
    for (let i = 0; i < str.length - 1; i++) {
        if (str[i] <= '0' || str[i] >= '9') {
            return false;
        }
    }

    if (str[str.length - 1] == '.') {
        return true;
    }
    return false;
}

function check_unordered_list(str) {
    if (str == '-') {
        return true;
    }

    return false;
};

function render_list(s, is_ordered) {
    let content = new String();
    content += '\n<li>\n' + s.scanLine();

    while (true) {
        s.skipOneReturn();
        let str2 = s.scanToken();

        if (str2 == '') {
            s.skipOneReturn();
            content += '\n</li>';
            break;
        } else if ((is_ordered && check_ordered_list(str2)) || (!is_ordered && check_unordered_list(str2))) {
            content += '\n</li>\n<li>\n' + s.scanLine();
        } else {
            content += '<br>' + str2 + s.scanLine();
        }

        if (s.isEnd()) {
            content += '\n</li>';
            break;
        }
    }

    let result = new String();
    if (is_ordered) {
        result = '<ol>' + content + '\n</ol>\n';
    } else {
        result = '<ul>' + content + '\n</ul>\n';
    }
    return result;
}

var render = [markdown => {
    let s = new Scanner(markdown);
    let result = new String();

    s.setLineBreakToLFMode();
    s.makeMarkHere();

    while (true) {
        let str = s.scanToken();
        if (str === '-') {
            result += render_list(s, false);
        } else if (check_ordered_list(str)) {
            result += render_list(s, true);
        } else {
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