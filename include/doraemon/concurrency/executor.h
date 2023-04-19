#ifndef DORAEMON_CONCURRENCY_EXECUTOR_H
#define DORAEMON_CONCURRENCY_EXECUTOR_H

#include <memory>

#include "doraemon/concurrency/future.h"
#include "doraemon/concurrency/task.h"

namespace doraemon{

    struct Executor{
    	template<class T> std::shared_ptr<Future<T>> submit(std::shared_ptr<Task<T>> t) {
            this->submit0(t);
            return t->get_promise();
        }
    protected:
        virtual void submit0(std::shared_ptr<WeakRunnable> t) = 0;
    };
};

#endif