#ifndef DORAEMON_CONCURRENCY_RUNNABLE_H
#define DORAEMON_CONCURRENCY_RUNNABLE_H

namespace doraemon{

    struct Runnable{
    protected:
    	virtual void run() = 0;
    public:
        virtual void start() = 0;
        virtual bool is_running() = 0;
        virtual bool is_alive() = 0;
    };
};

#endif