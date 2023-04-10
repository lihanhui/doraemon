#ifndef DORAEMON_IPC_SHAREDMEMORY_IMPL_H
#define DORAEMON_IPC_SHAREDMEMORY_IMPL_H

#include "doraemon/ipc/shared_memory.h"
#include "doraemon/atomic/ref_counted_object.h"

namespace doraemon {

class SharedMemoryImpl: public RefCountedObject
	/// A dummy implementation of shared memory, for systems
	/// that do not have shared memory support.
{
public:
	SharedMemoryImpl(const std::string& id, std::size_t size, SharedMemory::AccessMode mode, const void* addr, bool server);
		/// Creates or connects to a shared memory object with the given name.
		///
		/// For maximum portability, name should be a valid Unix filename and not
		/// contain any slashes or backslashes.
		///
		/// An address hint can be passed to the system, specifying the desired
		/// start address of the shared memory area. Whether the hint
		/// is actually honored is, however, up to the system. Windows platform
		/// will generally ignore the hint.

	char* begin() const;
		/// Returns the start address of the shared memory segment.

	char* end() const;
		/// Returns the one-past-end end address of the shared memory segment.

protected:
	~SharedMemoryImpl();
		/// Destroys the SharedMemoryImpl.

private:
	SharedMemoryImpl();
	SharedMemoryImpl(const SharedMemoryImpl&);
	SharedMemoryImpl& operator = (const SharedMemoryImpl&);
};


//
// inlines
//
inline char* SharedMemoryImpl::begin() const
{
	return 0;
}


inline char* SharedMemoryImpl::end() const
{
	return 0;
}


} // 


#endif 
