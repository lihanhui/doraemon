 
#include "doraemon/uuid/uuid.h"
 
#include <string>

#include "doraemon/random/random_util.h"
#include "doraemon/time/clock.h"

namespace doraemon {

static void append_hex(std::string &str, uint8_t n){
    static const char* digits = "0123456789abcdef";
    str += digits[(n>>4) & 0x0F];
    str += digits[n & 0x0F];
}

static void append_hex(std::string &str, uint16_t n){
    append_hex(str, (uint8_t)(n >> 8));
    append_hex(str, (uint8_t)(n & 0xFF));
}

static void append_hex(std::string &str, uint32_t n){
    append_hex(str, (uint16_t)(n >> 16));
    append_hex(str, (uint16_t)(n & 0xFFFF));
}

std::string  Uuid::uuid() {
    const int VER = 7;
    uint16_t counter = RandomUtil::random(0, 4096);
    int64_t now = WallClock::get_current_time_millis();
    uint32_t time_high = (uint32_t) ((now>>16) & 0xFFFFFFFF);
    uint16_t time_mid = (uint16_t) (now & 0xFFFF);
    uint16_t randa_ver= (counter & 0x0FFF) + (VER<<12);

    counter = RandomUtil::random(0, 4096);
    uint16_t randb_high_var = (uint16_t)((counter>>4) & 0x3FFF) | 0x8000;

    uint8_t randb_low[6];
    for(int i = 0; i < 6; ++i){
        randb_low[i] = RandomUtil::random_char();
    }

    std::string result ;
    result.reserve(32);
    append_hex(result, time_high);
    append_hex(result, time_mid);
    append_hex(result, randa_ver);
    append_hex(result, randb_high_var);
    for(int i = 0; i < 6; ++i){
        append_hex(result, randb_low[i]);
    }
    return result;
}




}; 
