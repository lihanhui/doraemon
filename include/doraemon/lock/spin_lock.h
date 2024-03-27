// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_LOCK_SPIN_LOCK_H_
#define INCLUDE_DORAEMON_LOCK_SPIN_LOCK_H_

#include <atomic>

#include "doraemon/lock/lock.h"

namespace doraemon {

class SpinLock : public Lockable {
 private:
    std::atomic_flag lck = ATOMIC_FLAG_INIT;

 public:
    void lock() override {
        while (lck.test_and_set(std::memory_order_acquire)) {
        }
    }

    void unlock() override {
        lck.clear(std::memory_order_release);
    }
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_LOCK_SPIN_LOCK_H_
