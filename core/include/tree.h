#pragma once

#include <stdexcept>
#include <functional>

namespace core {
    template <typename T>
    struct BSTNode {
        T val;
        BSTNode* left;
        BSTNode* right;

        BSTNode()
            : val(T()), left(nullptr), right(nullptr) {
        }
        BSTNode(const T& val_)
            : val{ val_ }, left(nullptr), right(nullptr) {
        }
        BSTNode(const T& val_, BSTNode* left_, BSTNode* right_)
            : val{ val_ }, left(left_), right(right_) {
        }
        BSTNode(const BSTNode&) = delete;
        BSTNode(BSTNode&&) = delete;
    };

    template <typename T>
    class BST {
    public:
        BST()
            : m_root(nullptr) {
        }
        BST(const BST&) = delete;
        BST(BST&&) = delete;
        ~BST() {
            // TODO: Use a traverse algo to delete every node
        }

        void insert(const T& val) {
            insert_(m_root, val);
        }

        // Traversals
        void preorder(std::function<void(const T&)> f) const {
            preorder_(m_root, f);
        }
        void inorder(std::function<void(const T&)> f) const {
            inorder_(m_root, f);
        }
        void postorder(std::function<void(const T&)> f) const {
            postorder_(m_root, f);
        }

        bool search(const T& val) const {
            bool found = false;
            search_(m_root, val, found);
            return found;
        }

    private:
        void insert_(BSTNode<T>*& node, const T& val) {
            if (!node) {
                node = new BSTNode<T>(val);
                return;
            }

            if (node->val == val) {
                throw std::invalid_argument("Value already exists in tree");
            }

            if (val < node->val) {
                insert_(node->left, val);
            }
            else {
                insert_(node->right, val);
            }
        }

        void preorder_(BSTNode<T>* node, std::function<void(const T&)> f) const {
            if (!node) {
                return;
            }

            f(node->val);
            preorder_(node->left, f);
            preorder_(node->right, f);
        }
        void inorder_(BSTNode<T>* node, std::function<void(const T&)> f) const {
            if (!node) {
                return;
            }

            inorder_(node->left, f);
            f(node->val);
            inorder_(node->right, f);
        }
        void postorder_(BSTNode<T>* node, std::function<void(const T&)> f) const {
            if (!node) {
                return;
            }

            postorder_(node->left, f);
            postorder_(node->right, f);
            f(node->val);
        }

        void search_(BSTNode<T>* node, const T& val, bool& found) const {
            if (!node || found) {
                return;
            }

            if (node->val == val) {
                found = true;
            }
            else if (val < node->val) {
                search_(node->left, val, found);
            }
            else {
                search_(node->right, val, found);
            }
        }

    private:
        BSTNode<T>* m_root;
    };
}