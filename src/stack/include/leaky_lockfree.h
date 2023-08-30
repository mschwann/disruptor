#pragma once
#include "base.h"

#include <atomic>

namespace Stack::WaitFree{
    template<class T> class Stack
    {
        public:
            Stack():
                head_(nullptr)
            {
            }
            ~Stack()
            {
                /*Node<T>* n = pop();
                while (n)
                {
                    Node<T>* next = n->next;
                    delete n;
                    n = next;
                }*/
            }
            void push(Node<T>* node)
            {
                Node<T>* oldHead = head_.load(std::memory_order_relaxed);
                do
                {
                    node->next = oldHead;
                }
                while (!head_.compare_exchange_weak(oldHead, node, std::memory_order_release, std::memory_order_relaxed));
            }
            Node<T>* pop()
            {
                Node<T>* oldHead = nullptr;
                do {
                    oldHead = head_.load(std::memory_order_relaxed);
                    if (!oldHead) // Nothing to grab
                        return nullptr;
                } while (!head_.compare_exchange_weak(oldHead, oldHead->next, std::memory_order_relaxed));
                
                return oldHead;
            }
        private:
            std::atomic<Node<T>*> head_;
    };
}