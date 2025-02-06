#include "doraemon/ipc/semaphore.h"

#include "gtest/gtest.h"

#include <iostream>
#include <string>

class SemaphoreTest : public ::testing::Test
{
protected:
    SemaphoreTest() {}
    ~SemaphoreTest() override {}

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
        std::cout << "first" << std::endl;
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(SemaphoreTest, open)
{

    doraemon::Semaphore m("hhhh");
    m.open();
    bool ok = m.acquire();
    if(ok){
        m.release();
    }
    m.close();
    
    ASSERT_TRUE(ok);
}
