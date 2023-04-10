#include "doraemon/ipc/shared_memory_dummy.h"

namespace doraemon {

SharedMemoryImpl::SharedMemoryImpl(const std::string&, std::size_t, SharedMemory::AccessMode, const void*, bool)
{
}

SharedMemoryImpl::~SharedMemoryImpl()
{
}

} // namespace 
