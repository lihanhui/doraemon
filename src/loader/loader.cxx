// Copyright (c) 2019 Hanhui LI
#include "doraemon/loader/loader.h"

#include <dlfcn.h>
#include <string>

namespace doraemon {

Handle Loader::load(const std::string& filename)
{
    return reinterpret_cast<Handle>(dlopen(filename.c_str(), RTLD_LAZY));
}

void Loader::unload(Handle h)
{
    dlclose(reinterpret_cast<void*>(h));
}

};  // namespace doraemon
