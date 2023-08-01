#include "circularbuffer.h"
#include "gtest/gtest.h"

//CirculatBuffer1Producer1Consumer
TEST(cb1p1c, BasicSingleReadWrite) {
    auto buff = SingleProducer::SingleConsumer::CircularBuffer(16);
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