#pragma once
#include "base.h"

#include <mutex>

namespace Stack::Waiting
{

    template<typename T> class Stack
    {
        public:
            Stack():
                head_(nullptr)
            {}
            void push(Node<T>* node)
            {
                std::unique_lock<std::mutex> lock(m_);
                node->next = head_;
                head_ = node;
            }
            Node<T>* pop()
            {
                std::unique_lock<std::mutex> lock(m_);
                Node<T>* oldHead = head_;
                if(!oldHead)
                    return nullptr;
                head_ = head_->next;
                return oldHead;
            }
        private:
            std::mutex m_;
            Node<T>* head_;
    };
}