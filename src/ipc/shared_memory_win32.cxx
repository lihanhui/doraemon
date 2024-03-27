#include "doraemon/ipc/shared_memory_win32.h"

namespace doraemon {

SharedMemoryImpl::SharedMemoryImpl(const std::string& name, std::size_t size, SharedMemory::AccessMode mode, const void*, bool):
    _name(name),
    _memHandle(INVALID_HANDLE_VALUE),
    _fileHandle(INVALID_HANDLE_VALUE),
    _size(static_cast<DWORD>(size)),
    _mode(PAGE_READONLY),
    _address(0)
{
    if (mode == SharedMemory::AM_WRITE)
        _mode = PAGE_READWRITE;

    std::wstring utf16name;
    UnicodeConverter::toUTF16(_name, utf16name);
    _memHandle = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, _mode, 0, _size, utf16name.c_str());

    if (!_memHandle)
    {
        DWORD dwRetVal = GetLastError();
#if defined (_WIN32_WCE)
        throw RuntimeError(format("Cannot create shared memory object %s [Error %d: %s]", _name, static_cast<int>(dwRetVal), Error::getMessage(dwRetVal)));
#else
        if (_mode != PAGE_READONLY || dwRetVal != 5)
            throw RuntimeError(format("Cannot create shared memory object %s [Error %d: %s]", _name, static_cast<int>(dwRetVal), Error::getMessage(dwRetVal)));

        _memHandle = OpenFileMappingW(PAGE_READONLY, FALSE, utf16name.c_str());
        if (!_memHandle)
        {
            dwRetVal = GetLastError();
            throw RuntimeError(format("Cannot open shared memory object %s [Error %d: %s]", _name, static_cast<int>(dwRetVal), Error::getMessage(dwRetVal)));
        }
#endif
    }
    map();
}

SharedMemoryImpl::~SharedMemoryImpl()
{
    unmap();
    close();
}

void SharedMemoryImpl::map()
{
    DWORD access = FILE_MAP_READ;
    if (_mode == PAGE_READWRITE)
        access = FILE_MAP_WRITE;
    LPVOID addr = MapViewOfFile(_memHandle, access, 0, 0, _size);
    if (!addr)
    {
        DWORD dwRetVal = GetLastError();
        throw RuntimeError(format("Cannot map shared memory object %s [Error %d: %s]", _name, (int)dwRetVal, Error::getMessage(dwRetVal)));
    }

    _address = static_cast<char*>(addr);
}

void SharedMemoryImpl::unmap()
{
    if (_address)
    {
        UnmapViewOfFile(_address);
        _address = 0;
        return;
    }
}

void SharedMemoryImpl::close()
{
    if (_memHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(_memHandle);
        _memHandle = INVALID_HANDLE_VALUE;
    }

    if (_fileHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(_fileHandle);
        _fileHandle = INVALID_HANDLE_VALUE;
    }
}

}  // namespace
