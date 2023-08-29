#include <thread>
#include "multiconsumermultiproducer.h"
namespace CircularBuffer
{
    bool MultiConsumerMultiProducer::pushByteImpl(uint8_t& item)
    {
        size_t oldWrite = write_.reserve.load(std::memory_order_acquire);
        size_t newWrite;
        //reserver
        do{
            newWrite = (oldWrite + 1) % size_;
            if(newWrite == read_.commit.load(std::memory_order_acquire))
            {
                //No space - fail.
                return false;
            }
        }
        while(!write_.reserve.compare_exchange_weak(oldWrite, newWrite, std::memory_order_acquire, std::memory_order_release));
        mem_[oldWrite] = std::move(item);

        while(write_.commit.load(std::memory_order_acquire) != oldWrite)
            std::this_thread::yield();
        write_.commit.store(newWrite, std::memory_order_release);
        return true;
    }

    bool MultiConsumerMultiProducer::popByteImpl(uint8_t& item)
    {
        size_t oldRead = read_.reserve.load(std::memory_order_acquire);
        size_t newRead;
        do{
            if(oldRead == write_.commit.load(std::memory_order_acquire))
            {
                //Nothing to read.
                return false;
            }
            newRead = (oldRead + 1) % size_;
        }
        while(!read_.reserve.compare_exchange_weak(oldRead, newRead, std::memory_order_acquire, std::memory_order_release));
        item = std::move(mem_[oldRead]);

        while(read_.commit.load(std::memory_order_acquire) != oldRead)
            std::this_thread::yield();
        read_.commit.store(newRead, std::memory_order_release);

        return true;
    }
}