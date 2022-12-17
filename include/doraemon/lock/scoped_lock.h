#ifndef DORAEMON_LOCK_SCOPED_LOCK_H
#define DORAEMON_LOCK_SCOPED_LOCK_H

#include <atomic>

#include "doraemon/lock/lock.h"

namespace doraemon{
namespace concurrency{

class scoped_lock{
private:
    lockable* lck;

private:
    scoped_lock() {}
public:
    scoped_lock(lockable &lck) { 
        this->lck = &lck;
        this->lck->lock(); 
    }
    ~scoped_lock() { this->lck->unlock(); }
};
};
};

#endif
