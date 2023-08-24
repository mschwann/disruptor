#pragma once
#include <cstdint>
#include <vector>
#include <atomic>
#include <mutex>

/*
Previous benchmarks:

---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_mpmc_pushpop/threads:1        12.8 ns         12.8 ns     44257566
BM_mpmc_pushpop/threads:2        6.72 ns         13.4 ns     52112978
BM_mpmc_pushpop/threads:4        3.47 ns         13.9 ns     49383336
BM_mpmc_pushpop/threads:8        1.83 ns         14.6 ns     47248352
BM_mpmc_pushpop/threads:16       1.48 ns         23.7 ns     29676480
BM_mpmc_pushpop/threads:32      0.965 ns         23.0 ns     31675200
BM_1pc1c_pushpop                 4.37 ns         4.37 ns    139627635


*/

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
    class CircularBufferCommiter;
    
    class ReserveCommitPair
    {
        public:
        ReserveCommitPair(size_t r, size_t c, size_t n)
        :reserve_(r)
        ,commit_(c)
        {}
        
        std::atomic<size_t>& getReserve() { return reserve_;}
        std::atomic<size_t>& getCommit() {return commit_;}
        
        void updateCommit()
        {
            std::vector<size_t> commits;
            //collect commits from reservers
            //update commit
        }

        CircularBufferCommiter& createCommiter(){
            //todo(schwanm) : Make this thread safe, huh?
        }


        private:
        std::atomic<size_t> reserve_;
        std::atomic<size_t> commit_;

        std::vector<CircularBufferCommiter> commiters_;
        std::mutex m_;

    };

    class CircularBufferCommiter
    {
         //todo(schwanm): Multithreading safety :)
        public:

        CircularBufferCommiter() = default;
        void commit(size_t n){
            commits_.push_back(n);
        }
        void transferCommits(std::vector<size_t>& vecTo)
        {
            vecTo.insert(vecTo.end(), std::begin(commits_), std::end(commits_));
            commits_.clear();
        }
        private:
            std::vector<size_t> commits_;

    };

    //todo: undo that pattern, back to plain class for testing.
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
        CircularBufferCommiter& getReadCommiter(){return read_.createCommiter();}
        CircularBufferCommiter& getWriteCommiter(){return write_.createCommiter();} 
        
        private:
        std::vector<size_t> mem_;
        ReserveCommitPair read_;
        ReserveCommitPair write_;
        size_t size_;
    };
}