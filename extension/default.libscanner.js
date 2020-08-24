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

function isBlankChar(x) {
    if (typeof(x) !== "string") {
        return false;
    }

    if (x == ' ' || x == '\t' || x == '\n' || x == '\r') {
        return true;
    }

    return false;
}

function Scanner(text) {
    this.text = text;
    this.pointer = 0;
    this.mark = undefined;

    this.resetScanner = () => {
        this.pointer = 0;
        this.mark = undefined;
    }

    this.setLineBreakToLFMode = () => {
        this.text = this.text.replaceAll("\r\n", "\n");
        this.text = this.text.replaceAll("\r", "\n");
    }

    this.skipSpace = () => {
        let result = false;
        while (this.text[this.pointer] == ' ') {
            this.pointer += 1;
            result = true;
        }

        return result;
    };

    this.skipTab = () => {
        let result = false;
        while (this.text[this.pointer] == '\t') {
            this.pointer += 1;
            result = true;
        }

        return result;
    };

    this.skipReturn = () => {
        let result = false;
        while (this.text[this.pointer] == '\r' || this.text[this.pointer] == '\n') {
            this.pointer += 1;
            result = true;
        }

        return result;
    };

    this.skipOneReturn = () => {
        let result = false;
        if (this.text[this.pointer] == '\r' || this.text[this.pointer] == '\n') {
            this.pointer += 1;
            result = true;
        }

        return result;
    };

    this.skipEmpty = () => {
        let result = false;
        while (this.skipSpace() || this.skipTab()) {
            result = true;
        }

        return result;
    };

    this.skipBlank = () => {
        let result = false;
        while (this.skipEmpty() || this.skipReturn()) {
            result = true;
        }

        return result;
    }

    this.skipChar = (length=1) => {
        this.pointer += length;
    };

    this.getChar = () => {
        return this.text[this.pointer];
    };

    this.skipUntil = target => {
        let match_length = 0;
        let result = false;

        while (!this.isEnd()) {
            if (this.scanChar() == target[match_length]) {
                match_length += 1;
            }

            if (match_length == target)
        }

        return result;
    }
    
    this.scanChar = () => {
        this.pointer += 1;
        return this.text[this.pointer - 1];
    };

    this.isEnd = () => {
        if (this.text[this.pointer] === undefined) {
            return true;
        }

        return false;
    }

    this.scanNumber = () => {
        let result = new Number(0);
        
        this.skipEmpty();
        while (isDigit(this.getChar())) {
            result *= 10;
            result += Number(this.scanChar());
            if (this.isEnd()) {
                break;
            }
        }

        return result;
    }

    this.scanToken = () => {
        let result = new String();

        this.skipEmpty();
        while (!isBlankChar(this.getChar()) && this.getChar() != undefined) {
            result += this.scanChar();
            if (this.isEnd()) {
                break;
            }
        }

        return result;
    }

    this.scanLine = () => {
        let result = new String();
        this.skipEmpty();

        while (this.getChar() !== '\n' && this.getChar() !== '\r' && this.getChar() != undefined) {
            result += this.scanChar();
            if (this.isEnd()) {
                break;
            }
        }

        return result;
    }


    this.makeMark = point => {
        this.mark = point;
    }

    this.makeMarkHere = () => {
        this.mark = this.pointer;
    }

    this.clearMark = () => {
        this.mark = undefined;
    }

    this.getTextFormMark = () => {
        if (this.mark === undefined) {
            return undefined;
        }
        
        return this.text.substr(this.mark, this.pointer - this.mark + 1);
    }

    return this;
}