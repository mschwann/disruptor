#include <stack/leaky_lockfree.h>
#include "gtest/gtest.h"


TEST(Stack, BasicSingleReadWrite) {
    Stack::WaitFree::Stack<uint8_t> ll;
    for(size_t i =0; i < 16; i++)
    {
        Stack::Node<uint8_t>* n = new Stack::Node<uint8_t>(i, nullptr);
        ll.push(n);
    }

    for(int i =15; i >= 0; i--)
    {
        EXPECT_EQ(ll.pop()->value, i);
    }
}


