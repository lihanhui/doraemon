#include <chrono>
#include <mutex>
#include <queue>
#include <thread>

#include "doraemon/concurrency/task_executor_service.h"
#include "doraemon/runtime/runtime_error.h"

namespace doraemon{
    using namespace std::chrono_literals;
	std::shared_ptr<WeakTask> SingleThreadTaskExecutorService::get_one(){
		std::shared_ptr<WeakTask> r = nullptr;
        if(this->tasks_.size() > 0){
            r = this->tasks_.front();
            this->tasks_.pop();
        }
        return r;
    	
    }
	void SingleThreadTaskExecutorService::run_one(std::shared_ptr<WeakTask> r){
        try{
            if( this->is_running() ){
                if( r->is_alive() && !r->is_running()){
                    r->start();
                }else{
                    throw RuntimeError("the runnable task with wrong status"); // can call get_status
                }
            }
        }catch(...){
            r->get_weak_promise()->try_failure(std::current_exception());
        }
    }
    void SingleThreadTaskExecutorService::run(){
    	try{
            while(this->is_alive()){
                if(!this->is_running()) {
                    std::this_thread::sleep_for(10ms);
                    continue;
                }
                std::shared_ptr<WeakTask> r = nullptr;
                {
                    std::unique_lock lck(this->queue_mtx_);
                    r = get_one();

                    if(r) {
                        run_one(r);
                    }else{
                        cv_.wait_for(lck, 10ms); // wait for incoming tasks
                    } 
                }
            }
    	}
    	catch(...){

    	}
    }

};