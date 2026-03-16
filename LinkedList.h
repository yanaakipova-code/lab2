#pragma once
#include <stdexcept>
#include <cstddef>

template<class T>
class LinkedList {
private:
    struct Node{
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        Node(const T& value, Node* next) : data(value), next(next), prev(nullptr) {}
        Node(const T& value, Node* next, Node* prev) : data(value), next(next), prev(prev) {}
    };
    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    LinkedList (T* items, size_t count);
    LinkedList ();
    LinkedList (const LinkedList<T>& linked_list);
    
    ~LinkedList()
};

#include "LinkedList.tpp"
