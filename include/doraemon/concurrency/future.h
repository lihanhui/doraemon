// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_FUTURE_H_
#define INCLUDE_DORAEMON_CONCURRENCY_FUTURE_H_

#include <exception>
#include <memory>

#include "doraemon/concurrency/generic_future_listener.h"
namespace doraemon
{

template<class T> class Future: public std::enable_shared_from_this<Future<T>> {
 public:
 /**
     * Returns {@code true} if and only if the I/O operation was completed
     * successfully.
     */
    virtual bool is_success() = 0;

    /**
     * Returns the cause of the failed I/O operation if the I/O operation has
     * failed.
     *
     * @return the cause of the failure.
     *         {@code null} if succeeded or this future is not
     *         completed yet.
     */
    virtual std::exception_ptr cause() = 0;

    /**
     * Adds the specified listener to this future.  The
     * specified listener is notified when this future is
     * {@linkplain #isDone() done}.  If this future is already
     * completed, the specified listener is notified immediately.
     */
    virtual void add_listener(
        std::shared_ptr<GenericFutureListener<T>> listener) = 0;

    /**
     * Return the result without blocking. If the future is not done yet this will return {@code null}.
     *
     * As it is possible that a {@code null} value is used to mark the future as successful you also need to check
     * if the future is really done with {@link #isDone()} and not relay on the returned {@code null} value.
     */
    virtual T get() = 0;
};

};  // namespace doraemon
#endif  // INCLUDE_DORAEMON_CONCURRENCY_FUTURE_H_
