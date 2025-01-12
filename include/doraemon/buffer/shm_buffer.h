#ifndef INCLUDE_DORAEMON_BUFFER_SHM_BUFFER_H_
#define INCLUDE_DORAEMON_BUFFER_SHM_BUFFER_H_

#include <string>

#include "doraemon/export/export_def.h"
#include "doraemon/buffer/buffer.h"
#include "doraemon/ipc/semaphore.h"
#include "doraemon/ipc/shared_memory.h"

namespace doraemon
{

struct D_CLASS_EXPORT ShmBuffer {
public:
    ShmBuffer(const std::string &sem_name, const std::string &shm_name, uint32_t size);
    ~ShmBuffer();

private : 
    ShmBuffer(){};

public :
    bool write(uint32_t type, const unsigned char *data, uint32_t len);
    bool write(uint32_t type, std::shared_ptr<Buffer> &data);
    std::shared_ptr<Buffer> update();   // data once success, otherwise with nullptr returned
    std::shared_ptr<Buffer> &get(); // current

    //inline std::string &get_name() { return name_; }
    inline uint32_t get_size() { return size_; }

protected:
    inline void set_address(char *address) { this->address_ = address ;}
    inline char *get_address() { return this->address_; }

private:
    std::string sem_name_; //
    std::string shm_name_; //
    uint32_t size_ = 0;

    Semaphore *sem_ = nullptr;
    SharedMemory *shm_ = nullptr;
    
    char *address_ = nullptr;
    uint64_t seq_ = -1;
    std::shared_ptr<Buffer> data_;
};

};

#endif