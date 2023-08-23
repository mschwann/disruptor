#pragma once

namespace Stack
{
    template<typename T> struct Node
    {
        Node(T val, Node* nextPtr = nullptr) :  value(val), next(nextPtr) {}
        ~Node() = default;
        T value;
        Node* next;
    };
}