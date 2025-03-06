#pragma once

#include "vector.h"
#include "linked_list.h"

#include <iostream>
#include <optional>
#include <iterator>

namespace core {

    template <typename K, typename V>
    struct InternalPair {
        K key{};
        V value{};
        bool occupied{};
    };

    template <typename K, typename V>
    struct KVPair {
        K key{};
        V value{};
    };

    template <typename K, typename V>
    class HashTable {
        using Pair = InternalPair<K, V>;
    public:
        class Iterator {
            using ValueType = KVPair<const K, V>;
            using Reference = ValueType&;
            using Pointer = ValueType*;

        public:
            Iterator(HashTable<K, V>* map, size_t idx)
                : m_map{ map }, m_idx{ idx } {
                advanceToOccupied();
            }
            ~Iterator() = default;

            ValueType operator*() const {
                return { m_map->m_slots[m_idx].key,m_map->m_slots[m_idx].value };
            }

            Iterator& operator++() {
                ++m_idx;
                advanceToOccupied();
                return *this;
            }
            Iterator operator++(int) {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const Iterator& other) const {
                return m_map == other.m_map && m_idx == other.m_idx;
            }
            bool operator!=(const Iterator& other) const {
                return !(*this == other);
            }

        private:
            void advanceToOccupied() {
                while (m_idx < m_map->m_capacity && !m_map->m_slots[m_idx].occupied) {
                    ++m_idx;
                }
            }

        private:
            HashTable<K, V>* m_map;
            size_t m_idx;
        };

        class ConstIterator {
            using ValueType = KVPair<const K, V>;
            using Reference = ValueType&;
            using Pointer = ValueType*;

        public:
            ConstIterator(HashTable<K, V>* map, size_t idx)
                : m_map{ map }, m_idx{ idx } {
                advanceToOccupied();
            }
            ~ConstIterator() = default;

            ValueType operator*() const {
                return { m_map->m_slots[m_idx].key,m_map->m_slots[m_idx].value };
            }

            ConstIterator& operator++() {
                ++m_idx;
                advanceToOccupied();
                return *this;
            }
            ConstIterator operator++(int) {
                ConstIterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const ConstIterator& other) const {
                return m_map == other.m_map && m_idx == other.m_idx;
            }
            bool operator!=(const ConstIterator& other) const {
                return !(*this == other);
            }

        private:
            void advanceToOccupied() {
                while (m_idx < m_map->m_capacity && !m_map->m_slots[m_idx].occupied) {
                    ++m_idx;
                }
            }

        private:
            HashTable<K, V>* m_map;
            size_t m_idx;
        };

        Iterator begin() {
            return Iterator(this, 0);
        }
        Iterator end() {
            return Iterator(this, m_capacity);
        }
        ConstIterator begin() const {
            return ConstIterator(this, 0);
        }
        ConstIterator end() const {
            return ConstIterator(this, m_capacity);
        }

    public:
        HashTable()
            : m_size{ 0 } {
            rebuild(8);
        }
        HashTable(const HashTable<K, V>&) = delete;
        HashTable(HashTable<K, V>&&) noexcept = delete;
        ~HashTable() {
            delete[] m_slots;
        }

        auto get(const K& key) const {
            size_t idx = findSlot(key);
            return m_slots[idx].occupied
                ? std::optional{ m_slots[idx].value }
            : std::nullopt;
        }

        void set(const K& key, const V& value) {
            size_t idx = findSlot(key);
            if (m_slots[idx].occupied) {
                m_slots[idx].value = value;
                return;
            }
            if (m_size * c_maxLoadFactor >= m_capacity) {
                rebuild(m_capacity + m_capacity / 2);
                idx = findSlot(key);
            }
            m_slots[idx].occupied = true;
            m_slots[idx].key = key;
            m_slots[idx].value = value;

            ++m_size;
        }

        void remove(const K& key) {
            size_t idx = findSlot(key);
            if (!m_slots[idx].occupied) {
                return;
            }

            m_slots[idx].occupied = false;
            size_t j = idx;
            while (true) {
                j = (j + 1) % m_capacity;
                if (!m_slots[j].occupied) {
                    return;
                }

                size_t k = hashFunc(m_slots[j].key) % m_capacity;
                if (idx <= j && idx < k && k <= j) {
                    continue;
                }
                else if (k <= j || idx < k) {
                    continue;
                }

                m_slots[idx].occupied = true;
                m_slots[idx].key = m_slots[j].key;
                m_slots[idx].value = m_slots[j].value;
                m_slots[j].occupied = false;

                idx = j;
            }
        }

        V& operator[](const K& key) {
            size_t idx = findSlot(key);
            if (!m_slots[idx].occupied) {
                if (m_size * c_maxLoadFactor >= m_capacity) {
                    rebuild(m_capacity + m_capacity / 2);
                    idx = findSlot(key);
                }

                m_slots[idx].occupied = true;
                m_slots[idx].key = key;
                m_slots[idx].value = V();

                ++m_size;
            }
            return m_slots[idx].value;
        }

        inline size_t size() const { return m_size; }

        bool empty() const { return false; }

        void clear() {
        }

    private:
        size_t findSlot(const K& key) const {
            size_t idx = hashFunc(key) % m_capacity;
            while (m_slots[idx].occupied && m_slots[idx].key != key) {
                idx = (idx + 1) % m_capacity;
            }
            return idx;
        }

        void rebuild(size_t newCapacity) {
            Pair* oldSlots = m_slots;

            m_slots = new Pair[newCapacity];
            m_size = 0;
            m_capacity = newCapacity;

            for (const auto& [key, value] : *this) {
                set(key, value);
            }

            delete[] oldSlots;
        }

        size_t hashFunc(const K& key) const {
            return std::hash<K>{}(key);
        }

    private:
        static constexpr float c_maxLoadFactor = 0.8f;

        Pair* m_slots{};
        size_t m_size{};
        size_t m_capacity{};
    };
}
