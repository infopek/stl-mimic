#include <vector.h>
#include <linked_list.h>
#include <tree.h>
#include <hash_table.h>
#include <priority_queue.h>

#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    try {
        core::PQueue<int, int> pq{};
        pq.insert(2, 2);
        pq.insert(6, 6);
        pq.insert(2, 2);
        pq.insert(11, 11);
        pq.insert(8, 8);
        pq.insert(4, 4);
        pq.insert(17, 17);
        pq.insert(3, 3);
        pq.insert(10, 10);
        pq.insert(9, 9);
        pq.insert(5, 5);

        std::cout << pq.peek();
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }

}