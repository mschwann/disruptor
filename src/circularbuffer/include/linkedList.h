#pragma once
#include <atomic>

template<typename T> struct Node
{
    Node(T val, Node* nextPtr = nullptr) :  value(val), next(nextPtr) {}
    ~Node() = default;
    T value;
    std::atomic<Node*> next;
};

template<class T> class LinkedList
{
    public:
        LinkedList():
            head_(nullptr)
        {
        }
        ~LinkedList()
        {
            while(Node<T>* n = popNode())
            {
                delete n;
            }
        }
        void appendNode(Node<T>* node)
        {
            Node<T>* oldHead = head_.load();
            do
            {
                node->next = oldHead;
            } 
            while(!head_.compare_exchange_weak(oldHead, node));            
        }

        Node<T>* popNode()
        {
            Node<T>* oldHead = head_.load();
            Node<T>* newHead;
            do{
                if(!oldHead) //Nothing to grab
                    return nullptr;
                newHead = oldHead->next;
            }
            while(!head_.compare_exchange_weak(oldHead, newHead));
            oldHead->next = nullptr;
            return oldHead;
        }
    private:
        std::atomic<Node<T>*> head_;
};