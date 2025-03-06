#include <vector.h>
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

std::string huffmanEncode(const std::string& str) {
    core::HashTable<char, int> freq{};
    for (const auto c : str) {
        ++freq[c];
    }

    for (const auto& [k, v] : freq) {
        std::cout << "kv: " << k << ' ' << v << '\n';
    }

    return "";
}

int main() {
    try {
        std::string str{ "BCCABBDDAECCBBAEDDCC" };
        std::cout << huffmanEncode(str);
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }
}