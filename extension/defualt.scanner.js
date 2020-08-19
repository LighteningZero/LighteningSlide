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

function isDigit(x) {
    if (typeof(x) !== "string") {
        return false;
    }

    // OPTIMIZE '0' and '9' to ASCII code
    if ("0".charCodeAt() <= x.charCodeAt() && x.charCodeAt() <= "9".charCodeAt()) {
        return true;
    }

    return false;
}

function Scanner(text) {
    this.text = text;
    this.pointer = 0;

    this.resetPointer = () => {
        this.pointer = 0;
    }

    this.skipSpace = () => {
        let resualt = false;
        while (this.text[this.pointer] == ' ') {
            this.pointer += 1;
            resualt = true;
        }

        return resualt;
    };

    this.skipTab = () => {
        let resualt = false;
        while (this.text[this.pointer] == '\t') {
            this.pointer += 1;
            resualt = true;
        }

        return resualt;
    };

    this.skipReturn = () => {
        let resualt = false;
        while (this.text[this.pointer] == '\r' || this.text[this.pointer] == '\n') {
            this.pointer += 1;
            resualt = true;
        }

        return resualt;
    };

    this.skipEmpty = () => {
        let resualt = false;
        while (this.skipSpace() || this.skipTab()) {
            resualt = true;
        }

        return resualt;
    };

    this.skipChar = (length=1) => {
        this.pointer += length;
    };

    this.getChar = () => {
        return this.text[this.pointer];
    };

    this.scanChar = () => {
        this.pointer += 1;
        return this.text[this.pointer - 1];
    };

    this.scanNumber = () => {
        let resualt = 0;
        
        this.skipEmpty();
        while (isDigit(this.getChar())) {
            resualt *= 10;
            resualt += Number(this.scanChar());
        }

        return resualt;
    }

    return this;
}