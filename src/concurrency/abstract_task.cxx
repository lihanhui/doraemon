#include <mutex>

#include "doraemon/concurrency/abstract_task.h"
#include "doraemon/runtime/runtime_error.h"

namespace doraemon{
    
    void AbstractTask::start() {
        {
            std::scoped_lock<std::mutex> lck(task_mtx_);
            if(this->task_status_ >= TaskStatus::Running) return ;
            this->task_status_ = TaskStatus::Running;
        }
        this->run();
    }
    void AbstractTask::cancel() {
        
        std::scoped_lock<std::mutex> lck(task_mtx_);
        if(this->task_status_ >= TaskStatus::Running) 
            this->task_status_ = TaskStatus::Cancelled;
    }
    

    void AbstractTask::run(){
        throw RuntimeError("not implemented");
    }

};