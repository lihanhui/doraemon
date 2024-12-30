 
#include "doraemon/time/clock.h"
 
#include <chrono>

namespace doraemon {

uint64_t  MonoClock::get_current_tick_millis() {
    auto timepoint = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(timepoint.time_since_epoch()).count();
}


int64_t  WallClock::get_current_time_millis() {
    auto timepoint = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(timepoint.time_since_epoch()).count();
}

}; 
