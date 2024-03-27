// Copyright (c) 2019 Hanhui LI
#include "doraemon/atomic/ref_counted_object.h"

namespace doraemon {

RefCountedObject::RefCountedObject(): counter_(1)
{
}

RefCountedObject::~RefCountedObject()
{
}

};  // namespace doraemon
