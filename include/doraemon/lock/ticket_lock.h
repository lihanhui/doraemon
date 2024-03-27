// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_LOCK_TICKET_LOCK_H_
#define INCLUDE_DORAEMON_LOCK_TICKET_LOCK_H_

#include <atomic>

#include "doraemon/lock/lock.h"

namespace doraemon {

class TicketLock: public Lockable {
 private:
    std::atomic_size_t serving_ticket_num = {0};
    std::atomic_size_t next_ticket_num = {0};

 public:
    void lock() override {
        const auto ticket_num = next_ticket_num.fetch_add(1,
            std::memory_order_relaxed);

        while (serving_ticket_num.load(
            std::memory_order_acquire) != ticket_num) {
        }
    }

    void unlock() override {
        const auto new_num = serving_ticket_num.load(
            std::memory_order_relaxed) + 1;
        serving_ticket_num.store(new_num, std::memory_order_release);
    }
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_LOCK_TICKET_LOCK_H_
