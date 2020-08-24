#!/bin/bash

# -*- shell -*- LighteningZero

# Copyright (C) 2020  Lightening Zero
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https:#www.gnu.org/licenses/>.

echo $1

function dfs_dirs() {
    echo scanning $1
    for file_cc in ` echo $1"/"*.cc `
    do
        if [ ! -f "$file_cc" ]
        then
            echo "skipping .cc files in $1"
        else
            echo formatting $file_cc
            clang-format $file_cc > /tmp/formatted.cc
            cat /tmp/formatted.cc > $file_cc
        fi
    done

    for file_h in ` echo $1"/"*.h `
    do
        if [ ! -f "$file_h" ]
        then
            echo "skipping .h files in $1 ($file_h)"
        else
            echo formatting $file_h
            clang-format $file_h > /tmp/formatted.cc
            cat /tmp/formatted.cc > $file_h
        fi
    done

    for file_tpp in ` echo $1"/"*.tpp `
    do
        if [ ! -f "$file_tpp" ]
        then
            echo "skipping .tpp files in $1"
        else
            echo formatting $file_tpp
            clang-format $file_tpp > /tmp/formatted.cc
            cat /tmp/formatted.cc > $file_tpp
        fi
    done

    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]   
        then
            dfs_dirs $1"/"$file  
        fi
    done
}

cd `dirname $0`
cd ..
INIT_PATH="$(pwd)"  
dfs_dirs $INIT_PATH