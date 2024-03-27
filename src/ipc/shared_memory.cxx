//
// SharedMemory.cpp
//
// Library: Foundation
// Package: Processes
// Module:  SharedMemory
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "doraemon/ipc/shared_memory.h"

#if defined(DORAMEMON_NO_SHAREDMEMORY)
#include "shared_memory_dummy.cxx"
#elif defined(__OS_FAMILY_WINDOWS__)
#include "shared_memory_win32.cxx"
#elif defined(__OS_FAMILY_UNIX__)
#include "shared_memory_posix.cxx"
#else
#include "shared_memory_dummy.cxx"
#endif

namespace doraemon {


SharedMemory::SharedMemory():
    _pImpl(0)
{
}

SharedMemory::SharedMemory(const std::string& name, std::size_t size, AccessMode mode, const void* addrHint, bool server):
    _pImpl(new SharedMemoryImpl(name, size, mode, addrHint, server))
{
}

SharedMemory::SharedMemory(const SharedMemory& other):
    _pImpl(other._pImpl)
{
    if (_pImpl)
        _pImpl->duplicate();
}

SharedMemory::~SharedMemory()
{
    if (_pImpl)
        _pImpl->release();
}

SharedMemory& SharedMemory::operator = (const SharedMemory& other)
{
    SharedMemory tmp(other);
    swap(tmp);
    return *this;
}

char* SharedMemory::begin() const
{
    if (_pImpl)
        return _pImpl->begin();
    else
        return 0;
}

char* SharedMemory::end() const
{
    if (_pImpl)
        return _pImpl->end();
    else
        return 0;
}

}  // namespace doraemon
