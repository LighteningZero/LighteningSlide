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
    let theme = origin => {
        let s = new Scanner(origin);
        let result = new String();
        s.makeMarkHere();

        while (true) {
            let str = s.scanToken();

            if (str != '%theme%' && str != '%THEME%') {
                result += s.getTextFormMark();
            } else {
                let content = s.scanLine();
                result += '<link rel="stylesheet" href="./reveal/dist/theme/' + content + '.css" />'
            }
            
            s.skipBlank();
            s.makeMarkHere();

            if (s.isEnd()) {
                break;
            }
        }

        return result;
    };

    let result = origin;
    
    result = theme(result);

    // Basic reveal
    result = result + '<link rel="stylesheet" href="./reveal/dist/reveal.css" />';
    result += '<script src="./reveal/dist/reveal.js"></script>\n';

    // Code highlight
    result += '<script src="./reveal/plugin/highlight/highlight.js"></script>\n';

    // Initialize reveal
    result += '<script> Reveal.initialize(); </script>\n';

    return result;
}];