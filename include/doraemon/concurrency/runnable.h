#ifndef DORAEMON_CONCURRENCY_RUNNABLE_H
#define DORAEMON_CONCURRENCY_RUNNABLE_H

namespace doraemon{

    struct Runnable{
    	virtual void start() = 0;
    	virtual void run() = 0;
    	virtual bool is_running() = 0;
        virtual bool is_alive() = 0;
        virtual ~Runnable() {}
    };
};

#endif