#ifndef INCLUDE_DORAEMON_CORE_TYPE_DEF_H_
#define INCLUDE_DORAEMON_CORE_TYPE_DEF_H_

namespace doraemon {

typedef uint64_t Handle;

#ifdef _WIN32

using nchar = wchar_t;
using nstring = std::wstring;

#else

using nchar = char;
using nstring = std::string;

#endif

struct Tl {
    uint32_t type_;
    uint32_t len_;
    Tl(uint32_t type = 0, uint32_t len = 0) : type_(type), len_(len)
    {
    }
};

};

#endif