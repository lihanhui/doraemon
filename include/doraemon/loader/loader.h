// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_LOADER_LOADER_H_
#define INCLUDE_DORAEMON_LOADER_LOADER_H_

#include <string>

namespace doraemon {

using Handle = void*;

class Loader {
 public:
    static Handle load(const std::string& filename);
    static void unload(Handle h);
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_LOADER_LOADER_H_
