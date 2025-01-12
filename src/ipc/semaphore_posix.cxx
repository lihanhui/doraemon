#include "doraemon/ipc/semaphore.h"

/*#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>//*/

#ifndef _WIN32

#include <semaphore.h>

#include "doraemon/runtime/runtime_error.h"

namespace doraemon {

 
static Handle NON_HANDLE = 0;

Semaphore::Semaphore(const std::string &name, int init_value):
name_(name),
handle_(NON_HANDLE),
value_(init_value)
{
}
Semaphore::~Semaphore()
{
    
}

bool Semaphore::open()
{
    if(handle_ == NON_HANDLE) return false;

    sem_t *sem;
    sem = sem_open(name_.data(), O_CREAT, 0644, value_);
    if (sem != SEM_FAILED)
    {
        handle_ = (Handle)sem;
        return true;
    }else{
        return false;
    }
}

bool Semaphore::acquire()
{
    if (handle_ == NON_HANDLE)
        return false;

    int err = sem_wait((sem_t*)handle_);
    return err == 0;
}

void Semaphore::release()
{
    if (handle_ == NON_HANDLE)
        return;

    sem_post((sem_t*)handle_);
}

void Semaphore::unlink()
{
    if (handle_ == NON_HANDLE)
        return;

    sem_unlink(name_.data());
}

void Semaphore::close()
{
    if (handle_ == NON_HANDLE)
        return;

    sem_close((sem_t*)handle_);
}


}  // namespace doraemon

#endif
