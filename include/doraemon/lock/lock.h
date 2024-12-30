// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_LOCK_LOCK_H_
#define INCLUDE_DORAEMON_LOCK_LOCK_H_

#include "doraemon/export/export_def.h"

namespace doraemon {

    class D_CLASS_EXPORT Lockable
    {
    public:
        virtual void lock() = 0;
        virtual void unlock() = 0;
    };

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_LOCK_LOCK_H_
