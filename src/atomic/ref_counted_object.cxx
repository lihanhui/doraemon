#include "doraemon/atomic/ref_counted_object.h"

namespace doraemon {

RefCountedObject::RefCountedObject(): _counter(1)
{
}


RefCountedObject::~RefCountedObject()
{
}


}