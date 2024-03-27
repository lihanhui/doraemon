// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_EXPORT_EXPORT_DEF_H_
#define INCLUDE_DORAEMON_EXPORT_EXPORT_DEF_H_

#ifdef _WIN32
#define SHARED_EXPORT __declspec(dllexport)
#define CALLING_CONVENTION __cdecl
#else
#define SHARED_EXPORT __attribute__ ((visibility ("default")))
#define CALLING_CONVENTION
#endif

namespace doraemon{
    typedef uint64_t Handle;
};

#endif  // INCLUDE_DORAEMON_EXPORT_EXPORT_DEF_H_
