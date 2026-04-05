#include <cstddef>
#include <stdexcept> 
#include "DynamicArray.hpp"

template<class T>
DynamicArray<T>::DynamicArray() {
    m_size = 0;
    m_data = nullptr;
}

template<class T>
DynamicArray<T>::DynamicArray(T* items, size_t count) {
    m_size = count;
    if (count == 0) {
        m_data = nullptr;
    } else {
        m_data = new T[count];
        for (size_t i = 0; i < count; i++) {
            m_data[i] = items[i];
        }
    }
}

template<class T>
DynamicArray<T>::DynamicArray(size_t size) {
    m_size = size;
    if (size == 0) {
        m_data = nullptr;
    } else {
        m_data = new T[size];
        for (size_t i = 0; i < size; i++) {
            m_data[i] = T();
        }
    }
}

template<class T>
DynamicArray<T>::DynamicArray(DynamicArray<T>& dynamic_array) {
    m_size = dynamic_array.m_size;
    if (m_size == 0) {
        m_data = nullptr;
    } else {
        m_data = new T[m_size];
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = dynamic_array.m_data[i];
        }
    }
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
}

template<class T>
T DynamicArray<T>::Get(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("DynamicArray::Get: индекс за пределами массива");
    }
    return m_data[index];
}

template<class T>
size_t DynamicArray<T>::GetSize() {
    return m_size;
}

template<class T>
void DynamicArray<T>::Set(size_t index, T value) {
    if (index >= m_size) {
        throw std::out_of_range("DynamicArray::Set: индекс за пределами массива");
    }
    m_data[index] = value;
}

template<class T>
void DynamicArray<T>::Resize(size_t new_size) {
    if (new_size == m_size) {
        return;
    }
    T* new_data = nullptr;
    if (new_size > 0) {
        new_data = new T[new_size];
    }
    size_t elements_to_copy;
    if (new_size < m_size) {
        elements_to_copy = new_size; 
    } else {
        elements_to_copy = m_size;
    }
    
    for (size_t i = 0; i < elements_to_copy; ++i) {
        new_data[i] = m_data[i];
    }

    for (size_t i = m_size; i < new_size; ++i) {
        new_data[i] = T();
    }
    
    delete[] m_data;
    m_data = new_data;
    m_size = new_size;
}

template<class T>
T* DynamicArray<T>::GetData() {
    return m_data;
}

template<class T>
const T* DynamicArray<T>::GetData() const {
    return m_data;
}

template<class T>
T& DynamicArray<T>::GetRef(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("DynamicArray::GetRef: индекс за пределами массива");
    }
    return m_data[index];
}

template<class T>
const T& DynamicArray<T>::GetRef(size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("DynamicArray::GetRef const: индекс за пределами массива");
    }
    return m_data[index];
}