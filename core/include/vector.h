#pragma once

#include <iterator> // random_access_iterator_tag
#include <memory> // allocator
#include <stddef.h> // size_t
#include <stdexcept>

namespace core {
    template <class T, class A = std::allocator<T>>
    class Vector {
    public:
        typedef A AllocatorType;
        typedef typename A::value_type ValueType;
        typedef typename A::size_type SizeType;
        typedef typename A::difference_type DifferenceType;
        typedef ValueType& Reference;
        typedef const ValueType& ConstReference;

        // Iterators
        class Iterator {
        public:
            typedef ValueType ValueType;
            typedef Reference Reference;
            typedef ValueType* Pointer;
            typedef DifferenceType DifferenceType;
            typedef std::random_access_iterator_tag IteratorCategory;
        public:
            Iterator()
                : m_ptr(nullptr)
            {
            }
            Iterator(Pointer ptr)
                : m_ptr(ptr)
            {
            }
            Iterator(const Iterator& other) :
                m_ptr(other.m_ptr)
            {
            }
            ~Iterator() = default;

            Iterator& operator=(const Iterator& other) {
                if (*this != other) {
                    m_ptr = other.m_ptr;
                }
                return *this;
            }

            bool operator==(const Iterator& other) const {
                return m_ptr == other.m_ptr;
            }
            bool operator!=(const Iterator& other) const {
                return !(m_ptr == other.m_ptr);
            }
            bool operator<(const Iterator& other) const {
                return m_ptr < other.m_ptr;
            }
            bool operator>(const Iterator& other) const {
                return m_ptr > other.m_ptr;
            }
            bool operator<=(const Iterator& other) const {
                return m_ptr <= other.m_ptr;
            }
            bool operator>=(const Iterator& other) const {
                return m_ptr >= other.m_ptr;
            }

            Iterator& operator++() {
                m_ptr++;
                return *this;
            }
            Iterator operator++(int) {
                Iterator it = *this;
                ++(*this);
                return it;
            }

            Iterator& operator--() {
                m_ptr--;
                return *this;
            }
            Iterator operator--(int) {
                Iterator it = *this;
                --(*this);
                return it;
            }

            Iterator& operator+=(SizeType offset) {
                m_ptr += offset;
                return *this;
            }
            Iterator operator+(SizeType offset) const {
                return Iterator(m_ptr + offset);
            }
            template <typename T2, typename A2>
            friend Iterator operator+(typename Vector<T2, A2>::SizeType offset, const typename Vector<T2, A2>::Iterator& it) {
                return Iterator(it.m_ptr + offset);
            }

            Iterator& operator-=(SizeType offset) {
                m_ptr -= offset;
                return *this;
            }
            Iterator operator-(SizeType offset) const {
                return Iterator(m_ptr - offset);
            }
            DifferenceType operator-(Iterator other) const {
                return m_ptr - other.m_ptr;
            }

            Reference operator*() const {
                return *m_ptr;
            }
            Pointer operator->() const {
                return m_ptr;
            }
            Reference operator[](SizeType idx) const {
                return *(m_ptr + idx);
            }

        private:
            Pointer m_ptr;
        };

        typedef std::reverse_iterator<Iterator> ReverseIterator;

    public:
        // ---------------- CONSTRUCTORS, DESTRUCTORS ---------------- //
        Vector()
            : m_data{ nullptr }, m_length{ 0 }
        {
            reallocate(2);
        }
        Vector(size_t length)
            : m_capacity{ length }, m_length{ length } {
            m_data = new T[length];
        }
        Vector(const Vector& other)
            : m_capacity{ other.m_capacity }, m_length{ other.m_length } {
            m_data = new T[m_length];
            for (size_t i = 0; i < m_length; i++) {
                m_data[i] = other.m_data[i];
            }

        }
        Vector(Vector&& other) noexcept
            : m_length{ std::move(other.m_length) },
            m_capacity{ std::move(other.m_capacity) } {
            m_data = other.m_data;
            other.m_data = nullptr;
        }
        ~Vector() {
            delete[] m_data;
        }

