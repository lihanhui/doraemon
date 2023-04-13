    
#include "doraemon/concurrency/abstract_service.h"
#include "doraemon/runtime/runtime_error.h"

namespace doraemon{
    
    void AbstractService::start() {
        this->thread_ = std::thread([this]{
                run();
            ;});
    }
    void AbstractService::pause() {
        this->service_status_ = ServiceStatus::Paused;
    }
    void AbstractService::stop() {
        this->service_status_ = ServiceStatus::Stopped;
    }

    void AbstractService::resume(){
        this->service_status_ = ServiceStatus::Running;
    }

    void AbstractService::run(){
        throw RuntimeError("not implemented");
    }

};
    
