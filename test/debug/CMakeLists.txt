# -*- Cmake -*- LighteningZero

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

INCLUDE_DIRECTORIES(../include/)

FILE(GLOB_RECURSE DEBUGTESTFILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/debug_*.cc")
FOREACH(DEBUGTESTFILE IN LISTS DEBUGTESTFILES)
    GET_FILENAME_COMPONENT(DEBUGTESTNAME ${DEBUGTESTFILE} NAME_WE)
    ADD_EXECUTABLE(${DEBUGTESTNAME} ${DEBUGTESTFILE} ${SRC_LIB_LIST})
ENDFOREACH()