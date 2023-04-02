#ifndef DORAEMON_NET_NET_H
#define DORAEMON_NET_NET_H

enum class ByteOrder{
    BigEndian = 1,
    LittleEndian = 2,
    NetworkByteOrder = BigEndian
};

class NetUtil
{
private:
	static int VALUE = 0x11223344;

public:
    static bool is_big_endian() { return *(unsigned char*)(&VALUE) == (unsigned char)(0x11); }
    static bool is_little_endian() { return *(unsigned char*)(&VALUE) == (unsigned char)(0x44); }
    static bool is_network_byteorder() {return is_big_endian();}
	
};

#endif