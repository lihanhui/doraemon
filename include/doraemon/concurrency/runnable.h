// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_RUNNABLE_H_
#define INCLUDE_DORAEMON_CONCURRENCY_RUNNABLE_H_

#include <memory>

#include "doraemon/concurrency/promise.h"

namespace doraemon{

struct Runnable{
    virtual void start() = 0;
    virtual void run() = 0;
    virtual bool is_running() = 0;
    virtual bool is_alive() = 0;
    virtual ~Runnable() {}
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_CONCURRENCY_RUNNABLE_H_
