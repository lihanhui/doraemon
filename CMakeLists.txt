cmake_minimum_required (VERSION 3.0)

set (CXX_STANDARD "c++17")
set (CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD}")

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

#add_subdirectory(src/wrapper)
#set(EXTRA_LIBS ${EXTRA_LIBS} wrapper)

#include(ExternalProject)
#ExternalProject_Add (
#      fmt
#      GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
#      GIT_TAG "5.3.0"
#      UPDATE_COMMAND ""
#      INSTALL_COMMAND "" )


#####################################
add_library(doraemon SHARED src/doraemon.cxx 
            src/conf/config.cxx
            src/md5/md5.cxx
            src/net/net.cxx
            src/loader/loader.cxx
            src/base64/base64.cxx)
set_target_properties(doraemon PROPERTIES VERSION 1.0 SOVERION 1)
target_link_libraries(doraemon  ${EXTRA_LIBS})

add_executable(doraemon-test src/doraemon.cxx)
target_link_libraries(doraemon-test  ${EXTRA_LIBS} doraemon)

# add the install targets
install (TARGETS doraemon DESTINATION lib
         EXPORT doraemon-targets )
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/doraemon"
         DESTINATION include)
install (EXPORT doraemon-targets
         DESTINATION lib/cmake/doraemon)

#export (TARGETS doraemon wrapper FILE doraemon-targets.cmake)
configure_file ( "${PROJECT_SOURCE_DIR}/pkg/doraemon-config.cmake.in"
                 "${PROJECT_BINARY_DIR}/doraemon-config.cmake" @ONLY)
                 
configure_file ( "${PROJECT_SOURCE_DIR}/pkg/doraemon-config-version.cmake.in"
                 "${PROJECT_BINARY_DIR}/doraemon-config-version.cmake" @ONLY)
                 
install (FILES 
        "${PROJECT_BINARY_DIR}/doraemon-config.cmake"
        "${PROJECT_BINARY_DIR}/doraemon-config-version.cmake"
        DESTINATION lib/cmake/doraemon)
