#include <vector.h>

#include <stdexcept>

namespace core {
    Vector::Vector()
        : m_data{ nullptr }, m_capacity{ 1 }, m_length{ 0 } {
    }

    Vector::Vector(size_t length)
        : m_capacity{ length }, m_length{ length } {
        m_data = new int[length];
    }

    Vector::Vector(const Vector& other)
        : m_capacity{ other.m_capacity }, m_length{ other.m_length } {
        m_data = new int[m_length];
        for (size_t i = 0; i < m_length; i++) {
            m_data[i] = other.m_data[i];
        }
    }

    Vector::Vector(Vector&& other) noexcept
        : m_length{ std::move(other.m_length) },
        m_capacity{ std::move(other.m_capacity) } {
        m_data = other.m_data;
        other.m_data = nullptr;
    }

    Vector::~Vector() {
        delete[] m_data;
    }

    void Vector::add(int item) {
        if (m_length + 1 >= m_capacity) {
            reallocate();
        }

        m_data[m_length] = item;
        ++m_length;
    }

    void Vector::pop() {
        if (m_length == 0) {
            throw std::runtime_error("The vector is empty");
        }

        m_data[m_length - 1] = 0;
        --m_length;
    }

    int& Vector::operator[](size_t idx) {
        if (idx >= m_length) {
            throw std::runtime_error("Index out of bounds");
        }

        return m_data[idx];
    }

    void Vector::reallocate() {
        m_capacity *= 2;
        int* newData = new int[m_capacity];
        for (size_t i = 0; i < m_length; i++) {
            newData[i] = m_data[i];
        }
        m_data = newData;
    }
}
