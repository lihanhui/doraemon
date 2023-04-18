#ifndef DORAEMON_CONCURRENCY_EXECUTOR_H
#define DORAEMON_CONCURRENCY_EXECUTOR_H

#include <memory>

#include "doraemon/concurrency/future.h"
#include "doraemon/concurrency/task.h"

namespace doraemon{

    struct Executor{
    	 template<class T> std::shared_ptr<Future<T>> submit(std::shared_ptr<Task<T>> t) ;
    };
};

#endif