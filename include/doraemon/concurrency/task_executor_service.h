#ifndef DORAEMON_CONCURRENCY_TASK_EXECUTOR_SERVICE_H
#define DORAEMON_CONCURRENCY_TASK_EXECUTOR_SERVICE_H

#include <memory>
#include <mutex>
#include <queue>

#include "doraemon/concurrency/abstract_service.h"
#include "doraemon/concurrency/task_executor.h"

namespace doraemon{

    class SingleThreadTaskExecutorService: public TaskExecutor, AbstractService{
    	private:
            std::queue<std::shared_ptr<Runnable>>  tasks_;
            std::mutex queue_mtx_;
        public:
            SingleThreadTaskExecutorService(){}
            void run() override;

            void submit(std::shared_ptr<Runnable> t) override;
        protected:
            void internal_run();
            std::shared_ptr<Runnable> get_one();

    };
};

#endif