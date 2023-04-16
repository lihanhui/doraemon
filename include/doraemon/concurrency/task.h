#ifndef DORAEMON_CONCURRENCY_TASK_H
#define DORAEMON_CONCURRENCY_TASK_H

#include "doraemon/concurrency/runnable.h"

namespace doraemon{
	enum class TaskStatus{
        Initialized = 1,
        Running = 2,
        Cancelled = 4,
        Finished = 8,
        Aborted = 16 // aborted cause some exceptions
	};

    struct Task : public Runnable{
        virtual void cancel() = 0;
        virtual TaskStatus get_status() = 0;
    };

};

#endif