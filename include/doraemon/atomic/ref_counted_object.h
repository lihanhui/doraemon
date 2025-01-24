// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_ATOMIC_REF_COUNTED_OBJECT_H_
#define INCLUDE_DORAEMON_ATOMIC_REF_COUNTED_OBJECT_H_

#include <stdexcept>

#include "doraemon/export/export_def.h"
#include "doraemon/atomic/atomic_counter.h"

    namespace doraemon {

class D_CLASS_EXPORT RefCountedObject
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

    int reference_count() const;
        /// Returns the reference count.

 protected:
    virtual ~RefCountedObject();
        /// Destroys the RefCountedObject.

 private:
    RefCountedObject(const RefCountedObject&);
    RefCountedObject& operator=(const RefCountedObject&);

    mutable AtomicCounter counter_;
};


//
// inlines
//
inline int RefCountedObject::reference_count() const
{
    return counter_.value();
}

inline void RefCountedObject::duplicate() const
{
    ++counter_;
}

inline void RefCountedObject::release() const noexcept
{
    try
    {
        if (--counter_ == 0)
            delete this;
    }
    catch (...)
    {
        //throw std::runtime_error("");
    }
}

}  // namespace doraemon

#endif  // INCLUDE_DORAEMON_ATOMIC_REF_COUNTED_OBJECT_H_
