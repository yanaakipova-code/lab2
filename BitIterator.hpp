#pragma once
#include <memory>
#include "Iterator.hpp"
#include "Bit.hpp"

template<std::integral T>
class BitSequence;

template<std::integral T>
class BitIterator : public Iterator<Bit> {
private:
    const BitSequence<T>* m_sequence;
    size_t m_index;
    
public:
    BitIterator(const BitSequence<T>* seq = nullptr, size_t index = 0) 
        : m_sequence(seq), m_index(index) {}
    
    typename Iterator<Bit>::reference operator*() override {
        static Bit bit;
        if (m_sequence && m_index < m_sequence->GetLength()) {
            bit = m_sequence->Get(m_index);
        }
        return bit;
    }
    
    typename Iterator<Bit>::pointer operator->() override {
        static Bit bit;
        if (m_sequence && m_index < m_sequence->GetLength()) {
            bit = m_sequence->Get(m_index);
        }
        return &bit;
    }
    
    Iterator<Bit>& operator++() override {
        ++m_index;
        return *this;
    }
    
    bool operator==(const Iterator<Bit>& other) const override {
        const BitIterator* other_bit = dynamic_cast<const BitIterator*>(&other);
        if (!other_bit) return false;
        return m_sequence == other_bit->m_sequence && m_index == other_bit->m_index;
    }
    
    bool operator!=(const Iterator<Bit>& other) const override {
        return !(*this == other);
    }
    
    std::unique_ptr<Iterator<Bit>> clone() const override {
        return std::make_unique<BitIterator<T>>(m_sequence, m_index);
    }
};

template<std::integral T>
class ConstBitIterator : public ConstIterator<Bit> {
private:
    const BitSequence<T>* m_sequence;
    size_t m_index;
    
public:
    ConstBitIterator(const BitSequence<T>* seq = nullptr, size_t index = 0) 
        : m_sequence(seq), m_index(index) {}
    
    typename ConstIterator<Bit>::reference operator*() const override {
        static Bit bit;
        if (m_sequence && m_index < m_sequence->GetLength()) {
            bit = m_sequence->Get(m_index);
        }
        return bit;
    }
    
    typename ConstIterator<Bit>::pointer operator->() const override {
        static Bit bit;
        if (m_sequence && m_index < m_sequence->GetLength()) {
            bit = m_sequence->Get(m_index);
        }
        return &bit;
    }
    
    ConstIterator<Bit>& operator++() override {
        ++m_index;
        return *this;
    }
    
    bool operator==(const ConstIterator<Bit>& other) const override {
        const ConstBitIterator* other_bit = dynamic_cast<const ConstBitIterator*>(&other);
        if (!other_bit) return false;
        return m_sequence == other_bit->m_sequence && m_index == other_bit->m_index;
    }
    
    bool operator!=(const ConstIterator<Bit>& other) const override {
        return !(*this == other);
    }
    
    std::unique_ptr<ConstIterator<Bit>> clone() const override {
        return std::make_unique<ConstBitIterator<T>>(m_sequence, m_index);
    }
};