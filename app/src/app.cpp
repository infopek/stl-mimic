#include <vector.h>
#include <linked_list.h>
#include <tree.h>
#include <hash_table.h>
#include <priority_queue.h>

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

int main() {
    try {
        core::PQueue<int, std::string> pq{
          {5, "Hali"},
          {1, "Holi"},
          {8, "Heli"},
          {9, "Hili"},
          {3, "Huli"},
          {2, "HHH"},
        };
        pq.print();
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }

}