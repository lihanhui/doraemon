#ifndef DORAEMON_CONCURRENCY_ABSTRACT_TASK_H
#define DORAEMON_CONCURRENCY_ABSTRACT_TASK_H

#include <condition_variable>
#include <mutex>
#include <thread>

#include "doraemon/concurrency/task.h"

namespace doraemon{

    class AbstractTask : public Task{
    private:
        TaskStatus task_status_;
        std::mutex task_mtx_;
    public:
        AbstractTask(){ task_status_ = TaskStatus::Initialized; }
        void start() override;
        void cancel() override;
        void run() override;
        bool is_running() override { return task_status_ == TaskStatus::Running; }
        bool is_alive() override { return task_status_ <  TaskStatus::Cancelled; }

        TaskStatus get_status() override {return task_status_;}
    protected:
        // 
        virtual void invoke() = 0;
    };

};

#endif