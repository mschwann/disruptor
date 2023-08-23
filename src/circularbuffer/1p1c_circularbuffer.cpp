#include "singleconsumersingleproducer.h"
namespace CircularBuffer
{

    bool SingleConsumerSingleProducer::pushByteImpl(uint8_t& item)
    {
        auto oldWrite = write_.load(std::memory_order_acquire);
        auto newWrite = (oldWrite + 1) % size_;
        if(newWrite == read_.load(std::memory_order_acquire))
        {
            //No space - fail.
            return false;
        }
        mem_[oldWrite] = std::move(item);
        write_.store(newWrite, std::memory_order_release);
        return true;
    }

    bool SingleConsumerSingleProducer::popByteImpl(uint8_t& item)
    {
        size_t readIdx = read_.load(std::memory_order_acquire);
        if(readIdx == write_.load(std::memory_order_acquire))
        {
            //Nothing to read.
            return false;
        }
        item = std::move(mem_[readIdx]);
        read_.store((readIdx + 1) % size_, std::memory_order_release);
        return true;
    }
}