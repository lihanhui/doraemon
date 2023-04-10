#ifndef DORAEMON_RUNTIME_RUMTIMEERROR_H
#define DORAEMON_RUNTIME_RUMTIMEERROR_H

#include <stdexcept>
#include <string>

namespace doraemon{

    class RuntimeError: std::runtime_error{
    public:
        RuntimeError(const std::string & info): std::runtime_error(info){}
    };	
};

#endif