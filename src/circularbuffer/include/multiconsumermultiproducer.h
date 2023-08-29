#pragma once
#include "base.h"

namespace CircularBuffer
{
    struct ReserveCommitPair
    {
        ReserveCommitPair(size_t r, size_t c, size_t n)
        :reserve(r)
        ,commit(c)
        {}
        
        std::atomic<size_t> reserve;
        std::atomic<size_t> commit;
    };
    class MultiConsumerMultiProducer : public ::CircularBufferBase<MultiConsumerMultiProducer>
    {
        public:
        MultiConsumerMultiProducer(size_t n)
        : ::CircularBufferBase<MultiConsumerMultiProducer>()
        , mem_(n)
        , read_(0, 0, n)
        , write_(0, 0, n)
        , size_(n)
        {}
        using ::CircularBufferBase<MultiConsumerMultiProducer>::popByte;
        using ::CircularBufferBase<MultiConsumerMultiProducer>::pushByte;
        
        virtual bool pushByteImpl(uint8_t& item) override;
        virtual bool popByteImpl(uint8_t& item) override;
        
        private:
        std::vector<size_t> mem_;
        ReserveCommitPair read_;
        ReserveCommitPair write_;
        size_t size_;
    };
}