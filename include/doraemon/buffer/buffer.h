#ifndef DORAEMON_BUFFER_BUFFER_H
#define DORAEMON_BUFFER_BUFFER_H

namespace doraemon::buffer{
struct Buffer
{
    unsigned int len;
    unsigned char *data;
};


struct TimedBuffer
{
    long timestamp;	
    unsigned int len;
    unsigned char *data;
};
};

#endif
