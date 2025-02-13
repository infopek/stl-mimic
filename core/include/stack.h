#pragma once

#include <cstddef>
#include <cstdlib>
#include <stdexcept>

namespace core {
    template <typename T>
    class Stack {
    public:
        Stack()
            : m_capacity(3), m_size(0) {
            m_data = static_cast<T*>(malloc(m_capacity * sizeof(T)));
        }
        Stack(const Stack&) = delete;
        Stack(Stack&&) noexcept = delete;
        ~Stack() {
            for (size_t i = 0; i < m_size; ++i) {
                m_data[i].~T();
            }
            free(m_data);
        }

        void push(const T& item) {
            if (m_size == m_capacity) {
                reallocate(m_capacity + m_capacity / 2);
            }

            m_data[m_size] = item;
            ++m_size;
        }
        void pop() {
            if (empty()) {
                throw std::logic_error("Stack is empty");
            }

            --m_size;
            m_data[m_size].~T();
        }

        const T& peek() const {
            if (empty()) {
                throw std::logic_error("Stack is empty");
            }

            return m_data[m_size - 1];
        }
        bool empty() const {
            return m_size == 0;
        }

    private:
        void reallocate(size_t newCapacity) {
            T* newData = static_cast<T*>(malloc(newCapacity * sizeof(T)));
            for (size_t i = 0; i < m_size; ++i) {
                new(&newData[i]) T(std::move(m_data[i]));
                m_data[i].~T();
            }

            free(m_data);
            m_data = newData;
            m_capacity = newCapacity;
        }
    private:
        T* m_data;
        size_t m_size{};
        size_t m_capacity{};
    };
}