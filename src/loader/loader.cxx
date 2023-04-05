#include <dlfcn.h>
#include <string>

#include "doraemon/loader/loader.h"

using namespace doraemon::loader;

handle loader::load(std::string& filename)
{
    return dlopen(filename.c_str(), RTLD_LAZY);
}

void loader::unload(handle h)
{
    dlclose(h);
}