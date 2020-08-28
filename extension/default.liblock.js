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

var _default_liblock_lockCnt = 0;
var _default_liblock_unuse = new Array();
var _default_liblock_store = new Array();

function Lock(newLock, id) {
    this.lockId = new Number();
    if (newLock) {
        if (_default_liblock_unuse.length > 0) {
            this.lockId = _default_liblock_unuse[_default_liblock_unuse.length - 1];
            _default_liblock_unuse.pop();
        } else {
            this.lockId = _default_liblock_lockCnt;
            _default_liblock_lockCnt += 1;
        }
    } else {
        this.lockId = id;
    }

    this.setLockCode = code => {
        _default_liblock_store[this.lockId] = code;
    }

    this.getLockCode = () => {
        return _default_liblock_store[this.lockId];
    }

    this.freeLock = () => {
        _default_liblock_store.splice(this.lockId, 1);
        _default_liblock_unuse.push(this.lockId);
    }
}