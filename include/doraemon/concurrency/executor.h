#ifndef DORAEMON_CONCURRENCY_EXECUTOR_H
#define DORAEMON_CONCURRENCY_EXECUTOR_H

#include <memory>

#include "doraemon/concurrency/runnable.h"

namespace doraemon{

    struct Executor{
    	virtual void submit(std::shared_ptr<Runnable> t) = 0;
    };
};

#endif