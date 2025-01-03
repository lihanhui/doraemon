// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_RUNTIME_RUNTIME_ERROR_H_
#define INCLUDE_DORAEMON_RUNTIME_RUNTIME_ERROR_H_

#include <stdexcept>
#include <string>

#include "doraemon/export/export_def.h"

namespace doraemon{

    class D_CLASS_EXPORT RuntimeError : std::runtime_error
    {
    public:
        explicit RuntimeError(const std::string &info) : std::runtime_error(info) {}
    };

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_RUNTIME_RUNTIME_ERROR_H_
