#pragma once
#include <cstdint>
#include <vector>
#include <atomic>

template<class Impl> class CircularBuffer
{
    public:
        CircularBuffer() = default;
        virtual ~CircularBuffer(){}

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

    class CircularBuffer : public ::CircularBuffer<CircularBuffer>
    {
        public:
        CircularBuffer(size_t n)
        : ::CircularBuffer<CircularBuffer>()
        , mem_(n)
        , read_(0, 0, n)
        , write_(0, 0, n)
        , size_(n)
        {}
        using ::CircularBuffer<CircularBuffer>::popByte;
        using ::CircularBuffer<CircularBuffer>::pushByte;
        
        virtual bool pushByteImpl(uint8_t& item) override;
        virtual bool popByteImpl(uint8_t& item) override;
        
        private:
        std::vector<size_t> mem_;
        ReserveCommitPair read_;
        ReserveCommitPair write_;
        size_t size_;
    };
}

namespace SingleProducer::SingleConsumer
{
class CircularBuffer : public ::CircularBuffer<CircularBuffer>
{
    public:
        CircularBuffer(size_t n)
        : ::CircularBuffer<CircularBuffer>()
        , mem_(n)
        , read_(0)
        , write_(0)
        , size_(n)
        {}
        using ::CircularBuffer<CircularBuffer>::popByte;
        using ::CircularBuffer<CircularBuffer>::pushByte;
        virtual bool pushByteImpl(uint8_t& item) override;
        virtual bool popByteImpl(uint8_t& item) override;
    private:
        std::vector<size_t> mem_;
        std::atomic<size_t> read_;
        std::atomic<size_t> write_;
        size_t size_;
};
}