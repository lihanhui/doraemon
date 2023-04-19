#ifndef DORAEMON_CONCURRENCY_THREAD_POOL_H
#define DORAEMON_CONCURRENCY_THREAD_POOL_H

#include <memory>

#include "doraemon/concurrency/executor.h"
#include "doraemon/concurrency/runnable.h"
#include "doraemon/concurrency/task_executor_service.h"
#include "doraemon/random/random_util.h"

namespace doraemon{

    struct ThreadPool: public TaskExecutor, public AbstractService{
    	virtual std::shared_ptr<Executor> get_executor() = 0;

    };

    class SimpleThreadPool: public ThreadPool{
    private:
        size_t count_;
        std::vector<std::shared_ptr<SingleThreadTaskExecutorService>> executors_;
    public:
        SimpleThreadPool(size_t count) {
            this->count_ = count;
            for(unsigned int i = 0; i < count; ++i){
                std::shared_ptr<SingleThreadTaskExecutorService> e =  std::make_shared<SingleThreadTaskExecutorService>();
                e->start();
                executors_.push_back(e);
            }
        }
        std::shared_ptr<Executor> get_executor() override{
            int r = RandomUtil::random(0, 10 * this->count_);
            return this->executors_[r % this->count_];
        }
    public:
        void submit0(std::shared_ptr<WeakTask> t) override{
            this->executors_[t->hash_code() % count_]->submit0(t); 
        }
        void start() override;
        void pause() override;
        void resume() override;
        void stop() override;
    protected:
        void run() override;
    };
};

#endif