
#include "doraemon/concurrency/abstract_task.h"
#include "doraemon/runtime/runtime_error.h"

namespace doraemon{
    
    void AbstractTask::start() {
        this->task_status_ = TaskStatus::Running;
        this->run();
    }
    void AbstractTask::cancel() {
        this->task_status_ = TaskStatus::Cancelled;
    }
    

    void AbstractTask::run(){
        throw RuntimeError("not implemented");
    }

};