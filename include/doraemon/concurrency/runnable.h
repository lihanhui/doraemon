#ifndef DORAEMON_CONCURRENCY_RUNNABLE_H
#define DORAEMON_CONCURRENCY_RUNNABLE_H

namespace doraemon{

    struct Runnable{
    	virtual void run() = 0;
    };
};

#endif