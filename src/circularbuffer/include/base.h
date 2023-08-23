#pragma once
#include <cstdint>
#include <vector>
#include <atomic>

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

namespace MultiProducer::MultiConsumer
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

    class CircularBuffer : public ::CircularBufferBase<CircularBuffer>
    {
        public:
        CircularBuffer(size_t n)
        : ::CircularBufferBase<CircularBuffer>()
        , mem_(n)
        , read_(0, 0, n)
        , write_(0, 0, n)
        , size_(n)
        {}
        using ::CircularBufferBase<CircularBuffer>::popByte;
        using ::CircularBufferBase<CircularBuffer>::pushByte;
        
        virtual bool pushByteImpl(uint8_t& item) override;
        virtual bool popByteImpl(uint8_t& item) override;
        
        private:
        std::vector<size_t> mem_;
        ReserveCommitPair read_;
        ReserveCommitPair write_;
        size_t size_;
    };
}