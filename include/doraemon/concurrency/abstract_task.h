// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_ABSTRACT_TASK_H_
#define INCLUDE_DORAEMON_CONCURRENCY_ABSTRACT_TASK_H_

#include <condition_variable> //NOLINT [build/c++11]
#include <memory>             //NOLINT [build/c++11]
#include <mutex>              //NOLINT [build/c++11]
#include <thread>             //NOLINT [build/c++11]

#include "doraemon/concurrency/task.h"
#include "doraemon/concurrency/default_promise.h"
#include "doraemon/export/export_def.h"
#include "doraemon/random/random_util.h"
#include "doraemon/runtime/runtime_error.h"

namespace doraemon{

template<typename T> class AbstractTask : public Task<T>{
 private:
    TaskStatus task_status_;
    std::mutex task_mtx_;
    std::shared_ptr<Promise<T>> promise_;

 public:
    AbstractTask() {
        task_status_ = TaskStatus::Initialized;
        promise_ = std::make_shared<DefaultPromise<T>>();
    }

    void start() override {
        {
            std::scoped_lock<std::mutex> lck(task_mtx_);
            if (this->task_status_ >= TaskStatus::Running) return;
            this->task_status_ = TaskStatus::Running;
        }
        this->run();
    }

    void cancel() override {
        std::scoped_lock<std::mutex> lck(task_mtx_);
        if (this->task_status_ >= TaskStatus::Running)
            this->task_status_ = TaskStatus::Cancelled;
    }

    void run() override {
        throw RuntimeError("not implemented");
    }

    bool is_running() override {
        return task_status_ == TaskStatus::Running; }
    bool is_alive() override {
        return task_status_ <  TaskStatus::Cancelled; }

    TaskStatus get_status() override { return task_status_; }

    size_t hash_code() override {
        return (size_t)((void*)this);
    }  // TODO: (Li Hanhui) wrong hashcode implementation, fix it later

    std::shared_ptr<Promise<T>> get_promise() override {
        return promise_;
    }

    std::shared_ptr<WeakPromise> get_weak_promise() override {
        return promise_;
    }

 protected:
    // virtual void invoke() = 0;
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_CONCURRENCY_ABSTRACT_TASK_H_
