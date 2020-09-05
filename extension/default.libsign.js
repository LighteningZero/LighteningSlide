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

var _default_lib_sign_ss = new Array();

function Signer(owner) {
    this.owner = owner;

    this.sign = function(value) {
        let lock = new Lock(true);
        lock.setLockCode(value);
        if (_default_lib_sign_ss[this.owner] === undefined) {
            _default_lib_sign_ss[this.owner] = new Array();
        }

        _default_lib_sign_ss[this.owner].push(lock.lockId);
        return ' PROTECT {name} {id} '.format({
            name: this.owner, 
            id: _default_lib_sign_ss[this.owner].length - 1
        });
    }

    this.unsign = function(value, process=x=>x) {
        let s = new Scanner(value);
        let result = new String();
        s.setLineBreakToLFMode();
        
        s.skipEmpty();
        s.makeMarkHere();
        while (true) {
            s.skipChar(-1);
            let before = s.getTextFormMark();
            s.skipChar(1);
            
            let now = s.scanToken();
            if (now == 'PROTECT') {
                let name = s.scanToken();
                let id = s.scanNumber();

                if (name == this.owner) {
                    result += before;
                    let lock = new Lock(false, _default_lib_sign_ss[this.owner][id]);
                    result += process(lock.getLockCode());
                    lock.freeLock();
                    s.skipChar();
                    s.makeMarkHere();
                }
            }

            s.skipOneReturn();

            if (s.isEnd()) {
                result += s.getTextFormMark();
                break;
            }
        }

        return result;
    }
}