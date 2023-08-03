#include "linkedList.h"
#include "gtest/gtest.h"


TEST(LinkedList, BasicSingleReadWrite) {
    LinkedList<uint8_t> ll;
    for(size_t i =0; i < 16; i++)
    {
        Node<uint8_t>* n = new Node<uint8_t>(i, nullptr);
        ll.appendNode(n);
    }

    for(int i =15; i >= 0; i--)
    {
        EXPECT_EQ(ll.popNode()->value, i);
    }
}


