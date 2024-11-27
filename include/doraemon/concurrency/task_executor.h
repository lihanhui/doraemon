// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_TASK_EXECUTOR_H_
#define INCLUDE_DORAEMON_CONCURRENCY_TASK_EXECUTOR_H_

#include <memory>

#include "doraemon/concurrency/executor.h"
#include "doraemon/concurrency/runnable.h"

namespace doraemon{

struct TaskExecutor: public Executor
{
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_CONCURRENCY_TASK_EXECUTOR_H_
