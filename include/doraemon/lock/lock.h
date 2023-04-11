#ifndef DORAEMON_LOCK_LOCK_H 
#define DORAEMON_LOCK_LOCK_H 

namespace doraemon{

class Lockable{

public:
    virtual void lock() = 0;
    virtual void unlock()= 0;
};

};

#endif
