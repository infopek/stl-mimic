#pragma once

#include <cstddef>
#include <iterator>

template <typename T>
class ExampleIterator {
public:
    using ValueType = T;
    using DifferenceType = std::ptrdiff_t;
    using Pointer = T*;
    using Reference = T&;
    using IteratorCategory = std::random_access_iterator_tag;
public:
    ExampleIterator()
        : m_ptr(nullptr)
    {
    }
    ExampleIterator(Pointer ptr)
        : m_ptr(ptr)
    {
    }
    ExampleIterator(const ExampleIterator& other)
        : m_ptr(other.m_ptr)
    {
    }

    ExampleIterator& operator=(const ExampleIterator& other) {
        if (*this != other) {
            m_ptr = other.m_ptr;
        }
        return *this;
    }

    Reference operator*() const { return *m_ptr; }
    Pointer operator->() const { return m_ptr; }
    Reference operator[](DifferenceType offset) const { return *(m_ptr + offset); }

    ExampleIterator& operator++() {
        ++m_ptr;
        return *this;
    }
    ExampleIterator operator++(int) {
        ExampleIterator temp = *this;
        ++m_ptr;
        return temp;
    }
    ExampleIterator& operator--() {
        --m_ptr;
        return *this;
    }
    ExampleIterator operator--(int) {
        ExampleIterator temp = *this;
        --m_ptr;
        return temp;
    }

    ExampleIterator& operator+=(DifferenceType offset) {
        m_ptr += offset;
        return *this;
    }
    ExampleIterator& operator-=(DifferenceType offset) {
        m_ptr -= offset;
        return *this;
    }

    friend bool operator==(const ExampleIterator& lhs, const ExampleIterator& rhs) {
        return lhs.m_ptr == rhs.m_ptr;
    }
    friend bool operator!=(const ExampleIterator& lhs, const ExampleIterator& rhs) {
        return !(lhs == rhs);
    }
    friend bool operator<(const ExampleIterator& lhs, const ExampleIterator& rhs) {
        return lhs.m_ptr < rhs.m_ptr;
    }
    friend bool operator>(const ExampleIterator& lhs, const ExampleIterator& rhs) {
        return rhs < lhs;
    }
    friend bool operator<=(const ExampleIterator& lhs, const ExampleIterator& rhs) {
        return !(rhs < lhs);
    }
    friend bool operator>=(const ExampleIterator& lhs, const ExampleIterator& rhs) {
        return !(lhs < rhs);
    }

    friend ExampleIterator operator+(const ExampleIterator& it, DifferenceType offset) {
        ExampleIterator temp = it;
        temp += offset;
        return temp;
    }
    friend ExampleIterator operator+(DifferenceType offset, const ExampleIterator& it) {
        return it + offset;
    }
    friend ExampleIterator operator-(const ExampleIterator& it, DifferenceType offset) {
        ExampleIterator temp = it;
        temp -= offset;
        return temp;
    }

    friend DifferenceType operator-(const ExampleIterator& lhs, const ExampleIterator& rhs) {
        return lhs.m_ptr - rhs.m_ptr;
    }

private:
    Pointer m_ptr;
};
