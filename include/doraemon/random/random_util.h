#ifndef DORAEMON_RANDOM_RANDOM_UTIL_H
#define DORAEMON_RANDOM_RANDOM_UTIL_H

#include <random>

namespace doraemon{

struct random_util {

    static int random(int start, int end){
        // Seed with a real random value, if available
        std::random_device r;
 
        // Choose a random mean between 1 and 6
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(start, end);
        return uniform_dist(e1);
    }
    
    static unsigned char random_char() {
        std::random_device rd;
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> dis(0, 255);
        return static_cast<unsigned char>(dis(gen));
    }
};

};
#endif