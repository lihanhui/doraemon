#include "doraemon/ipc/shared_memory_posix.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "doraemon/runtime/runtime_error.h"

namespace doraemon {

SharedMemoryImpl::SharedMemoryImpl(const std::string& name, std::size_t size, SharedMemory::AccessMode mode, const void* addrHint, bool server):
    _size(size),
    _fd(-1),
    _address(0),
    _access(mode),
    _name("/"),
    _fileMapped(false),
    _server(server)
{
//#if _OS == _OS_HPUX
//	_name.append("tmp/");
//#endif

    _name.append(name);

    int flags = _server ? O_CREAT : 0;
    if (_access == SharedMemory::AM_WRITE)
        flags |= O_RDWR;
    else
        flags |= O_RDONLY;

    // open the shared memory segment
    _fd = ::shm_open(_name.c_str(), flags, S_IRUSR | S_IWUSR);
    if (_fd == -1)
        throw RuntimeError("Cannot create shared memory object" + _name);

    // now set the correct size for the segment
    if (_server && -1 == ::ftruncate(_fd, size))
    {
        ::close(_fd);
        _fd = -1;
        ::shm_unlink(_name.c_str());
        throw RuntimeError("Cannot resize shared memory object" + _name);
    }
    map(addrHint);
}

SharedMemoryImpl::~SharedMemoryImpl()
{
    unmap();
    close();
}

void SharedMemoryImpl::map(const void* addrHint)
{
    int access = PROT_READ;
    if (_access == SharedMemory::AM_WRITE)
        access |= PROT_WRITE;

    void* addr = ::mmap(const_cast<void*>(addrHint), _size, access, MAP_SHARED, _fd, 0);
    if (addr == MAP_FAILED)
        throw RuntimeError("Cannot map file into shared memory" + _name);

    _address = static_cast<char*>(addr);
}

void SharedMemoryImpl::unmap()
{
    if (_address)
    {
        ::munmap(_address, _size);
    }
}

void SharedMemoryImpl::close()
{
    if (_fd != -1)
    {
        ::close(_fd);
        _fd = -1;
    }
    if (!_fileMapped && _server)
    {
        ::shm_unlink(_name.c_str());
    }
}

}  // namespace doraemon
