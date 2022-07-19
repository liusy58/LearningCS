#include <thread>
#include <iostream>
#include <atomic>

template<typename T>
class Stack{
    struct node {
        T val;
        node* next;
        node(const T&x) : val(x) {}
    };

    std::atomic<node*>head;
public:
    void push(const T&x){
        const auto new_node = new node(x);
        new_node->next = head.load();
        while(!head.compare_exchange_weak(new_node->next,new_node));
    }

    void pop() {}
};