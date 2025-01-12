#ifndef INCLUDE_DORAEMON_IPC_SHARED_MEMORY_WIN32_H_
#define INCLUDE_DORAEMON_IPC_SHARED_MEMORY_WIN32_H_

#include <string>

#include "doraemon/export/export_def.h"
#include "doraemon/ipc/shared_memory.h"
#include "doraemon/atomic/ref_counted_object.h"

namespace doraemon {

class D_CLASS_EXPORT SharedMemoryImpl : public RefCountedObject
    // Shared memory implementation for Windows platforms.
{
 public:
    SharedMemoryImpl(const std::string& name, std::size_t size, SharedMemory::AccessMode mode, const void* addrHint, bool server);
        // Creates or connects to a shared memory object with the given name.
        //
        // For maximum portability, name should be a valid Unix filename and not
        // contain any slashes or backslashes.
        //
        // An address hint can be passed to the system, specifying the desired
        // start address of the shared memory area. Whether the hint
        // is actually honored is, however, up to the system. Windows platform
        // will generally ignore the hint.

    char* begin() const;
        // Returns the begin address of the SharedMemory segment. Will be null for illegal segments.

    char* end() const;
        // Points past the last byte of the end address of the SharedMemory segment. Will be null for illegal segments.

 protected:
    void map();
        // Maps the shared memory object.

    void unmap();
        // Unmaps the shared memory object.

    void close();
        // Releases the handle for the shared memory segment.

    ~SharedMemoryImpl();
        // Destroys the SharedMemoryImpl.

 private:
    SharedMemoryImpl();
    SharedMemoryImpl(const SharedMemoryImpl&);
    SharedMemoryImpl& operator = (const SharedMemoryImpl&);

    std::string _name;
    HANDLE  _memHandle;
    HANDLE  _fileHandle;
    DWORD   _size;
    DWORD   _mode;
    char*   _address;
};

// inlines
inline char* SharedMemoryImpl::begin() const
{
    return _address;
}

inline char* SharedMemoryImpl::end() const
{
    return _address + _size;
}

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_IPC_SHARED_MEMORY_WIN32_H_
