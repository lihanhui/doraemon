// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_QUEUE_QUEUE_FIFO_H_
#define INCLUDE_DORAEMON_QUEUE_QUEUE_FIFO_H_

#include <mutex>

namespace doraemon {
template<typename T> struct QueueNode {
    QueueNode* next_;
    T* data_;

 public:
    explicit QueueNode(T *data = nullptr) : next_(nullptr), data_(data) {}
};

template<typename T> class QueueFifo{
 public:
    QueueFifo(): head_(nullptr), tail_(nullptr), count_(0) { }

 public:
    void push(T* t) {
        std::scoped_lock lock(lock_);
        QueueNode<T> *node = new QueueNode<T>(t);
        if ( tail_ ) {
            tail_->_next = node;
            tail_ = node;
        } else {
            head_ = node;
            tail_ = node;
        }
        ++count_;
    }

    T* pop() {
        std::scoped_lock lock(lock_);
        QueueNode<T> *head = head_;
        T* data = nullptr;
        if ( head_ )
        {
            T* data = head->_data;
            if (head_->_next)
            {  // more than one node
                head_ = _head->_next;
            } else {  // only one node
                head_ = tail_ = nullptr;
            }
            delete head;
            --count_;
        }
        return data;
    }

    int count() {
        std::scoped_lock lock(lock_);
        return count_;
    }

    void clear() {
        std::scoped_lock lock(lock_);
        QueueNode<T> *head = head_;
        QueueNode<T>* next = nullptr;
        while ( head ) {
            next = head->_next;
            delete head;
            head = next;
        }
        head_ = tail_ = nullptr;
        count_ = 0;
    }

 private:
    std::mutex lock_;
    QueueNode<T> *head_;
    QueueNode<T> *tail_;
    int count_;
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_QUEUE_QUEUE_FIFO_H_
