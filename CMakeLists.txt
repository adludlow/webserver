cmake_minimum_required (VERSION 3.0)
project (Webtoy)
# Version number.
set(Webtoy_VERSION_MAJOR 0)
set(Webtoy_VERSION_MINOR_1)

#include_directories(include)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cxx")

# configure a header file to pass some settings to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/src/WebtoyConfig.h.in"
    "${PROJECT_SOURCE_DIR}/src/WebtoyConfig.h"
    )

add_library(webserver ${SOURCES})
add_executable(webserver_main ${SOURCES})


