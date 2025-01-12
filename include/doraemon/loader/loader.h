// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_LOADER_LOADER_H_
#define INCLUDE_DORAEMON_LOADER_LOADER_H_

#include <string>

#include "doraemon/core/type_def.h"
#include "doraemon/export/export_def.h"

namespace doraemon {

//using Handle = void*;

class D_CLASS_EXPORT Loader
{
public:
    static Handle load(const std::string& filename);
    static void unload(Handle h);
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_LOADER_LOADER_H_
