#include <vector.h>
#include <linked_list.h>
#include <tree.h>
#include <hash_table.h>

#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    try {
        core::SLinkedList<int> list{};
        list.pushBack(6);
        list.pushBack(2);
        list.pushBack(1);
        list.pushFront(9);
        list.pushFront(0);
        list.pushBack(5);

        for (auto n : list) {
            std::cout << n << '\n';
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }

}