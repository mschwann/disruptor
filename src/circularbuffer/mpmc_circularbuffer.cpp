#include <thread>
#include "base.h"
namespace MultiProducer::MultiConsumer
{
    /*
    
    Multiple commit heads - linked list.
    Commit head, once "reached" by read could just go into a common space to be reused.

    How about a Linked list of memory, where one could return it to the pool ?
    */
    bool CircularBuffer::pushByteImpl(uint8_t& item)
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
        
        //this synchronises :(
        /*size_t tmp;
        do{
            tmp = oldWrite;
        }
        while(!write_.commit.compare_exchange_weak(tmp, newWrite, std::memory_order_acquire, std::memory_order_release));
        */

        while(write_.commit.load(std::memory_order_acquire) != oldWrite)
            std::this_thread::yield();
        write_.commit.store(newWrite, std::memory_order_release);
        return true;
    }

    bool CircularBuffer::popByteImpl(uint8_t& item)
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
        
        /*size_t tmp;
        do{
            tmp = oldRead;
        }
        while(!write_.commit.compare_exchange_weak(tmp, newRead, std::memory_order_acquire, std::memory_order_release));
        */


        return true;
    }
}