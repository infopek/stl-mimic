#pragma once

#include <stddef.h>

namespace core {
    class Vector {
    public:
        Vector();
        Vector(size_t length);
        Vector(const Vector& other);
        Vector(Vector&& other) noexcept;
        ~Vector();

        void add(int item);
        void pop();
        int& operator[](size_t idx);

        inline size_t capacity() const { return m_capacity; }
        inline size_t length() const { return m_length; }
        inline const int* data() const { return m_data; }

    private:
        void reallocate();

    private:
        int* m_data;
        size_t m_capacity{};
        size_t m_length{};
    };
}
