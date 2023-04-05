#ifndef DORAEMON_LOADER_LOADER_H 
#define DORAEMON_LOADER_LOADER_H 

#include <string>

namespace doraemon{
namespace loader{

using handle = void*;

class loader{


public:
    static handle load(std::string& filename);
    static void unload(handle h);
};
};
};

#endif
