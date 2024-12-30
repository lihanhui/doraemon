// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_TIME_CLOCK_H_
#define INCLUDE_DORAEMON_TIME_CLOCK_H_

#include <chrono>

#include "doraemon/export/export_def.h"

namespace doraemon{

    class D_CLASS_EXPORT MonoClock
    {
    public:
        static uint64_t get_current_tick_millis();
    };

    class D_CLASS_EXPORT WallClock
    {
    public:
        static int64_t get_current_time_millis();
    };

};  // namespace doraemon


#endif  // INCLUDE_DORAEMON_TIME_CLOCK_H_
