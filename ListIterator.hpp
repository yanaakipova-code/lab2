#pragma once
#include "Iterator.hpp"

template<class T>
class LinkedList;

template<class T>
class ListIterator : public Iterator<T, ListIterator> {
private:
    typename LinkedList<T>::Node* m_node_ptr;
    
public:
    ListIterator(typename LinkedList<T>::Node* ptr = nullptr) : m_node_ptr(ptr) {}
    
    T& operator*() {
        return m_node_ptr->data;
    }
    
    T* operator->() {
        return &(m_node_ptr->data);
    }
    
    ListIterator& operator++() {
        if (m_node_ptr) {
            m_node_ptr = m_node_ptr->next;
        }
        return *this;
    }
    
    bool operator==(const ListIterator& other) const {
        return m_node_ptr == other.m_node_ptr;
    }
    
    bool operator!=(const ListIterator& other) const {
        return !(*this == other);
    }
};

template<class T>
class ConstListIterator : public ConstIterator<T, ConstListIterator> {
private:
    const typename LinkedList<T>::Node* m_node_ptr;
    
public:
    ConstListIterator(const typename LinkedList<T>::Node* ptr = nullptr) : m_node_ptr(ptr) {}
    
    const T& operator*() const {
        return m_node_ptr->data;
    }
    
    const T* operator->() const {
        return &(m_node_ptr->data);
    }
    
    ConstListIterator& operator++() {
        if (m_node_ptr) {
            m_node_ptr = m_node_ptr->next;
        }
        return *this;
    }
    
    bool operator==(const ConstListIterator& other) const {
        return m_node_ptr == other.m_node_ptr;
    }
    
    bool operator!=(const ConstListIterator& other) const {
        return !(*this == other);
    }
};