#include <chrono>
#include <mutex>
#include <queue>
#include <thread>

#include "doraemon/concurrency/task_executor_service.h"
#include "doraemon/runtime/runtime_error.h"

namespace doraemon{
    using namespace std::chrono_literals;
	std::shared_ptr<Runnable> SingleThreadTaskExecutorService::get_one(){
		std::shared_ptr<Runnable> r = nullptr;
        {
        	std::lock_guard<std::mutex> lck (this->queue_mtx_);
        	if(this->tasks_.size() > 0){
        		r = this->tasks_.front();
                this->tasks_.pop();
        	}
        }
        return r;
    	
    }
	void SingleThreadTaskExecutorService::internal_run(){
		std::shared_ptr<Runnable> r = nullptr;
    	while(r = get_one(), r){
    		r->run();
    	}
    	
    }
    void SingleThreadTaskExecutorService::run(){
    	try{

  			internal_run();
  			std::this_thread::sleep_for(10ms);
    	}
    	catch(...){

    	}
    }

    void SingleThreadTaskExecutorService::submit(std::shared_ptr<Runnable> t){
    	std::lock_guard<std::mutex> lck (this->queue_mtx_);
    	this->tasks_.push(t);
    }
};