        // ---------------- MODIFIERS ---------------- //
        void pushBack(const T& item) {
            if (m_length >= m_capacity) {
                reallocate(m_capacity * 2);
            }

            m_data[m_length] = item;
            ++m_length;
        }
        void pushBack(T&& item) {
            if (m_length >= m_capacity) {
                reallocate(m_capacity * 2);
            }

            m_data[m_length] = std::move(item);
            ++m_length;
        }
        void pushFront(const T& item) {
            if (m_length >= m_capacity) {
                reallocate(m_capacity * 2);
            }

            m_data[m_length] = item;
            ++m_length;
        }
        void pushFront(T&& item) {
            if (m_length >= m_capacity) {
                reallocate(m_capacity * 2);
            }

            m_data[m_length] = std::move(item);
            ++m_length;
        }
        template <typename... Args>
        void emplaceBack(Args&&... args) {
            if (m_length >= m_capacity) {
                reallocate(m_capacity * 2);
            }

            m_data[m_length] = T(std::forward<Args>(args)...);
            ++m_length;
        }
        template <typename... Args>
        void emplaceFront(Args&&... args) {
            if (m_length >= m_capacity) {
                reallocate(m_capacity * 2);
            }

            m_data[0] = T(std::forward<Args>(args)...);
            ++m_length;
        }
        void popBack() {
            if (m_length == 0) {
                throw std::runtime_error("The vector is empty");
            }

            // TODO: fix this so that the vector actually shrinks
            m_data[m_length - 1] = T();
            --m_length;
        }
        void popFront() {
            if (m_length == 0) {
                throw std::runtime_error("The vector is empty");
            }

            for (size_t i = 1; i < m_length; ++i) {
                m_data[i - 1] = std::move(m_data[i]);
            }

            m_data[m_length - 1] = T();
            --m_length;
        }
        void insert(Iterator at, const T& item) {
        }

        void reserve(size_t newCapacity) {
            if (newCapacity <= m_capacity) {
                return;
            }

            reallocate(newCapacity);
        }
        void resize(size_t newLength) {
            reserve(newLength);

            m_length = newLength;
        }
        void resize(size_t newLength, ConstReference val) {
            reserve(newLength);
            for (size_t i = m_length; i < newLength; ++i) {
                m_data[i] = val;
            }

            m_length = newLength;
        }
        void clear() {
            for (size_t i = 0; i < m_length; ++i) {
                m_data[i] = T();
            }

            m_length = 0;
        }
        void shrinkToFit() {
            if (m_capacity < m_length * 2) {
                return;
            }

            reallocate(m_length);
        }

        // Element access
        T& at(size_t idx) {
            if (idx >= m_length) {
                throw std::runtime_error("Index out of bounds");
            }

            return m_data[idx];
        }
        const T& at(size_t idx) const {
            if (idx >= m_length) {
                throw std::runtime_error("Index out of bounds");
            }

            return m_data[idx];
        }
        T& front() {
            return m_data[0];
        }
        const T& front() const {
            return m_data[0];
        }
        T& back() {
            return m_data[m_length - 1];
        }
        const T& back() const {
            return m_data[m_length - 1];
        }

        T& operator[](size_t idx) {
            return m_data[idx];
        }
        const T& operator[](size_t idx) const {
            return m_data[idx];
        }

        // Getters
        inline size_t capacity() const { return m_capacity; }
        inline size_t length() const { return m_length; }
        inline const T* data() const { return m_data; }

        // Traversing
        Iterator begin() {
            return Iterator(m_data);
        }
        Iterator end() {
            return Iterator(m_data + m_length);
        }

        ReverseIterator rbegin() {
        }
        ReverseIterator rend() {

        }

    private:
        void reallocate(size_t newCapacity) {
            T* newData = new T[newCapacity];
            for (size_t i = 0; i < m_length; ++i) {
                newData[i] = std::move(m_data[i]);
            }

            delete[] m_data;
            m_data = newData;
            m_capacity = newCapacity;
        }

    private:
        T* m_data;
        size_t m_capacity{};
        size_t m_length{};
    };
}
