cmake_minimum_required(VERSION 3.16)

PROJECT(LighteningSlide)

INCLUDE_DIRECTORIES(
    include
)

SET(SRC_LIST 
    src/main.cc
    src/js-runner/js.cc
    src/js-runner/exceptions.cc
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST})

LINK_LIBRARIES(fmt jerry-core jerry-ext, jerry-libm, jerry-port-default)
