// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_LOCK_MUTEX_LOCK_H_
#define INCLUDE_DORAEMON_LOCK_MUTEX_LOCK_H_

#include <mutex> //NOLINT [build/c++11]

#include "doraemon/lock/lock.h"

namespace doraemon {

class MutexLock : public Lockable {
 private:
    std::mutex lck_;

 public:
    void lock() override {
        lck_.lock();
    }

    void unlock() override {
        lck_.unlock();
    }
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_LOCK_MUTEX_LOCK_H_
