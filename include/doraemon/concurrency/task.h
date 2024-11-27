// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_TASK_H_
#define INCLUDE_DORAEMON_CONCURRENCY_TASK_H_

#include <memory>

#include "doraemon/concurrency/runnable.h"
#include "doraemon/concurrency/promise.h"

namespace doraemon{
enum class TaskStatus
{
    Initialized = 1,
    Running = 2,
    Cancelled = 4,
    Finished = 8,
    Aborted = 16  // aborted cause some exceptions
};

struct WeakTask: public Runnable
{
    virtual std::shared_ptr<WeakPromise> get_weak_promise() = 0;
    virtual TaskStatus get_status() = 0;
    virtual void cancel() = 0;
    virtual size_t hash_code() = 0;
};

template<typename T> struct Task : public WeakTask
{
    virtual std::shared_ptr<Promise<T>> get_promise() = 0;
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_CONCURRENCY_TASK_H_
