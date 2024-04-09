// Copyright (c) 2019 Hanhui LI
#include <mutex> //NOLINT [build/c++11]

#include "doraemon/concurrency/abstract_service.h"
#include "doraemon/runtime/runtime_error.h"

namespace doraemon {

    void AbstractService::start() {
        std::scoped_lock<std::mutex> lck(service_mtx_);
        if ( this->service_status_  >= ServiceStatus::Running) return;
        this->service_status_ = ServiceStatus::Running;
        this->thread_ = std::thread([this]{
                run();
            });
    }
    void AbstractService::pause() {
        std::scoped_lock<std::mutex> lck(service_mtx_);
        if (this->service_status_ == ServiceStatus::Running) {
            this->service_status_ = ServiceStatus::Paused;
        }
    }
    void AbstractService::stop() {
        std::scoped_lock<std::mutex> lck(service_mtx_);
        if (this->service_status_ <= ServiceStatus::Running) {
            this->service_status_ = ServiceStatus::Stopped;
        }
    }

    void AbstractService::resume() {
        std::scoped_lock<std::mutex> lck(service_mtx_);
        if (this->service_status_ == ServiceStatus::Paused) {
            this->service_status_ = ServiceStatus::Running;
        }
    }

    void AbstractService::run(){
        throw RuntimeError("not implemented");
    }

};  // namespace doraemon
