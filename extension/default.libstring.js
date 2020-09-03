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

if (String.prototype.format === undefined) {
    String.prototype.format = function(args) {
        let result = this;
        if (arguments.length < 1) {
            return result;
        }

        let data = arguments;
        if (arguments.length === 1 && typeof (args) === 'object') {
            data = args;
        }

        for (let key in data) {
            let value = data[key];
            if (value !== undefined) {
                result = result.replace('{' + key + '}', value);
            }
        }
        return result;
    }
}

if (String.prototype.replaceAll === undefined) {
    String.prototype.replaceAll = function(before, after) {
        let res = new String();
        let matched = 0;
        for (let i = 0; i < this.length; i += 1) {
            if (this[i] === before[matched]) {
                matched += 1;
                if (matched === before.length) {
                    res += after;
                    matched = 0;
                }
            } else {
                matched = 0;
                res += this[i];
            }
        }

        for (let i = this.length - matched; i < this.length; i += 1) {
            res += this[i];
        }

        return res;
    };
}

if (String.prototype.trim === undefined) {
    String.prototype.trim = function() {
        return this.replace(/^[\s\uFEFF\xA0]+|[\s\uFEFF\xA0]+$/g, '');
    };
}