#pragma once

#include <initializer_list>
#include <stdexcept>

template <typename T>
struct SNode {
    T val{};
    SNode* next;

    SNode()
        : val(T()), next(nullptr)
    {
    }
    SNode(T val)
        : val(val), next(nullptr)
    {
    }
    SNode(T val, SNode* n)
        : val(val), next(n)
    {
    }
};

template <typename T>
class SLinkedList {
public:
    SLinkedList()
        : m_head(nullptr)
    {
    }
    SLinkedList(T val)
        : m_head(new SNode<T>(val))
    {
    }
    SLinkedList(std::initializer_list<T> list) {

    }
    ~SLinkedList() {
        SNode<T>* curr = m_head;
        SNode<T>* next = nullptr;
        while (curr) {
            next = curr->next;
            delete curr;
            curr = next;
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
        while (curr->next) {
            curr = curr->next;
        }

        // At last non null node
        curr->next = new SNode<T>(item);
    }
    void insert(size_t idx, const T& item) {
    }

    void popFront() {
    }
    void popBack() {
    }
    void erase(const T& val) {

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

    SNode<T>* m_head;
};
