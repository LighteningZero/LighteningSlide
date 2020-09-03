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
    let result = origin;
    // Italic
    result = inlineMark(result, '_', 'i', false);
    result = inlineMark(result, '*', 'i', false);

    // Bold
    result = inlineMark(result, '_', 'strong', true);
    result = inlineMark(result, '*', 'strong', true);

    // Delete
    result = inlineMark(result, '~', 'del', false);
    result = inlineMark(result, '~', 'del', true);
    return result;
}]