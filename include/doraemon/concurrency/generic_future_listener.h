#ifndef DORAEMON_CONCURRENCY_GENERIC_FUTURE_LISTENER_H
#define DORAEMON_CONCURRENCY_GENERIC_FUTURE_LISTENER_H

#include <functional>

#include "doraemon/concurrency/event_listener.h"
#include "doraemon/concurrency/future.h"

namespace doraemon
{

template<class T> class Future;

template <typename T, typename F = Future<T>> class GenericFutureListener: public EventListener{
private:
	std::function<void(const std::shared_ptr<F> future)> callable;
public:
    GenericFutureListener(std::function<void(const std::shared_ptr<F> future)> callable){
        this->callable = callable;
    }
    void operationComplete(const std::shared_ptr<F> future){
    	callable(future);
    }
};

}; // namespace doraemon
//typedef GenericFutureListener<typename T>;
#endif
