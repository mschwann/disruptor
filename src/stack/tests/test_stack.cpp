#include <stack/leaky_lockfree.h>
#include "gtest/gtest.h"


TEST(Stack, BasicSingleReadWrite) {
    Stack<uint8_t> ll;
    for(size_t i =0; i < 16; i++)
    {
        Node<uint8_t>* n = new Node<uint8_t>(i, nullptr);
        ll.push(n);
    }

    for(int i =15; i >= 0; i--)
    {
        EXPECT_EQ(ll.pop()->value, i);
    }
}


