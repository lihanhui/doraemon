// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_TASK_EXECUTOR_SERVICE_H_
#define INCLUDE_DORAEMON_CONCURRENCY_TASK_EXECUTOR_SERVICE_H_

#include <condition_variable> //NOLINT [build/c++11]
#include <memory>
#include <mutex> //NOLINT [build/c++11]
#include <queue>

#include "doraemon/concurrency/abstract_service.h"
#include "doraemon/concurrency/task_executor.h"

namespace doraemon
{

class SingleThreadTaskExecutorService:
public TaskExecutor, public AbstractService
{
 private:
    std::queue<std::shared_ptr<WeakTask>>  tasks_;
    std::mutex queue_mtx_;
    std::condition_variable cv_;

 public:
    SingleThreadTaskExecutorService() {}

 protected:
    void run() override;

 public:
    void submit0(std::shared_ptr<WeakTask> t) override
    {
        std::lock_guard<std::mutex> lck(this->queue_mtx_);
        this->tasks_.push(t);
        cv_.notify_all();
    }

 private:
    void run_one(std::shared_ptr<WeakTask> r);
    std::shared_ptr<WeakTask> get_one();

 public:
    virtual ~SingleThreadTaskExecutorService()
    {
        std::lock_guard<std::mutex> lck(this->queue_mtx_);
        while (tasks_.size() > 0)
        {
            tasks_.pop();
        }
    }
};
};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_CONCURRENCY_TASK_EXECUTOR_SERVICE_H_
