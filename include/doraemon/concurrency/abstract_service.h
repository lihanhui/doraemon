#ifndef DORAEMON_CONCURRENCY_ABSTRACT_SERVICE_H
#define DORAEMON_CONCURRENCY_ABSTRACT_SERVICE_H

#include <condition_variable>
#include <mutex>
#include <thread>

#include "doraemon/concurrency/service.h"

namespace doraemon{

    class AbstractService : public Service{
    private:
        //std::mutex service_mtx_;
        std::condition_variable cv_;
        std::thread thread_;
    protected:
        ServiceStatus service_status_;
        std::mutex service_mtx_;
    public:
        AbstractService(){ service_status_ = ServiceStatus::Initialized; }
        void start() override;
        void pause() override;
        void resume() override;
        void stop() override;
        void run() override;
        bool is_running() override { return service_status_ == ServiceStatus::Running; }
        bool is_alive() override { return service_status_ <  ServiceStatus::Stopped; }

        ServiceStatus get_status() override {return service_status_;}

    };

};

#endif