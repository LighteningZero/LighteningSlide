cmake_minimum_required(VERSION 3.16)

PROJECT(LighteningSlide)

INCLUDE_DIRECTORIES(
    include/
)

set(CMAKE_CXX_STANDARD 17)

SET(SRC_LIST 
    src/main.cc
    src/js-runner/js.cc
    src/js-runner/exceptions.cc
)

find_package(PkgConfig)

pkg_search_module(FMT REQUIRED fmt)

pkg_search_module(JERRYSCRIPTCORE REQUIRED libjerry-core)
pkg_search_module(JERRYSCRIPTEXT REQUIRED libjerry-ext)
pkg_search_module(JERRYSCRIPTLIBM REQUIRED libjerry-libm)
pkg_search_module(JERRYSCRIPTPORTDEFAULT REQUIRED libjerry-port-default)

LINK_LIBRARIES(
    ${FMT_LIBRARIES}
    ${JERRYSCRIPTCORE_LIBRARIES}
    ${JERRYSCRIPTEXT_LIBRARIES}
    ${JERRYSCRIPTLIBM_LIBRARIES}
    ${JERRYSCRIPTPORTDEFAULT_LIBRARIES}
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST})
