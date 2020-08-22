# -*- C++ -*- LighteningZero

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

FIND_PACKAGE(PkgConfig)
PKG_SEARCH_MODULE(GOOGLETESTS REQUIRED gtest)

INCLUDE_DIRECTORIES(../include/)
LINK_LIBRARIES(${GOOGLETESTS_LIBRARIES})
ADD_SUBDIRECTORY(debug/)

FILE(GLOB_RECURSE TESTFILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/test_*.cc")
FOREACH(TESTFILE IN LISTS TESTFILES)
    GET_FILENAME_COMPONENT(TESTNAME ${TESTFILE} NAME_WE)
    ADD_EXECUTABLE(${TESTNAME} ${TESTFILE} ${SRC_LIB_LIST})
    ADD_TEST(NAME ${TESTNAME} COMMAND ${TESTNAME})
ENDFOREACH()