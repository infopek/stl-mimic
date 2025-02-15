#pragma once

#include "vector.h"
#include "linked_list.h"

#include <iostream>
#include <optional>

namespace core {
    template <typename K, typename T>
    struct KVPair {
        K key;
        T value;
    };

    template <typename K, typename V>
    class HashTable {
    public:
        HashTable() = default;
        HashTable(const HashTable<K, V>&) = delete;
        HashTable(HashTable<K, V>&&) noexcept = delete;
        ~HashTable() = default;

        void insert(const K& key, const V& value) {
            size_t idx = hashFunc(key);
            m_data[idx].pushBack(KVPair{
                 .key = key,
                 .value = value
                });
        }

        void remove(const K& key) {
            size_t idx = hashFunc(key);
            m_data[idx].clear();
        }

        std::optional<V> get(const K& key) const {
            if (!contains(key)) {
                return {};
            }

            // Return the first one
            size_t idx = hashFunc(key);
            return m_data[idx].front().value;
        }

        V& operator[](const K& key) {
            size_t idx = hashFunc(key);
            for (auto& kv : m_data[idx]) {
                if (kv.key == key) {
                    return kv.value;
                }
            }

            m_data[idx].pushBack(KVPair{
                .key = key,
                .value = V()
                });
            return m_data[idx].back().value;
        }

        bool contains(const K& key) const {
            size_t idx = hashFunc(key);
            return !m_data[idx].empty();
        }

        inline size_t size() const { return c_hashSize; }

        bool empty() const { return false; }

        void clear() {
            for (auto& list : m_data) {
                list.clear();
            }
        }

    private:
        static size_t hashFunc(const K& key) {
            return std::hash<K>{}(key) % c_hashSize;
        }

    private:
        static constexpr size_t c_hashSize = 100;
        SLinkedList<KVPair<K, V>> m_data[c_hashSize];
    };
}