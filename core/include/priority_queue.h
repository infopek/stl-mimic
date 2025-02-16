#pragma once

#include <memory>
#include <iostream>

namespace core {
    template <typename P, typename V>
    struct HeapNode {
        P priority;
        V value;

        HeapNode() = default;
        HeapNode(const P& priority_, const V& value_)
            : priority{ priority_ }
            , value{ value_ } {
        }
        HeapNode(const HeapNode& other)
            : priority(other.priority)
            , value(other.value) {

        }
        HeapNode(HeapNode&& other) noexcept
            : priority{ std::move(other.priority) }
            , value{ std::move(other.value) } {
        }

        HeapNode& operator=(const HeapNode& other) {
            if (this != &other) {
                priority = other.priority;
                value = other.value;
            }
            return *this;
        }
        HeapNode& operator=(HeapNode&& other) noexcept {
            if (this != &other) {
                priority = other.priority;
                value = other.value;
            }
            return *this;
        }
        ~HeapNode() = default;
    };

    template <typename P, typename V>
    class PQueue {
    private:
        using Node = HeapNode<P, V>;

    public:
        PQueue()
            : m_heap{ nullptr }, m_size{ 0 }, m_capacity{ 0 } {
            reallocate(c_initCapacity);
        }

        ~PQueue() {
            clear();
            ::operator delete(m_heap, m_capacity * sizeof(Node));
        }

        void insert(const P& priority, const V& value) {
            if (m_size == m_capacity) {
                reallocate(m_capacity + m_capacity / 2);
            }

            m_heap[m_size] = Node(priority, value);
            if (m_size > 0) {
                bubbleUp();
            }
            ++m_size;
        }

        const V& peek() const {
            return m_heap[0].value;
        }

        void clear() {
            for (size_t i = 0; i < m_size; ++i) {
                m_heap[i].~Node();
            }
            m_size = 0;
        }

    private:
        void reallocate(size_t newCapacity) {
            Node* newHeap = (Node*)::operator new(newCapacity * sizeof(Node));
            for (size_t i = 0; i < m_size; ++i) {
                new(&newHeap[i]) Node(std::move(m_heap[i]));
                m_heap[i].~Node();
            }

            ::operator delete(m_heap, m_capacity * sizeof(Node));
            m_heap = newHeap;
            m_capacity = newCapacity;
        }

        /// Assumes that the newly inserted item is at index m_size - 1
        void bubbleUp() {
            size_t idx = m_size;
            size_t parentIdx = (idx - 1) / 2;
            while (m_heap[idx].priority < m_heap[parentIdx].priority) {
                std::swap(m_heap[idx], m_heap[parentIdx]);
                idx = parentIdx;
                parentIdx = (idx - 1) / 2;
            }
        }

    private:
        constexpr static size_t c_initCapacity = 3;

        Node* m_heap;
        size_t m_size{};
        size_t m_capacity{};
    };
}