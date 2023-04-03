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
	static const int VALUE;

public:
    static bool is_big_endian() ;
    static bool is_little_endian() ;
    static bool is_network_byteorder() ;
	
};

#endif