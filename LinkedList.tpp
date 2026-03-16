#include <LinkedList.h>
#include <cstddef>
#include <stdexcept> 

template<class T>
LinkedList<T>::LinkedList()
    : m_head(nullptr), m_tail(nullptr), m_size(0){}

template<class T>
LinkedList<T>::LinkedList (T* items, size_t count)
    : LinkedList()
    {
        if (items = nullptr){
            throw std::invalid_argument("Нулевое значение аргумента");
        }

        for (size_t i = 0; i < count; ++i) {
            Node* newNode = new Node(items[i]);
            if (m_size == 0) {
                m_head = newNode;
                m_tail = newNode;
            } else {
                m_tail->next = newNode;
                newNode->prev = m_tail;
                m_tail = newNode;
            }
            ++m_size;
        }
}

template<class T>
LinkedList<T>::LinkedList (const LinkedList<T>& linked_list)
    : LinkedList(){
        Node* current = linked_list.m_head;
    while (current != nullptr) {
        Node* newNode = new Node(current->data);
        if (m_size == 0) {
            m_head = newNode;
            m_tail = newNode;
        } else {
            m_tail->next = newNode;
            newNode->prev = m_tail;
            m_tail = newNode;
        }
        ++m_size;
        current = current->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node* current = m_head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

