// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_JSON_JSONABLE_H_
#define INCLUDE_DORAEMON_JSON_JSONABLE_H_

#include <string>

#include "doraemon/export/export_def.h"

namespace doraemon {

    struct D_CLASS_EXPORT Jsonable
    {
        virtual std::string to_json() = 0;
        virtual void from_json(const std::string &json) = 0;
    };

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_JSON_JSONABLE_H_
