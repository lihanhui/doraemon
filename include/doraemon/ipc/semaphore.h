// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_IPC_SEMAPHORE_H_
#define INCLUDE_DORAEMON_IPC_SEMAPHORE_H_

#include <string>

#include "doraemon/core/type_def.h"

namespace doraemon {

class Semaphore {
public:
    //Semaphore(const std::string &name);
    Semaphore(const std::string &name, int init_value = 1);
    ~Semaphore();
public:
    bool open();
    bool acquire();
    void release();
    void unlink();
    void close();
public:
    inline int get_value() { return value_; }
private:
    std::string name_;
    Handle handle_;
    int value_ = 0;
};

};

#endif