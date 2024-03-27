// Copyright (c) 2019 Hanhui LI
#include "doraemon/net/net.h"

namespace doraemon {

static int VALUE = 0x11223344;

bool NetUtil::is_big_endian() {
    return *(unsigned char*)(&VALUE) == (unsigned char)(0x11); }

bool NetUtil::is_little_endian() {
    return *(unsigned char*)(&VALUE) == (unsigned char)(0x44); }

bool NetUtil::is_network_byteorder() { return is_big_endian(); }

};  // namespace doraemon
