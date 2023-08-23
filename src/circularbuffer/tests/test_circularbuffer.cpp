#include "singleconsumersingleproducer.h"
#include "base.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <atomic>
#include <thread>

//CirculatBuffer1Producer1Consumer
TEST(cb1p1c, BasicSingleReadWrite) {
    CircularBuffer::SingleConsumerSingleProducer buff(16);
    uint8_t src = 12;
    EXPECT_EQ(buff.pushByte(src), true);
    src = 13;
    EXPECT_EQ(buff.pushByte(src), true);
    uint8_t dst;
    EXPECT_EQ(buff.popByte(dst), true);
    EXPECT_EQ(dst, 12);
    EXPECT_EQ(buff.popByte(dst), true);
    EXPECT_EQ(dst, 13);
}

//CirculatBuffer1Producer1Consumer
TEST(cbmpmc, BasicSingleReadWrite) {
    MultiProducer::MultiConsumer::CircularBuffer buff(16);
    uint8_t src = 12;
    EXPECT_EQ(buff.pushByte(src), true);
    uint8_t dst;
    EXPECT_EQ(buff.popByte(dst), true);
    EXPECT_EQ(dst, 12);
}

TEST(cbmpmc, MultiWriteConsistency) {
    MultiProducer::MultiConsumer::CircularBuffer buff(64);
    std::vector<uint8_t> vals(32);
    std::generate(std::begin(vals), std::end(vals), [i = 0]() mutable {return i++;});
    std::vector<uint8_t> valsBackup = vals;
    auto tstFunc = [&](uint8_t& val){
        for(size_t i=0;i<100;i++)
        {
            while(!buff.pushByte(val));
            while(!buff.popByte(val));
        }
    };
    std::vector<std::thread> ts;
    for(size_t i=0; i < 32; i++)
    {
        ts.push_back(std::thread(tstFunc, std::ref(vals[i])));
    }
    for(auto& t : ts)
        t.join();
    std::sort(std::begin(vals), std::end(vals));
    EXPECT_EQ(vals, valsBackup);

}

