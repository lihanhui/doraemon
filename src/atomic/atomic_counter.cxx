// Copyright (c) 2019 Hanhui LI
#include "doraemon/atomic/atomic_counter.h"

namespace doraemon {

AtomicCounter::AtomicCounter() : counter_(0)
{
}

AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue):
    counter_(initialValue)
{
}

AtomicCounter::AtomicCounter(const AtomicCounter &counter):
    counter_(counter.value())
{
}

AtomicCounter::~AtomicCounter()
{
}

AtomicCounter& AtomicCounter::operator=(const AtomicCounter& counter)
{
    counter_.store(counter.counter_.load());
    return *this;
}


AtomicCounter& AtomicCounter::operator=(AtomicCounter::ValueType value)
{
    counter_.store(value);
    return *this;
}

};  // namespace doraemon
