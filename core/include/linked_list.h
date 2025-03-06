#pragma once

#include <initializer_list>
#include <iterator>
#include <stdexcept>

namespace core {
    template <typename T>
    struct SNode {
        T val{};
        SNode* next;

        SNode()
            : val(T()), next(nullptr)
        {
        }
        SNode(const T& val_)
            : val(val_), next(nullptr)
        {
        }
        SNode(const T& val_, SNode<T>* n)
            : val(val_), next(n)
        {
        }
    };

    template <typename T>
    class SLinkedList {
    public:
        class Iterator {
            using ValueType = T;
            using Reference = T&;
        public:
            Iterator()
                : m_ptr(nullptr) {
            }
            Iterator(const Iterator& other)
                : m_ptr(other.m_ptr) {
            }
            Iterator(SNode<ValueType>* ptr)
                : m_ptr(ptr) {
            }

            Iterator& operator=(const Iterator& other) {
                if (*this != other) {
                    m_ptr = other.m_ptr;
                }
                return *this;
            }

            Reference operator*() const { return m_ptr->val; }

            Iterator& operator++() {
                if (m_ptr) {
                    m_ptr = m_ptr->next;
                }
                return *this;
            }
            Iterator operator++(int) {
                Iterator temp = *this;
                ++*this;
                return temp;
            }

            bool operator==(const Iterator& other) const {
                return m_ptr == other.m_ptr;
            }
            bool operator!=(const Iterator& other) const {
                return !(*this == other);
            }
        private:
            SNode<ValueType>* m_ptr;
        };

        class ConstIterator {
            using ValueType = T;
            using Reference = T&;
        public:
            ConstIterator()
                : m_ptr(nullptr) {
            }
            ConstIterator(const ConstIterator& other)
                : m_ptr(other.m_ptr) {
            }
            ConstIterator(const Iterator& other)
                : m_ptr(other.m_ptr) {
            }
            ConstIterator(SNode<ValueType>* ptr)
                : m_ptr(ptr) {
            }

            ConstIterator& operator=(const ConstIterator& other) {
                if (*this != other) {
                    m_ptr = other.m_ptr;
                }
                return *this;
            }

            Reference operator*() const { return m_ptr->val; }

            ConstIterator operator++() {
                if (m_ptr) {
                    m_ptr = m_ptr->next;
                }
                return *this;
            }
            ConstIterator operator++(int) {
                ConstIterator temp = *this;
                ++*this;
                return temp;
            }

            bool operator==(const ConstIterator& other) const {
                return m_ptr == other.m_ptr;
            }
            bool operator!=(const ConstIterator& other) const {
                return !(*this == other);
            }
        private:
            SNode<ValueType>* m_ptr;

            friend class Iterator;
        };

        Iterator begin() {
            return Iterator(m_head);
        }
        Iterator end() {
            return Iterator(nullptr);
        }
        ConstIterator begin() const {
            return ConstIterator(m_head);
        }
        ConstIterator end() const {
            return ConstIterator(nullptr);
        }

        ConstIterator cbegin() const {
            return ConstIterator(m_head);
        }
        ConstIterator cend() const {
            return ConstIterator(nullptr);
        }

    public:
        SLinkedList()
            : m_head(nullptr) {
        }
        SLinkedList(std::initializer_list<T> list) {
        }
        SLinkedList(const SLinkedList<T>& other)
            : m_head{ nullptr } {
            SNode<T>* curr = other.m_head;
            while (curr != nullptr) {
                pushBack(curr->val);
                curr = curr->next;
            }
        }
        SLinkedList(SLinkedList<T>&& other) noexcept
            : m_head{ other.m_head } {
            other.m_head = nullptr;
        }
        SLinkedList<T>& operator=(const SLinkedList<T>& other) {
            if (this == &other) {
                return *this;
            }

            clear();

            SNode<T>* curr = other.m_head;
            while (curr != nullptr) {
                pushBack(curr->val);
                curr = curr->next;
            }

            return *this;
        }
        SLinkedList<T>& operator=(SLinkedList<T>&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            clear();

            m_head = other.m_head;
            other.m_head = nullptr;

            return *this;
        }
        ~SLinkedList() {
            while (m_head) {
                SNode<T>* temp = m_head;
                m_head = m_head->next;
                delete temp;
            }
        }

        void pushFront(const T& item) {
            if (!m_head) {
                m_head = new SNode<T>(item);
                return;
            }

            SNode<T>* newHead = new SNode<T>(item);
            newHead->next = m_head;
            m_head = newHead;
        }
        void pushBack(const T& item) {
            if (!m_head) {
                m_head = new SNode<T>(item);
                return;
            }

            SNode<T>* curr = m_head;
            while (curr && curr->next) {
                curr = curr->next;
            }

            // At last non null node
            curr->next = new SNode<T>(item);
        }
        void insert(size_t idx, const T& item) {
            size_t i = 0;
            SNode<T>* prev = nullptr;
            SNode<T>* curr = m_head;
            while (i < idx && curr) {
                prev = curr;
                curr = curr->next;
                ++i;
            }

            if (i == idx) {
                prev->next = new SNode<T>(item, curr);
            }
            else {
                throw std::out_of_range("Index " + std::to_string(idx) + " is larger than size of list");
            }
        }

        void popFront() {
            if (!m_head) {
                throw std::logic_error("The list is empty");
            }

            SNode<T>* next = m_head->next;
            delete m_head;
            m_head = next;
        }
        void popBack() {
            if (!m_head) {
                throw std::logic_error("The list is empty");
            }

            SNode<T>* prev = nullptr;
            SNode<T>* curr = m_head;
            while (curr->next) {
                prev = curr;
                curr = curr->next;
            }

            prev->next = curr->next;
            delete curr;
        }
        void erase(const T& val) {
            if (!m_head) {
                throw std::logic_error("The list is empty");
            }

            SNode<T>* prev = nullptr;
            SNode<T>* curr = m_head;
            while (curr && curr->val != val) {
                prev = curr;
                curr = curr->next;
            }

            if (curr) {
                prev->next = curr->next;
                delete curr;
            }
            else {
                throw std::invalid_argument("The value is not in the list");
            }
        }

        const T& front() const {
            if (!m_head) {
                throw std::logic_error("The list is empty");
            }
            return m_head->val;
        }
        const T& back() const {
            if (!m_head) {
                throw std::logic_error("The list is empty");
            }

            SNode<T>* curr = m_head;
            while (curr->next) {
                curr = curr->next;
            }

            return curr->val;
        }

        T& front() {
            if (!m_head) {
                throw std::logic_error("The list is empty");
            }
            return m_head->val;
        }
        T& back() {
            if (!m_head) {
                throw std::logic_error("The list is empty");
            }

            SNode<T>* curr = m_head;
            while (curr->next) {
                curr = curr->next;
            }

            return curr->val;
        }

        bool find(const T& item) const {
            SNode<T>* curr = m_head;
            while (curr) {
                if (curr->val == item) {
                    return true;
                }
                curr = curr->next;
            }
            return false;
        }
        bool empty() const {
            return !m_head;
        }

        void clear() {
            while (m_head) {
                SNode<T>* next = m_head->next;
                delete m_head;
                m_head = next;
            }
        }

        SNode<T>* m_head;
    };
}