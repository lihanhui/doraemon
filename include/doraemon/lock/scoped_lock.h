// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_LOCK_SCOPED_LOCK_H_
#define INCLUDE_DORAEMON_LOCK_SCOPED_LOCK_H_

#include <atomic>

#include "doraemon/lock/lock.h"

namespace doraemon {

class ScopedLock {
 private:
    Lockable* lck;

 private:
    ScopedLock() {}

 public:
    explicit ScopedLock(const Lockable &lck) {
        this->lck = &lck;
        this->lck->lock();
    }

    ~ScopedLock() { this->lck->unlock(); }
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_LOCK_SCOPED_LOCK_H_
