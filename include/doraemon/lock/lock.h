// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_LOCK_LOCK_H_
#define INCLUDE_DORAEMON_LOCK_LOCK_H_

namespace doraemon {

class Lockable {
 public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_LOCK_LOCK_H_
