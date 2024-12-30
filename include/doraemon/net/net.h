// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_NET_NET_H_
#define INCLUDE_DORAEMON_NET_NET_H_

#include "doraemon/export/export_def.h"

namespace doraemon {

    enum class D_CLASS_EXPORT ByteOrder
    {
        BigEndian = 1,
        LittleEndian = 2,
        NetworkByteOrder = BigEndian
    };

    class D_CLASS_EXPORT NetUtil
    {
    public:
        static bool is_big_endian();
        static bool is_little_endian();
        static bool is_network_byteorder();
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_NET_NET_H_
