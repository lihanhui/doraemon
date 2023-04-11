#ifndef DORAEMON_LOCK_SCOPED_LOCK_H
#define DORAEMON_LOCK_SCOPED_LOCK_H

#include <atomic>

#include "doraemon/lock/lock.h"

namespace doraemon{

class ScopedLock{
private:
    Lockable* lck;

private:
    ScopedLock() {}
public:
    ScopedLock(Lockable &lck) { 
        this->lck = &lck;
        this->lck->lock(); 
    }
    ~ScopedLock() { this->lck->unlock(); }
};

};

#endif
