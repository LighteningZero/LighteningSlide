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

cmake_minimum_required(VERSION 3.16)

PROJECT(LighteningSlide)

INCLUDE_DIRECTORIES(
    include/
)

SET(CMAKE_CXX_STANDARD 17)

SET(SRC_LIB_LIST 
    ${PROJECT_SOURCE_DIR}/src/js-runner/js.cc
    ${PROJECT_SOURCE_DIR}/src/js-runner/exceptions.cc
    ${PROJECT_SOURCE_DIR}/src/config-reader/config.cc
    ${PROJECT_SOURCE_DIR}/src/config-reader/exceptions.cc
    ${PROJECT_SOURCE_DIR}/src/io/input.cc
    ${PROJECT_SOURCE_DIR}/src/io/output.cc
    ${PROJECT_SOURCE_DIR}/src/io/fs.cc
    ${PROJECT_SOURCE_DIR}/src/file/file.cc
    ${PROJECT_SOURCE_DIR}/src/extension-engine/main-engine.cc
)

SET(SRC_MAIN_LST
    ${SRC_LIB_LIST}
    ${PROJECT_SOURCE_DIR}/src/main.cc
)

ENABLE_TESTING()

# ADD_COMPILE_OPTIONS(-g3)

FIND_PACKAGE(PkgConfig)

PKG_SEARCH_MODULE(FMT REQUIRED fmt)

PKG_SEARCH_MODULE(JERRYSCRIPTCORE REQUIRED libjerry-core)
PKG_SEARCH_MODULE(JERRYSCRIPTEXT REQUIRED libjerry-ext)
PKG_SEARCH_MODULE(JERRYSCRIPTLIBM REQUIRED libjerry-libm)
PKG_SEARCH_MODULE(JERRYSCRIPTPORTDEFAULT REQUIRED libjerry-port-default)

PKG_SEARCH_MODULE(JSONCPP REQUIRED jsoncpp)

LINK_LIBRARIES(
    ${FMT_LIBRARIES}
    ${JERRYSCRIPTCORE_LIBRARIES}
    ${JERRYSCRIPTEXT_LIBRARIES}
    ${JERRYSCRIPTLIBM_LIBRARIES}
    ${JERRYSCRIPTPORTDEFAULT_LIBRARIES}
    ${JSONCPP_LIBRARIES}
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_MAIN_LST})

ADD_SUBDIRECTORY(test/)