#pragma once
#include "base.h"

namespace CircularBuffer
{
class SingleConsumerSingleProducer : public ::CircularBufferBase<SingleConsumerSingleProducer>
{
    public:
        SingleConsumerSingleProducer(size_t n)
        : ::CircularBufferBase<SingleConsumerSingleProducer>()
        , mem_(n)
        , read_(0)
        , write_(0)
        , size_(n)
        {}
        using ::CircularBufferBase<SingleConsumerSingleProducer>::popByte;
        using ::CircularBufferBase<SingleConsumerSingleProducer>::pushByte;
        virtual bool pushByteImpl(uint8_t& item) override;
        virtual bool popByteImpl(uint8_t& item) override;
    private:
        std::vector<size_t> mem_;
        std::atomic<size_t> read_;
        std::atomic<size_t> write_;
        size_t size_;
};
}