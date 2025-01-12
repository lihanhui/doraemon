// Copyright (c) 2019 Hanhui LI
#include "doraemon/loader/loader.h"

#include <string>

namespace doraemon
{
#ifdef _WIN32
#include <libloaderapi.h>

Handle Loader::load(const std::string &filename)
{
    return reinterpret_cast<Handle>(LoadLibraryA(filename.c_str(), RTLD_LAZY));
}

void Loader::unload(Handle h)
{
    FreeLibrary(reinterpret_cast<HMODULE>(h));
}

#else

#include <dlfcn.h>

Handle Loader::load(const std::string& filename)
{
    return reinterpret_cast<Handle>(dlopen(filename.c_str(), RTLD_LAZY));
}

void Loader::unload(Handle h)
{
    dlclose(reinterpret_cast<void*>(h));
}

#endif

}; // namespace doraemon
