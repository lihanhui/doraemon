// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONCURRENCY_DEFAULT_PROMISE_H_
#define INCLUDE_DORAEMON_CONCURRENCY_DEFAULT_PROMISE_H_

#include <list>
#include <memory>
#include <mutex> //NOLINT [build/c++11]
#include <thread> //NOLINT [build/c++11]
#include <utility>

#include "doraemon/concurrency/future.h"
#include "doraemon/concurrency/generic_future_listener.h"
#include "doraemon/concurrency/promise.h"
#include "doraemon/export/export_def.h"

namespace doraemon
{

template <typename T> class DefaultPromise: public Promise<T>
{
 private:
    std::mutex locker_;
    std::atomic_bool done_;
    std::atomic_bool succeeded;
    std::exception_ptr ex;

    std::list<std::shared_ptr<GenericFutureListener<T>>> listeners;

 private:
    std::mutex& get_locker() {
        return locker_;
    }

    bool get_done() {
        return done_.load();
    }

    void set_done() {
        return done_.store(true);
    }

    std::list<std::shared_ptr<GenericFutureListener<T>>> & get_listeners() {
        return listeners;
    }

 public:
    DefaultPromise() {
        done_     = false;
        succeeded = false;
        ex        = nullptr;
    }

    virtual ~DefaultPromise() {
    }

    ///////////////////////

    bool is_success() override { return succeeded; }
    std::exception_ptr cause() override { return ex; }

    void add_listener(
        std::shared_ptr<GenericFutureListener<T>> listener) override {
        std::lock_guard<std::mutex> guard(locker_);
        if (get_done()) {
            listener->operationComplete(this->shared_from_this());
        }
        listeners.push_back(listener);
    }

    T get() override {
        return this->get_future().get();
    }

    //////////////////////
    bool done() override { return this->get_done(); }
    bool success(const T& v) override {
        std::lock_guard<std::mutex> guard(locker_);
        if (this->get_done()) return false;

        this->set_value(v);
        this->done_ = true;
        this->succeeded = true;
        for (std::shared_ptr<GenericFutureListener<T>> &listener : listeners) {
            listener->operationComplete(this->shared_from_this());
        }
        return true;
    }
    bool success(T&& v) override {
        std::lock_guard<std::mutex> guard(locker_);
        if (this->get_done()) return false;

        this->set_value(std::move(v));
        this->done_ = true;
        this->succeeded = true;
        for (std::shared_ptr<GenericFutureListener<T>> &listener : listeners) {
            listener->operationComplete(this->shared_from_this());
        }
        return true;
    }

    bool try_success(const T& v) override {
        std::lock_guard<std::mutex> guard(locker_);
        if (this->get_done()) return false;

        this->set_value(v);
        this->done_ = true;
        this->succeeded = true;

        for (std::shared_ptr<GenericFutureListener<T>> &listener : listeners) {
            listener->operationComplete(this->shared_from_this());
        }
        return true;
    }

    bool try_success(T&& v) override {
        std::lock_guard<std::mutex> guard(locker_);
        if (this->get_done()) return false;

        this->set_value(std::move(v));
        this->done_ = true;
        this->succeeded = true;

        for (std::shared_ptr<GenericFutureListener<T>> &listener : listeners) {
            listener->operationComplete(this->shared_from_this());
        }
        return true;
    }

    bool failure(std::exception_ptr cause) override {
        std::lock_guard<std::mutex> guard(locker_);
        if (this->get_done()) return false;

        this->done_ = true;
        this->succeeded = false;
        this->set_exception(cause);
        this->ex = cause;

        for (std::shared_ptr<GenericFutureListener<T>> &listener : listeners) {
            listener->operationComplete(this->shared_from_this());
        }
        return true;
    }

    bool try_failure(std::exception_ptr cause) override {
        std::lock_guard<std::mutex> guard(locker_);
        if (this->get_done()) return false;

        this->done_ = true;
        this->succeeded = false;
        this->set_exception(cause);
        this->ex = cause;

        for (std::shared_ptr<GenericFutureListener<T>> &listener : listeners) {
            listener->operationComplete(this->shared_from_this());
        }
        return true;
    }
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_CONCURRENCY_DEFAULT_PROMISE_H_
