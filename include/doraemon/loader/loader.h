#ifndef DORAEMON_LOADER_LOADER_H 
#define DORAEMON_LOADER_LOADER_H 

#include <string>

namespace doraemon{

using Handle = void*;

class Loader{


public:
    static Handle load(std::string& filename);
    static void unload(Handle h);
};

};

#endif
