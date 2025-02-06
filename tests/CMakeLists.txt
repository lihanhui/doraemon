# GTest include code would
# go somewhere in here

find_package(GTest REQUIRED)

add_executable(doraemon_test doraemon_test.cpp 
    base64/test_base64.cxx
    ipc/test_semaphore.cxx
    uuid/test_uuid.cxx
    )

target_link_libraries(doraemon_test
 PRIVATE
  GTest::GTest
  doraemon)

add_test(doraemon_gtests doraemon_test)

