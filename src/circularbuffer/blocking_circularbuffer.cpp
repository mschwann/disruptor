#include "circularbuffer.h"

namespace Blocking
{

    bool CircularBuffer::pushByteImpl(uint8_t& item)
    {
        std::unique_lock<std::mutex> lock(m_);
        if (isFull()) {
            return false;
        }

        mem_[write_] = std::move(item);
        write_ = (write_ + 1) % size_;
        return true;
    }

    bool CircularBuffer::popByteImpl(uint8_t& item)
    {
        std::unique_lock<std::mutex> lock(m_);
        if (isEmpty()) {
            return false;
        }

        item = mem_[read_];
        read_ = (read_ + 1) % size_;
        return true;
    }
}