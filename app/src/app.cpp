#include <vector.h>
#include <stack.h>
#include <linked_list.h>
#include <tree.h>
#include <hash_table.h>
#include <priority_queue.h>
#include <graph.h>

#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <stack>


template <typename T>
void heapify(T* arr, size_t size, size_t idx) {
    size_t max = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    if (left < size && arr[idx] < arr[left]) {
        max = left;
    }
    if (right < size && arr[max] < arr[right]) {
        max = right;
    }

    if (max == idx) {
        return;
    }

    std::swap(arr[idx], arr[max]);
    heapify(arr, size, max);
}


template <typename T>
void heapSort(T* arr, size_t size) {
    // Build heap
    for (int i = size / 2; i >= 0; --i) {
        heapify(arr, size, i);
    }

    // Heapify until last node is removed
    for (int i = size - 1; i > 0; --i) {
        std::swap(arr[i], arr[0]);

        heapify(arr, i, 0);
    }
}

template <typename T>
void printArr(const T* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
}

struct HuffmanNode {
    char data{};
    size_t freq{};

    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data_, size_t freq_)
        : data{ data_ }, freq{ freq_ }, left{ nullptr }, right{ nullptr } {
    }
    HuffmanNode(char data_, size_t freq_, HuffmanNode* left_, HuffmanNode* right_)
        : data{ data_ }, freq{ freq_ }, left{ left_ }, right{ right_ } {
    }
};

struct EncodedHuffman {
    std::string encodedMessage{};
    HuffmanNode* root;
};

EncodedHuffman huffmanEncode(const std::string& str) {
    if (str.empty()) {
        return EncodedHuffman {
            .encodedMessage = "",
            .root = nullptr
        };
    }

    core::HashTable<char, size_t> freq{};
    for (const auto c : str) {
        ++freq[c];
    }

    core::PQueue<size_t, HuffmanNode*> pq{};
    for (const auto& [k, v] : freq) {
        pq.insert(v, new HuffmanNode(k, v));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.peek();
        pq.pop();

        HuffmanNode* right = pq.peek();
        pq.pop();

        size_t sum = left->freq + right->freq;
        HuffmanNode* combined = new HuffmanNode(' ', sum, left, right);
        pq.insert(sum, combined);
    }

    // Iterative preorder so that I can do this inside this method
    core::Vector<std::string> codes(256);   // ascii
    core::Stack<std::pair<HuffmanNode*, std::string>> stack{};

    HuffmanNode* root = pq.peek();
    stack.push({ root, "" });
    while (!stack.empty()) {
        auto [node, code] = stack.peek();
        stack.pop();

        if (!node->left && !node->right) {
            codes[static_cast<size_t>(node->data)] = code;
        }

        if (node->left) {
            stack.push({ node->left, code + "0" });
        }
        if (node->right) {
            stack.push({ node->right, code + "1" });
        }
    }

    // Join the codes to get final encoded msg
    size_t encodedLength = 0;
    for (const auto c : str) {
        encodedLength += codes[static_cast<size_t>(c)].length();
    }

    std::string encoded{};
    encoded.reserve(encodedLength);
    for (const auto c : str) {
        encoded += codes[static_cast<size_t>(c)] + " ";
    }

    return EncodedHuffman {
        .encodedMessage = encoded,
        .root = root
    };
}

int main() {
    try {
        std::string str = "BCCABBDDAECCBBAEDDCC";
        EncodedHuffman res = huffmanEncode(str);
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }
}