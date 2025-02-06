#include "doraemon/buffer/shm_buffer.h"

#include "doraemon/ipc/shared_memory.h"

namespace doraemon{

ShmBuffer::ShmBuffer(const std::string &sem_name, const std::string &shm_name, uint32_t size):
sem_name_(sem_name),
shm_name_(shm_name),
size_(size),
sem_(new Semaphore(sem_name)),
shm_(new SharedMemory(shm_name_, size_, SharedMemory::AccessMode::AM_WRITE))
{
    address_ = shm_->begin();
}

ShmBuffer::~ShmBuffer(){
    if (sem_)
    {
        sem_->unlink();
        delete sem_;
        sem_ = nullptr;
    }
    if(shm_){
       delete shm_;
       shm_ = nullptr;
    }
}

bool ShmBuffer::write(uint32_t type, const unsigned char *data, uint32_t len){
    if(!sem_->acquire()){
        return false;
    }
    uint32_t offset = 0;
    *(uint64_t *)this->address_ = ++seq_;
    
    Tl tl(type, len);
    offset += sizeof(seq_);
    std::memcpy(this->address_ + offset, &tl, std::min(len, size_ - offset));

    offset += sizeof(tl);
    std::memcpy(this->address_ + offset, data, std::min(len, size_ - offset));
    sem_->release();

    return true;
}

bool ShmBuffer::write(uint32_t type, std::shared_ptr<Buffer> &data){
    return this->write(type, data->get_data(), data->limit());
}

std::shared_ptr<Buffer> ShmBuffer::update()
{ // data once success, otherwise with nullptr returned
    if (!sem_->acquire())
    {
        return nullptr;
    }
    if(*(uint64_t *)this->address_ == seq_){
        sem_->release();
        return nullptr;
    }
    seq_ = *(uint64_t *)this->address_;

    uint32_t offset = sizeof(seq_);
    Tl *tl = (Tl*)(this->address_ + offset);
    uint32_t len = tl->len_;

    offset += sizeof(*tl);
    if (offset+len > size_)
    {
        sem_->release();
        return nullptr;
    }

    std::shared_ptr<Buffer> b = std::make_shared<Buffer>(sizeof(Tl)+len);
    b->put((unsigned char *)this->address_ + offset, sizeof(Tl) + len);
    data_ = b;
    return data_;
}

std::shared_ptr<Buffer> &ShmBuffer::get(){    // current
    return data_;
}

};
