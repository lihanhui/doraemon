#include "doraemon/uuid/uuid.h"

#include "gtest/gtest.h"

#include <iostream>
#include <string>

class UuidTest: public ::testing::Test{
protected:
    UuidTest(){}
    ~UuidTest() override { }
    
    void SetUp() override {
       // Code here will be called immediately after the constructor (right
       // before each test).
       std::cout<<"first"<<std::endl;
    }

    void TearDown() override {
       // Code here will be called immediately after each test (right
       // before the destructor).
    }
};

TEST_F(UuidTest, uuid) {
  
  std::string uuid2 = doraemon::Uuid::uuid();
  std::cout<<uuid2<<std::endl;
  ASSERT_EQ(uuid2.size(), 32);
}

