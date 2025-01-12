#include "doraemon/ipc/semaphore.h"

#ifdef _WIN32

#include <windows.h>

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
    if (handle_ == NON_HANDLE)
        return false;

    HANDLE h = CreateSemaphore(
        NULL,   // default security attributes
        value_, // initial count
        value_, // maximum count
        name_.data());  // unnamed semaphore

    if (h != NULL)
    {
        handle_ = (Handle)sem;
        return true;
    }
    else
    {
        return false;
    }
}

bool Semaphore::acquire()
{
    if (handle_ == NON_HANDLE)
        return false;

    DWORD dwWaitResult = dwWaitResult = WaitForSingleObject(
        (HANDLE)handle_, // handle to semaphore
        0L);

    return dwWaitResult == WAIT_OBJECT_0;
}

void Semaphore::release()
{
    if (handle_ == NON_HANDLE)
        return;

    return ReleaseSemaphore(
        (HANDLE)handle_, // handle to semaphore
        1,               // increase count by one
        NULL);
}

void Semaphore::unlink()
{

}

void Semaphore::close()
{
    if (handle_ == NON_HANDLE)
        return;

    CloseHandle((HANDLE)handle_);
}

}  // namespace

#endif
