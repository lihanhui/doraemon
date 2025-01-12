// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_EXPORT_EXPORT_DEF_H_
#define INCLUDE_DORAEMON_EXPORT_EXPORT_DEF_H_

#include <cstdint>

#ifdef _WIN32
#define SHARED_EXPORT __declspec(dllexport)
#define CALLING_CONVENTION __cdecl
#else
#define SHARED_EXPORT __attribute__ ((visibility ("default")))
#define CALLING_CONVENTION
#endif

#ifdef _WIN32
#define D_CLASS_EXPORT __declspec(dllexport)
#define D_CLASS_IMPORT __declspec(dllimport)
#define D_FUNC_EXPORT __declspec(dllexport)
#define D_FUNC_IMPORT __declspec(dllimport)
#else
#define D_CLASS_EXPORT __attribute__((visibility("default")))
#define D_CLASS_IMPORT __attribute__((visibility("default")))
#define D_CLASS_HIDDEN __attribute__((visibility("hidden")))
#endif

#endif  // INCLUDE_DORAEMON_EXPORT_EXPORT_DEF_H_
