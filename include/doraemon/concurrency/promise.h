// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_PROMISE_H_
#define INCLUDE_DORAEMON_CONCURRENCY_PROMISE_H_

#include <future> //NOLINT [build/c++11]

#include "doraemon/concurrency/future.h"

namespace doraemon
{
struct WeakPromise
{
     /**
     * Marks this future as a failure and notifies all
     * listeners.
     *
     * If it is success or failed already it will throw an {@link IllegalStateException}.
     */
    virtual bool failure(std::exception_ptr cause) = 0;

    /**
     * Marks this future as a failure and notifies all
     * listeners.
     *
     * @return {@code true} if and only if successfully marked this future as
     *         a failure. Otherwise {@code false} because this future is
     *         already marked as either a success or a failure.
     */
    virtual bool try_failure(std::exception_ptr cause) = 0;
};

template <typename T> class Promise:
public WeakPromise, public Future<T>, public std::promise<T>
{
 public:
     /**
     * Marks this future as a success and notifies all
     * listeners.
     *
     * If it is success or failed already it will throw an {@link IllegalStateException}.
     */
    virtual bool success(const T& v) = 0;
    virtual bool success(T&& v) = 0;

    /**
     * Marks this future as a success and notifies all
     * listeners.
     *
     * @return {@code true} if and only if successfully marked this future as
     *         a success. Otherwise {@code false} because this future is
     *         already marked as either a success or a failure.
     */
    virtual bool try_success(const T& v) = 0;
    virtual bool try_success(T&& v) = 0;

    virtual bool done() = 0;
};

};  // namespace doraemon
#endif  // INCLUDE_DORAEMON_CONCURRENCY_PROMISE_H_
