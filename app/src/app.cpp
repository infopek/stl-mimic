#include <vector.h>
#include <linked_list.h>

#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    try {
        core::SLinkedList<int> list{};
        list.pushBack(4);
        list.pushBack(6);
        list.pushFront(9);
        list.pushBack(1);

    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }

}