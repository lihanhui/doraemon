    
#include "doraemon/concurrency/abstract_service.h"
#include "doraemon/runtime/runtime_error.h"

namespace doraemon{
    
    void AbstractService::start() {
        this->service_status_ = ServiceStatus::Running;
        this->thread_ = std::thread([this]{
                run();
            });
    }
    void AbstractService::pause() {
        if(this->service_status_ == ServiceStatus::Running){
            this->service_status_ = ServiceStatus::Paused;
        }
    }
    void AbstractService::stop() {
        if(this->service_status_ <= ServiceStatus::Running){
            this->service_status_ = ServiceStatus::Stopped;
        }
    }

    void AbstractService::resume(){
        if(this->service_status_ == ServiceStatus::Paused){
            this->service_status_ = ServiceStatus::Running;
        }
    }

    void AbstractService::run(){
        throw RuntimeError("not implemented");
    }

};
    
