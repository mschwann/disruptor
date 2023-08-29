#pragma once
#include <cstdint>
#include <vector>
#include <atomic>
#include <mutex>

template<class Impl> class CircularBufferBase
{
    public:
        CircularBufferBase() = default;
        virtual ~CircularBufferBase(){}

        bool pushByte(uint8_t& item)
        {
            return static_cast<Impl*>(this)->pushByteImpl(item);
        }
        bool popByte(uint8_t& item)
        {
            return static_cast<Impl*>(this)->popByteImpl(item);
        }

        virtual bool pushByteImpl(uint8_t& item) = 0;
        virtual bool popByteImpl(uint8_t& item) = 0;

};