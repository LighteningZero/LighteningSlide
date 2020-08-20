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

var render = [markdown => {
    let s = new Scanner(markdown);
    let result = new String();
    let lastLineIsBlockquote = false;
    s.setLineBreakToLFMode();
    s.makeMarkHere();
    while (true) {
        let str = s.scanToken();
        if (str === ">" || (str !== "" && lastLineIsBlockquote)) {
            let content = new String();
            if(str === ">") {
                content = s.scanLine();
            } else {
                content = str + s.scanLine();
            }
            if (!lastLineIsBlockquote) {
                result += '<blockquote>' + content;
                lastLineIsBlockquote = true;
            } else {
                result += '\n' + content;
            }
        } else {
            if(lastIsBlockquote) {
                lastLineIsBlockquote = false;
                result += '</blockquote>';
            }
            result += s.getTextFormMark();
        }
        
        s.skipOneReturn();
        s.makeMarkHere();
        if (s.isEnd()) {
            if(lastLineIsBlockquote) {
                result += '</blockquote>';
            }
            break;
        }
    }

    return result;
}];