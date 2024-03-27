#include "doraemon/base64/base64.h"

#include "gtest/gtest.h"

class Base64Test: public ::testing::Test{
protected:
    Base64Test(){}
    ~Base64Test() override { }
    
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

TEST_F(Base64Test, Encode) {
  const std::string source = "hello base64";
  const std::string encoded = "aGVsbG8gYmFzZTY0";
  
  ASSERT_STREQ(doraemon::Base64::encode((unsigned char const*)source.c_str(), source.size()).c_str(), encoded.c_str());
}

TEST_F(Base64Test, Decode) {
  const std::string source = "hello base64";
  const std::string encoded = "aGVsbG8gYmFzZTY0";

  ASSERT_STREQ(doraemon::Base64::decode(encoded).c_str(), source.c_str());
}
