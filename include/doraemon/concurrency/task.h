#ifndef DORAEMON_CONCURRENCY_TASK_H
#define DORAEMON_CONCURRENCY_TASK_H

#include <memory>

#include "doraemon/concurrency/runnable.h"
#include "doraemon/concurrency/promise.h"

namespace doraemon{
	enum class TaskStatus{
        Initialized = 1,
        Running = 2,
        Cancelled = 4,
        Finished = 8,
        Aborted = 16 // aborted cause some exceptions
	};

    template<typename T> struct Task : public WeakRunnable{
        virtual void cancel() = 0;
        virtual TaskStatus get_status() = 0;

        virtual std::shared_ptr<Promise<T>> get_promise() = 0;
        virtual size_t hash_code() = 0;
    };

};

#endif