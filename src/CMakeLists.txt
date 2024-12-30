IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    add_definitions( -D__OS_FAMILY_LINUX__  )
    add_definitions( -D__OS_FAMILY_UNIX__  )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    add_definitions( -D__OS_FAMILY_WINDOWS__  )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    MESSAGE(STATUS "current platform: FreeBSD")
    add_definitions( -D__OS_FAMILY_FREEBSD__  )
    add_definitions( -D__OS_FAMILY_UNIX__  )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: APPLE")
    add_definitions( -D__OS_FAMILY_APPLE__  )
    add_definitions( -D__OS_FAMILY_UNIX__  )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
    add_definitions( -D__OS_FAMILY_UNKNOWN__  )
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

#####################################
add_library(doraemon SHARED doraemon.cxx
            buffer/buffer.cxx 
            atomic/atomic_counter.cxx
            atomic/ref_counted_object.cxx
            concurrency/abstract_service.cxx
            concurrency/task_executor_service.cxx
            concurrency/thread_pool.cxx
            conf/config.cxx
            ipc/shared_memory.cxx
            md5/md5.cxx
            time/clock.cxx
            net/net.cxx
            sys/system.cxx
            loader/loader.cxx
            base64/base64.cxx)
set_target_properties(doraemon PROPERTIES VERSION 1.0 SOVERION 1)
target_link_libraries(doraemon  ${EXTRA_LIBS})

#add_executable(doraemon-tmp doraemon.cxx)
#target_link_libraries(doraemon-tmp  ${EXTRA_LIBS} doraemon)

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
