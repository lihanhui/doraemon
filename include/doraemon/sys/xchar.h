// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_SYS_XCHAR_H_
#define INCLUDE_DORAEMON_SYS_XCHAR_H_

#include <string>

#include "doraemon/export/export_def.h"

#ifdef _WIN32

using nchar = wchar_t;
using nstring = std::wstring;

#else

using nchar = char;
using nstring = std::string;

#endif

#endif  // INCLUDE_DORAEMON_SYS_XCHAR_H_
