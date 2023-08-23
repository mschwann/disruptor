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
                while(Node<T>* n = pop())
                {
                    delete n;
                }
            }
            void push(Node<T>* node)
            {
                Node<T>* oldHead = head_.load(std::memory_order_acquire);
                do
                {
                    node->next = oldHead;
                } 
                while(!head_.compare_exchange_weak(oldHead, node, std::memory_order_acquire, std::memory_order_release));            
            }

            Node<T>* pop()
            {
                Node<T>* oldHead = head_.load(std::memory_order_acquire);
                Node<T>* newHead;
                do{
                    if(!oldHead) //Nothing to grab
                        return nullptr;
                    newHead = oldHead->next;
                }
                while(!head_.compare_exchange_weak(oldHead, newHead, std::memory_order_acquire, std::memory_order_release));
                oldHead->next = nullptr;
                return oldHead;
            }
        private:
            std::atomic<Node<T>*> head_;
    };
}