// Copyright (c) 2019 Hanhui LI
#include "doraemon/buffer/buffer.h"

#include <string>

namespace doraemon{
    std::string Buffer::get_string(int length) {
        if (length > remaining())
            return "";
        return std::string(reinterpret_cast<char *>(this->data_)
          + next_get_index(length), length);
    }

    void Buffer::get(unsigned char* dst, int length) {
        if (length > remaining())
            return;
        std::memcpy(dst, this->data_+ position(), length);
        position(position() + length);
        return;
    }

    unsigned char Buffer::get(int index) {
        int i = check_index(index);
        if (i < 0) {
            return (unsigned char)0x00;
        }
        return *(this->data_+ i);
    }

    unsigned char Buffer::get() {
        int i = next_get_index();
        if (i < 0) {
            return (unsigned char)0x00;
        }
        return *(this->data_ + i);
    }

    void Buffer::put(unsigned char* src, int length) {
        if (length > remaining())
            return;
        std::memcpy(this->data_ + position(), src, length);
        position(position() + length);
        return;
    }

    void Buffer::put(int index, unsigned char byte) {
        int i = check_index(index);
        if (i < 0) {
            return;
        }
        *(this->data_ + i) = byte;
    }

    void Buffer::put(unsigned char byte) {
        int i = next_get_index();
        if (i < 0) {
            return;
        }
        *(this->data_ + i) = byte;
    }

    void Buffer::put(std::shared_ptr<Buffer> buffer) {
        if (this != buffer.get()) {
            int n = buffer->remaining();
            if (n > remaining())
                return;
            std::memcpy(buffer->data_ + buffer->position(),
                data_ + position(), n);
            buffer->position(buffer->position() + n);
            position(position() + n);
        }
    }

    int Buffer::capacity() {
        return capacity_;
    }

    int Buffer::position() {
        return position_;
    }

    struct Buffer* Buffer::position(int new_position) {
        if ((new_position > limit_) || (new_position < 0))
            return nullptr;
        position_ = new_position;
        if (mark_ > position_) mark_ = -1;
        return this;
    }

    int Buffer::limit() {
        return limit_;
    }

    struct Buffer* Buffer::limit(int new_limit) {
        if ((new_limit > capacity_) || (new_limit < 0))
            return nullptr;
        limit_ = new_limit;
        if (position_ > limit_) position_ = limit_;
        if (mark_ > limit_) mark_ = -1;
        return this;
    }

    struct Buffer* Buffer::mark() {
        mark_ = position_;
        return this;
    }

    struct Buffer* Buffer::reset() {
        int m = mark_;
        if (m < 0)
            return nullptr;
        position_ = m;
        return this;
    }

    struct Buffer* Buffer::clear() {
        position_ = 0;
        limit_ = capacity_;
        mark_ = -1;
        return this;
    }

    struct Buffer* Buffer::flip() {
        limit_ = position_;
        position_ = 0;
        mark_ = -1;
        return this;
    }

    struct Buffer* Buffer::rewind() {
        position_ = 0;
        mark_ = -1;
        return this;
    }

    int Buffer::remaining() {
        return limit_ - position_;
    }

    bool Buffer::has_remaining() {
        return position_ < limit_;
    }

    int Buffer::next_get_index() {
        if (position_ >= limit_)
            return -1;
        return position_++;
    }

    int Buffer::next_get_index(int nb) {
        if (limit_ - position_ < nb)
            return -1;
        int p = position_;
        position_ += nb;
        return p;
    }

    int Buffer::next_put_index() {
        if (position_ >= limit_)
            return -1;
        return position_++;
    }

    int Buffer::next_put_index(int nb) {
        if (limit_ - position_ < nb)
            return -1;
        int p = position_;
        position_ += nb;
        return p;
    }

    int Buffer::check_index(int i) {
        if ((i < 0) || (i >= limit_))
            return -1;
        return i;
    }

    int Buffer::check_index(int i, int nb) {
        if ((i < 0) || (nb > limit_ - i))
            return -1;
        return i;
    }

    int Buffer::mark_value() {
        return mark_;
    }

    void Buffer::truncate() {
        mark_ = -1;
        position_ = 0;
        limit_ = 0;
        capacity_ = 0;
    }

    void Buffer::discard_mark() {
        mark_ = -1;
    }
};  // namespace doraemon
