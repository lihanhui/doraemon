#include <chrono>
#include <mutex>
#include <queue>
#include <thread>

#include "doraemon/concurrency/thread_pool.h"

namespace doraemon{
    using namespace std::chrono_literals;
    void SimpleThreadPool::run(){
    	try{
            while(this->is_alive()){
                std::this_thread::sleep_for(10ms);
            }
    	}
    	catch(...){

    	}
    }

    void SimpleThreadPool::start() {
        std::scoped_lock<std::mutex> lck(service_mtx_);
        if(this->service_status_  >= ServiceStatus::Running) return;
        this->service_status_ = ServiceStatus::Running;
        
        for(unsigned int i = 0; i < this->executors_.size(); ++i ){
        	this->executors_[i]->start();
        }
    }
    void SimpleThreadPool::pause() {
        std::scoped_lock<std::mutex> lck(service_mtx_);
        if(this->service_status_ == ServiceStatus::Running){
            this->service_status_ = ServiceStatus::Paused;
        }

        for(unsigned int i = 0; i < this->executors_.size(); ++i ){
        	this->executors_[i]->pause();
        }

    }
    void SimpleThreadPool::stop() {
        std::scoped_lock<std::mutex> lck(service_mtx_);
        if(this->service_status_ <= ServiceStatus::Running){
            this->service_status_ = ServiceStatus::Stopped;
        }

        for(unsigned int i = 0; i < this->executors_.size(); ++i ){
        	this->executors_[i]->stop();
        }
    }

    void SimpleThreadPool::resume(){
        std::scoped_lock<std::mutex> lck(service_mtx_);
        if(this->service_status_ == ServiceStatus::Paused){
            this->service_status_ = ServiceStatus::Running;
        }

        for(unsigned int i = 0; i < this->executors_.size(); ++i ){
        	this->executors_[i]->resume();
        }
    }

};