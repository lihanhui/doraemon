#include <dlfcn.h>
#include <string>

#include "doraemon/loader/loader.h"

using namespace doraemon;

Handle Loader::load(std::string& filename)
{
    return dlopen(filename.c_str(), RTLD_LAZY);
}

void Loader::unload(Handle h)
{
    dlclose(h);
}