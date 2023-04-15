#ifndef DORAEMON_CONCURRENCY_RUNNABLE_H
#define DORAEMON_CONCURRENCY_RUNNABLE_H

namespace doraemon{

    struct Runnable{
    	virtual void run() = 0;
        virtual bool is_runnable() = 0;
        virtual bool is_alive() = 0;
    };
};

#endif