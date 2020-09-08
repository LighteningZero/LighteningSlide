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
    let count_mark_number = str => {
        let mark_number = 0;
        for (let i = 0; i < str.length; i += 1) {
            if (str[i] == '+') {
                mark_number += 1;
            } else if (str[i] == ' ') {
                break;
            } else {
                return 0;
            }
        }

        return mark_number;
    };

    let s = new Scanner(markdown);
    let result = new String();
    let last_is_section = false;
    let first_mark = true;

    s.setLineBreakToLFMode();
    s.makeMarkHere();

    while (true) {
        let str = s.scanLine();

        let mark_number = count_mark_number(str);

        if (mark_number >= 3) {
            if (first_mark) {
                first_mark = false;
            } else {
                result += '</section>\n';
            }

            if (!s.isEnd()) {
                let color = new String();
                let image = new String();
                let video = new String();
                let iframe = new String();

                let ss = new Scanner(str);

                while (true) {
                    let str2 = ss.scanToken();
                    if (str2 == 'color') {
                        color = ss.scanToken();
                    } else if (str2 == 'image') {
                        image = ss.scanToken();
                    } else if (str2 == 'video') {
                        video = ss.scanToken();
                    } else if (str2 == 'iframe') {
                        iframe = ss.scanToken();
                    }

                    if (ss.isEnd()) {
                        break;
                    }
                }

                result += '<section ';

                if (color.length > 0) {
                    result += ' data-background-color="' + color + '" ';
                }
                if (image.length > 0) {
                    result += ' data-background-image="' + image + '" ';
                }
                if (video.length > 0) {
                    result += ' data-background-video="' + video + '" ';
                }
                if (iframe.length > 0) {
                    result += ' data-background-iframe="' + iframe + '" ';
                }

                result += ' >\n';
            }

            last_is_section = true;
        } else {
            result += s.getTextFormMark();
            last_is_section = false;
        }

        s.skipOneReturn();
        s.makeMarkHere();

        if (s.isEnd()) {
            result += s.getTextFormMark();
            if (!last_is_section) {
                result += '\n</section>\n';
            }
            break;
        }
    }

    result = '<div class="reveal">\n<div class="slides">\n' + result + '\n</div>\n</div>';

    return result;
}];