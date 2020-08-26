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

    while (true) {
        let ch = s.scanChar();

        if (ch == '_') {
            let new_ch;
            let mid = '';
            let have_end = true;

            while (true) {
                new_ch = s.scanChar();
                if (new_ch == '_') {
                    break;
                }
                mid += new_ch;

                if (s.isEnd()) {
                    have_end = false;
                    break;
                }
            }

            if (have_end && mid != '') {
                result += '<i>' + mid + '</i>';
            } else {
                if (mid == '') {
                    result += '_';
                }

                result += '_';

                if (mid != 'undefined') {
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
}]