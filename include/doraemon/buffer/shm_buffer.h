#ifndef INCLUDE_DORAEMON_BUFFER_SHM_BUFFER_H_
#define INCLUDE_DORAEMON_BUFFER_SHM_BUFFER_H_

#include <string>

#include "doraemon/export/export_def.h"
#include "doraemon/buffer/buffer.h"

namespace doraemon
{

struct D_CLASS_EXPORT ShmBuffer {
public:
    ShmBuffer(std::string name, uint32_t size);
    ~ShmBuffer();

private : 
    ShmBuffer();

public : 
    void write(const char *data, int len);
    std::shared_ptr<Buffer> update();   // data once success, otherwise with nullptr returned
    
    std::shared_ptr<Buffer> get(); // current
    inline std::string &get_name() { return name_; }
    inline uint32_t get_size() { return size_; }

protected:
    inline void set_address(char *address) { this->address_ = address ;}
    inline char *get_address() { return this->address_; }

private:
    std::string name_; //
    uint64_t seq_;
    std::shared_ptr<Buffer> data_;

    char *address_;
    uint32_t size_;
};

};

#endif