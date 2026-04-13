#pragma once
#include "Iterator.hpp"
#include "Bit.hpp"

template<std::integral T>
class BitSequence;

template<std::integral T>
class BitIterator : public Iterator<Bit<T>, BitIterator> {
private:
    const BitSequence<T>* m_sequence;
    size_t m_index;
    
public:
    BitIterator(const BitSequence<T>* seq = nullptr, size_t index = 0) 
        : m_sequence(seq), m_index(index) {}
    
    Bit<T> operator*() {
        if (m_sequence && m_index < m_sequence->GetLength()) {
            bool bit_value = m_sequence->GetBit(m_index);
            return Bit<T>(bit_value);
        }
        return Bit<T>(false);
    }
    
    Bit<T>* operator->() {
        static Bit<T> bit;
        if (m_sequence && m_index < m_sequence->GetLength()) {
            bool bit_value = m_sequence->GetBit(m_index);
            bit = Bit<T>(bit_value);
        }
        return &bit;
    }
    
    BitIterator& operator++() {
        ++m_index;
        return *this;
    }
    
    bool operator==(const BitIterator& other) const {
        return m_sequence == other.m_sequence && m_index == other.m_index;
    }
    
    bool operator!=(const BitIterator& other) const {
        return !(*this == other);
    }
};

template<std::integral T>
class ConstBitIterator : public ConstIterator<Bit<T>, ConstBitIterator> {
private:
    const BitSequence<T>* m_sequence;
    size_t m_index;
    
public:
    ConstBitIterator(const BitSequence<T>* seq = nullptr, size_t index = 0) 
        : m_sequence(seq), m_index(index) {}
    
    Bit<T> operator*() const {
        if (m_sequence && m_index < m_sequence->GetLength()) {
            bool bit_value = m_sequence->GetBit(m_index);
            return Bit<T>(bit_value);
        }
        return Bit<T>(false);
    }
    
    const Bit<T>* operator->() const {
        static Bit<T> bit;
        if (m_sequence && m_index < m_sequence->GetLength()) {
            bool bit_value = m_sequence->GetBit(m_index);
            bit = Bit<T>(bit_value);
        }
        return &bit;
    }
    
    ConstBitIterator& operator++() {
        ++m_index;
        return *this;
    }
    
    bool operator==(const ConstBitIterator& other) const {
        return m_sequence == other.m_sequence && m_index == other.m_index;
    }
    
    bool operator!=(const ConstBitIterator& other) const {
        return !(*this == other);
    }
};