#ifndef DORAEMON_LOCK_SPIN_LOCK_H
#define DORAEMON_LOCK_SPIN_LOCK_H

#include <atomic>

#include "doraemon/lock/lock.h"

namespace doraemon{

class SpinLock : public Lockable {
private:
    std::atomic_flag lck = ATOMIC_FLAG_INIT;

public:
    virtual void lock() override {
        while (lck.test_and_set (std::memory_order_acquire)){
        }
    }

    virtual void unlock () override {
        lck.clear (std::memory_order_release);
    }
};

};

#endif
