cmake_minimum_required (VERSION 3.0)

set (CXX_STANDARD "c++17")
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -fPIC -g ${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD}")

project (doraemon VERSION 1.0.0)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("/usr/local/include")

find_library(FMT_LIBRARY fmt HINTS /usr/local/lib)
set(EXTRA_LIBS ${EXTRA_LIBS} ${FMT_LIBRARY}) 
message("fmt-libraries - ${FMT_LIBRARY}") 

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
