#ifndef DORAEMON_CONCURRENCY_SERVICE_H
#define DORAEMON_CONCURRENCY_SERVICE_H

#include "doraemon/concurrency/runnable.h"

namespace doraemon{
	enum class ServiceStatus{
        Initialized = 1,
        Running = 2,
        Paused  = 4,
        Stopped = 8,
        Aborted = 16 // aborted cause some exceptions
	};

    struct Service : public Runnable{
        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual void stop() = 0;
        virtual ServiceStatus get_status() = 0;
    };

};

#endif