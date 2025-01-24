// Copyright [2024] <Copyright hanhui.li@google.com>

#include "gtest/gtest.h"

#include "doraemon/ipc/shared_memory.h"

int main(int argc, char **argv) {
  doraemon::SharedMemory* sm = new doraemon::SharedMemory("example", 1024, doraemon::SharedMemory::AccessMode::AM_WRITE);
  sm->begin();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

