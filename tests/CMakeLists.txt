# GTest include code would
# go somewhere in here

find_package(GTest REQUIRED)

add_executable(doraemon_test doraemon_test.cpp)

target_link_libraries(doraemon_test
 PRIVATE
  GTest::GTest
  doraemon)

add_test(doraemon_gtests doraemon_test)

