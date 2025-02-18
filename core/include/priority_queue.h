#pragma once

#include <vector.h>

#include <memory>
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <cmath>

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
            priority = std::move(other.priority);
            value = std::move(other.value);
            return *this;
        }
        ~HeapNode() = default;
    };

    template <typename P, typename V, typename Comp = std::less<P>>
    class PQueue {
    private:
        using Node = HeapNode<P, V>;

    public:
        PQueue()
            : m_heap{ nullptr }, m_size{ 0 }, m_capacity{ 0 } {
            reallocate(c_initCapacity);
        }
        PQueue(std::initializer_list<std::pair<P, V>> list)
            : m_size{ list.size() }
            , m_capacity{ m_size * 2 } {
            m_heap = static_cast<Node*>(::operator new(sizeof(Node) * m_capacity));

            size_t i = 0;
            for (const auto& [priority, value] : list) {
                new (&m_heap[i]) Node(priority, value);
                ++i;
            }

            for (int i = m_size / 2 - 1; i >= 0; --i) {
                bubbleDown(i);
            }
        }
        PQueue(const PQueue<P, V, Comp>&) = delete;
        PQueue& operator=(const PQueue<P, V, Comp>&) = delete;
        ~PQueue() {
            clear();
            ::operator delete(m_heap);
        }

        void insert(const P& priority, const V& value) {
            if (m_size == m_capacity) {
                reallocate(m_capacity + m_capacity / 2);
            }

            new(&m_heap[m_size]) Node(priority, value);
            ++m_size;
            if (m_size > 1) {
                bubbleUp();
            }
        }
        void pop() {
            if (m_size == 0) {
                throw std::out_of_range("The queue is empty");
            }

            m_heap[0] = std::move(m_heap[m_size - 1]);
            --m_size;
            if (m_size > 1) {
                bubbleDown(0);
            }
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

        void print() {
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << m_heap[i].value << " ";
            }
        }

    private:
        void reallocate(size_t newCapacity) {
            Node* newHeap = (Node*)::operator new(newCapacity * sizeof(Node));
            for (size_t i = 0; i < m_size; ++i) {
                new(&newHeap[i]) Node(std::move(m_heap[i]));
                m_heap[i].~Node();
            }

            ::operator delete(m_heap);
            m_heap = newHeap;
            m_capacity = newCapacity;
        }

        /// Assumes that the newly inserted item is already at index m_size - 1
        void bubbleUp() {
            size_t idx = m_size - 1;
            size_t parentIdx = (idx - 1) / 2;
            while (idx != 0 && m_comp(m_heap[idx].priority, m_heap[parentIdx].priority)) {
                std::swap(m_heap[idx], m_heap[parentIdx]);
                idx = parentIdx;
                parentIdx = (idx - 1) / 2;
            }
        }

        void bubbleDown(size_t idx) {
            while (true) {
                size_t smallest = idx; // or biggest, depending on comp
                size_t left = idx * 2 + 1;
                size_t right = idx * 2 + 2;
                // if (child1Idx < m_size && child2Idx < m_size
                //     && (m_heap[child1Idx].priority < m_heap[idx].priority
                //         || m_heap[child2Idx].priority < m_heap[idx].priority)
                //     ) {
                //     // In case of same priority, choose right child 
                //     minChildIdx = m_comp(m_heap[child1Idx].priority, m_heap[child2Idx].priority)
                //         ? child1Idx
                //         : child2Idx;
                // }
                // else if (child1Idx < m_size && m_comp(m_heap[child1Idx].priority, m_heap[idx].priority)) {
                //     minChildIdx = child1Idx;
                // }
                // else if (child2Idx < m_size && m_comp(m_heap[child2Idx].priority, m_heap[idx].priority)) {
                //     minChildIdx = child2Idx;
                // }
                // else {
                //     break;
                // }
                if (left < m_size && m_comp(m_heap[left].priority, m_heap[idx].priority)) {
                    smallest = left;
                }
                if (right < m_size && m_comp(m_heap[right].priority, m_heap[smallest].priority)) {
                    smallest = right;
                }
                if (smallest == idx) {
                    return;
                }

                std::swap(m_heap[idx], m_heap[smallest]);
                idx = smallest;
            }
        }

    private:
        constexpr static size_t c_initCapacity = 3;

        Node* m_heap;
        size_t m_size{};
        size_t m_capacity{};
        Comp m_comp{};
    };
}