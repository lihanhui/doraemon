#ifndef DORAEMON_CONCURRENCY_ABSTRACT_TASK_H
#define DORAEMON_CONCURRENCY_ABSTRACT_TASK_H

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include "doraemon/concurrency/task.h"
#include "doraemon/concurrency/default_promise.h"

namespace doraemon{

    template<typename T> class AbstractTask : public Task<T>{
    private:
        TaskStatus task_status_;
        std::mutex task_mtx_;
        std::shared_ptr<Promise<T>> promise_;
    public:
        AbstractTask(){ 
            task_status_ = TaskStatus::Initialized;
            promise_ = std::make_shared<DefaultPromise<T>>();
        }

        void start() override {
            {
                std::scoped_lock<std::mutex> lck(task_mtx_);
                if(this->task_status_ >= TaskStatus::Running) return ;
                this->task_status_ = TaskStatus::Running;
            }
            this->run();
        }
        void cancel() override {
            
            std::scoped_lock<std::mutex> lck(task_mtx_);
            if(this->task_status_ >= TaskStatus::Running) 
                this->task_status_ = TaskStatus::Cancelled;
        }
    

        void run() override{
            throw RuntimeError("not implemented");
        }

        bool is_running() override { return task_status_ == TaskStatus::Running; }
        bool is_alive() override { return task_status_ <  TaskStatus::Cancelled; }

        TaskStatus get_status() override {return task_status_;}
        size_t hash_code() override {return (size_t)(void*)this;}

        std::shared_ptr<Promise<T>> get_promise() override {
            return promise_;
        }
    protected:
        // 
        virtual void invoke() = 0;
    };

};

#endif