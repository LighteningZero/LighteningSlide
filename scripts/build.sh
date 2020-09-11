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

if [ ! -d "./src" ]
then
    cd ..
fi

if [ ! -d "./reveal.js" ]
then
    git clone https://github.com/hakimel/reveal.js --depth=1 -b master
fi

if [ ! -d "./mathjax" ]
then
    git clone https://github.com/mathjax/MathJax --depth=1 -b master

    mkdir mathjax
    mv MathJax/es5/* mathjax
    rm -rf MathJax
fi

mkdir build
cd build

mkdir data
cp ../LICENSE ./LICENSE
cp -r ../extension  ./extension
cp ../template.json ./data/extension_config.json

mkdir reveal
cp -r ../reveal.js/dist ./reveal/dist
cp -r ../reveal.js/plugin ./reveal/plugin

mkdir mathjax
cp ../mathjax/tex-chtml.js ./mathjax/mathjax.js
cp -r ../mathjax/output ./mathjax/output

cmake ..
make -j8
