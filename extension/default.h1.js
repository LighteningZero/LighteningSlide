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

var render = [origin => {
    let s = new Scanner(origin);
    let resualt = new String();
    s.makeMarkHere();
    while (true) {
        let str = s.scanToken();
        if (str !== "#") {
            resualt += s.getTextFormMark();
        } else {
            let content = s.scanLine();
            resualt += '<h1>' + content + '</h1>\n';
        }
        
        s.skipBlank();
        s.makeMarkHere();
        if (s.isEnd()) {
            break;
        }
    }

    return resualt;
}];