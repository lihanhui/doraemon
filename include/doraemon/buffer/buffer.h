// Copyright (c) 2019 Hanhui LI

#ifndef INCLUDE_DORAEMON_BUFFER_BUFFER_H_
#define INCLUDE_DORAEMON_BUFFER_BUFFER_H_

#include <memory>
#include <cstring>
#include <string>

#include "doraemon/export/export_def.h"

    namespace doraemon
{
    struct D_CLASS_EXPORT Buffer
    {
    private:
        int mark_ = -1;
        int position_ = 0;
        int limit_;
        int capacity_;
        unsigned char *data_;

    private:
        Buffer()
        {
            this->data_ = nullptr;
            this->limit_ = 0;
            this->capacity_ = 0;
        }

    public:
        explicit Buffer(int capacity) : Buffer(capacity, capacity)
        {
        }

        Buffer(int limit, int capacity)
        {
            this->limit_ = limit;
            this->capacity_ = capacity;
            this->data_ = new unsigned char[limit];
	    std::memset(this->data_, 0, limit);
        }

        ~Buffer()
        {
            delete[] this->data_;
            this->data_ = nullptr;
            this->limit_ = 0;
            this->capacity_ = 0;
        }

        unsigned char *get_data()
        {
            return data_;
        }

        std::string get_string(int length);
        void get(unsigned char *dst, int length);
        unsigned char get(int index);
        unsigned char get();

        void put(unsigned char *src, int length);
        void put(int index, unsigned char byte);
        void put(unsigned char byte);
        void put(std::shared_ptr<Buffer> buffer);

        int capacity();
        int position();
        Buffer *position(int new_position);
        int limit();
        Buffer *limit(int new_limit);
        Buffer *mark();
        Buffer *reset();
        Buffer *clear();
        Buffer *flip();
        Buffer *rewind();
        int remaining();
        bool has_remaining();
        int next_get_index();
        int next_get_index(int nb);
        int next_put_index();
        int next_put_index(int nb);
        int check_index(int i);
        int check_index(int i, int nb);
        int mark_value();
        void truncate();
        void discard_mark();
    };

    struct TimedBuffer : Buffer
    {
    private:
        int64_t timestamp_;

    public:
        int64_t get_timestamp() { return timestamp_; }
        void set_timestamp(int64_t timestamp) { this->timestamp_ = timestamp; }

    public:
        explicit TimedBuffer(int capacity) : Buffer(capacity)
        {
        }

        TimedBuffer(int limit, int capacity) : Buffer(limit, capacity)
        {
        }
    };
}; // namespace doraemon

#endif  // INCLUDE_DORAEMON_BUFFER_BUFFER_H_
