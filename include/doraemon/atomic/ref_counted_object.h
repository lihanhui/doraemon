#ifndef DORAEMON_IPC_REFCOUNTEDOBJECT_H
#define DORAEMON_IPC_REFCOUNTEDOBJECT_H

#include <stdexcept>

#include "doraemon/atomic/atomic_counter.h"

namespace doraemon {


class RefCountedObject
	/// A base class for objects that employ
	/// reference counting based garbage collection.
	///
	/// Reference-counted objects inhibit construction
	/// by copying and assignment.
{
public:
	RefCountedObject();
		/// Creates the RefCountedObject.
		/// The initial reference count is one.

	void duplicate() const;
		/// Increments the object's reference count.

	void release() const noexcept;
		/// Decrements the object's reference count
		/// and deletes the object if the count
		/// reaches zero.

	int referenceCount() const;
		/// Returns the reference count.

protected:
	virtual ~RefCountedObject();
		/// Destroys the RefCountedObject.

private:
	RefCountedObject(const RefCountedObject&);
	RefCountedObject& operator = (const RefCountedObject&);

	mutable AtomicCounter _counter;
};


//
// inlines
//
inline int RefCountedObject::referenceCount() const
{
	return _counter.value();
}


inline void RefCountedObject::duplicate() const
{
	++_counter;
}


inline void RefCountedObject::release() const noexcept
{
	try
	{
		if (--_counter == 0) delete this;
	}
	catch (...)
	{
		throw std::runtime_error("");
	}
}


} // namespace doraemon


#endif
