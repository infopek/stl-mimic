#include <vector.h>
#include <linked_list.h>
#include <tree.h>

#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    try {
        core::BST<int> tree;
        tree.insert(50);
        tree.insert(30);
        tree.insert(20);
        tree.insert(40);
        tree.insert(70);
        tree.insert(60);
        tree.insert(80);

        tree.preorder([](const int& val) {std::cout << std::to_string(val) << " ";});
        std::cout << '\n';
        tree.inorder([](const int& val) {std::cout << std::to_string(val) << " ";});
        std::cout << '\n';
        tree.postorder([](const int& val) {std::cout << std::to_string(val) << " ";});
        std::cout << '\n';

        std::cout << tree.search(40);
        std::cout << tree.search(87);
        std::cout << tree.search(0);
        std::cout << tree.search(-1);
        std::cout << tree.search(50);
        std::cout << tree.search(80);
        std::cout << tree.search(10);
        std::cout << tree.search(20);
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }

}