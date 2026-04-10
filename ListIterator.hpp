#pragma once
#include <memory>
#include "Iterator.hpp"

template<class T>
class LinkedList;

template<class T>
class ListIterator : public Iterator<T> {
private:
    typename LinkedList<T>::Node* m_node_ptr;
    
public:
    ListIterator(typename LinkedList<T>::Node* ptr = nullptr) : m_node_ptr(ptr) {}
    
    typename Iterator<T>::reference operator*() override {
        return m_node_ptr->data;
    }
    
    typename Iterator<T>::pointer operator->() override {
        return &(m_node_ptr->data);
    }
    
    Iterator<T>& operator++() override {
        if (m_node_ptr) m_node_ptr = m_node_ptr->next;
        return *this;
    }
    
    bool operator==(const Iterator<T>& other) const override {
        const ListIterator* other_list = dynamic_cast<const ListIterator*>(&other);
        if (!other_list) return false;
        return m_node_ptr == other_list->m_node_ptr;
    }
    
    bool operator!=(const Iterator<T>& other) const override {
        return !(*this == other);
    }
    
    std::unique_ptr<Iterator<T>> clone() const override {
        return std::make_unique<ListIterator<T>>(m_node_ptr);
    }
};

template<class T>
class ConstListIterator : public ConstIterator<T> {
private:
    const typename LinkedList<T>::Node* m_node_ptr;
    
public:
    ConstListIterator(const typename LinkedList<T>::Node* ptr = nullptr) : m_node_ptr(ptr) {}
    
    typename ConstIterator<T>::reference operator*() const override {
        return m_node_ptr->data;
    }
    
    typename ConstIterator<T>::pointer operator->() const override {
        return &(m_node_ptr->data);
    }
    
    ConstIterator<T>& operator++() override {
        if (m_node_ptr) m_node_ptr = m_node_ptr->next;
        return *this;
    }
    
    bool operator==(const ConstIterator<T>& other) const override {
        const ConstListIterator* other_list = dynamic_cast<const ConstListIterator*>(&other);
        if (!other_list) return false;
        return m_node_ptr == other_list->m_node_ptr;
    }
    
    bool operator!=(const ConstIterator<T>& other) const override {
        return !(*this == other);
    }
    
    std::unique_ptr<ConstIterator<T>> clone() const override {
        return std::make_unique<ConstListIterator<T>>(m_node_ptr);
    }
};