// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_EXECUTOR_H_
#define INCLUDE_DORAEMON_CONCURRENCY_EXECUTOR_H_

#include <memory>

#include "doraemon/concurrency/future.h"
#include "doraemon/concurrency/task.h"
#include "doraemon/export/export_def.h"

namespace doraemon{

struct Executor
{
    template<class T> std::shared_ptr<Future<T>> submit(
        std::shared_ptr<Task<T>> t) 
    {
        this->submit0(t);
        return t->get_promise();
    }
 protected:
    virtual void submit0(std::shared_ptr<WeakTask> t) = 0;
};
};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_CONCURRENCY_EXECUTOR_H_
