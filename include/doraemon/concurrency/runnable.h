#ifndef DORAEMON_CONCURRENCY_RUNNABLE_H
#define DORAEMON_CONCURRENCY_RUNNABLE_H

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

    struct WeakRunnable: public Runnable{
        virtual std::shared_ptr<WeakPromise> get_weak_promise() = 0;
    };
};

#endif